#pragma once

#ifndef A_STR_H
#define A_STR_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"

#define ASSERT_STR_EQ(first, second) internal::Assert::assertStringEquals((first), (second), __FILE__, __LINE__)
#define ASSERT_STR_NE(first, second) internal::Assert::assertStringNotEquals((first), (second), __FILE__, __LINE__)
#define ASSERT_STR_EMT(first) internal::Assert::assertStringEmpty((first), __FILE__, __LINE__)
#define ASSERT_STR_NEMT(first) internal::Assert::assertStringNotEmpty((first), __FILE__, __LINE__)
#define ASSERT_STR_CONTAINS(first, substr) internal::Assert::expectStringContains((first), (substr), __FILE__, __LINE__)
#define ASSERT_STR_STARTS_WITH(first, substr) internal::Assert::expectStringStartsWith((first), (substr), __FILE__, __LINE__)
#define ASSERT_STR_ENDS_WITH(first, substr) internal::Assert::expectStringEndsWith((first), (substr), __FILE__, __LINE__)


namespace internal {
    namespace Assert {
        /// @brief An Assert test that asserts if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringEquals(const std::string& first, const std::string& second, 
            const char* file, const int line) 
        {
            auto result = impl_str::stringEquals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that asserts if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringEquals(const char* first, const char* second, 
            const char* file, const int line) 
        {
            auto result = impl_str::stringEquals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that asserts if two strings are equal
        /// @tparam N the length of the first string
        /// @tparam M the length of the second string
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N, size_t M>
        inline void assertStringEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const int line) 
        {
            auto result = impl_str::stringEquals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that asserts if two strings are not equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringNotEquals(const std::string& first, 
            const std::string& second, 
            const char* file, 
            const int line) 
        {
            auto result = impl_str::stringNotEquals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that asserts if two strings are not equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringNotEquals(
            const char* first, 
            const char* second, 
            const char* file,
            const int line) 
        {
            auto result = impl_str::stringNotEquals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that asserts if two strings are not equal
        /// @tparam N the length of the first string
        /// @tparam M the length of the second string
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N, size_t M>
        inline void assertStringNotEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const int line) 
        {
            auto result = impl_str::stringNotEquals(first, second, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that tests if a string is empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringEmpty(const std::string& first, const char* file, const int line) {
            auto result = impl_str::stringEmpty(first, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that tests if a string is empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringEmpty(const char* first, const char* file, const int line) {
            auto result = impl_str::stringEmpty(first, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that tests if a string is empty
        /// @tparam N the size of the array
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N>
        inline void assertStringEmpty(const char(&first)[N], const char* file, const int line) {
            auto result = impl_str::stringEmpty(first, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that tests if a string is not empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringNotEmpty(const std::string& first, const char* file, const int line) {
            auto result = impl_str::stringNotEmpty(first, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that tests if a string is not empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringNotEmpty(const char* first, const char* file, const int line) {
            auto result = impl_str::stringNotEmpty(first, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test that tests if a string is not empty
        /// @tparam N the size of the array
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N>
        inline void assertStringNotEmpty(const char(&first)[N], const char* file, const int line) {
            auto result = impl_str::stringNotEmpty(first, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for if a string contains another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void assertStringContains(const std::string& first, const std::string& substr,
            const char* file, const int line)
        {
            auto result = impl_str::stringContains(first, substr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for if a string contains another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void assertStringContains(const char* first, const char* substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringContains(first, substr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief an Assert test for if a string contains another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <size_t N, size_t M>
        inline void assertStringContains(const char(&first)[N], const char(&substr)[M], 
            const char* file, const int line)
        {
            auto result = impl_str::stringContains(first, substr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for if a string starts with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void assertStringStartsWith(const std::string& first, const std::string& substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringStartsWith(first, substr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for if a string starts with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void assertStringStartsWith(const char* first, const char* substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringStartsWith(first, substr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for if a string starts with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <size_t N, size_t M>
        inline void assertStringStartsWith(const char(&first)[N], const char(&substr)[M],
            const char* file, const int line)
        {
            auto result = impl_str::stringStartsWith(first, substr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for if a string ends with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void assertStringEndsWith(const std::string& first, const std::string& substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringEndsWith(first, substr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for if a string ends with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void assertStringEndsWith(const char* first, const char* substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringEndsWith(first, substr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
        
        /// @brief An Assert test for if a string ends with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <size_t N, size_t M>
        inline void assertStringEndsWith(const char(&first)[N], const char(&substr)[M],
            const char* file, const int line)
        {
            auto result = impl_str::stringEndsWith(first, substr, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif