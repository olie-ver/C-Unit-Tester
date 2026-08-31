#pragma once

#ifndef E_CMP_H
#define E_CMP_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"
#include "../Concepts.hpp"

#define EXPECT_EQ(a, b) internal::Expects::expectEquals((a), (b), __FILE__, __LINE__)
#define EXPECT_NE(a, b) internal::Expects::expectNotEquals((a), (b), __FILE__, __LINE__)
#define EXPECT_LT(a, b) internal::Expects::expectLessThan((a), (b), __FILE__, __LINE__)
#define EXPECT_LE(a, b) internal::Expects::expectLessThanEquals((a), (b), __FILE__, __LINE__)
#define EXPECT_GT(a, b) internal::Expects::expectGreaterThan((a), (b), __FILE__, __LINE__)
#define EXPECT_GE(a, b) internal::Expects::expectGreaterThanEquals((a), (b), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        /// @brief An Expects test for expecting two values to be equal
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires Concepts::HasEQ<A, B>
        inline void expectEquals(const A& a, const B& b, const char* file, const int line)
        {
            auto result = impl_cmp::equals(a, b, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for expecting two values to be not equal
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires (Concepts::HasNE<A, B> || Concepts::HasEQ<A, B>)
        inline void expectNotEquals(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::notEquals(a, b, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for expecting the first argument to be strictly less than the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasLT<A, B>)
        inline void expectLessThan(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::lessThan(a, b, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for expecting the first argument to be less than or equal to the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasLE<A, B>)
        inline void expectLessThanEquals(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::lessThanEqual(a, b, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for expecting the first argument to be strictly greater than the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasGT<A, B>)
        inline void expectGreaterThan(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::greaterThan(a, b, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for expecting the first argument to be strictly greater than or equal to the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasGE<A, B>)
        inline void expectGreaterThanEquals(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::greaterThanEqual(a, b, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
    }
}

#endif