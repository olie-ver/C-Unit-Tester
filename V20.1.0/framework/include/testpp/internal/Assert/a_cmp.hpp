#pragma once

#ifndef A_CMP_H
#define A_CMP_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"
#include "../Concepts.hpp"

#define ASSERT_EQ(a, b) internal::Assert::assertEquals((a), (b), __FILE__, __LINE__)
#define ASSERT_NE(a, b) internal::Assert::assertNotEquals((a), (b), __FILE__, __LINE__)
#define ASSERT_LT(a, b) internal::Assert::assertLessThan((a), (b), __FILE__, __LINE__)
#define ASSERT_LE(a, b) internal::Assert::assertLessThanEquals((a), (b), __FILE__, __LINE__)
#define ASSERT_GT(a, b) internal::Assert::assertGreaterThan((a), (b), __FILE__, __LINE__)
#define ASSERT_GE(a, b) internal::Assert::assertGreaterThanEquals((a), (b), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief An Asserts test for asserting two values to be equal
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires Concepts::HasEQ<A, B>
        inline void assertEquals(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::equals(a, b, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Asserts test for asserting two values to be not equal
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires (Concepts::HasNE<A, B> || Concepts::HasEQ<A, B>)
        inline void assertNotEquals(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::notEquals(a, b, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for asserting that the first argument to be strictly less than the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasLT<A, B>)
        inline void assertLessThan(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::lessThan(a, b, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for asserting that the first argument to be less than or equal to the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasLE<A, B>)
        inline void assertLessThanEquals(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::lessThanEqual(a, b, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for asserting that the first argument to be strictly greater than the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasGT<A, B>)
        inline void assertGreaterThan(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::greaterThan(a, b, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for asserting that the first argument to
        ///         be strictly greater than or equal to the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasGE<A, B>)
        inline void assertGreaterThanEquals(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_cmp::greaterThanEqual(a, b, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif