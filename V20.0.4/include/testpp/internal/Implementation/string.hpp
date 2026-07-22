#pragma once

#ifndef STR_H
#define STR_H

#include "../Core.hpp"
#include <optional>
#include <string>
#include <string_view>

namespace internal {
    namespace impl_str {
        inline std::optional<const Core::FailureInfo> 
        stringEquals(const std::string_view& first, const std::string_view& second, 
            const char* file, const uint32_t line)
        {
            if (first != second) {
                std::string message;
                message.reserve(first.size() + second.size() + 64);
                message += "Expected first == second";
                message += "\n    first = \"";
                message += first;
                message += "\"\n    second = \"";
                message += second;
                message += '\"';

                return Core::FailureInfo(
                    message,
                    file,
                    line
                ); 
            }
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        stringNotEquals(const std::string_view& first, const std::string_view& second, 
            const char* file, const uint32_t line)
        {
            if (first == second) {
                std::string message;
                message.reserve(first.size() + second.size() + 64);
                message += "Expected first == second";
                message += "\n    first = \"";
                message += first;
                message += "\"\n    second = \"";
                message += second;
                message += '\"';

                return Core::FailureInfo(
                    message,
                    file,
                    line
                ); 
            }
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        stringEmpty(const std::string_view& first, const char* file, const uint32_t line)
        {
            if (!first.empty()) {
                std::string message;
                message.reserve(first.size() + 64);
                message += "Expected string to be empty, but wasn't: first = ";
                message += first;

                return Core::FailureInfo(
                    message,
                    file,
                    line
                ); 
            }

            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo>
        stringNotEmpty(const std::string_view& first, const char* file, const uint32_t line)
        {
            if (first.empty()) {
                std::string message;
                message.reserve(first.size() + 64);
                message += "Expected string to be nonempty, but wasn't: first = ";
                message += first;

                return Core::FailureInfo(
                    message,
                    file,
                    line
                ); 
            }

            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo>
        stringContains(const std::string_view& first, const std::string_view& substr,
            const char* file, const uint32_t line) 
        {
            if (first.find(substr) == std::string_view::npos) {
                std::string message;
                message.reserve(first.size() + substr.size() + 64);

                message += "Expected: \"";
                message += first;
                message += "\"\nto contain: \"";
                message += substr;
                message += "\"\nbut it didn't";

                return Core::FailureInfo(message, file, line);
            }

            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo>
        stringStartsWith(const std::string_view& first, const std::string_view& substr, 
            const char* file, const uint32_t line)
        {
            if (!first.starts_with(substr)) {
                std::string message;
                message.reserve(first.size() + substr.size() + 64);

                message += "Expected: \"";
                message += first;
                message += "\"\nto start with: \"";
                message += substr;
                message += "\"\nbut it didn't";

                return Core::FailureInfo(message, file, line);
            }
            
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo>
        stringEndsWith(const std::string_view& first, const std::string_view& substr, 
            const char* file, const uint32_t line)
        {
            if (!first.ends_with(substr)) {
                std::string message;
                message.reserve(first.size() + substr.size() + 64);

                message += "Expected: \"";
                message += first;
                message += "\"\nto end with: \"";
                message += substr;
                message += "\"\nbut it didn't";

                return Core::FailureInfo(message, file, line);
            }

            return std::nullopt;
        }
    }
}

#endif