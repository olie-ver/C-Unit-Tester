#pragma once

#ifndef EXIT_H
#define EXIT_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"

#ifdef _WIN32
    #include "../../Runner.hpp"
#endif

namespace internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult success(Func&& func) {
            #ifdef _WIN32
                size_t id = internal::Runner::registerDeathTest(func);
                Core::ExecutionResult result = isolateRun(id);
                return result;
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult failure(Func&& func) {
            #ifdef _WIN32
                size_t id = internal::Runner::registerDeathTest(func);
                Core::ExecutionResult result = isolateRun(id);
                return result;
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult nonzeroExit(Func&& func) {
            #ifdef _WIN32
                size_t id = internal::Runner::registerDeathTest(func);
                Core::ExecutionResult result = isolateRun(id);
                return result;
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult exitCode(Func&& func) {
            #ifdef _WIN32
                size_t id = internal::Runner::registerDeathTest(func);
                Core::ExecutionResult result = isolateRun(id);
                return result;
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult completes(Func&& func) {
            #ifdef _WIN32
                size_t id = internal::Runner::registerDeathTest(func);
                Core::ExecutionResult result = isolateRun(id);
                return result;
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }
    }
}

#endif