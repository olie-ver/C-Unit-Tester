#pragma once

#ifndef GENERIC_H
#define GENERIC_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

namespace internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult executionStatus(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult crashType(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult terminationSignal(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult processKilled(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }
    }
}

#endif