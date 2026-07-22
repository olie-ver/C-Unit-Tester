#include <testpp/internal/PCH/pch.hpp>

#include <testpp/internal/Renderer.hpp>
#include <iostream>

namespace internal {
    namespace Renderer {
        void ConsoleRenderer::render(Core::TestRun& testRun) 
        {

            if (jsonFile != "") {
                switch (verb) {
                    case Verbosity::Default:
                        renderDefaultJson(testRun);
                        break;
                    case Verbosity::Minimum:
                        renderMinimumJson(testRun);
                        break;
                    case Verbosity::PassOnly:
                        renderPassOnlyJson(testRun);
                        break;
                    case Verbosity::FailOnlyMin:
                        renderFailMinJson(testRun);
                        break;
                    case Verbosity::FailOnlyAll:
                        renderFailAllJson(testRun);
                        break;
                }
            }

            if (junitFile != "") {
                switch (verb) {
                    case Verbosity::Default:
                        renderDefaultXml(testRun);
                        break;
                    case Verbosity::Minimum:
                        renderMinimumXml(testRun);
                        break;
                    case Verbosity::PassOnly:
                        renderPassOnlyXml(testRun);
                        break;
                    case Verbosity::FailOnlyMin:
                        renderFailMinXml(testRun);
                        break;
                    case Verbosity::FailOnlyAll:
                        renderFailAllXml(testRun);
                        break;
                }
            }

            if (jsonFile != "" || junitFile != "") {
                return;
            }

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
    }
}