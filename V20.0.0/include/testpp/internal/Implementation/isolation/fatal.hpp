#pragma once

#ifndef FATAL_H
#define FATAL_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

#ifdef _WIN32
    #include "../../Runner.hpp"
#endif

#include <iostream>

namespace internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult death(Func&& func) {
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
        inline Core::ExecutionResult segfault(Func&& func) {
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
        inline Core::ExecutionResult abort(Func&& func) {
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
        Core::ExecutionResult fatal(Func&& func) {
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
        Core::ExecutionResult nonFatal(Func&& func) {
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