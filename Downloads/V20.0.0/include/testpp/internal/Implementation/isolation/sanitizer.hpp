#pragma once

#ifndef SANITIZER_H
#define SANITIZER_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

namespace internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult asanFailure(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult ubsanFailure(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult tsanFailure(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult lsanFailure(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult sanFailure(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }
    }
}

#endif