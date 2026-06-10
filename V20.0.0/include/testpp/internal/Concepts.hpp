#pragma once

#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <ranges>

namespace internal {
    namespace Concepts {
        //A concept for types with == defined
        template <typename A, typename B>
        concept HasEQ = requires(A a, B b) {
            { a == b } -> std::convertible_to<bool>;
        };

        //A concept for types with != defined
        template <typename A, typename B>
        concept HasNE = requires(A a, B b) {
            { a != b } -> std::convertible_to<bool>;
        };

        //A concept for types with < defined
        template <typename A, typename B>
        concept HasLT = requires(A a, B b) {
            { a < b } -> std::convertible_to<bool>;
        };

        //A concept for types with <= defined
        template <typename A, typename B>
        concept HasLE = requires(A a, B b) {
            { a <= b } -> std::convertible_to<bool>;
        };

        //A concept for types with > defined
        template <typename A, typename B>
        concept HasGT = requires(A a, B b) {
            { a > b } -> std::convertible_to<bool>;
        };

        //A concept for types with >= defined
        template <typename A, typename B>
        concept HasGE = requires(A a, B b) {
            { a >= b } -> std::convertible_to<bool>;
        };

        //A concept for types that can be nullable
        template <typename T>
        concept Nullable = std::is_pointer_v<std::decay_t<T>> || //is a raw pointer or decays to a raw pointer
            std::is_null_pointer_v<std::decay_t<T>> || //or it decays to nullptr
            requires(T t) { t.get(); } || //has .get() like a smart pointer
            requires(T t) { { t.has_value() } -> std::convertible_to<bool>; }; //has .has_value() like an optional


        //A concept for a common floating point type
        template <typename A, typename B, typename C, typename D>
        concept CommonFloat = requires() {
            std::is_floating_point<std::common_type<A, B, C, D>>::value;
        };

        //A concept for types that are iterable and the types of what they contain are comparable by ==
        template <typename A, typename B>
        concept IterableAndComparable = requires()
        {
            std::ranges::range<A>;
            std::ranges::range<B>;
            HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>;
        };

        //A concept for types that are hashable
        template <typename A>
        concept Hashable = requires(A& a) {
            { std::hash<A>{}(a) } -> std::convertible_to<size_t>;
        };

        //A concept for types that have a size
        template <typename A>
        concept Sizeable = requires(A& a) {
            { a.size() } ->  std::convertible_to<size_t>;
        };
    }
}

#endif