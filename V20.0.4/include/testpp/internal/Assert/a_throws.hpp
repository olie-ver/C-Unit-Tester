#pragma once

#ifndef A_THROWS_H
#define A_THROWS_H

#include "../PCH/impl_pch.hpp"

#include "../Runner.hpp"
#include "../Helpers.hpp"

#define ASSERT_THROWS_1_ARGS(func) internal::Assert::assertThrows([&]() {(func);}, #func, __FILE__, __LINE__)
#define ASSERT_THROWS_2_ARGS(func, ex) internal::Assert::assertThrows<ex>([&]() {(func);}, #func, __FILE__, __LINE__)

#define GET_3RD_ARG(arg1, arg2, arg3, ...) arg3

#define ASSERT_THROWS_MACRO_CHOOSER(...) \
    GET_3RD_ARG(__VA_ARGS__, ASSERT_THROWS_2_ARGS, ASSERT_THROWS_1_ARGS)

//The actual tests
#define ASSERT_THROWS(...) ASSERT_THROWS_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
#define ASSERT_DOES_NOT_THROW(func) internal::Assert::assertDoesNotThrow([&](){(func);}, #func, __FILE__, __LINE__)
#define ASSERT_THROWS_MSG(func, message) \
    internal::Assert::assertThrowsWithMessage([&](){(func);}, #func, (message), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief Checks if the passed in function throws an error, or a specified error
        /// @tparam Expected the expected thing that should be throw 
        /// @tparam Func the function type
        /// @param func the function
        /// @param funcName the name of the function
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <typename Expected = void, typename Func>
        inline void assertThrows(Func&& func, const char* funcName, const char* file, int line) {
            auto result = impl_throws::throws<Expected>(func, funcName, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief An Assert test for throwing an error with a message
        /// @tparam Func the function type
        /// @param func the function being tested
        /// @param funcName the name of the function
        /// @param message the message it should throw with
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <typename Func>
        inline void assertThrowsWithMessage(Func&& func, const char* funcName, 
            const std::string& message, const char* file, const int line)
        {
            auto result = impl_throws::throwsWithMessage(func, funcName, message, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        /// @brief Checks that the passed in function doesn't throw anything
        /// @tparam Func the function's type
        /// @param func the passed in function
        /// @param funcName the name of the function
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <typename Func>
        inline void assertDoesNotThrow(Func&& func, const char* funcName, const char* file, int line) {
            auto result = impl_throws::doesNotThrow(func, funcName, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif