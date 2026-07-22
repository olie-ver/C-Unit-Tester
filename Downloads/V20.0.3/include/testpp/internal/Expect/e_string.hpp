#pragma once

#ifndef E_STR_H
#define E_STR_H

#include "../PCH/impl_pch.hpp"

#include "../Fail.hpp"

#define EXPECT_STR_EQ(first, second) internal::Expects::expectStringEquals((first), (second), __FILE__, __LINE__)
#define EXPECT_STR_NE(first, second) internal::Expects::expectStringNotEquals((first), (second), __FILE__, __LINE__)
#define EXPECT_STR_EMT(first) internal::Expects::expectStringEmpty((first), __FILE__, __LINE__)
#define EXPECT_STR_NEMT(first) internal::Expects::expectStringNotEmpty((first), __FILE__, __LINE__)
#define EXPECT_STR_CONTAINS(first, substr) internal::Expects::expectStringContains((first), (substr), __FILE__, __LINE__)
#define EXPECT_STR_STARTS_WITH(first, substr) internal::Expects::expectStringStartsWith((first), (substr), __FILE__, __LINE__)
#define EXPECT_STR_ENDS_WITH(first, substr) internal::Expects::expectStringEndsWith((first), (substr), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        /// @brief An Expects test that checks if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringEquals(const std::string& first, const std::string& second, 
            const char* file, const int line) 
        {
            auto result = impl_str::stringEquals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that checks if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringEquals(const char* first, const char* second, 
            const char* file, const int line) 
        {
            auto result = impl_str::stringEquals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that checks if two strings are equal
        /// @tparam N the length of the first string
        /// @tparam M the length of the second string
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N, size_t M>
        inline void expectStringEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const int line) 
        {
            auto result = impl_str::stringEquals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that checks if two strings are not equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringNotEquals(const std::string& first, 
            const std::string& second, 
            const char* file, 
            const int line) 
        {
            auto result = impl_str::stringNotEquals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that checks if two strings are not equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringNotEquals(
            const char* first, 
            const char* second, 
            const char* file,
            const int line) 
        {
            auto result = impl_str::stringNotEquals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that checks if two strings are not equal
        /// @tparam N the length of the first string
        /// @tparam M the length of the second string
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N, size_t M>
        inline void expectStringNotEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const int line) 
        {
            auto result = impl_str::stringNotEquals(first, second, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that tests if a string is empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringEmpty(const std::string& first, const char* file, const int line) {
            auto result = impl_str::stringEmpty(first, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that tests if a string is empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringEmpty(const char* first, const char* file, const int line) {
            auto result = impl_str::stringEmpty(first, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that tests if a string is empty
        /// @tparam N the size of the array
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N>
        inline void expectStringEmpty(const char(&first)[N], const char* file, const int line) {
            auto result = impl_str::stringEmpty(first, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that tests if a string is not empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringNotEmpty(const std::string& first, const char* file, const int line) {
            auto result = impl_str::stringNotEmpty(first, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that tests if a string is not empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringNotEmpty(const char* first, const char* file, const int line) {
            auto result = impl_str::stringNotEmpty(first, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test that tests if a string is not empty
        /// @tparam N the size of the array
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N>
        inline void expectStringNotEmpty(const char(&first)[N], const char* file, const int line) {
            auto result = impl_str::stringNotEmpty(first, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for if a string contains another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void expectStringContains(const std::string& first, const std::string& substr,
            const char* file, const int line)
        {
            auto result = impl_str::stringContains(first, substr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for if a string contains another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void expectStringContains(const char* first, const char* substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringContains(first, substr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for if a string contains another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <size_t N, size_t M>
        inline void expectStringContains(const char(&first)[N], const char(&substr)[M], 
            const char* file, const int line)
        {
            auto result = impl_str::stringContains(first, substr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for if a string starts with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void expectStringStartsWith(const std::string& first, const std::string& substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringStartsWith(first, substr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for if a string starts with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void expectStringStartsWith(const char* first, const char* substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringStartsWith(first, substr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for if a string starts with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <size_t N, size_t M>
        inline void expectStringStartsWith(const char(&first)[N], const char(&substr)[M],
            const char* file, const int line)
        {
            auto result = impl_str::stringStartsWith(first, substr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for if a string ends with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void expectStringEndsWith(const std::string& first, const std::string& substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringEndsWith(first, substr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for if a string ends with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        inline void expectStringEndsWith(const char* first, const char* substr, 
            const char* file, const int line)
        {
            auto result = impl_str::stringEndsWith(first, substr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
        
        /// @brief An Expects test for if a string ends with another string
        /// @param first the "super" string
        /// @param substr the substring
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <size_t N, size_t M>
        inline void expectStringEndsWith(const char(&first)[N], const char(&substr)[M],
            const char* file, const int line)
        {
            auto result = impl_str::stringEndsWith(first, substr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
    }
}

#endif