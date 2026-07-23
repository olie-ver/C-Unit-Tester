#pragma once

#ifndef A_BOOL_H
#define A_BOOL_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"

#define ASSERT_TRUE(cond) internal::Assert::assertTrue((cond), #cond, __FILE__, __LINE__)
#define ASSERT_FALSE(cond) internal::Assert::assertFalse((cond), #cond, __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief An Asserts test for asserting a true value
        /// @param cond a condition
        /// @param expr the condition as an expression
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertTrue(const bool cond, const char* expr, const char* file, const int line) {
            auto result = impl_bool::True(cond, expr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Asserts test for asserting a false value
        /// @param cond a condition
        /// @param expr the condition as an expression
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertFalse(const bool cond, const char* expr, const char* file, const int line) {
            auto result = impl_bool::False(cond, expr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif