#pragma once

#ifndef STR_H
#define STR_H

#include "../Core.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_str {
        std::optional<const Core::FailureInfo> 
        stringEquals(const std::string& first, const std::string& second, 
            const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo> 
        stringEquals(const char* first, const char* second, 
            const char* file, const uint32_t line); 

        template <size_t N, size_t M>
        std::optional<const Core::FailureInfo> 
        stringEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo> 
        stringNotEquals(const std::string& first, const std::string& second, 
            const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo> 
        stringNotEquals(const char* first, const char* second, 
            const char* file, const uint32_t line);

        template <size_t N, size_t M>
        std::optional<const Core::FailureInfo> 
        stringNotEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo> 
        stringEmpty(const std::string& first, const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo> 
        stringEmpty(const char* first, const char* file, const uint32_t line);

        template <size_t N>
        std::optional<const Core::FailureInfo> 
        stringEmpty(const char(&first)[N], const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo>
        stringNotEmpty(const std::string& first, const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo> 
        stringNotEmpty(const char* first, const char* file, const uint32_t line);

        template <size_t N>
        std::optional<const Core::FailureInfo> 
        stringNotEmpty(const char(&first)[N], const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo> 
        stringContains(const std::string& first, const std::string& substr,
            const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo>
        stringContains(const char* first, const char* substr, 
            const char* file, const uint32_t line);

        template <size_t N, size_t M>
        std::optional<const Core::FailureInfo>
        stringContains(const char(&first)[N], const char(&substr)[M], 
            const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo>
        stringStartsWith(const std::string& first, const std::string& substr, 
            const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo>
        stringStartsWith(const char* first, const char* substr, 
            const char* file, const uint32_t line);

        template <size_t N, size_t M>
        std::optional<const Core::FailureInfo>
        stringStartsWith(const char(&first)[N], const char(&substr)[M],
            const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo>
        stringEndsWith(const std::string& first, const std::string& substr, 
            const char* file, const uint32_t line);

        std::optional<const Core::FailureInfo> 
        stringEndsWith(const char* first, const char* substr, 
            const char* file, const uint32_t line);

        template <size_t N, size_t M>
        std::optional<const Core::FailureInfo> 
        stringEndsWith(const char(&first)[N], const char(&substr)[M],
            const char* file, const uint32_t line);
    }
}

#include "string/str_contains.hpp"
#include "string/str_empty.hpp"
#include "string/str_eq.hpp"
#include "string/str_ne.hpp"
#include "string/str_start_end.hpp"

#endif