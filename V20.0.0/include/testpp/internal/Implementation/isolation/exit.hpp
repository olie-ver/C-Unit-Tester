#pragma once

#ifndef EXIT_H
#define EXIT_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"

namespace internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult success(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult failure(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult nonzeroExit(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult exitCode(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult completes(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }
    }
}

#endif