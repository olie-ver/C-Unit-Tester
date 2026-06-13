#pragma once

#ifndef OUTPUT_H
#define OUPUT_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

#ifdef _WIN32
    #include "../../Runner.hpp"
#endif

namespace internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult stdoutContains(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult stderrContains(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult noStdout(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult noStderr(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult stdoutMatches(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult stderrMatches(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }
    }
}

#endif