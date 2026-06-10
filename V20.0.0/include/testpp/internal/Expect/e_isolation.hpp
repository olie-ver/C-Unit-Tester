#pragma once

#ifndef E_ISO_H
#define E_ISO_H

#include "../Core.hpp"
#include "../Fail.hpp"
#include "../Helpers.hpp"
#include "../Implementation/isolation.hpp"

#include <algorithm>

//Fatal tests
#define EXPECT_DEATH(func) internal::Expects::expectDeath((func), #func, __FILE__, __LINE__)
#define EXPECT_SEGFAULT(func) internal::Expects::expectSegFault((func), #func, __FILE__, __LINE__)
#define EXPECT_ABORT(func) internal::Expects::expectAbort((func), #func, __FILE__, __LINE__)
#define EXPECT_FATAL(func) internal::Expects::expectFatal((func), #func, __FILE__, __LINE__)
#define EXPECT_NONFATAL(func) internal::Expects::expectNonFatal((func), #func, __FILE__, __LINE__)

//Exit tests
#define EXPECT_SUCCESS(func) internal::Expects::expectSuccess((func), #func, __FILE__, __LINE__)
#define EXPECT_FAILURE(func) internal::Expects::expectFailure((func), #func, __FILE__, __LINE__)
#define EXPECT_NONZERO_EXIT(func) internal::Expects::expectNonzeroExit((func), #func, __FILE__, __LINE__)
#define EXPECT_EXITCODE(func, code) internal::Expects::expectExitCode((func), #func, code, __FILE__, __LINE__)
#define EXPECT_COMPLETES(func) internal::Expects::expectCompletes((func), #func, __FILE__, __LINE__)

//Output tests
#define EXPECT_STDOUT_CONTAINS(func, content) internal::Expects::expectStdoutContains((func), (content), __FILE__, __LINE__)
#define EXPECT_STDERR_CONTAINS(func, content) internal::Expects::expectStderrContains((func), (content), __FILE__, __LINE__)
#define EXPECT_NO_STDOUT(func) internal::Expects::expectNoStdout((func), __FILE__, __LINE__)
#define EXPECT_NO_STDERR(func) internal::Expects::expectNoStderr((func), __FILE__, __LINE__)
#define EXPECT_STDOUT_MATCHES(func, content) internal::Expects::expectStdoutMatches((func), (content) __FILE__, __LINE__)
#define EXPECT_STDERR_MATCHES(func, content) internal::Expects::expectStderrMatches((func), (content) __FILE__, __LINE__)

//Sanitizer tests
#define EXPECT_ASAN_FAILURE(func) internal::Expects::expectAsanFailure((func), __FILE__, __LINE__)
#define EXPECT_NASAN_FAILURE(func) internal::Expects::expectNoAsanFailure((func), __FILE__, __LINE__)
#define EXPECT_UBSAN_FAILURE(func) internal::Expects::expectUbsanFailure((func), __FILE__, __LINE__)
#define EXPECT_NUBSAN_FAILURE(func) internal::Expects::expectNoUbsanFailure((func), __FILE__, __LINE__)
#define EXPECT_TSAN_FAILURE(func) internal::Expects::expectTsanFailure((func), __FILE__, __LINE__)
#define EXPECT_NTSAN_FAILURE(func) internal::Expects::expectNoTsanFailure((func), __FILE__, __LINE__)
#define EXPECT_LSAN_FAILURE(func) internal::Expects::expectLsanFailure((func), __FILE__, __LINE__)
#define EXPECT_NLSAN_FAILURE(func) internal::Expects::expectNoLsanFailure((func), __FILE__, __LINE__)
#define EXPECT_SAN_FAILURE(func) internal::Expects::expectSanFailure((func), __FILE__, __LINE__)
#define EXPECT_NSAN_FAILURE(func) internal::Expects::expectNoSanFailure((func), __FILE__, __LINE__)

//Timing/Concurrency tests
#define EXPECT_TIMEOUT(func, timeLimit) internal::Expects::expectTimeout((func), (timeLimit), __FILE__, __LINE__)
#define EXPECT_COMPLETES_WITHIN(func, timeLimit) \
    internal::Expects::expectCompletesWithin((func), (timeLimit), __FILE__, __LINE__)

//Generic tests

#define EXPECT_STATUS(func, status) internal::Expects::expectStatus((func), (status), __FILE__, __LINE__)
#define EXPECT_CRASH_TYPE(func, crash_type) \
    internal::Expects::expectCrashType((func), (crash_type), __FILE__, __LINE__)

#define EXPECT_SIGNAL(func, signal) \
    internal::Expects::expectTerminationSignal((func), (signal), __FILE__, __LINE__)
#define EXPECT_KILLED(func) internal::Expects::expectKilled((func), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        //Fatal Tests

        template<typename Func>
        inline void expectDeath(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            //need to store execution result
            Core::ExecutionResult execRes = impl_iso::death(func);
            if (execRes.execution_status != Core::ExecutionStatus::Completed) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to complete, but it died",
                    file,
                    line
                });
                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void expectSegFault(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::segfault(func);
            if (execRes.crash_type != Core::CrashType::SegmentationFault) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to seg fault, but it didn't",
                    file,
                    line
                });
                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void expectAbort(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::abort(func);
            if (execRes.crash_type != Core::CrashType::Abort) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to abort, but it didn't",
                    file,
                    line
                });
                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void expectFatal(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::fatal(func);
            if (execRes.execution_status == Core::ExecutionStatus::Completed 
                && execRes.crash_type == Core::CrashType::None)
            {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to fail or crash, but it didn't",
                    file,
                    line
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void expectNonFatal(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::nonFatal(func);
            if (execRes.execution_status != Core::ExecutionStatus::Completed 
                && execRes.crash_type != Core::CrashType::None)
            {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to not have a failure, "
                        "but it failed with execution status: "
                    + Core::ExecutionStrings[(int)execRes.execution_status] 
                    + " and crash type: " + Core::CrashStrings[(int)execRes.crash_type],
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        //Exit Tests

        template<typename Func>
        inline void expectSuccess(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::success(func);
            if (execRes.process.native_exit_code != EXIT_SUCCESS) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to exit with code" 
                    + Helpers::toString(EXIT_SUCCESS) + ", but it exited with code: "
                    + Helpers::toString(execRes.process.native_exit_code),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void expectFailure(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::failure(func);
            if (execRes.process.native_exit_code != EXIT_FAILURE) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to exit with code" 
                    + Helpers::toString(EXIT_FAILURE) + ", but it exited with code: "
                    + Helpers::toString(execRes.process.native_exit_code),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void expectNonzeroExit(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::nonzeroExit(func);
            if (execRes.process.native_exit_code == 0) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName 
                    + " to exit with a nonzero code, but it exited with code: 0",
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void expectExitCode(Func&& func, const char* funcName, const int code, 
            const char* file, const uint32_t line)
        {
            Core::ExecutionResult execRes = impl_iso::nonzeroExit(func);
            if (execRes.process.native_exit_code != code) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to exit with code" 
                    + Helpers::toString(code) + ", but it exited with code: "
                    + Helpers::toString(execRes.process.native_exit_code),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void expectCompletes(Func&& func, const char* funcName,
            const char* file, const uint32_t line)
        {
            Core::ExecutionResult execRes = impl_iso::completes(func);
            if (execRes.execution_status != Core::ExecutionStatus::Completed) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to complete" 
                    ", but it exited with status: "
                    + Core::ExecutionStrings[(int)execRes.execution_status],
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        //Output Tests
        template <typename Func>
        inline void expectStdoutContains(Func&& func, const std::string& content, 
            const char* file, const uint32_t line)
        {
            Core::ExecutionResult execRes = impl_iso::stdoutContains(func);
            if (execRes.output.stdout_text.find(content) == std::string::npos) {
                size_t maxSize = 1024;
                Core::FailureInfo fail({
                    std::string("Expected stdout to contain: \"") + content + "\", but it didn't.\n" 
                    "stdout: " + execRes.output.stdout_text.substr(0, std::min(maxSize, execRes.output.stdout_text.size())),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectStderrContains(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::stderrContains(func);
            if (execRes.output.stderr_text.find(content) == std::string::npos) {
                size_t maxSize = 1024;
                Core::FailureInfo fail({
                    std::string("Expected stderr to contain: \"") + content + "\", but it didn't.\n" 
                    "stderr: " + execRes.output.stderr_text.substr(0, std::min(maxSize, execRes.output.stderr_text.size())),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectNoStdout(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStdout(func);
            if (!execRes.output.stdout_text.empty()) {
                size_t maxSize = 1024;
                Core::FailureInfo fail({
                    std::string("Expected stdout to be empty, but it wasn't.\"")
                    + "stdout: " 
                    + execRes.output.stdout_text.substr(0, std::min(maxSize, execRes.output.stdout_text.size())),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectNoStderr(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStderr(func);
            if (!execRes.output.stderr_text.empty()) {
                size_t maxSize = 1024;
                Core::FailureInfo fail({
                    std::string("Expected stderr to be empty, but it wasn't.\"")
                    + "stderr: "
                    + execRes.output.stderr_text.substr(0, std::min(maxSize, execRes.output.stderr_text.size())),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

          template <typename Func>
        inline void expectStdoutMatches(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStdout(func);
            if (execRes.output.stdout_text != content) {
                size_t maxSize = 1024;
                Core::FailureInfo fail({
                    std::string("Expected stdout to match: \"") + content + "\", but it didn't.\n" 
                    "stdout: " + execRes.output.stdout_text.substr(0, std::min(maxSize, execRes.output.stdout_text.size())),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectStderrMatches(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStderr(func);
            if (execRes.output.stderr_text != content) {
                size_t maxSize = 1024;
                Core::FailureInfo fail({
                    std::string("Expected stderr to match: \"") + content + "\", but it didn't.\n" 
                    "stderr: " + execRes.output.stderr_text.substr(0, std::min(maxSize, execRes.output.stderr_text.size())),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectAsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::asanFailure(func);
            if (!execRes.sanitizers.asan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected Address Sanitizer to fail, but it didn't"),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectNoAsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::asanFailure(func);
            if (execRes.sanitizers.asan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected no Address Sanitizer failure, but there was:\n")
                    + "Asan failure: " + execRes.sanitizers.asan_msg,
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectUbsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::ubsanFailure(func);
            if (!execRes.sanitizers.ubsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected Undefined-Behavior Sanitizer to fail, but it didn't"),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectNoUbsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::ubsanFailure(func);
            if (execRes.sanitizers.asan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected no Undefined-Behavior Sanitizer failure, but there was:\n")
                    + "Ubsan failure: " + execRes.sanitizers.ubsan_msg,
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectTsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::tsanFailure(func);
            if (!execRes.sanitizers.tsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected Thread Sanitizer to fail, but it didn't"),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectNoTsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::tsanFailure(func);
            if (execRes.sanitizers.tsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected no Thread Sanitizer failure, but there was:\n")
                    + "Tsan failure: " + execRes.sanitizers.asan_msg,
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectLsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::lsanFailure(func);
            if (!execRes.sanitizers.lsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected Leak Sanitizer to fail, but it didn't"),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectNoLsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::lsanFailure(func);
            if (execRes.sanitizers.lsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected no Leak Sanitizer failure, but there was:\n")
                    + "Lsan failure: " + execRes.sanitizers.asan_msg,
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectSanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::sanFailure(func);
            if (!execRes.sanitizers.asan_detected && !execRes.sanitizers.ubsan_detected
                && !execRes.sanitizers.tsan_detected && !execRes.sanitizers.lsan_detected) 
            {
                Core::FailureInfo fail({
                    std::string("Expected a sanitizer to fail, but none did"),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectNoSanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::sanFailure(func);
            if (execRes.sanitizers.asan_detected || execRes.sanitizers.ubsan_detected
                || execRes.sanitizers.tsan_detected || execRes.sanitizers.lsan_detected) 
            {
                Core::FailureInfo fail({
                    std::string("Expected no sanitizer failure, but there was"),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        //Timing Tests
        template <typename Func>
        inline void expectTimeout(Func&& func, const int timeLimitMs, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::timeout(func, timeLimitMs);
            if (execRes.execution_status != Core::ExecutionStatus::TimedOut) 
            {
                Core::FailureInfo fail({
                    std::string("Expected func to last longer than ")
                    + Helpers::toString(timeLimitMs) + "ms, but it didn't",
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectCompletesWithin(Func&& func, const int timeLimitMs, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::completesWithin(func, timeLimitMs);
            if (execRes.execution_status == Core::ExecutionStatus::TimedOut) 
            {
                Core::FailureInfo fail({
                    std::string("Expected func to complete within ")
                    + Helpers::toString(timeLimitMs) + "ms, but it didn't",
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        //Generic Tests
        template <typename Func>
        inline void expectStatus(Func&& func, const Core::ExecutionStatus status, 
            const char* file, const uint32_t line)
        {
            Core::ExecutionResult execRes = impl_iso::executionStatus(func);
            if (execRes.execution_status != status) 
            {
                Core::FailureInfo fail({
                    std::string("Expected func to have execution status: ")
                    + Core::ExecutionStrings[(int)status]
                    + "\n but it had execution status: " + Core::ExecutionStrings[(int)execRes.execution_status],
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectCrashType(Func&& func, const Core::CrashType type, 
            const char* file, const uint32_t line)
        {
            Core::ExecutionResult execRes = impl_iso::executionStatus(func);
            if (execRes.crash_type != type) 
            {
                Core::FailureInfo fail({
                    std::string("Expected func to have crash type: ")
                    + Core::ExecutionStrings[(int)type]
                    + "\n but it had crash type: " + Core::ExecutionStrings[(int)execRes.crash_type],
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectTerminationSignal(Func&& func, const int signal, 
            const char* file, const uint32_t line)
        {
            Core::ExecutionResult execRes = impl_iso::executionStatus(func);
            if (execRes.process.native_signal != signal) 
            {
                Core::FailureInfo fail({
                    std::string("Expected func to have native signal: ")
                    + Helpers::toString(signal)
                    + "\n but it had native signal: " 
                    + Helpers::toString(execRes.process.native_signal),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void expectKilled(Func&& func, const int signal, 
            const char* file, const uint32_t line)
        {
            Core::ExecutionResult execRes = impl_iso::executionStatus(func);
            if (execRes.crash_type != Core::CrashType::Killed) 
            {
                Core::FailureInfo fail({
                    std::string("Expected func be killed, but it wasn't"),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }
    }
}

#endif