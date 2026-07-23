#pragma once

#ifndef ITER_UNORDER_H
#define ITER_UNORDER_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include <algorithm>
#include <optional>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

namespace internal {
    namespace impl_iter {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo>
        unorderedEquals(const A& first, const B& second, const char* file, const uint32_t line)
        {
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

            using a_val = std::ranges::range_value_t<A>;
            using b_val = std::ranges::range_value_t<B>;

            if constexpr (Concepts::Hashable<a_val> && Concepts::Hashable<b_val> 
                && Concepts::HasEQ<a_val, b_val>)
            {
                return unorderedEqualsHashable(first, second, file, line);
            } else if constexpr (Concepts::HasLT<a_val, b_val>) 
            {
                return unorderedEqualsLessThan(first, second, file, line);
            } else 
            {
                return unorderedEqualsGeneral(first, second, file, line);
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::Hashable<std::ranges::range_value_t<A>>
            && Concepts::Hashable<std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline std::optional<Core::FailureInfo> 
        unorderedEqualsHashable(const A& first, const B& second, const char* file, const uint32_t line)
        {
            using a_val = std::ranges::range_value_t<A>;
            using b_val = std::ranges::range_value_t<B>;

            using T = std::common_type_t<a_val, b_val>;
            std::unordered_map<T, size_t> counts;

            for (const a_val& a_val : first) {
                counts[a_val]++;
            }

            auto b_itr = std::ranges::cbegin(second);
            auto b_end = std::ranges::cend(second);
            for (; b_itr != b_end; ++b_itr) {
                if (counts[*b_itr] == 0) {
                    return Core::FailureInfo({
                        std::string("Mismatched element: ") + Helpers::toString(*b_itr),
                        file,
                        line
                    });
                } else {
                    counts[*b_itr]--;
                }
            }

            for (const auto& [key, count] : counts) {
                if (count != 0) {
                    return Core::FailureInfo({
                        std::string("Mismatched element: ") + Helpers::toString(key),
                        file,
                        line
                    });
                }
            }

            return std::nullopt;
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::HasLT<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline std::optional<Core::FailureInfo>
        unorderedEqualsLessThan(const A& first, const B& second, const char* file, const uint32_t line)
        {
            using a_val = std::ranges::range_value_t<A>;
            using b_val = std::ranges::range_value_t<B>;

            std::vector<a_val> a_vals(std::ranges::begin(first), std::ranges::end(first));
            std::vector<b_val> b_vals(std::ranges::begin(second), std::ranges::end(second));

            std::sort(a_vals.begin(), a_vals.end());
            std::sort(b_vals.begin(), b_vals.end());

            size_t size = a_vals.size();

            for (size_t i = 0; i < size; i++) {
                if (a_vals[i] != b_vals[i]) {
                    return Core::FailureInfo({
                        std::string("Mismatched element: ") + Helpers::toString(a_vals[i]),
                        file,
                        line
                    });
                }
            }

            return std::nullopt;
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline std::optional<Core::FailureInfo> 
        unorderedEqualsGeneral(const A& first, const B& second, const char* file, const uint32_t line)
        {
            //since this function is being called, first and second have the same size
            std::vector<bool> used(std::ranges::size(first));

            auto a_itr = std::ranges::begin(first);

            auto a_end = std::ranges::end(first);
            auto b_end = std::ranges::end(second);

            for (; a_itr != a_end; ++a_itr) {
                size_t idx = 0;
                auto b_itr = std::ranges::begin(second);
                bool found = false;
                for (; b_itr != b_end; ++b_itr, ++idx) {
                    if (*b_itr == *a_itr) {
                        if (!used[idx]) {
                            used[idx] = true;
                            found = true;
                            break;
                        }
                    } 
                }

                if (!found) {
                    return Core::FailureInfo({
                        std::string("Missing element: ") + Helpers::toString(*a_itr),
                        file,
                        line
                    });
                }
            }

            for (size_t i = 0; i < used.size(); i++) {
                if (!used[i]) {
                    return Core::FailureInfo({
                        "Collections not equivalent",
                        file,
                        line
                    });
                }
            }

            return std::nullopt;
        }

        // This can also be optimized the same way unorderedEquals is optimized
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo>
        unorderedUnequals(const A& first, const B& second, const char* file, const uint32_t line)
        {
            size_t size_a = std::ranges::size(first);
            size_t size_b = std::ranges::size(second);

            if (size_a == size_b) {
                std::vector<bool> used(size_a);

                auto a_itr = std::ranges::begin(first);

                auto a_end = std::ranges::end(first);
                auto b_end = std::ranges::end(second);

                for (; a_itr != a_end; ++a_itr) {
                    size_t idx = 0;
                    auto b_itr = std::ranges::begin(second);
                    bool found = false;
                    for (; b_itr != b_end; ++b_itr, ++idx) {
                        if (*b_itr == *a_itr) {
                            if (!used[idx]) {
                                used[idx] = true;
                                found = true;
                                break;
                            }
                        } 
                    }

                    //if there's an element in a that's not in b, then they aren't equal => return
                    if (!found) {
                        return std::nullopt;
                    }
                }

                //unnecessary, but will keep just in case I'm wrong
                // for (size_t i = 0; i < used.size(); i++) {
                //     if (!used[i]) {
                //         return std::nullopt;
                //     }
                // }

                return Core::FailureInfo({
                    "Collections are equivalent",
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif