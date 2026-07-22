#include <testpp/internal/PCH/pch.hpp>

#include <testpp/internal/Renderer.hpp>
#include <iostream>
#include <mutex>

namespace internal {
    namespace Renderer {
        void ConsoleRenderer::render(Core::TestRun& testRun) 
        {
            if (jsonFile != "") {
                switch (verb) {
                    case Verbosity::Default:
                        renderDefaultJson(testRun);
                        return;
                    case Verbosity::Minimum:
                        renderMinimumJson(testRun);
                        return;
                    case Verbosity::PassOnly:
                        renderPassOnlyJson(testRun);
                        return;
                    case Verbosity::FailOnlyMin:
                        renderFailMinJson(testRun);
                        return;
                    case Verbosity::FailOnlyAll:
                        renderFailAllJson(testRun);
                        return;
                }
            }

            if (junitFile != "") {
                switch (verb) {
                    case Verbosity::Default:
                        renderDefaultXml(testRun);
                        return;
                    case Verbosity::Minimum:
                        renderMinimumXml(testRun);
                        return;
                    case Verbosity::PassOnly:
                        renderPassOnlyXml(testRun);
                        return;
                    case Verbosity::FailOnlyMin:
                        renderFailMinXml(testRun);
                        return;
                    case Verbosity::FailOnlyAll:
                        renderFailAllXml(testRun);
                        return;
                }
            }

            std::cout << std::string(50, '-') << '\n' << std::endl;

            std::cout << "Ran " << testRun.total << " tests..." << std::endl;
 
            std::cout << std::endl;

            switch (verb) {
                case Verbosity::Default:
                    renderDefault(testRun);
                    break;
                case Verbosity::Minimum:
                    renderMinimum(testRun);
                    break;
                case Verbosity::PassOnly:
                    renderPassOnly(testRun);
                    break;
                case Verbosity::FailOnlyMin:
                    renderFailMin(testRun);
                    break;
                case Verbosity::FailOnlyAll:
                    renderFailAll(testRun);
                    break;
            }

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Total: " << testRun.total;
            std::cout << " | Passed: " << passed;
            std::cout << " | Failed: " << failed;
            std::cout << " | Skipped: " << skipped << std::endl;
            std::cout << "Time: " << testRun.totalMs << " ms" << std::endl;
        }

        void stream(const std::string_view& msg) {
            static std::mutex m;

            std::lock_guard lock(m);
            std::cout << msg;
        }
    }
}