#pragma once

#ifndef A_PRED_H
#define A_PRED_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"

#define ASSERT_ALL(container, condition) \
    internal::Assert::assertAllOf((container), (condition), __FILE__, __LINE__)

#define ASSERT_SOME(container, condition) \
    internal::Assert::assertAnyOf((container), (condition), __FILE__, __LINE__)

#define ASSERT_NONE(container, condition) \
    internal::Assert::assertNoneOf((container), (condition), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void assertAllOf(const T& t, const Func& func, const char* file, const int line) {
            auto result = impl_pred::allOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, size_t N, typename Func>
        inline void assertAllOf(const T(& t)[N], const Func& func, const char* file, const int line) {
            auto result = impl_pred::allOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void assertAnyOf(const T& t, const Func& func, const char* file, const int line) {
            auto result = impl_pred::anyOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, size_t N, typename Func>
        inline void assertAnyOf(const T(& t)[N], const Func& func, const char* file, const int line) {
            auto result = impl_pred::anyOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void assertNoneOf(const T& t, const Func& func, const char* file, const int line) {
            auto result = impl_pred::noneOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, size_t N, typename Func>
        inline void assertNoneOf(const T(& t)[N], const Func& func, const char* file, const int line) {
            auto result = impl_pred::noneOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif