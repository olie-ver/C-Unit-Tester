#pragma once

#ifndef A_ISO_H
#define A_ISO_H

#include "../Core.hpp"
#include "../Fail.hpp"
#include "../Helpers.hpp"
#include "../Implementation/isolation.hpp"

#include <algorithm>

//Fatal tests
#define ASSERT_DEATH(func) internal::Assert::assertDeath((func), #func, __FILE__, __LINE__)
#define ASSERT_SEGFAULT(func) internal::Assert::assertSegFault((func), #func, __FILE__, __LINE__)
#define ASSERT_ABORT(func) internal::Assert::assertAbort((func), #func, __FILE__, __LINE__)
#define ASSERT_FATAL(func) internal::Assert::assertFatal((func), #func, __FILE__, __LINE__)
#define ASSERT_NONFATAL(func) internal::Assert::assertNonFatal((func), #func, __FILE__, __LINE__)

//Exit tests
#define ASSERT_SUCCESS(func) internal::Assert::assertSuccess((func), #func, __FILE__, __LINE__)
#define ASSERT_FAILURE(func) internal::Assert::assertFailure((func), #func, __FILE__, __LINE__)
#define ASSERT_NONZERO_EXIT(func) internal::Assert::assertNonzeroExit((func), #func, __FILE__, __LINE__)
#define ASSERT_EXITCODE(func, code) internal::Assert::assertExitCode((func), #func, code, __FILE__, __LINE__)
#define ASSERT_COMPLETES(func) internal::Assert::assertCompletes((func), #func, __FILE__, __LINE__)

//Output tests
#define ASSERT_STDOUT_CONTAINS(func, content) internal::Assert::assertStdoutContains((func), (content), __FILE__, __LINE__)
#define ASSERT_STDERR_CONTAINS(func, content) internal::Assert::assertStderrContains((func), (content), __FILE__, __LINE__)
#define ASSERT_NO_STDOUT(func) internal::Assert::assertNoStdout((func), __FILE__, __LINE__)
#define ASSERT_NO_STDERR(func) internal::Assert::assertNoStderr((func), __FILE__, __LINE__)
#define ASSERT_STDOUT_MATCHES(func, content) internal::Assert::assertStdoutMatches((func), (content) __FILE__, __LINE__)
#define ASSERT_STDERR_MATCHES(func, content) internal::Assert::assertStderrMatches((func), (content) __FILE__, __LINE__)

//Sanitizer tests
#define ASSERT_ASAN_FAILURE(func) internal::Assert::assertAsanFailure((func), __FILE__, __LINE__)
#define ASSERT_NASAN_FAILURE(func) internal::Assert::assertNoAsanFailure((func), __FILE__, __LINE__)
#define ASSERT_UBSAN_FAILURE(func) internal::Assert::assertUbsanFailure((func), __FILE__, __LINE__)
#define ASSERT_NUBSAN_FAILURE(func) internal::Assert::assertNoUbsanFailure((func), __FILE__, __LINE__)
#define ASSERT_TSAN_FAILURE(func) internal::Assert::assertTsanFailure((func), __FILE__, __LINE__)
#define ASSERT_NTSAN_FAILURE(func) internal::Assert::assertNoTsanFailure((func), __FILE__, __LINE__)
#define ASSERT_LSAN_FAILURE(func) internal::Assert::assertLsanFailure((func), __FILE__, __LINE__)
#define ASSERT_NLSAN_FAILURE(func) internal::Assert::assertNoLsanFailure((func), __FILE__, __LINE__)
#define ASSERT_SAN_FAILURE(func) internal::Assert::assertSanFailure((func), __FILE__, __LINE__)
#define ASSERT_NSAN_FAILURE(func) internal::Assert::assertNoSanFailure((func), __FILE__, __LINE__)

//Timing/Concurrency tests
#define ASSERT_TIMEOUT(func, timeLimit) internal::Assert::assertTimeout((func), (timeLimit), __FILE__, __LINE__)
#define ASSERT_COMPLETES_WITHIN(func, timeLimit) \
    internal::Assert::assertCompletesWithin((func), (timeLimit), __FILE__, __LINE__)

//Generic tests

#define ASSERT_STATUS(func, status) internal::Assert::assertStatus((func), (status), __FILE__, __LINE__)
#define ASSERT_CRASH_TYPE(func, crash_type) \
    internal::Assert::assertCrashType((func), (crash_type), __FILE__, __LINE__)

#define ASSERT_SIGNAL(func, signal) \
    internal::Assert::assertTerminationSignal((func), (signal), __FILE__, __LINE__)
#define ASSERT_KILLED(func) internal::Assert::assertKilled((func), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        //Fatal Tests

        template<typename Func>
        inline void assertDeath(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            //need to store execution result
            Core::ExecutionResult execRes = impl_iso::death(func);
            if (execRes.execution_status != Core::ExecutionStatus::Completed) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to complete, but it died",
                    file,
                    line
                });
                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void assertSegFault(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::segfault(func);
            if (execRes.crash_type != Core::CrashType::SegmentationFault) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to seg fault, but it didn't",
                    file,
                    line
                });
                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void assertAbort(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::abort(func);
            if (execRes.crash_type != Core::CrashType::Abort) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to abort, but it didn't",
                    file,
                    line
                });
                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void assertFatal(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::fatal(func);
            if (execRes.execution_status == Core::ExecutionStatus::Completed 
                && execRes.crash_type == Core::CrashType::None)
            {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to fail or crash, but it didn't",
                    file,
                    line
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void assertNonFatal(Func&& func, const char* funcName, const char* file, const uint32_t line) {
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        //Exit Tests

        template<typename Func>
        inline void assertSuccess(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::success(func);
            if (execRes.process.native_exit_code != EXIT_SUCCESS) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to exit with code" 
                    + Helpers::toString(EXIT_SUCCESS) + ", but it exited with code: "
                    + Helpers::toString(execRes.process.native_exit_code),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void assertFailure(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::failure(func);
            if (execRes.process.native_exit_code != EXIT_FAILURE) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName + " to exit with code" 
                    + Helpers::toString(EXIT_FAILURE) + ", but it exited with code: "
                    + Helpers::toString(execRes.process.native_exit_code),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void assertNonzeroExit(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::nonzeroExit(func);
            if (execRes.process.native_exit_code == 0) {
                Core::FailureInfo fail({
                    std::string("Expected function: ") + funcName 
                    + " to exit with a nonzero code, but it exited with code: 0",
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void assertExitCode(Func&& func, const char* funcName, const int code, 
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template<typename Func>
        inline void assertCompletes(Func&& func, const char* funcName,
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        //Output Tests
        template <typename Func>
        inline void assertStdoutContains(Func&& func, const std::string& content, 
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertStderrContains(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::stderrContains(func);
            if (execRes.output.stderr_text.find(content) == std::string::npos) {
                size_t maxSize = 1024;
                Core::FailureInfo fail({
                    std::string("Expected stderr to contain: \"") + content + "\", but it didn't.\n" 
                    "stderr: " + execRes.output.stderr_text.substr(0, std::min(maxSize, execRes.output.stderr_text.size())),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertNoStdout(Func&& func, const char* file, const uint32_t line) {
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertNoStderr(Func&& func, const char* file, const uint32_t line) {
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

          template <typename Func>
        inline void assertStdoutMatches(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStdout(func);
            if (execRes.output.stdout_text != content) {
                size_t maxSize = 1024;
                Core::FailureInfo fail({
                    std::string("Expected stdout to match: \"") + content + "\", but it didn't.\n" 
                    "stdout: " + execRes.output.stdout_text.substr(0, std::min(maxSize, execRes.output.stdout_text.size())),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertStderrMatches(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStderr(func);
            if (execRes.output.stderr_text != content) {
                size_t maxSize = 1024;
                Core::FailureInfo fail({
                    std::string("Expected stderr to match: \"") + content + "\", but it didn't.\n" 
                    "stderr: " + execRes.output.stderr_text.substr(0, std::min(maxSize, execRes.output.stderr_text.size())),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertAsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::asanFailure(func);
            if (!execRes.sanitizers.asan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected Address Sanitizer to fail, but it didn't"),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertNoAsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::asanFailure(func);
            if (execRes.sanitizers.asan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected no Address Sanitizer failure, but there was:\n")
                    + "Asan failure: " + execRes.sanitizers.asan_msg,
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertUbsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::ubsanFailure(func);
            if (!execRes.sanitizers.ubsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected Undefined-Behavior Sanitizer to fail, but it didn't"),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertNoUbsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::ubsanFailure(func);
            if (execRes.sanitizers.asan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected no Undefined-Behavior Sanitizer failure, but there was:\n")
                    + "Ubsan failure: " + execRes.sanitizers.ubsan_msg,
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertTsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::tsanFailure(func);
            if (!execRes.sanitizers.tsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected Thread Sanitizer to fail, but it didn't"),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertNoTsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::tsanFailure(func);
            if (execRes.sanitizers.tsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected no Thread Sanitizer failure, but there was:\n")
                    + "Tsan failure: " + execRes.sanitizers.asan_msg,
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertLsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::lsanFailure(func);
            if (!execRes.sanitizers.lsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected Leak Sanitizer to fail, but it didn't"),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertNoLsanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::lsanFailure(func);
            if (execRes.sanitizers.lsan_detected) {
                Core::FailureInfo fail({
                    std::string("Expected no Leak Sanitizer failure, but there was:\n")
                    + "Lsan failure: " + execRes.sanitizers.asan_msg,
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertSanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::sanFailure(func);
            if (!execRes.sanitizers.asan_detected && !execRes.sanitizers.ubsan_detected
                && !execRes.sanitizers.tsan_detected && !execRes.sanitizers.lsan_detected) 
            {
                Core::FailureInfo fail({
                    std::string("Expected a sanitizer to fail, but none did"),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertNoSanFailure(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::sanFailure(func);
            if (execRes.sanitizers.asan_detected || execRes.sanitizers.ubsan_detected
                || execRes.sanitizers.tsan_detected || execRes.sanitizers.lsan_detected) 
            {
                Core::FailureInfo fail({
                    std::string("Expected no sanitizer failure, but there was"),
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        //Timing Tests
        template <typename Func>
        inline void assertTimeout(Func&& func, const int timeLimitMs, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::timeout(func, timeLimitMs);
            if (execRes.execution_status != Core::ExecutionStatus::TimedOut) 
            {
                Core::FailureInfo fail({
                    std::string("Expected func to last longer than ")
                    + Helpers::toString(timeLimitMs) + "ms, but it didn't",
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertCompletesWithin(Func&& func, const int timeLimitMs, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::completesWithin(func, timeLimitMs);
            if (execRes.execution_status == Core::ExecutionStatus::TimedOut) 
            {
                Core::FailureInfo fail({
                    std::string("Expected func to complete within ")
                    + Helpers::toString(timeLimitMs) + "ms, but it didn't",
                    file,
                    line 
                });

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        //Generic Tests
        template <typename Func>
        inline void assertStatus(Func&& func, const Core::ExecutionStatus status, 
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertCrashType(Func&& func, const Core::CrashType type, 
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertTerminationSignal(Func&& func, const int signal, 
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }

        template <typename Func>
        inline void assertKilled(Func&& func, const int signal, 
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

                Fail::a_fail(fail);
            }
            Runner::TEST_STACK.back().execution_results.push_back(execRes);
        }
    }
}

#endif