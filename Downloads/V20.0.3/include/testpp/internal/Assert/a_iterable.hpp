#pragma once

#ifndef A_ITER_H
#define A_ITER_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"
#include "../Concepts.hpp"

#define ASSERT_ORDERED_EQ(first, second) \
    internal::Assert::assertOrderedEquals((first), (second), __FILE__, __LINE__)
#define ASSERT_UNORDERED_EQ(first, second) \
    internal::Assert::assertUnorderedEquals((first), (second), __FILE__, __LINE__)

#define ASSERT_ORDERED_NE(first, second) \
    internal::Assert::assertOrderedUnequals((first), (second), __FILE__, __LINE__)

#define ASSERT_UNORDERED_NE(first, second) \
    internal::Assert::assertUnorderedUnequals((first), (second), __FILE__, __LINE__)

#define ASSERT_EMPTY(container) internal::Assert::assertEmpty((container), __FILE__, __LINE__)
#define ASSERT_NEMPTY(container) internal::Assert::assertNotEmpty((container), __FILE__, __LINE__)
#define ASSERT_SIZE(container, size) internal::Assert::assertSize((container), (size), __FILE__, __LINE__)
#define ASSERT_CONTAINS(container, value) internal::Assert::assertContains((container), (value), __FILE__, __LINE__)
#define ASSERT_DOES_NOT_CONTAIN(container, value) \
    internal::Assert::assertDoesNotContain((container), (value), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertOrderedEquals(const A& first, const B& second, 
            const char* file, const int line)
        {
            auto result = impl_iter::orderedEquals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertOrderedUnequals(const A& first, const B& second, const char* file, const int line) {
            auto result = impl_iter::orderedUnequals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertUnorderedEquals(const A& first, const B& second,
            const char* file, const int line) 
        {
            auto result = impl_iter::unorderedEquals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertUnorderedUnequals(const A& first, const B& second, 
            const char* file, const int line)
        {
            auto result = impl_iter::unorderedUnequals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test to check if a container is empty
        /// @tparam T a container that has the .size() method
        /// @param container the container
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Sizeable<T>
        inline void assertEmpty(const T& container, const char* file, const int line) {
            auto result = impl_iter::empty(container, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test to check if a container is empty
        /// @tparam T a container that has the .size() method
        /// @param container the container
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Sizeable<T>
        inline void assertNotEmpty(const T& container, const char* file, const int line) {
            auto result = impl_iter::notEmpty(container, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test to check if a container is has a certain size
        /// @tparam T a container that has the .size() method
        /// @param container the container
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Sizeable<T>
        inline void assertSize(const T& container, const size_t size, const char* file, const int line) {
            auto result = impl_iter::size(container, size, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for seeing if a container contains a value
        /// @tparam T a ranges container
        /// @tparam U the value to be found
        /// @param container a container that fulfills the ranges concept
        /// @param find the value to be found
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T, typename U>
        requires std::ranges::range<T>
        inline void assertContains(const T& container, const U& find, const char* file, const int line) {
            auto result = impl_iter::contains(container, find, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for seeing if a container does not contain a value
        /// @tparam T a ranges container
        /// @tparam U the value to be found
        /// @param container a container that fulfills the ranges concept
        /// @param find the value to be found
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T, typename U>
        requires std::ranges::range<T>
        inline void assertDoesNotContain(const T& container, const U& find, const char* file, const int line) {
            auto result = impl_iter::doesNotContain(container, find, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif