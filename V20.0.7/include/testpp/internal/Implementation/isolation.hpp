#pragma once

#ifndef ISO_H
#define ISO_H

#include "../Core.hpp"
#include "isolation_types.hpp"

#include <optional>
#include <string>

namespace internal {
    namespace impl_iso {
        // ============================================================
        // Crash / Fatal Behavior Assertions
        // ============================================================

        //fails if Execution Status != Completed
        template<typename Func> 
        Core::ExecutionResult death(Func&& func);

        //passes if Crash Type == SegmentationFault
        template<typename Func> 
        Core::ExecutionResult segfault(Func&& func);

        //Passes if Crash Type == Abort
        template<typename Func> 
        Core::ExecutionResult abort(Func&& func);

        //"Bad thing tests"
        //Passes if something fatal happens
        template<typename Func> 
        Core::ExecutionResult fatal(Func&& func);

        //Passes if nothing fatal happens
        template<typename Func> 
        Core::ExecutionResult nonFatal(Func&& func);

        // ============================================================
        // Process Exit Assertions
        // ============================================================

        //Passes if exit code == EXIT_SUCCESS
        template<typename Func> 
        Core::ExecutionResult success(Func&& func);

        //Passes if exit code == EXIT_FAILURE
        template<typename Func> 
        Core::ExecutionResult failure(Func&& func);

        //Passes if exit code != 0
        template<typename Func> 
        Core::ExecutionResult nonzeroExit(Func&& func);

        //Passes if exit code == (param) exit code
        template<typename Func> 
        Core::ExecutionResult exitCode(Func&& func);

        //Passes if Execution Status == Completed
        template<typename Func> 
        Core::ExecutionResult completes(Func&& func);

        // ============================================================
        // Output Assertions
        // ============================================================

        //Passes if stdout output contains (param) string
        template<typename Func> 
        Core::ExecutionResult stdoutContains(Func&& func);

        //Passes if stderr output contains (param) string
        template<typename Func> 
        Core::ExecutionResult stderrContains(Func&& func);

        //Passes if there is no stderr output
        template<typename Func> 
        Core::ExecutionResult noStdout(Func&& func);

        //Passes if there is no stdout output
        template<typename Func> 
        Core::ExecutionResult noStderr(Func&& func);

        //Passes if output == (param) output
        template<typename Func> 
        Core::ExecutionResult stdoutMatches(Func&& func);

        //Passes if output == (param) output
        template<typename Func> 
        Core::ExecutionResult stderrMatches(Func&& func);

        // ============================================================
        // Sanitizer Assertions
        // ============================================================

        template<typename Func> 
        Core::ExecutionResult asanFailure(Func&& func);

        template<typename Func> 
        Core::ExecutionResult ubsanFailure(Func&& func);

        template<typename Func> 
        Core::ExecutionResult tsanFailure(Func&& func);

        template<typename Func> 
        Core::ExecutionResult lsanFailure(Func&& func);

        template<typename Func> 
        Core::ExecutionResult sanFailure(Func&& func);

        // ============================================================
        // Timing / Concurrency Assertions
        // ============================================================

        //Passes if it runs longer than the passed in timeout
        template<typename Func> 
        Core::ExecutionResult timeout(Func&& func, int timeLimitMs);

        //Passes if it runs shorter than the passed in timeout
        template<typename Func> 
        Core::ExecutionResult completesWithin(Func&& func, int timeLimitMs);

        // ============================================================
        // Generic / Advanced Assertions
        // ============================================================

        //Passes if the process result == (param) result
        template<typename Func> 
        Core::ExecutionResult executionStatus(Func&& func);

        template<typename Func> 
        Core::ExecutionResult crashType(Func&& func);

        template<typename Func> 
        Core::ExecutionResult terminationSignal(Func&& func);

        //Passes if the process was killed
        template<typename Func> 
        Core::ExecutionResult processKilled(Func&& func);

        //Passes if the core was dumped
        template<typename Func> 
        Core::ExecutionResult coreDumped(Func&& func);
    }
}

#include "isolation/exit.hpp"
#include "isolation/fatal.hpp"
#include "isolation/generic.hpp"
#include "isolation/output.hpp"
#include "isolation/sanitizer.hpp"
#include "isolation/timing.hpp"

#endif