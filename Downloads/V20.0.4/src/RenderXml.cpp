#include <testpp/internal/PCH/pch.hpp>

#include <testpp/internal/Renderer.hpp>
#include <testpp/internal/Escape.hpp>
#include <testpp/internal/Runner.hpp>
#include <fstream>

/* Example xml
    <testsuites>
        <testsuite name="MathTests" tests="2" failures="1">
            <testcase name="AdditionWorks"/>
            <testcase name="DivisionFails">
                <failure message="Expected 4 but got 5"/>
                <executionResult 
                    executionStatus="STATUS"
                    crashType="TYPE"
                    msToRun="ms"
                    pid="pid"
                    nativeExitCode="code"
                    nativeSignal="signal"
                    asan="true"
                    ubsan="true"
                    tsan="true"
                    lsan="true"
                    stdout="stdout output NO TRUNCATION"
                    stderr="stderr output NO TRUNCATION"
                    frameworkMessage="frameworkMessage"
                />
            </testcase>
        </testsuite>
    </testsuites>
*/

namespace internal::Renderer {

    namespace {

        using TestList = std::vector<Core::TestResult>;

        struct SuiteStats {
            int passed = 0;
            int failed = 0;
            int skipped = 0;
            int unknown = 0;
            int expectedFail = 0;
        };

        SuiteStats calculateStats(const TestList& tests) {
            SuiteStats stats;

            for (const auto& test : tests) {
                switch (test.test_status) {
                    case Core::TestStatus::Passed:
                        stats.passed++;
                        break;

                    case Core::TestStatus::Failed:
                        stats.failed++;
                        break;

                    case Core::TestStatus::Skipped:
                        stats.skipped++;
                        break;
                }
            }

            return stats;
        }

        void renderFailures(std::ostream& stream, const Core::TestResult& test) {
            for (const auto& failure : test.failures) {
                stream << "\t\t\t<failure "
                       << "message=\"" << Helpers::escapeXml(failure.message) << "\" "
                       << "file=\"" << Helpers::escapeXml(failure.file) << "\" "
                       << "line=\"" << failure.line << "\"/>\n";
            }
        }

        void renderExecutionResults(std::ostream& stream, const Core::TestResult& test) {
            if (test.execution_results.empty()) {
                return;
            }

            for (const auto& res : test.execution_results) {
                stream << "\t\t\t<executionResult\n";
                stream << "\t\t\t\texecutionStatus=\"" << Core::ExecutionStrings[(int)res.execution_status] << "\"\n";
                stream << "\t\t\t\tcrashType=\"" << Core::CrashStrings[(int)res.crash_type] << "\"\n";
                stream << "\t\t\t\tmsToRun=\"" << res.execution_ms << "\"\n";
                stream << "\t\t\t\tpid=\"" << res.process.process_id << "\"\n";
                stream << "\t\t\t\tnativeExitCode=\"" << res.process.native_exit_code << "\"\n";
                stream << "\t\t\t\tnativeSignal=\"" << res.process.native_signal << "\"\n";
                stream << "\t\t\t\tasan=\"" << res.sanitizers.asan_detected << "\"\n";
                stream << "\t\t\t\tubsan=\"" << res.sanitizers.ubsan_detected << "\"\n";
                stream << "\t\t\t\ttsan=\"" << res.sanitizers.tsan_detected << "\"\n";
                stream << "\t\t\t\tlsan=\"" << res.sanitizers.lsan_detected << "\"\n";
                stream << "\t\t\t\tstdout=\"" << Helpers::escapeXml(res.output.stdout_text) << "\"\n";
                stream << "\t\t\t\tstderr=\"" << Helpers::escapeXml(res.output.stderr_text) << "\"\n";
                stream << "\t\t\t\tframeworkMessage=\"" << Helpers::escapeXml(res.framework_message) << "\"\n";
                stream << "\t\t\t/>\n";
            }
        }

        void renderTestcase(
            std::ostream& stream,
            const Core::TestResult& test,
            bool includeFailures
        ) {
            const std::string& status = Core::StatusStrings[(int)test.test_status];

            if (includeFailures && test.test_status == Core::TestStatus::Failed) {

                stream << "\t\t<testcase "
                       << "name=\"" << Helpers::escapeXml(test.testName) << "\" "
                       << "status=\"" << status << "\">\n";

                renderFailures(stream, test);
                renderExecutionResults(stream, test);

                stream << "\t\t</testcase>\n";
            }
            else {
                if (test.execution_results.empty()) {
                    stream << "\t\t<testcase "
                       << "name=\"" << Helpers::escapeXml(test.testName) << "\" "
                       << "status=\"" << status << "\"/>\n";
                } else {
                    stream << "\t\t<testcase "
                        "name=\"" << Helpers::escapeXml(test.testName) << "\" "
                       << "status=\"" << status << "\"\n";
                    renderExecutionResults(stream, test);
                    stream << "\t\t</testcase>\n";
                }
            }
        }

        template <typename SuitePredicate, typename TestPredicate>
        void renderXml(
            std::ostream& stream,
            Core::TestRun& testRun,
            SuitePredicate suitePredicate,
            TestPredicate testPredicate,
            bool includeFailures
        ) {
            stream << "<testsuites>\n";

            for (auto&& [suiteName, tests] : testRun.results) {

                SuiteStats stats = calculateStats(tests);

                if (!suitePredicate(suiteName, tests, stats)) {
                    continue;
                }

                stream << "\t<testsuite "
                       << "name=\"" << Helpers::escapeXml(suiteName) << "\" "
                       << "tests=\"" << tests.size() << "\" "
                       << "successes=\"" << stats.passed << "\" "
                       << "failures=\"" << stats.failed << "\" "
                       << "skips=\"" << stats.skipped << "\" "
                       << "unknowns=\"" << stats.unknown << "\" "
                       << "expected_failure\"" << stats.expectedFail << "\">\n";

                for (const auto& test : tests) {

                    if (!testPredicate(test)) {
                        continue;
                    }

                    renderTestcase(
                        stream,
                        test,
                        includeFailures
                    );
                }

                stream << "\t</testsuite>\n";
            }

            stream << "</testsuites>";
        }

    }

    void ConsoleRenderer::renderDefaultXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats&) {
                return true;
            },
            [](const Core::TestResult&) {
                return true;
            },
            true
        );
    }

    void ConsoleRenderer::renderMinimumXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats&) {
                return true;
            },
            [](const Core::TestResult&) {
                return true;
            },
            false
        );
    }

    void ConsoleRenderer::renderPassOnlyXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats& stats) {
                return stats.passed > 0;
            },
            [](const Core::TestResult& test) {
                return test.test_status == Core::TestStatus::Passed;
            },
            false
        );
    }

    void ConsoleRenderer::renderFailAllXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats& stats) {
                return stats.failed > 0;
            },
            [](const Core::TestResult& test) {
                return test.test_status == Core::TestStatus::Failed;
            },
            true
        );
    }

    void ConsoleRenderer::renderFailMinXml(Core::TestRun& testRun) {
        std::fstream stream(junitFile, std::fstream::out);

        renderXml(
            stream,
            testRun,
            [](const std::string&, const TestList&, const SuiteStats& stats) {
                return stats.failed > 0;
            },
            [](const Core::TestResult& test) {
                return test.test_status == Core::TestStatus::Failed;
            },
            false
        );
    }

}