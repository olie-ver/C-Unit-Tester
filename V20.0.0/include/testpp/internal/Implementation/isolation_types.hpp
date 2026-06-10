#pragma once

#ifndef ISO_TYPE_H
#define ISO_TYPE_H

#include "../Core.hpp"

namespace internal {
    namespace impl_iso {
        //The definition all platforms must implement to 
        //  be able to run tests in isolation
        Core::ExecutionResult runIsolatedImpl(const std::function<void()>& func, const int timeLimit);

        /// @brief The core behind running an isolated test
        /// @tparam Func a function to runs
        /// @param func the function to run
        /// @return a TestExecutionResult
        template<typename Func>
        inline Core::ExecutionResult isolateRun(Func&& func, const int timeLimit = 10000)
        {
            return internal::impl_iso::runIsolatedImpl(
                std::function<void()>( std::forward<Func>(func)),
                timeLimit
            );
        }
    }
}

#endif