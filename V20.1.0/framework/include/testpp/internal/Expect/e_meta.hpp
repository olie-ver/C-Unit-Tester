#pragma once

#ifndef E_META_H
#define E_META_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"

#define EXPECT_PASSES(test) internal::Expects::expectPasses([&](){(test);}, #test, __FILE__, __LINE__)
#define EXPECT_FAILS(test) internal::Expects::expectFails([&](){(test);}, #test, __FILE__, __LINE__)
#define EXPECT_FAILS_MSG(test, msg) \
    internal::Expects::expectFailsWithMessage([&](){(test);}, #test, (msg), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        inline void expectPasses(const std::function<void()>& test, const char* testName, 
            const char* file, const int line) 
        {
            auto result = impl_meta::passes(test, testName, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        inline void expectFails(const std::function<void()>& test, const char* testName, 
            const char* file, const int line) 
        {
            auto result = impl_meta::fails(test, testName, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        inline void expectFailsWithMessage(const std::function<void()>& test, const char* testName, 
            const std::string& msg, const char* file, const int line) 
        {
            auto result = impl_meta::failsWithMessage(test, testName, msg, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
    }
}

#endif