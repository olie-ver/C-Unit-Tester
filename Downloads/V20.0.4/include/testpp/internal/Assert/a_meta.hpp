#pragma once

#ifndef A_META_H
#define A_META_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"

#define ASSERT_PASSES(test) internal::Assert::assertPasses([&](){(test);}, #test, __FILE__, __LINE__)
#define ASSERT_FAILS(test) internal::Assert::assertFails([&](){(test);}, #test, __FILE__, __LINE__)
#define ASSERT_FAILS_MSG(test, msg) \
    internal::Assert::assertFailsWithMessage([&](){(test);}, #test, (msg), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        inline void assertPasses(const std::function<void()>& test, const char* testName, 
            const char* file, const int line) 
        {
            auto result = impl_meta::passes(test, testName, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        inline void assertFails(const std::function<void()>& test, const char* testName, 
            const char* file, const int line) 
        {
            auto result = impl_meta::fails(test, testName, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        inline void assertFailsWithMessage(const std::function<void()>& test, const char* testName, 
            const std::string& msg, const char* file, const int line) 
        {
            auto result = impl_meta::failsWithMessage(test, testName, msg, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif