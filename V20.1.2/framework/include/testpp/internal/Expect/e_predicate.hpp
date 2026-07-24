#pragma once

#ifndef E_PRED_H
#define E_PRED_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"

#define EXPECT_ALL(container, condition) \
    internal::Expects::expectAllOf((container), (condition), __FILE__, __LINE__)

#define EXPECT_SOME(container, condition) \
    internal::Expects::expectAnyOf((container), (condition), __FILE__, __LINE__)

#define EXPECT_NONE(container, condition) \
    internal::Expects::expectNoneOf((container), (condition), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void expectAllOf(const T& t, const Func& func, const char* file, const int line) {
            auto result = impl_pred::allOf(t, func, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename T, size_t N, typename Func>
        inline void expectAllOf(const T(& t)[N], const Func& func, const char* file, const int line) {
            auto result = impl_pred::allOf(t, func, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void expectAnyOf(const T& t, const Func& func, const char* file, const int line) {
            auto result = impl_pred::anyOf(t, func, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename T, size_t N, typename Func>
        inline void expectAnyOf(const T(& t)[N], const Func& func, const char* file, const int line) {
            auto result = impl_pred::anyOf(t, func, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void expectNoneOf(const T& t, const Func& func, const char* file, const int line) {
            auto result = impl_pred::noneOf(t, func, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename T, size_t N, typename Func>
        inline void expectNoneOf(const T(& t)[N], const Func& func, const char* file, const int line) {
            auto result = impl_pred::noneOf(t, func, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
    }
}

#endif