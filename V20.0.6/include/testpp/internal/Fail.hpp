#pragma once

#ifndef FAIL_H
#define FAIL_H

#include "Core.hpp"
#include "Runner.hpp"

namespace internal {
    namespace Fail {
        inline void e_fail(const Core::FailureInfo& result) {
            Runner::TEST_STACK.back().failures.push_back(result);
        }

        inline void a_fail(const Core::FailureInfo& result) {
            Runner::TEST_STACK.back().failures.push_back(result);
            throw Core::AssertionFailure();
        }
    }
}

#endif