#pragma once

#ifndef FATAL_H
#define FATAL_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

#include <iostream>

namespace internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult death(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            std::cout << "Execution status: " << Core::ExecutionStrings[(int)result.execution_status] << std::endl;
            std::cout << "Child pid: " << result.process.process_id << std::endl;
            std::cout << "Native exit code: " << result.process.native_exit_code << std::endl;
            std::cout << "Native signal " << result.process.native_signal << std::endl;
            std::cout << "Crash type: " << Core::CrashStrings[(int)result.crash_type] << std::endl;
            std::cout << "Duration (ms): " << result.execution_ms << std::endl;
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult segfault(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        inline Core::ExecutionResult abort(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        Core::ExecutionResult fatal(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }

        template<typename Func> 
        Core::ExecutionResult nonFatal(Func&& func) {
            Core::ExecutionResult result = isolateRun(func);
            return result;
        }
    }
}

#endif