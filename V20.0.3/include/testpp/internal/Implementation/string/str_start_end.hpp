#pragma once

#ifndef STR_START_END_H
#define STR_START_END_H

#include "../../Core.hpp"
#include "../../Helpers.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_str {
        inline std::optional<const Core::FailureInfo>
        stringStartsWith(const std::string& first, const std::string& substr, 
            const char* file, const uint32_t line)
        {
            if (!first.starts_with(substr)) {
                return Core::FailureInfo(
                    std::string("Expected " + first + " to start with " + substr + " but it didn't"),
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo>
        stringStartsWith(const char* first, const char* substr, 
            const char* file, const uint32_t line)
        {
            if (first == nullptr) {
                return Core::FailureInfo(
                    "First string is nullptr",
                    file,
                    line
                );
            } else if (substr == nullptr) {
                return Core::FailureInfo(
                    "Substring is nullptr",
                    file,
                    line
                );
            }

            return stringStartsWith(std::string(first), std::string(substr), file, line);
        }

        template <size_t N, size_t M>
        inline std::optional<const Core::FailureInfo>
        stringStartsWith(const char(&first)[N], const char(&substr)[M],
            const char* file, const uint32_t line)
        {
            if (N < M) {
                return Core::FailureInfo({
                    "Substring longer than string to check",
                    file,
                    line
                });
            }

            return stringStartsWith(std::string(first), std::string(substr), file, line);
        }

        inline std::optional<const Core::FailureInfo>
        stringEndsWith(const std::string& first, const std::string& substr, 
            const char* file, const uint32_t line)
        {
            if (!first.ends_with(substr)) {
                return Core::FailureInfo(
                    std::string("Expected " 
                        + first 
                        + " to start with " 
                        + substr + " but it didn't"
                    ),
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        stringEndsWith(const char* first, const char* substr, 
            const char* file, const uint32_t line)
        {
            if (first == nullptr) {
                return Core::FailureInfo(
                    "First string is nullptr",
                    file,
                    line
                );
            } else if (substr == nullptr) {
                return Core::FailureInfo(
                    "Substring is nullptr",
                    file,
                    line
                );
            }

            return stringEndsWith(std::string(first), std::string(substr), file, line);
        }

        template <size_t N, size_t M>
        inline std::optional<const Core::FailureInfo> 
        stringEndsWith(const char(&first)[N], const char(&substr)[M],
            const char* file, const uint32_t line)
        {
            if (N < M) {
                return Core::FailureInfo({
                    "Substring longer than string to check",
                    file,
                    line
                });
            }

            return stringEndsWith(std::string(first), std::string(substr), file, line);
        }
    }
}

#endif