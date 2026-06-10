#pragma once

#ifndef STR_NE_H
#define STR_NE_H

#include "../../Core.hpp"
#include "../../Helpers.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_str {
        inline std::optional<const Core::FailureInfo> 
        stringNotEquals(const std::string& first, const std::string& second, 
            const char* file, const uint32_t line)
        {
            if (first == second) {
                return Core::FailureInfo(
                    std::string("Expected a == b")
                    + "\n    a = \"" + first + '\"'
                    + "\n    b = \"" + second + '\"',
                    file,
                    line
                );
            }
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        stringNotEquals(const char* first, const char* second, 
            const char* file, const uint32_t line)
        {
            bool first_null = (first == nullptr);
            bool second_null = (second == nullptr);

            if (first_null ^ second_null) {
                return Core::FailureInfo(
                    std::string("Mismatched nullptrs")
                    + "\n    a = nullptr: " + Helpers::toString(first_null)
                    + "\n    b = nullptr:" + Helpers::toString(second_null),
                    file,
                    line
                );
            }

            if (!strcmp(first, second)) {
                return Core::FailureInfo(
                    std::string("Expected a != b")
                    + "\n    a = \"" + first + '\"'
                    + "\n    b = \"" + second + '\"',
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        template <size_t N, size_t M>
        inline std::optional<const Core::FailureInfo> 
        stringNotEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const uint32_t line)
        {
            size_t low_bound = std::min(N, M);

            for (size_t i = 0; i < low_bound; i++) {
                if (first[i] != second[i]) {
                    return std::nullopt;
                }
            }

            //create displayable copies of the parameters
            char a[N + 1];
            char b[M + 1];
            std::copy(std::begin(first), std::end(first), std::begin(a));
            std::copy(std::begin(second), std::end(second), std::begin(b));
            a[N] = '\0';
            b[M] = '\0';

            //they were equal up to low_bound, and if N == M, low_bound == up_bound, hence they're equal
            if (N == M) {
                return Core::FailureInfo({
                    std::string("Expected a != b")
                    + "\n    first = \"" + a + '\"'
                    + "\n    second = \"" + b + '\"',
                    file,
                    line
                });
            }

            //the lengths aren't equal, but they've still been equal, so now need to check if the larger one
            //  terminates or not
            //if the larger one terminates => they are equal, otherwise, they are not equal

            if (low_bound == N && second[low_bound] == '\0') {
                return Core::FailureInfo({
                    std::string("Expected a != b")
                    + "\n    first = \"" + a + '\"'
                    + "\n    second = \"" + b + '\"',
                    file,
                    line
                });
            } else if (low_bound == M && first[low_bound] == '\0') {
                return Core::FailureInfo({
                    std::string("Expected a != b")
                    + "\n    first = \"" + a + '\"'
                    + "\n    second = \"" + b + '\"',
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif