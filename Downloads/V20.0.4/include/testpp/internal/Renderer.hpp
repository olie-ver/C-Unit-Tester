#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "Core.hpp"

/// @brief An internal namespace. Using anything from within is not advised
namespace internal {
    /// @brief A rendering namespace to render the output from running tests
    namespace Renderer {
        /// @brief Flags for renderer verbosity
        enum class Verbosity {
            Default,
            Minimum,
            PassOnly,
            FailOnlyAll,
            FailOnlyMin
        };

        class ITestRenderer {
            public:
                virtual ~ITestRenderer() = default;
                virtual void render(Core::TestRun& result) = 0;
        };

        class ConsoleRenderer : public ITestRenderer {
            public:
                ConsoleRenderer(const std::string jsonFile = "", const std::string junitFile = "", 
                    Verbosity verbosity = Verbosity::Default, const int stdoutSize = 0, const int stderrSize = 0) 
                    : verb(verbosity), jsonFile(jsonFile), junitFile(junitFile), stdoutSize(stdoutSize),
                        stderrSize(stderrSize) {};

                void render(Core::TestRun& result) override;

            private:
                Verbosity verb;
                const std::string jsonFile;
                const std::string junitFile;
                int passed = 0;
                int failed = 0;
                int skipped = 0;
                
                int stdoutSize = 0;
                int stderrSize = 0;
                
                void renderDefaultJson(Core::TestRun& result);
                void renderMinimumJson(Core::TestRun& result);
                void renderPassOnlyJson(Core::TestRun& result);
                void renderFailAllJson(Core::TestRun& result);
                void renderFailMinJson(Core::TestRun& result);

                void renderDefaultXml(Core::TestRun& result);
                void renderMinimumXml(Core::TestRun& result);
                void renderPassOnlyXml(Core::TestRun& result);
                void renderFailAllXml(Core::TestRun& result);
                void renderFailMinXml(Core::TestRun& result);

                void renderDefault(Core::TestRun& result);
                void renderMinimum(Core::TestRun& result);
                void renderPassOnly(Core::TestRun& result);
                void renderFailAll(Core::TestRun& result);
                void renderFailMin(Core::TestRun& result);
        };
        
    }
}

#endif