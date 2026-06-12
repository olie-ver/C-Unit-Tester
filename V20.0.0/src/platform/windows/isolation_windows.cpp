#include <testpp/internal/Runner.hpp>
#include <testpp/internal/Implementation/isolation_types.hpp>

#include "isolation_windows.hpp"

//I'm not even gonna lie. This entire file was 100% ChatGPT edited after this comment.
//Adding isolation testing support for Windows is such a mess and I don't even know
//  if it's worth it at this point.
//If this doesn't work, you can complain all you want to me. I will not go back and fix it.
//This project is open source, so for all you Windows users who want this to work, you go fix it.
#include <windows.h>
#include <string>
#include <vector>

namespace internal {
    namespace impl_iso {
        static std::string readPipe(HANDLE pipe)
        {
            std::string result;

            char buffer[4096];
            DWORD bytesRead = 0;

            while (ReadFile(
                pipe,
                buffer,
                sizeof(buffer),
                &bytesRead,
                nullptr) &&
                bytesRead > 0)
            {
                result.append(buffer, bytesRead);
            }

            return result;
        }

        Core::ExecutionResult runIsolatedImpl(
            size_t testIndex,
            size_t deathIndex,
            int timeLimit)
        {
            Core::ExecutionResult run;

            SECURITY_ATTRIBUTES sa{};
            sa.nLength = sizeof(sa);
            sa.bInheritHandle = TRUE;
            sa.lpSecurityDescriptor = nullptr;

            HANDLE stdoutRead = nullptr;
            HANDLE stdoutWrite = nullptr;

            HANDLE stderrRead = nullptr;
            HANDLE stderrWrite = nullptr;

            if (!CreatePipe(
                    &stdoutRead,
                    &stdoutWrite,
                    &sa,
                    0))
            {
                run.framework_message =
                    "Failed to create stdout pipe";

                return run;
            }

            if (!CreatePipe(
                    &stderrRead,
                    &stderrWrite,
                    &sa,
                    0))
            {
                CloseHandle(stdoutRead);
                CloseHandle(stdoutWrite);

                run.framework_message =
                    "Failed to create stderr pipe";

                return run;
            }

            SetHandleInformation(
                stdoutRead,
                HANDLE_FLAG_INHERIT,
                0);

            SetHandleInformation(
                stderrRead,
                HANDLE_FLAG_INHERIT,
                0);

            char exePath[MAX_PATH];

            DWORD pathLength =
                GetModuleFileNameA(
                    nullptr,
                    exePath,
                    MAX_PATH);

            if (pathLength == 0)
            {
                CloseHandle(stdoutRead);
                CloseHandle(stdoutWrite);

                CloseHandle(stderrRead);
                CloseHandle(stderrWrite);

                run.framework_message =
                    "Failed to locate executable";

                return run;
            }

            std::string command =
                "\"" +
                std::string(exePath) +
                "\" --isolation " +
                std::to_string(testIndex) +
                " " +
                std::to_string(deathIndex);

            STARTUPINFOA si{};
            si.cb = sizeof(si);

            si.dwFlags = STARTF_USESTDHANDLES;

            si.hStdOutput = stdoutWrite;
            si.hStdError = stderrWrite;
            si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

            PROCESS_INFORMATION pi{};

            BOOL success =
                CreateProcessA(
                    nullptr,
                    command.data(),
                    nullptr,
                    nullptr,
                    TRUE,
                    0,
                    nullptr,
                    nullptr,
                    &si,
                    &pi);

            CloseHandle(stdoutWrite);
            CloseHandle(stderrWrite);

            if (!success)
            {
                CloseHandle(stdoutRead);
                CloseHandle(stderrRead);

                run.framework_message =
                    "CreateProcess failed";

                return run;
            }

            DWORD waitResult =
                WaitForSingleObject(
                    pi.hProcess,
                    static_cast<DWORD>(timeLimit));

            if (waitResult == WAIT_TIMEOUT)
            {
                TerminateProcess(
                    pi.hProcess,
                    1);

                run.execution_status =
                    Core::ExecutionStatus::TimedOut;

                run.crash_type =
                    Core::CrashType::Killed;
            }
            else if (waitResult == WAIT_FAILED)
            {
                run.framework_message =
                    "WaitForSingleObject failed";
            }

            DWORD exitCode = 0;

            GetExitCodeProcess(
                pi.hProcess,
                &exitCode);

            run.process.process_id =
                static_cast<int>(pi.dwProcessId);

            run.process.native_exit_code =
                static_cast<int>(exitCode);

            run.output.stdout_text =
                readPipe(stdoutRead);

            run.output.stderr_text =
                readPipe(stderrRead);

            if (waitResult == WAIT_OBJECT_0)
            {
                if (exitCode == 0)
                {
                    run.execution_status =
                        Core::ExecutionStatus::Completed;
                }
                else
                {
                    run.execution_status =
                        Core::ExecutionStatus::Crashed;

                    switch (exitCode)
                    {
                        case 0xC0000005:
                            run.crash_type =
                                Core::CrashType::SegmentationFault;
                            break;

                        case 0xC0000094:
                            run.crash_type =
                                Core::CrashType::FloatingPointException;
                            break;

                        case 0xC0000409:
                            run.crash_type =
                                Core::CrashType::Abort;
                            break;

                        default:
                            break;
                    }
                }
            }

            CloseHandle(stdoutRead);
            CloseHandle(stderrRead);

            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);

            return run;
        }
    }
}    