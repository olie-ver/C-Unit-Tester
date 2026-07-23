#pragma once

#ifndef ITER_ORDER_H
#define ITER_ORDER_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include <algorithm>
#include <optional>
#include <ranges>
#include <string>

namespace internal {
    namespace impl_iter {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo> 
        orderedEquals(const A& first, const B& second, const char* file, const uint32_t line)
        {
            auto a_itr = std::ranges::cbegin(first);
            auto b_itr = std::ranges::cbegin(second);

            auto a_end = std::ranges::cend(first);

            size_t size_a = std::ranges::size(first);
            size_t size_b = std::ranges::size(second);

            if (size_a != size_b) {
                return Core::FailureInfo({
                    std::string("Size of collections are not the same\n      Size of first: ") 
                    + Helpers::toString(size_a)
                    + std::string("\n      Size of second: ") + Helpers::toString(size_b),
                    file,
                    line
                });
            }

            size_t index = 0;

            for (; a_itr != a_end; ++a_itr, ++b_itr, ++index) {
                auto&& a_val = *a_itr;
                auto&& b_val = *b_itr;

                if (!(a_val == b_val)) {
                    std::string idx = Helpers::toString(index);
                    return Core::FailureInfo({
                        std::string("Mismatch at index = ") + idx
                        + "\n    a[" + idx + "]: " + Helpers::toString(a_val)
                        + "\n    b[" + idx + "]: " + Helpers::toString(b_val),
                        file,
                        line
                    });
                }
            }

            return std::nullopt;
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo>
        orderedUnequals(const A& first, const B& second, const char* file, const uint32_t line)
        {
            namespace ranges = std::ranges;

            auto a_itr = ranges::cbegin(first);
            auto b_itr = ranges::cbegin(second);

            auto a_end = ranges::cend(first);

            size_t size_a = ranges::size(first);
            size_t size_b = ranges::size(second);

            if (size_a != size_b) {
                return Core::FailureInfo({
                    std::string("Size of collections are not the same\n      Size of first: ") 
                    + Helpers::toString(size_a)
                    + std::string("\n      Size of second: ") + Helpers::toString(size_b),
                    file,
                    line
                });
            }

            for (; a_itr != a_end; ++a_itr, ++b_itr) {
                if (!(*a_itr == *b_itr)) {
                    return std::nullopt;
                }
            }

            return Core::FailureInfo({
                "Collections were equal",
                file,
                line
            });
        }
    }
}

#endif