#pragma once

#ifndef E_ITER_H
#define E_ITER_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"
#include "../Concepts.hpp"

#define EXPECT_ORDERED_EQ(first, second) \
    internal::Expects::expectOrderedEquals((first), (second), __FILE__, __LINE__)
#define EXPECT_UNORDERED_EQ(first, second) \
    internal::Expects::expectUnorderedEquals((first), (second), __FILE__, __LINE__)

#define EXPECT_ORDERED_NE(first, second) \
    internal::Expects::expectOrderedUnequals((first), (second), __FILE__, __LINE__)

#define EXPECT_UNORDERED_NE(first, second) \
    internal::Expects::expectUnorderedUnequals((first), (second), __FILE__, __LINE__)

#define EXPECT_EMPTY(container) internal::Expects::expectEmpty((container), __FILE__, __LINE__)
#define EXPECT_NEMPTY(container) internal::Expects::expectNotEmpty((container), __FILE__, __LINE__)
#define EXPECT_SIZE(container, size) internal::Expects::expectSize((container), (size), __FILE__, __LINE__)
#define EXPECT_CONTAINS(container, value) internal::Expects::expectContains((container), (value), __FILE__, __LINE__)
#define EXPECT_DOES_NOT_CONTAIN(container, value) \
    internal::Expects::expectDoesNotContain((container), (value), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectOrderedEquals(const A& first, const B& second, 
            const char* file, const int line)
        {
            auto result = impl_iter::orderedEquals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectOrderedUnequals(const A& first, const B& second, const char* file, const int line) {
            auto result = impl_iter::orderedUnequals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectUnorderedEquals(const A& first, const B& second,
            const char* file, const int line) 
        {
            auto result = impl_iter::unorderedEquals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectUnorderedUnequals(const A& first, const B& second, 
            const char* file, const int line)
        {
            auto result = impl_iter::unorderedUnequals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }


        /// @brief An Expects test to check if a container is empty
        /// @tparam T a container that has the .size() method
        /// @param container the container
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Sizeable<T>
        inline void expectEmpty(const T& container, const char* file, const int line) {
            auto result = impl_iter::empty(container, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test to check if a container is empty
        /// @tparam T a container that has the .size() method
        /// @param container the container
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Sizeable<T>
        inline void expectNotEmpty(const T& container, const char* file, const int line) {
            auto result = impl_iter::notEmpty(container, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test to check if a container is has a certain size
        /// @tparam T a container that has the .size() method
        /// @param container the container
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Sizeable<T>
        inline void expectSize(const T& container, const size_t size, const char* file, const int line) {
            auto result = impl_iter::size(container, size, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for seeing if a container contains a value
        /// @tparam T a ranges container
        /// @tparam U the value to be found
        /// @param container a container that fulfills the ranges concept
        /// @param find the value to be found
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T, typename U>
        requires std::ranges::range<T>
        inline void expectContains(const T& container, const U& find, const char* file, const int line) {
            auto result = impl_iter::contains(container, find, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for seeing if a container does not contain a value
        /// @tparam T a ranges container
        /// @tparam U the value to be found
        /// @param container a container that fulfills the ranges concept
        /// @param find the value to be found
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T, typename U>
        requires std::ranges::range<T>
        inline void expectDoesNotContain(const T& container, const U& find, const char* file, const int line) {
            auto result = impl_iter::doesNotContain(container, find, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
    }
}

#endif