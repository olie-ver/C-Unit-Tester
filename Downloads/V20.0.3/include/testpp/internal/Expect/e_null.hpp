#pragma once

#ifndef E_NULL_H
#define E_NULL_H

#include "../PCH/impl_pch.hpp"

#include "../Concepts.hpp"

#define EXPECT_NULL(val) internal::Expects::expectNull((val), __FILE__, __LINE__)
#define EXPECT_NOT_NULL(val) internal::Expects::expectNotNull((val), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        /// @brief An Expects test to check if something is the nullptr
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Nullable<T>
        inline void expectNull(const T& val, const char* file, const int line) {
            auto result = impl_null::Null(val, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test to check if something is not the nullptr
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Nullable<T>
        inline void expectNotNull(const T& val, const char* file, const int line) {
            auto result = impl_null::NotNull(val, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
    }
}

#endif