#include <testpp/internal/PCH/pch.hpp>

#include <testpp/internal/Renderer.hpp>
#include <testpp/internal/Escape.hpp>
#include <testpp/internal/Runner.hpp>
#include <fstream>

/* Example json
    {
        suites: [
            {
                suite_name: name,
                tests: [
                    {
                        suiteName: name,
                        testName: test,
                        status: status,
                        durationMs: durationMs,
                        failures: [
                            {
                                message: message,
                                file: file,
                                line: line
                            }
                        ],
                        executionResults: [
                            {
                                executionStatus: status,
                                crashType: type,
                                msToRun: timeToRun,
                                pid: pid,
                                nativeExitCode: exitCode,
                                nativeSignal: signal,
                                aSan: true/false,
                                ubsan: true/false,
                                tsan: true/false,
                                lsan: true/false,
                                stdout: stdoutOutput (NO TRUNCATION)
                                stderr: stderrOutput (NO TRUNCATION)
                                frameworkMessage: 
                            }
                        ]
                    },
                ]
            }
        ]
    }
*/

namespace internal::Renderer {
    namespace {
        using TestList = std::vector<Core::TestResult>;

        bool hasStatus(const TestList& tests, Core::TestStatus status) {
            for (const auto& test : tests) {
                if (test.test_status == status) {
                    return true;
                }
            }

            return false;
        }

        void renderFailures(std::fstream& stream, const Core::TestResult& test) {
            stream << "[\n\t\t\t\t\t\t";

            bool first = true;

            for (const auto& failure : test.failures) {
                if (!first) {
                    stream << ",\n\t\t\t\t\t\t";
                }

                first = false;

                stream << "{\n\t\t\t\t\t\t\t";
                stream << "\"message\": \"" << Helpers::escapeJson(failure.message) << "\",\n\t\t\t\t\t\t\t";
                stream << "\"file\": \"" << Helpers::escapeJson(failure.file) << "\",\n\t\t\t\t\t\t\t";
                stream << "\"line\": " << failure.line << "\n\t\t\t\t\t\t";
                stream << "}";
            }

            stream << "\n\t\t\t\t\t]";
        }

        void renderExecutionResults(std::fstream& stream, const Core::TestResult& test) {
            if (test.execution_results.empty()) {
                return;
            }

            bool first = true;

            for (const auto& res : test.execution_results) {
                if (!first) {
                    stream << ",\n\t\t\t\t\t\t";
                }

                first = false;

                stream << "{\n\t\t\t\t\t\t\t";
                stream << "\"executionStatus\": \"" 
                    << Core::ExecutionStrings[(int)res.execution_status]  << "\",\n\t\t\t\t\t\t\t";
                stream << "\"crashType\": \"" 
                    << Core::CrashStrings[(int)res.crash_type] << "\",\n\t\t\t\t\t\t\t";
                stream << "\"timeToRun\": " << res.execution_ms << ",\n\t\t\t\t\t\t";
                stream << "\"pid\": " << res.process.process_id << ",\n\t\t\t\t\t\t";
                stream << "\"nativeExitCode\": " << res.process.native_exit_code << ",\n\t\t\t\t\t\t";
                stream << "\"nativeSignal\": " << res.process.native_signal << ",\n\t\t\t\t\t\t";
                stream << "\"aSan\": " << res.sanitizers.asan_detected << ",\n\t\t\t\t\t\t";
                stream << "\"ubSan\": " << res.sanitizers.ubsan_detected << ",\n\t\t\t\t\t\t";
                stream << "\"tSan\": " << res.sanitizers.tsan_detected << ",\n\t\t\t\t\t\t";
                stream << "\"lSan\": " << res.sanitizers.lsan_detected << ",\n\t\t\t\t\t\t";
                stream << "\"stdout\": \"" << Helpers::escapeJson(res.output.stdout_text)
                    << "\",\n\t\t\t\t\t\t\t";
                stream << "\"stderr\": \"" << Helpers::escapeJson(res.output.stderr_text)
                    << "\",\n\t\t\t\t\t\t\t";
                stream << "\"frameworkMessage\": \"" << Helpers::escapeJson(res.framework_message)
                    << "\"\n\t\t\t\t\t\t\t";

                stream << "}";
            }

            stream << "\n\t\t\t\t\t]";
        }

        void renderTest(
            std::fstream& stream,
            const std::string& suiteName,
            const Core::TestResult& test,
            bool includeFailures
        ) {
            stream << "{\n\t\t\t\t\t";
            stream << "\"suiteName\": \"" << Helpers::escapeJson(suiteName) << "\",\n\t\t\t\t\t";
            stream << "\"testName\": \"" << Helpers::escapeJson(test.testName) << "\",\n\t\t\t\t\t";
            stream << "\"status\": \"" << Core::StatusStrings[(int)test.test_status] << "\",\n\t\t\t\t\t";
            stream << "\"total_ms\": " << test.execution_ms << ",\n\t\t\t\t\t";
            stream << "\"failures\": ";

            if (includeFailures) {
                renderFailures(stream, test);
            }
            else {
                stream << "[]";
            }

            renderExecutionResults(stream, test);

            stream << "\n\t\t\t\t}";
        }

        template <typename SuitePredicate, typename TestPredicate>
        void renderJson(
            std::fstream& stream,
            Core::TestRun& testRun,
            SuitePredicate suitePredicate,
            TestPredicate testPredicate,
            bool includeFailures
        ) {
            stream << "{\n\t\"suites\": [\n\t\t";

            bool firstSuite = true;

            for (auto&& [suiteName, tests] : testRun.results) {

                if (!suitePredicate(suiteName, tests)) {
                    continue;
                }

                if (!firstSuite) {
                    stream << ",\n\t\t";
                }

                firstSuite = false;

                stream << "{\n\t\t\t";
                stream << "\"suite_name\": \"" << Helpers::escapeJson(suiteName) << "\",\n\t\t\t";
                stream << "\"tests\": [\n\t\t\t\t";

                bool firstTest = true;

                for (const auto& test : tests) {

                    if (!testPredicate(test)) {
                        continue;
                    }

                    if (!firstTest) {
                        stream << ",\n\t\t\t\t";
                    }

                    firstTest = false;

                    renderTest(stream, suiteName, test, includeFailures);
                }

                stream << "\n\t\t\t]\n\t\t";
                stream << "}";
            }

            stream << "\n\t]\n}";
        }

    }

    void ConsoleRenderer::renderDefaultJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList&) {
                return !Runner::shouldSkip(suite);
            },
            [](const Core::TestResult&) {
                return true;
            },
            true
        );
    }

    void ConsoleRenderer::renderMinimumJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList&) {
                return !Runner::shouldSkip(suite);
            },
            [](const Core::TestResult&) {
                return true;
            },
            false
        );
    }

    void ConsoleRenderer::renderPassOnlyJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList& tests) {
                return !Runner::shouldSkip(suite)
                    && hasStatus(tests, Core::TestStatus::Passed);
            },
            [](const Core::TestResult& test) {
                return test.test_status == Core::TestStatus::Passed;
            },
            false
        );
    }

    void ConsoleRenderer::renderFailAllJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList& tests) {
                return !Runner::shouldSkip(suite)
                    && hasStatus(tests, Core::TestStatus::Failed);
            },
            [](const Core::TestResult& test) {
                return test.test_status == Core::TestStatus::Failed;
            },
            true
        );
    }

    void ConsoleRenderer::renderFailMinJson(Core::TestRun& testRun) {
        std::fstream stream(jsonFile, std::fstream::out);

        renderJson(
            stream,
            testRun,
            [](const std::string& suite, const TestList& tests) {
                return !Runner::shouldSkip(suite)
                    && hasStatus(tests, Core::TestStatus::Failed);
            },
            [](const Core::TestResult& test) {
                return test.test_status == Core::TestStatus::Failed;
            },
            false
        );
    }
}