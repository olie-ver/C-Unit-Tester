#pragma once

#ifndef OUTPUT_H
#define OUPUT_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

namespace internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult stdoutContains(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult stderrContains(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult noStdout(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult noStderr(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult stdoutMatches(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult stderrMatches(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }
    }
}

#endif