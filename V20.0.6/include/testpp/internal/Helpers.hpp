#pragma once
#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <sstream>
#include <type_traits>
#include <utility>
#include <ranges>
#include <concepts>
#include <iterator>

#if defined(__clang__) || defined(__GNUG__)
    #include <cxxabi.h>
    #include <cstdlib>
#endif

namespace internal {
    namespace Helpers {

        // -----------------------------
        // Concepts
        // -----------------------------

        template <typename T>
        concept Streamable = requires(std::ostream& os, T a) {
            { os << a } -> std::same_as<std::ostream&>;
        };

        template <typename T>
        concept Range = std::ranges::range<T>;

        template <typename T>
        concept StringLike =
            std::same_as<std::decay_t<T>, std::string> ||
            std::same_as<std::decay_t<T>, std::string_view> ||
            std::same_as<std::decay_t<T>, const char*>;

        // -----------------------------
        // Forward declaration
        // -----------------------------

        template <typename T>
        std::string toString(const T& value);

        // -----------------------------
        // Streamable types
        // -----------------------------

        template <Streamable T>
        std::string toString(const T& value) {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }

        // -----------------------------
        // Pair
        // -----------------------------

        template <typename A, typename B>
        std::string toString(const std::pair<A, B>& p) {
            return "(" + toString(p.first) + ", " + toString(p.second) + ")";
        }

        // -----------------------------
        // Iterable containers (vector, set, etc.)
        // -----------------------------

        template <Range T>
            requires (!StringLike<T> && !Streamable<T>)
        std::string toString(const T& range) {
            std::ostringstream oss;
            oss << "[";

            bool first = true;
            for (const auto& elem : range) {
                if (!first) oss << ", ";
                first = false;
                oss << toString(elem);
            }

            oss << "]";
            return oss.str();
        }

        // -----------------------------
        // Fallback
        // -----------------------------

        template <typename T>
        std::string toString(const T&) {
            return "<unprintable>";
        }

        // -----------------------------
        // Demangle
        // -----------------------------

        inline std::string demangle(const char* name) {
        #if defined(__clang__) || defined(__GNUG__)
            int status = 0;
            char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);

            std::string result = (status == 0 && demangled) ? demangled : name;

            std::free(demangled);
            return result;
        #else
            return name;
        #endif
        }

    }
}

#endif