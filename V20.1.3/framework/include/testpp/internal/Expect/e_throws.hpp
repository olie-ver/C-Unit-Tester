#pragma once

#ifndef E_THROWS_H
#define E_THROWS_H

#include "../PCH/impl_pch.hpp"

#include "../Runner.hpp"
#include "../Helpers.hpp"

#define EXPECT_THROWS_1_ARGS(func) internal::Expects::expectThrows([&]() {(func);}, #func, __FILE__, __LINE__)
#define EXPECT_THROWS_2_ARGS(func, ex) internal::Expects::expectThrows<ex>([&]() {(func);}, #func, __FILE__, __LINE__)

#define GET_3RD_ARG(arg1, arg2, arg3, ...) arg3

#define EXPECT_THROWS_MACRO_CHOOSER(...) \
    GET_3RD_ARG(__VA_ARGS__, EXPECT_THROWS_2_ARGS, EXPECT_THROWS_1_ARGS)

//The actual tests
#define EXPECT_THROWS(...) EXPECT_THROWS_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
#define EXPECT_DOES_NOT_THROW(func) internal::Expects::expectDoesNotThrow([&](){(func);}, #func, __FILE__, __LINE__)
#define EXPECT_THROWS_MSG(func, message) \
    internal::Expects::expectThrowsWithMessage([&](){(func);}, #func, (message), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        /// @brief Checks if the passed in function throws an error, or a specified error
        /// @tparam Expected the expected thing that should be throw 
        /// @tparam Func the function type
        /// @param func the function
        /// @param funcName the name of the function
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <typename Expected = void, typename Func>
        inline void expectThrows(Func&& func, const char* funcName, const char* file, int line) {
            auto result = impl_throws::throws<Expected>(func, funcName, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for throwing an error with a message
        /// @tparam Func the function type
        /// @param func the function being tested
        /// @param funcName the name of the function
        /// @param message the message it should throw with
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <typename Func>
        inline void expectThrowsWithMessage(Func&& func, const char* funcName, 
            const std::string& message, const char* file, const int line)
        {
            auto result = impl_throws::throwsWithMessage(func, funcName, message, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief Checks that the passed in function doesn't throw anything
        /// @tparam Func the function's type
        /// @param func the passed in function
        /// @param funcName the name of the function
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <typename Func>
        inline void expectDoesNotThrow(Func&& func, const char* funcName, const char* file, int line) {
            auto result = impl_throws::doesNotThrow(func, funcName, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
    }
}

#endif