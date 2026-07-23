#pragma once

#ifndef SET_H
#define SET_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_set {
        inline bool isPresent(auto&& a_itr, auto&& b_itr, auto&& b_end) {
            for (; b_itr != b_end; b_itr++) {
                if (*a_itr == *b_itr) {
                    return true;
                }
            }
            
            return false;
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo> 
        sameSet(const A& a, const B& b, const char* file, const uint32_t line) {
            //everything in A appears in B, and everything in B appears in A
            auto a_itr = std::ranges::cbegin(a);
            auto a_end = std::ranges::cend(a);
            auto b_end = std::ranges::cend(b);

            //check that everything in A appears in B
            for (; a_itr != a_end; ++a_itr) {
                auto b_itr = std::ranges::cbegin(b);

                if (!isPresent(a_itr, b_itr, b_end)) {
                    return Core::FailureInfo({
                        std::string("Element in first not present in second: " 
                            + Helpers::toString(*a_itr)),
                        file,
                        line
                    });
                }
            }

            //check that everything in B appears in A
            auto b_itr = std::ranges::cbegin(b); //get the start of B since we're checking B now
            for (; b_itr != b_end; ++b_itr) {
                a_itr = std::ranges::cbegin(a); //RESET a_itr to point at the beginning again
                if (!isPresent(b_itr, a_itr, a_end)) {
                    return Core::FailureInfo({
                        std::string("Element in second not present in first: " 
                            + Helpers::toString(*b_itr)),
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
        notSameSet(const A& a, const B& b, const char* file, const uint32_t line) {
            //not everything in A appears in B, or not everything in B appears in A

            auto a_itr = std::ranges::cbegin(a);
            auto a_end = std::ranges::cend(a);
            auto b_end = std::ranges::cend(b);

            for (; a_itr != a_end; ++a_itr) {
                auto b_itr = std::ranges::cbegin(b);

                //something in A is not in B => not the same set => return
                if (!isPresent(a_itr, b_itr, b_end)) {
                    return std::nullopt;
                }
            }

            auto b_itr = std::ranges::cbegin(b);

            for (; b_itr != b_end; ++b_itr) {
                a_itr = std::ranges::cbegin(a);

                //something in B is not in A => not the same set => return
                if (!isPresent(b_itr, a_itr, a_end)) {
                    return std::nullopt;
                }
            }

            return Core::FailureInfo({
                "Both sets are the same",
                file,
                line
            });
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo> 
        subset(const A& sub, const B& super, const char* file, const uint32_t line) {
            //everything in sub appears in super
            auto a_itr = std::ranges::cbegin(sub);

            auto a_end = std::ranges::cend(sub);
            auto b_end = std::ranges::cend(super);

            for (; a_itr != a_end; ++a_itr) {
                auto b_itr = std::ranges::cbegin(super);

                if (!isPresent(a_itr, b_itr, b_end)) {
                    return Core::FailureInfo({
                        std::string("Element in first not present in second: " 
                            + Helpers::toString(*a_itr)),
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
        superset(const A& super, const B& sub, const char* file, const uint32_t line) {
            //everything in B appears in A
            auto b_itr = std::ranges::cbegin(sub);

            auto a_end = std::ranges::cend(super);
            auto b_end = std::ranges::cend(sub);

            for (; b_itr != b_end; ++b_itr) {
                auto a_itr = std::ranges::cbegin(super);

                if (!isPresent(b_itr, a_itr, a_end)) {
                    return Core::FailureInfo({
                        std::string("Element in second not present in first: " 
                            + Helpers::toString(*b_itr)),
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
        strictSubset(const A& sub, const B& super, const char* file, const uint32_t line) {
            //everything in A appears in B, but B has at least one element that does not appear in A

            auto a_itr = std::ranges::cbegin(sub);

            auto a_end = std::ranges::cend(sub);
            auto b_end = std::ranges::cend(super);

            for (; a_itr != a_end; ++a_itr) {
                auto b_itr = std::ranges::cbegin(super);
                
                if (!isPresent(a_itr, b_itr, b_end)) {
                    return Core::FailureInfo({
                        std::string("Element in first not present in second: " 
                            + Helpers::toString(*a_itr)),
                        file,
                        line
                    });
                }
            }

            //after this point, everything in A has been found in B
            //now need to check if there's something in B that's not in A

            auto b_itr = std::ranges::cbegin(super);
            for (; b_itr != b_end; ++b_itr) {
                a_itr = std::ranges::cbegin(sub);

                //if there's an element in B that's not in A, 
                //  A is a strict subset => return
                if (!isPresent(b_itr, a_itr, a_end)) {
                    return std::nullopt;
                }
            }

            return Core::FailureInfo({
                "First is not a strict subset of Second (everything in Second is in First)" ,
                file,
                line
            });
        }
    }
}

#endif