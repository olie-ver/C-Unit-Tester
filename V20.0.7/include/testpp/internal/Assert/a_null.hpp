#pragma once

#ifndef A_NULL_H
#define A_NULL_H

#include "../PCH/impl_pch.hpp"

#include "../Concepts.hpp"
#include "../Fail.hpp"

#define ASSERT_NULL(val) internal::Assert::assertNull((val), __FILE__, __LINE__)
#define ASSERT_NOT_NULL(val) internal::Assert::assertnotNull((val), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief An Assert test to assert if something is the nullptr
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Nullable<T>
        inline void assertNull(const T& val, const char* file, const int line) {
            auto result = impl_null::Null(val, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test to assert if something is not the nullptr
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Nullable<T>
        inline void assertNotNull(const T& val, const char* file, const int line) {
            auto result = impl_null::NotNull(val, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif