#pragma once

#ifndef A_SET_H
#define A_SET_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"

#define ASSERT_SET_EQ(first, second) internal::Assert::assertSameSet((first), (second), __FILE__, __LINE__)
#define ASSERT_SET_NE(first, second) internal::Assert::assertNotSameSet((first), (second), __FILE__, __LINE__)
#define ASSERT_SUBSET(first, second) internal::Assert::assertSubset((first), (second), __FILE__, __LINE__)
#define ASSERT_SUPERSET(first, second) internal::Assert::assertSuperset((first), (second), __FILE__, __LINE__)
#define ASSERT_STRICT_SUBSET(first, second) internal::Assert::assertStrictSubset((first), (second), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertSameSet(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_set::sameSet(a, b, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertNotSameSet(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_set::notSameSet(a, b, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertSubset(const A& sub, const B& super, const char* file, const int line) {
            auto result = impl_set::subset(sub, super, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertSuperset(const A& super, const B& sub, const char* file, const int line) {
            auto result = impl_set::superset(super, sub, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertStrictSubset(const A& sub, const B& super, const char* file, const int line) {
            auto result = impl_set::strictSubset(sub, super, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif