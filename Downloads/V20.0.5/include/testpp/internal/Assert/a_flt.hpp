#pragma once

#ifndef A_FLT_H
#define A_FLT_H

#include "../PCH/impl_pch.hpp"

#include "../Concepts.hpp"

#define ASSERT_NEAR_3_ARGS(first, second, abs_tol) \
    internal::Assert::absolutelyEqual((first), (second), (abs_tol), __FILE__, __LINE__)

#define ASSERT_NEAR_4_ARGS(first, second, abs_tol, rel_tol) \
    internal::Assert::nearlyEqual((first), (second), (abs_tol), (rel_tol), __FILE__, __LINE__)

#define GET_5TH_ARG(arg1, arg2, arg3, arg4, arg5, ...) arg5

#define ASSERT_NEAR_MACRO_CHOOSER(...) \
    GET_5TH_ARG(__VA_ARGS__, ASSERT_NEAR_4_ARGS, ASSERT_NEAR_3_ARGS)

//The actual tests
#define ASSERT_NEAR(...) ASSERT_NEAR_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define ASSERT_REL_NEAR(first, second, rel_tol) \
    internal::Assert::relativelyEqual((first), (second), (rel_tol), __FILE__, __LINE__)

#define ASSERT_ABS_NEAR(first, second, abs_tol) \
    internal::Assert::absolutelyEqual((first), (second), (abs_tol), __FILE__, __LINE__)

#define ASSERT_NAN(number) internal::Assert::isNaN((number), __FILE__, __LINE__)
#define ASSERT_NOT_NAN(number) internal::Assert::isNotNaN((number), __FILE__, __LINE__)

#define ASSERT_INF(number) internal::Assert::isInf((number), __FILE__, __LINE__)
#define ASSERT_POS_INF(number) internal::Assert::isPosInf((number), __FILE__, __LINE__)
#define ASSERT_NEG_INF(number) internal::Assert::isNegInf((number), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief Checks if two floating point values are "close enough" to each other
        /// @tparam A a generic floating point type
        /// @tparam B a generic floating point type
        /// @tparam T1 a generic floating point type
        /// @tparam T2 a generic floating point type
        /// @param a the first value
        /// @param b the second value
        /// @param abs_tol the absolute tolerance
        /// @param rel_tol the relative tolerance
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B, typename T1, typename T2>
        requires Concepts::CommonFloat<A, B, T1, T2>
        inline void nearlyEqual(const A& a, const B& b, const T1& abs_tol, const T2& rel_tol, 
            const char* file, int line)
        {
            auto result = impl_flt::nearlyEqual(a, b, abs_tol, rel_tol, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief Checks if two floating point values are absolutely near to each other
        /// @tparam A a generic floating point type
        /// @tparam B a generic floating point type
        /// @tparam T1 a generic floating point type
        /// @param a the first value
        /// @param b the second value
        /// @param abs_tol the absolute tolerance
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1> //add in an extra T1 to satisfy the concept
        inline void absolutelyEqual(const A& a, const B& b, const T1& abs_tol, 
            const char* file, int line)
        {
            auto result = impl_flt::absolutelyEqual(a, b, abs_tol, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief Checks if two floating point values are relatively near to each other
        /// @tparam A a generic floating point type
        /// @tparam B a generic floating point type
        /// @tparam T1 a generic floating point type
        /// @param a the first value
        /// @param b the second value
        /// @param rel_tol the relative tolerance
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1>
        inline void relativelyEqual(const A& a, const B& b, const T1& rel_tol,
            const char* file, int line)
        {
            auto result = impl_flt::relativelyEqual(a, b, rel_tol, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief Checks if something is NaN
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function is called from
        /// @param line the line the function is called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isNaN(const T& val, const char* file, int line) {
            auto result = impl_flt::isNaN(val, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief Checks if something is not NaN
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function is called from
        /// @param line the line the function is called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isNotNaN(const T& val, const char* file, int line) {
            auto result = impl_flt::isNotNaN(val, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for checking if a floating point value is infinity/negative infinity
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isInf(const T& val, const char* file, const int line) {
            auto result = impl_flt::isInf(val, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for checking if a floating point value is positive infinity
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isPosInf(const T& val, const char* file, const int line) {
            auto result = impl_flt::isPosInf(val, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for checking if a floating point value is negative infinity
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isNegInf(const T& val, const char* file, const int line) {
            auto result = impl_flt::isNegInf(val, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif