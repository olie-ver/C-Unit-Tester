#pragma once

#ifndef STR_CONT_H
#define STR_CONT_H

#include "../../Core.hpp"
#include "../../Helpers.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_str {
        inline std::optional<const Core::FailureInfo> 
        stringContains(const std::string& first, const std::string& substr,
            const char* file, const uint32_t line)
        {
            if (first.find(substr) == std::string::npos) {
                return Core::FailureInfo(
                    std::string("Expected string: " 
                        + first 
                        + " to contain " 
                        + substr 
                        + " but it didn't"
                    ),
                    file,
                    line
                ); 
            }

            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo>
        stringContains(const char* first, const char* substr, 
            const char* file, const uint32_t line)
        {
            bool first_null = first == nullptr;
            bool substr_null = substr == nullptr;

            if (first_null ^ substr_null) {
                return Core::FailureInfo(
                    std::string("Mismatched nullptrs")
                    + "\n    a = nullptr: " + Helpers::toString(first_null)
                    + "\n    b = nullptr:" + Helpers::toString(substr_null),
                    file,
                    line
                );
            }

            return stringContains(std::string(first), std::string(substr), file, line);
        }

        template <size_t N, size_t M>
        inline std::optional<const Core::FailureInfo>
        stringContains(const char(&first)[N], const char(&substr)[M], 
            const char* file, const uint32_t line)
        {
            if (N < M) {
                return Core::FailureInfo({
                    "Substring longer than string to check",
                    file,
                    line
                });
            }

            return stringContains(std::string(first), std::string(substr), file, line);
        }
    }
}

#endif