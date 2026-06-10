#pragma once

#ifndef TEST_CORE_H
#define TEST_CORE_H

#include <string>
#include <functional>
#include <map>
#include <vector>

/// @brief An internal namespace. Using anything from within is not advised
namespace internal {
    /// @brief A core namespace containing the core data structures used by the rest of the internal namespace
    namespace Core {
        /// @brief The types of statuses a test can have after being run
        enum class TestStatus {
            Passed,
            Failed,
            Skipped,
        };

        /// @brief A simple mapping from TestStatus => string representation
        static std::string StatusStrings[] = {"Passed", "Failed", "Skipped"};

        /// @brief The types of statuses a test can have after execution
        enum class ExecutionStatus
        {
            NotRun, //filtered/skipped dependencies
            Completed, //child exited normally
            Crashed, //signal/exception
            TimedOut, //watchdog kill
            LaunchFailed, //CreateProcess/fork failure
            CommunicationFailure, //pipe/socket broke
            InternalFrameworkError, //framework bug
            SanitizerFailure, //sanitizer failure
            Cancelled //future parallel cancellation support
        };

        /// @brief A simple mapping from ExecutionStatus => string representation
        static std::string ExecutionStrings[] = 
            {
                "Not Run", "Completed", "Crashed", "Timed Out", "Launched Failed",
                "Communication Failure", "Internal Error", "Cancelled"
            };

        /// @brief Types of crashes that can happen
        enum class CrashType {
            None,
            SegmentationFault,
            AccessViolation,
            Abort,
            DivideByZero,
            IllegalInstruction,
            BusError,
            FloatingPointException,
            Trap,
            Killed,
            Unknown
        };

        /// @brief A simple mapping from CrashType => string representation
        static std::string CrashStrings[] = 
            {
                "None", "Seg Fault", "Access Violation", "Abort", "Divide By Zero",
                "Illegal Instruction", "Bus Error", "Floating Point Exception",
                "Trap", "Killed", "Unknown"
            };

        /// @brief A ProcessInfo struct
        /// Contains: process id, the native exit code, the native signal, if the core was dumped
        struct ProcessInfo
        {
            pid_t process_id = -1;
            int native_exit_code = -1;
            int native_signal = -1;
        };

        /// @brief A struct that captures output
        /// Contains: stdout-output, stderr-output, whether or not either output was truncated
        struct OutputCapture
        {
            std::string stdout_text = "";
            std::string stderr_text = "";
            bool stdout_truncated = false;
            bool stderr_truncated = false;
        };

        /// @brief A struct containing failure information
        /// Contains: message, file, line, expression, expected, actual
        struct FailureInfo
        {
            std::string message;
            std::string file;
            uint32_t line;
            std::string expression;
            std::string expected;
            std::string actual;
        };

        /// @brief Whether or not something was run in isolation
        enum class IsolationMode
        {
            None,
            Process
        };

        enum class SanitizerError {
            None,

            HeapBufferOverflow,
            StackBufferOverflow,
            UseAfterFree,
            DoubleFree,
            AllocDeallocMismatch,
            StackUseAfterReturn,

            SignedIntegerOverflow,
            InvalidShift,
            NullDereference,
            MisalignedAccess,
            DivideByZero,
            InvalidEnum,
            Unreachable,

            DataRace,

            MemoryLeak,

            Unknown
        };

        /// @brief Sanitizer information
        struct SanitizerInfo
        {
            bool asan_detected = false;
            SanitizerError asan_err = SanitizerError::None;
            std::string asan_msg = "";

            bool ubsan_detected = false;
            SanitizerError ubsan_err = SanitizerError::None;
            std::string ubsan_msg = "";

            bool tsan_detected = false;
            SanitizerError tsan_err = SanitizerError::None;
            std::string tsan_msg = "";

            bool lsan_detected = false;
            SanitizerError lsan_err = SanitizerError::None;
            std::string lsan_msg = "";
        };

        struct ExecutionResult
        {
            ExecutionStatus execution_status = ExecutionStatus::Completed;
            CrashType crash_type = CrashType::None;

            uint64_t execution_ms;
            ProcessInfo process;
            OutputCapture output;
            SanitizerInfo sanitizers;

            std::string framework_message = "";
        };

        /// @brief The final struct for a test's execution results
        struct TestResult
        {
            std::string suiteName;
            std::string testName;

            TestStatus test_status;
            uint64_t execution_ms;

            IsolationMode isolation_mode = IsolationMode::None;
            std::vector<FailureInfo> failures;
            std::vector<ExecutionResult> execution_results;
        };

        /// @brief The types of time units for timeout
        enum class TimeUnit {
            Seconds,
            Milliseconds
        };

        /// @brief A Test struct that contains information about a test
        struct Test {
            std::string suite_name;
            std::string test_name;
            std::function<void()> test;

            bool operator==(const Test& other) const {
                return suite_name == other.suite_name
                    && test_name == other.test_name;
            }
        };

        /// @brief A TestRun struct that contains information about the tests being run
        struct TestRun {
            std::map<std::string, std::vector<TestResult>> results;

            int total = 0;
            double totalMs = 0.0;
        };

        /// @brief Hashes a Test struct
        struct TestHash {
            size_t operator()(const Test& p) const {
                size_t h1 = std::hash<std::string>{}(p.suite_name);
                size_t h2 = std::hash<std::string>{}(p.test_name);
                return h1 ^ (h2 << 1);
            }
        };

        //An assertion failure struct
        struct AssertionFailure : public std::exception {
            const char* what() const noexcept override {
                return "Assertion failed";
            }
        };
    }
}

#endif