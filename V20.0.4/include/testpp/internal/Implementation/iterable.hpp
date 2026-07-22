#pragma once

#ifndef ITER_H
#define ITER_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include <optional>

namespace internal {
    namespace impl_iter {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo> 
        orderedEquals(const A& first, const B& second, const char* file, const uint32_t line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo>
        orderedUnequals(const A& first, const B& second, const char* file, const uint32_t line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo>
        unorderedEquals(const A& first, const B& second, const char* file, const uint32_t line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::Hashable<std::ranges::range_value_t<A>>
            && Concepts::Hashable<std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline std::optional<Core::FailureInfo> 
        unorderedEqualsHashable(const A& first, const B& second, const char* file, const uint32_t line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::HasLT<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline std::optional<Core::FailureInfo>
        unorderedEqualsLessThan(const A& first, const B& second, const char* file, const uint32_t line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline std::optional<Core::FailureInfo> 
        unorderedEqualsGeneral(const A& first, const B& second, const char* file, const uint32_t line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::FailureInfo>
        unorderedUnequals(const A& first, const B& second, const char* file, const uint32_t line);

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::FailureInfo>
        empty(const T& container, const char* file, const uint32_t line);

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::FailureInfo>
        notEmpty(const T& container, const char* file, const uint32_t line);

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::FailureInfo>
        size(const T& container, const size_t size, const char* file, const uint32_t line);

        template <typename T, typename U>
        requires std::ranges::range<T>
        inline std::optional<Core::FailureInfo>
        contains(const T& container, const U& find, const char* file, const uint32_t line);

        template <typename T, typename U>
        requires std::ranges::range<T>
        inline std::optional<Core::FailureInfo>
        doesNotContain(const T& container, const U& find, const char* file, const uint32_t line);
    }
}

#include "iterable/attributes.hpp"
#include "iterable/ordered.hpp"
#include "iterable/unordered.hpp"

#endif