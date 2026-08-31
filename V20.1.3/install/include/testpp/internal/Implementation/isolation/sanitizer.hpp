#pragma once

#ifndef SANITIZER_H
#define SANITIZER_H

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
        inline Core::ExecutionResult asanFailure(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult ubsanFailure(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult tsanFailure(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult lsanFailure(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult sanFailure(Func&& func) {
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