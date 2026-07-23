#pragma once

#ifndef THROWS_H
#define THROWS_H

#include "../Core.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_throws {
        template <typename Func>
        inline std::optional<Core::FailureInfo> 
            void_throws(Func&& func, const char* funcName, const char* file, uint32_t line)
        {
            try {
                func();
                return Core::FailureInfo({
                    std::string("Expected function \"") + funcName 
                    + std::string("\" to throw an exception, but it didn't"),
                    file,
                    line
                });
            }
            catch (...) { }
        
            return std::nullopt; 
        }

        template <typename Expected = void, typename Func>
        inline std::optional<Core::FailureInfo> 
            type_throws(Func&& func, const char* funcName, const char* file, uint32_t line)
        {
            try {
                func();
                return Core::FailureInfo({
                    std::string("Expected function \"") + funcName 
                    + std::string("\" to throw an exception, but it didn't"),
                    file,
                    line
                });
            } catch (const Expected& ex) {

            } catch (...) {
                std::string actualType = "unknown";
                std::string expectedType = Helpers::demangle(typeid(Expected).name());

                try {
                    throw;
                } catch (const std::exception& ex) {
                    actualType = Helpers::demangle(typeid(ex).name());
                } catch (...) {
                    actualType = "non-std::exception";
                }

                return Core::FailureInfo({
                    std::string("Expected function \"") + funcName +
                    "\" to throw exception of expected type: \"" 
                        + expectedType 
                        + "\" but got: \"" 
                        + actualType +'\"',
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename Expected = void, typename Func>
        inline std::optional<Core::FailureInfo> 
            throws(Func&& func, const char* funcName, const char* file, uint32_t line)
        {
            if constexpr (std::is_same_v<Expected, void>) {
                return void_throws(func, funcName, file, line);
            } else {
                return type_throws<Expected>(func, funcName, file, line);
            }
        }

        template <typename Func>
        inline std::optional<const Core::FailureInfo> 
            throwsWithMessage(Func&& func, const char* funcName, 
                const std::string& message, const char* file, const uint32_t line)
        {
            try {
                func();
                return Core::FailureInfo({
                    std::string("Expected ") + funcName + " to throw an error, but it didn't",
                    file, 
                    line
                });
            } catch (const std::exception& ex) {
                std::string what(ex.what());
                if (message != what) {
                    return Core::FailureInfo({
                        std::string("Expected ") + funcName + " to throw an error with message: " 
                            +  message + ", but it threw with message: " + what,
                        file, 
                        line
                    });
                }
            } catch (std::string what) {
                if (message != what) {
                    return Core::FailureInfo({
                        std::string("Expected ") + funcName + " to throw an error with message: " 
                            +  message + ", but it threw with message: " + what,
                        file, 
                        line
                    });
                }
            } catch (...) {
                return Core::FailureInfo({
                    funcName + std::string(" threw an unknown exception type"),
                    file, 
                    line
                });
            }

            return std::nullopt;
        }

        template <typename Func>
        inline std::optional<const Core::FailureInfo> 
        doesNotThrow(Func&& func, const char* funcName, const char* file, uint32_t line) {
            try {
                func();
            } catch (const std::exception& ex){
                return Core::FailureInfo({
                    std::string("Expected function \"") + funcName 
                    + std::string("\" to not throw an exception, but it did\n") 
                    + std::string("    Error message: \"") + ex.what() + "\"",
                    file,
                    line
                });
            } catch (...) {
                return Core::FailureInfo({
                    std::string("Expected function \"") + funcName 
                    + std::string("\" to not throw an exception, but it did\n") 
                    + std::string("    Exception type: unknown"),
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif