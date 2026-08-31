#include <testpp/internal/Implementation/isolation.hpp>
#include <testpp/internal/Implementation/isolation_types.hpp>
#include "isolation_unix.hpp"

#include <array>
#include <fcntl.h>

namespace internal {
    namespace impl_iso {
        bool drainPipe(int pipefd, std::string& target, std::array<char, 1024>& buffer);

        Core::ExecutionResult runIsolatedImpl(const std::function<void()>& func, const int timeLimit) {
            using ms = std::chrono::milliseconds;

            int timeStep = timeLimit / 10;

            Core::ExecutionResult run;

            // pipe[0] = read end
            // pipe[1] = write end
            int stdoutPipe[2];
            int stderrPipe[2];

            bool pipeError = false;

            if (pipe(stdoutPipe) == -1) {
                perror("pipe");
                run.execution_status = Core::ExecutionStatus::CommunicationFailure;
                run.crash_type = Core::CrashType::Unknown;
                run.framework_message = "stdout pipe failed";
                return run;
            } else if (pipe(stderrPipe) == -1) {
                perror("pipe");
                run.execution_status = Core::ExecutionStatus::CommunicationFailure;
                run.crash_type = Core::CrashType::Unknown;
                run.framework_message = "stderr pipe failed";
                return run;
            }

            pid_t child_pid = fork();

            if (child_pid == -1) {
                //fork failed
                run.execution_status = Core::ExecutionStatus::LaunchFailed;
                run.process.process_id = child_pid;
                run.process.native_exit_code = -1;
                run.crash_type = Core::CrashType::None;
                run.framework_message = "Fork failed";
            } else if (child_pid > 0) {
                //parent   

                close(stdoutPipe[1]);
                close(stderrPipe[1]);
                fcntl(stdoutPipe[0], F_SETFL, O_NONBLOCK);
                fcntl(stderrPipe[0], F_SETFL, O_NONBLOCK);

                std::array<char, 1024> stdoutBuffer{};
                std::array<char, 1024> stderrBuffer{};

                auto start = std::chrono::steady_clock::now();
                int child_status = 0;
                bool timed_out = false;
                pid_t result; 
                std::chrono::steady_clock::time_point now;
                int elapsed = 0;

                while (true) {
                    //read over and over
                    pipeError |= drainPipe(stdoutPipe[0], run.output.stdout_text, stdoutBuffer);
                    pipeError |= drainPipe(stderrPipe[0], run.output.stderr_text, stderrBuffer);

                    while (true)
                    {
                        result = waitpid(child_pid, &child_status, WNOHANG);
                        if (result == -1)
                        {
                            if (errno == EINTR)
                            {
                                continue;
                            } else if (errno == ECHILD) {
                                run.execution_status = Core::ExecutionStatus::InternalFrameworkError;
                                run.crash_type = Core::CrashType::Unknown;
                                auto end = std::chrono::steady_clock::now();
                                run.execution_ms = std::chrono::duration_cast<ms>(end - start).count();
                                run.framework_message = "Error with waiting on child process";
                                return run;
                            }
                        }
                        break;
                    }

                    if (result == child_pid) {
                        //read until no more output after child terminates
                        pipeError |= drainPipe(stdoutPipe[0], run.output.stdout_text, stdoutBuffer);
                        pipeError |= drainPipe(stderrPipe[0], run.output.stderr_text, stderrBuffer);

                        run.process.process_id = result;
                        break;
                    }
                    now = std::chrono::steady_clock::now();
                    elapsed = std::chrono::duration_cast<ms>(now - start).count();

                    if (elapsed > timeLimit) { 
                        if (kill(child_pid, SIGKILL) == -1)
                        {
                            if (errno != ESRCH)
                            {
                                run.execution_status = Core::ExecutionStatus::InternalFrameworkError;
                                run.crash_type = Core::CrashType::Unknown;
                                run.framework_message = "Failed to terminate child process";
                                run.execution_ms = elapsed;
                                return run;
                            }
                        }

                        //read after timeout
                        pipeError |= drainPipe(stdoutPipe[0], run.output.stdout_text, stdoutBuffer);
                        pipeError |= drainPipe(stderrPipe[0], run.output.stderr_text, stderrBuffer);

                        while (true)
                        {
                            result = waitpid(child_pid, &child_status, 0);
                            if (result == -1)
                            {
                                if (errno == EINTR)
                                {
                                    continue;
                                } else if (errno == ECHILD) {
                                    run.execution_status = Core::ExecutionStatus::InternalFrameworkError;
                                    run.crash_type = Core::CrashType::Unknown;
                                    run.execution_ms = elapsed;
                                    run.framework_message = "Error with waiting on child process";
                                    return run;
                                }
                            }
                            break;
                        }

                        run.execution_status = Core::ExecutionStatus::TimedOut;
                        run.process.process_id = child_pid;
                        timed_out = true;

                        break;
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(timeStep));
                }

                //close pipes once AFTER loop terminates instead of inside
                close(stdoutPipe[0]);
                close(stderrPipe[0]);

                if (WIFEXITED(child_status)) {
                    int exit_status = WEXITSTATUS(child_status);
                    run.execution_status = Core::ExecutionStatus::Completed;
                    run.process.native_exit_code = exit_status;

                    if (exit_status == EXIT_SUCCESS) {

                    } else {

                    }
                } else if (WIFSIGNALED(child_status)) {
                    int signal_status = WTERMSIG(child_status);
                    if (timed_out) {
                        run.execution_status = Core::ExecutionStatus::TimedOut;
                    } else {
                        run.execution_status = Core::ExecutionStatus::Crashed;
                    }

                    run.process.native_signal = signal_status;

                    if (run.output.stderr_text.find("AddressSanitizer") != std::string::npos) {
                        run.sanitizers.asan_detected = true;
                        run.execution_status = Core::ExecutionStatus::SanitizerFailure;

                        size_t pos = run.output.stderr_text.find("ERROR:");
                        if (pos != std::string::npos)
                        {
                            size_t end = run.output.stderr_text.find('\n', pos);

                            run.sanitizers.asan_msg = run.output.stderr_text.substr(pos, end - pos);
                        }

                        if (run.output.stderr_text.find("heap-buffer-overflow") != std::string::npos) {
                            run.sanitizers.asan_err = Core::SanitizerError::HeapBufferOverflow;
                        } else if (run.output.stderr_text.find("stack-buffer-overflow") != std::string::npos) {
                            run.sanitizers.asan_err = Core::SanitizerError::StackBufferOverflow;
                        } else if (run.output.stderr_text.find("use-after-free") != std::string::npos) {
                            run.sanitizers.asan_err = Core::SanitizerError::UseAfterFree;
                        } else if (run.output.stderr_text.find("double-free") != std::string::npos) {
                            run.sanitizers.asan_err = Core::SanitizerError::DoubleFree;
                        } else if (run.output.stderr_text.find("alloc-dealloc-mismatch") != std::string::npos) {
                            run.sanitizers.asan_err = Core::SanitizerError::AllocDeallocMismatch;
                        } else if (run.output.stderr_text.find("stack-use-after-return") != std::string::npos) {
                            run.sanitizers.asan_err = Core::SanitizerError::StackUseAfterReturn;
                        }
                    }

                    if (run.output.stderr_text.find("UndefinedBehaviorSanitizer") != std::string::npos
                        || run.output.stderr_text.find("runtime error:") != std::string::npos)
                    {
                        run.sanitizers.ubsan_detected = true;
                        run.execution_status = Core::ExecutionStatus::SanitizerFailure;

                        size_t pos = run.output.stderr_text.find("ERROR:");
                        if (pos != std::string::npos)
                        {
                            size_t end = run.output.stderr_text.find('\n', pos);

                            run.sanitizers.ubsan_msg = run.output.stderr_text.substr(pos, end - pos);
                        }

                        if (run.output.stderr_text.find("signed integer overflow") != std::string::npos) {
                            run.sanitizers.ubsan_err = Core::SanitizerError::SignedIntegerOverflow;
                        } else if (run.output.stderr_text.find("invalid shift") != std::string::npos) {
                            run.sanitizers.ubsan_err = Core::SanitizerError::InvalidShift;
                        } else if (run.output.stderr_text.find("null dereference") != std::string::npos) {
                            run.sanitizers.ubsan_err = Core::SanitizerError::NullDereference;
                        } else if (run.output.stderr_text.find("misaligned pointer") != std::string::npos) {
                            run.sanitizers.ubsan_err = Core::SanitizerError::MisalignedAccess;
                        } else if (run.output.stderr_text.find("division by zero") != std::string::npos) {
                            run.sanitizers.ubsan_err = Core::SanitizerError::DivideByZero;
                        } else if (run.output.stderr_text.find("invalid enum") != std::string::npos) {
                            run.sanitizers.ubsan_err = Core::SanitizerError::InvalidEnum;
                        } else if (run.output.stderr_text.find("unreachable") != std::string::npos) {
                            run.sanitizers.ubsan_err = Core::SanitizerError::Unreachable;
                        }
                    }

                    if (run.output.stderr_text.find("ThreadSanitizer") != std::string::npos) {
                        run.sanitizers.tsan_detected = true;
                        run.execution_status = Core::ExecutionStatus::SanitizerFailure;

                        size_t pos = run.output.stderr_text.find("ERROR:");
                        if (pos != std::string::npos)
                        {
                            size_t end = run.output.stderr_text.find('\n', pos);

                            run.sanitizers.tsan_msg = run.output.stderr_text.substr(pos, end - pos);
                        }

                        if (run.output.stderr_text.find("data race") != std::string::npos) {
                            run.sanitizers.tsan_err = Core::SanitizerError::DataRace;
                        }
                    }

                    if (run.output.stderr_text.find("LeakSanitizer") != std::string::npos) {
                        run.sanitizers.lsan_detected = true;
                        run.execution_status = Core::ExecutionStatus::SanitizerFailure;

                        size_t pos = run.output.stderr_text.find("ERROR:");
                        if (pos != std::string::npos)
                        {
                            size_t end = run.output.stderr_text.find('\n', pos);

                            run.sanitizers.lsan_msg = run.output.stderr_text.substr(pos, end - pos);
                        }

                        if (run.output.stderr_text.find("memory leak") != std::string::npos) {
                            run.sanitizers.lsan_err = Core::SanitizerError::MemoryLeak;
                        }
                    }

                    if (signal_status == SIGSEGV) {
                        run.crash_type = Core::CrashType::SegmentationFault;
                    } else if (signal_status == SIGABRT) {
                        run.crash_type = Core::CrashType::Abort;
                    } else if (signal_status == SIGFPE) {
                        run.crash_type = Core::CrashType::DivideByZero;
                    } else if (signal_status == SIGILL) {
                        run.crash_type = Core::CrashType::IllegalInstruction;
                    } else if (signal_status == SIGBUS) {
                        run.crash_type = Core::CrashType::BusError;
                    } else if (signal_status == SIGKILL) {
                        run.crash_type = Core::CrashType::Killed;
                    } else if (signal_status == SIGTRAP) {
                        run.crash_type = Core::CrashType::Trap;
                    } else {
                        run.crash_type = Core::CrashType::Unknown;
                    }

                } else if (WIFSTOPPED(child_status)) {
                    // int stop_signal = WSTOPSIG(child_status);
                }

                if (result == -1) {
                    run.execution_status = Core::ExecutionStatus::InternalFrameworkError;
                }
                run.execution_ms = elapsed;
                //not sure how to use WIFCONTINUED(child_status);

            } else {
                //child
                close(stdoutPipe[0]);
                close(stderrPipe[0]);

                if (dup2(stdoutPipe[1], STDOUT_FILENO) == -1) {
                    std::cout.flush();
                    std::cerr.flush();
                    _exit(EXIT_FAILURE);
                }

                if (dup2(stderrPipe[1], STDERR_FILENO) == -1) {
                    std::cout.flush();
                    std::cerr.flush();
                    _exit(EXIT_FAILURE);
                }

                close(stdoutPipe[1]);
                close(stderrPipe[1]);

                try {
                    func();

                    //flush all buffers
                    fflush(nullptr);

                    //flush cout and cerr just in case
                    std::cout.flush();
                    std::cerr.flush();

                    _exit(EXIT_SUCCESS);
                } catch (...) {
                    //flush all buffers
                    fflush(nullptr);

                    //flush cout and cerr just in case
                    std::cout.flush();
                    std::cerr.flush();

                    _exit(EXIT_FAILURE);
                }
            }

            if (pipeError) {
                run.execution_status = Core::ExecutionStatus::CommunicationFailure;
                run.crash_type = Core::CrashType::Unknown;
                run.framework_message = "Failed to read from pipes";
            }

            return run;
        }

        //Returns true if there was an error reading from the pipe, false otherwise
        bool drainPipe(int pipefd, std::string& target, std::array<char, 1024>& buffer) {
            ssize_t count = 0;
            while (true) {
                count = read(pipefd, buffer.data(), buffer.size());

                if (count > 0) { target.append(buffer.data(), count); }
                else if (count == 0) {
                    // pipe closed
                    break;
                }
                else
                {
                    if (errno == EINTR) { continue; }
                    else if (errno == EAGAIN || errno == EWOULDBLOCK) { break; }
                    else { return true; }
                }
            }

            return false;
        }
    }
}
