#include <testpp/internal/PCH/pch.hpp>

#include <testpp/internal/Renderer.hpp>
#include <iostream>

namespace internal {
    namespace Renderer {
        void renderExecutionResult(const Core::ExecutionResult& res, const int stdoutSize, const int stderrSize);

        void ConsoleRenderer::renderDefault(Core::TestRun& testRun) {
            auto& tests = testRun.results;

            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];

                    switch (result.test_status) {
                        case Core::TestStatus::Passed:
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_ms << " ms" << ')' << std::endl;

                            if (!result.execution_results.empty()) {
                                for (size_t j = 0; j < result.execution_results.size(); j++) {
                                    renderExecutionResult(result.execution_results[j], stdoutSize, stderrSize);
                                }
                            }

                            passed++;
                            break;
                    
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_ms << " ms" << ')' << std::endl;

                            for (size_t j = 0; j < result.failures.size(); j++) {
                                const Core::FailureInfo& fail = result.failures[j];
                                std::cout << "\tat: " << fail.file << ":" << fail.line << std::endl;
                                std::cout << '\t' << fail.message << std::endl;
                                std::cout << std::endl;
                            }

                            if (!result.execution_results.empty()) {
                                for (size_t j = 0; j < result.execution_results.size(); j++) {
                                    renderExecutionResult(result.execution_results[j], stdoutSize, stderrSize);
                                }
                            }

                            failed++;
                            break;

                        case Core::TestStatus::Skipped:
                            std::cout << "[SKIP] " << result.suiteName << " -> " 
                                << result.testName << std::endl;
                            skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderMinimum(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];

                    switch (result.test_status) {
                        case Core::TestStatus::Passed:
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_ms << " ms" << ')' << std::endl;
                            passed++;
                            break;
                    
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_ms << " ms" << ')' << std::endl;
                            failed++;
                            break;

                        case Core::TestStatus::Skipped:
                            std::cout << "[SKIP] " << result.suiteName << " -> " << result.testName << std::endl;
                            skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderPassOnly(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];
                    switch (result.test_status) {
                        case Core::TestStatus::Passed: 
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_ms << " ms" << ')' << std::endl;

                            if (!result.execution_results.empty()) {
                                for (size_t j = 0; j < result.execution_results.size(); j++) {
                                    renderExecutionResult(result.execution_results[j], stdoutSize, stderrSize);
                                }
                            }

                            passed++;
                            break;
                        case Core::TestStatus::Failed:
                            failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderFailAll(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];
                    switch (result.test_status) {
                        case Core::TestStatus::Passed: 
                            passed++;
                            break;
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_ms << " ms" << ')' << std::endl;

                            for (size_t j = 0; j < result.failures.size(); j++) {
                                const Core::FailureInfo& fail = result.failures[j];
                                std::cout << "\tat: " << fail.file << ":" << fail.line << std::endl;
                                std::cout << '\t' << fail.message << std::endl;
                                std::cout << std::endl;
                            }

                            if (!result.execution_results.empty()) {
                                for (size_t j = 0; j < result.execution_results.size(); j++) {
                                    renderExecutionResult(result.execution_results[j], stdoutSize, stderrSize);
                                }
                            }

                            failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderFailMin(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];
                    switch (result.test_status) {
                        case Core::TestStatus::Passed: 
                            passed++;
                            break;
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_ms << " ms" << ')' << std::endl;
                            failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            skipped++;
                            break;
                    }
                }
            }
        }

        void renderExecutionResult(const Core::ExecutionResult& res, const int stdoutSize, const int stderrSize) {
            std::cout << "Execution Status: " << 
                Core::ExecutionStrings[(int)res.execution_status] << std::endl;
            std::cout << "Crash Type: " << 
                Core::CrashStrings[(int)res.crash_type] << std::endl;
            std::cout << "Time to run process: " << res.execution_ms << std::endl;
            std::cout << "Process ID: " << res.process.process_id << std::endl;
            std::cout << "Native Exit Code: " << res.process.native_exit_code << std::endl;
            std::cout << "Native Signal: " << res.process.native_signal << std::endl; 
            std::cout << "Address Sanitizer: " << res.sanitizers.asan_detected << std::endl;
            std::cout << "Undefined Behavior Sanitizer: " 
                << res.sanitizers.ubsan_detected << std::endl;
            std::cout << "Thread Sanitizer: " << res.sanitizers.tsan_detected << std::endl;
            std::cout << "Leak Sanitizer: " << res.sanitizers.lsan_detected << std::endl;
            if (!res.output.stdout_text.empty()) {
                if (!stdoutSize) {
                    std::cout << "stdout Capture (" << stdoutSize << " chars): "
                        << res.output.stdout_text.substr(std::min((size_t)stdoutSize, res.output.stdout_text.length()))
                        << std::endl;
                } else {
                    std::cout << "stdout Capture (full length): " << res.output.stdout_text << std::endl;
                }
            }

            if (!res.output.stderr_text.empty()) {
                if (!stderrSize) {
                    std::cout << "stderr Capture (" << stderrSize << " chars): "
                        << res.output.stderr_text.substr(std::min((size_t)stderrSize, res.output.stderr_text.length()))
                        << std::endl;
                } else {
                    std::cout << "stderr Capture (full length): " << res.output.stderr_text << std::endl;
                }
            }

            if (!res.framework_message.empty()) {
                std::cout << "Framework Message: " << res.framework_message << std::endl;
            }
        }
    }
}