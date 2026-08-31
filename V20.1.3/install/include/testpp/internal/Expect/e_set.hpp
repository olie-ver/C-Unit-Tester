#pragma once

#ifndef E_SET_H
#define E_SET_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"

#define EXPECT_SET_EQ(first, second) internal::Expects::expectSameSet((first), (second), __FILE__, __LINE__)
#define EXPECT_SET_NE(first, second) internal::Expects::expectNotSameSet((first), (second), __FILE__, __LINE__)
#define EXPECT_SUBSET(first, second) internal::Expects::expectSubset((first), (second), __FILE__, __LINE__)
#define EXPECT_SUPERSET(first, second) internal::Expects::expectSuperset((first), (second), __FILE__, __LINE__)
#define EXPECT_STRICT_SUBSET(first, second) internal::Expects::expectStrictSubset((first), (second), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectSameSet(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_set::sameSet(a, b, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectNotSameSet(const A& a, const B& b, const char* file, const int line) {
            auto result = impl_set::notSameSet(a, b, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectSubset(const A& sub, const B& super, const char* file, const int line) {
            auto result = impl_set::subset(sub, super, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectSuperset(const A& super, const B& sub, const char* file, const int line) {
            auto result = impl_set::superset(super, sub, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectStrictSubset(const A& sub, const B& super, const char* file, const int line) {
            auto result = impl_set::strictSubset(sub, super, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
    }
}

#endif