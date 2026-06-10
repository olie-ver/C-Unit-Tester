#pragma once

#ifndef STR_EQ_H
#define STR_EQ_H

#include "../../Core.hpp"
#include "../../Helpers.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_str {
        inline std::optional<const Core::FailureInfo> 
        stringEquals(const std::string& first, const std::string& second, 
            const char* file, const uint32_t line) 
        {
            if (first != second) {
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
        stringEquals(const char* first, const char* second, 
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

            if (strcmp(first, second)) {
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

        template <size_t N, size_t M>
        inline std::optional<const Core::FailureInfo> 
        stringEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const uint32_t line)
        {
            //create displayable copies of the parameters
            char a[N + 1];
            char b[M + 1];
            std::copy(std::begin(first), std::end(first), std::begin(a));
            std::copy(std::begin(second), std::end(second), std::begin(b));
            a[N] = '\0';
            b[M] = '\0';

            size_t low_bound = std::min(N, M);
            size_t up_bound = std::max(N, M);

            for (size_t i = 0; i < low_bound; i++) {
                if (first[i] != second[i]) { //both not equal
                    return Core::FailureInfo({
                        std::string("Expected a == b")
                        + "\n    first = \"" + a + '\"'
                        + "\n    second = \"" + b + '\"',
                        file,
                        line
                    });
                } else { //both are equal
                    if (first[i] == '\0') { //both have terminated
                        return std::nullopt;
                    }
                }
            }

            //Both were equal up to the smaller of N and M and neither terminated
            if (N != M) {
                //if the larger char[] doesn't terminate after this point, their lengths are considered
                //  mismatched.
                if (up_bound == N && first[low_bound] != '\0') { //the first string is the larger one
                    return Core::FailureInfo({
                        std::string("Mismatched char[] lengths:")
                        + "\n    length of first = " + Helpers::toString(N)
                        + "\n    length of second = " + Helpers::toString(M),
                        file,
                        line
                    });
                } else if (up_bound == M && second[low_bound] != '\0') {
                    return Core::FailureInfo({
                        std::string("Mismatched char[] lengths:")
                        + "\n    length of first = " + Helpers::toString(N)
                        + "\n    length of second = " + Helpers::toString(M),
                        file,
                        line
                    });
                }
            }
            
            return std::nullopt;
        }
    }
}

#endif