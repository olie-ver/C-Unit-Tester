#pragma once

#ifndef BOOL_H
#define BOOL_H

#include "../Core.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_bool {
        inline std::optional<const Core::FailureInfo> True(const bool cond, const char* expr,
            const char* file, const uint32_t line)
        {
            if (!cond) {
                return Core::FailureInfo(
                    "Expected: " + std::string(expr) + " to be true", //message
                    file, //file
                    line, //line
                    expr, //expression
                    "true", //expected
                    "false" //actual
                );
            }

            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> False(const bool cond, const char* expr,
            const char* file, const uint32_t line)
        {
            if (cond) {
                return Core::FailureInfo(
                    "Expected: " + std::string(expr) + " to be false", //message
                    file, //file
                    line, //line
                    expr, //expression
                    "false", //expected
                    "true" //actual
                );
            }

            return std::nullopt;
        }
    }
}

#endif