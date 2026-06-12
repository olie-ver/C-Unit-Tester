#pragma once

#ifndef GENERIC_H
#define GENERIC_H

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
        inline Core::ExecutionResult executionStatus(Func&& func) {
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
        inline Core::ExecutionResult crashType(Func&& func) {
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
        inline Core::ExecutionResult terminationSignal(Func&& func) {
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
        inline Core::ExecutionResult processKilled(Func&& func) {
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