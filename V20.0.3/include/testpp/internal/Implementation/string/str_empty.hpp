#pragma once

#ifndef STR_EMPTY_H
#define STR_EMPTY_H

#include "../../Core.hpp"
#include "../../Helpers.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_str {
        std::optional<const Core::FailureInfo> 
        inline stringEmpty(const std::string& first, const char* file, const uint32_t line)
        {
            if (!first.empty()) {
                return Core::FailureInfo(
                    "Expected string to be empty, but wasn't: first = " + first,
                    file,
                    line
                ); 
            }

            return std::nullopt;
        }

        std::optional<const Core::FailureInfo> 
        inline stringEmpty(const char* first, const char* file, const uint32_t line)
        {
            if (first == nullptr) {
                return Core::FailureInfo(
                    "nullptr passed in",
                    file,
                    line
                );
            }

            if (first[0] != '\0') {
                return Core::FailureInfo(
                    std::string("Expected string to be empty, but wasn't: first = ") + first,
                    file,
                    line
                ); 
            }

            return std::nullopt;
        }

        template <size_t N>
        std::optional<const Core::FailureInfo> 
        inline stringEmpty(const char(&first)[N], const char* file, const uint32_t line)
        {
            if (first[0] != '\0') {
                char a[N + 1];
                std::copy(std::begin(first), std::end(first), std::begin(a));
                a[N] = '\0';
                return Core::FailureInfo({
                    std::string("Expected string to be empty, but wasn't: first = ") + a,
                    file,
                    line
                }); 
            }

            return std::nullopt;
        }

        std::optional<const Core::FailureInfo>
        inline stringNotEmpty(const std::string& first, const char* file, const uint32_t line)
        {
            if (first.empty()) {
                return Core::FailureInfo(
                    "Expected string to not be empty, but was",
                    file,
                    line
                ); 
            }

            return std::nullopt;
        }

        std::optional<const Core::FailureInfo> 
        inline stringNotEmpty(const char* first, const char* file, const uint32_t line)
        {
            if (first == nullptr) {
                return Core::FailureInfo(
                    "nullptr passed in",
                    file,
                    line
                );
            }

            if (first[0] == '\0') {
                return Core::FailureInfo(
                    std::string("Expected string to not be empty, but was"),
                    file,
                    line
                ); 
            }

            return std::nullopt;
        }

        template <size_t N>
        inline std::optional<const Core::FailureInfo> 
        stringNotEmpty(const char(&first)[N], const char* file, const uint32_t line)
        {
            if (first[0] == '\0') {
                return Core::FailureInfo({
                    std::string("Expected string to not be empty, but was"),
                    file,
                    line
                }); 
            }
            
            return std::nullopt;
        }
    }
}

#endif