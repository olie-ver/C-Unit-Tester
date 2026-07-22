#pragma once

#ifndef PRED_H
#define PRED_H

#include "../Core.hpp"
#include <optional>
#include <ranges>

namespace internal {
    namespace impl_pred {
        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline std::optional<Core::FailureInfo>
        allOf(const T& t, const Func& func, const char* file, const uint32_t line) {
            if (!std::all_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                return Core::FailureInfo({
                    "Not every element satisfied the passed in condition",
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, size_t N, typename Func>
        inline std::optional<Core::FailureInfo>
        allOf(const T(& t)[N], const Func& func, const char* file, const uint32_t line) {
            if (!std::all_of(t, t + N, func)) {
                return Core::FailureInfo(
                    "Not every element satisfied the passed in condition",
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline std::optional<Core::FailureInfo>
       anyOf(const T& t, const Func& func, const char* file, const uint32_t line) {
            if (!std::any_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                return Core::FailureInfo(
                    "No element satisfied the passed in condition",
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        template <typename T, size_t N, typename Func>
        inline std::optional<Core::FailureInfo>
        anyOf(const T(& t)[N], const Func& func, const char* file, const uint32_t line) {
            if (!std::any_of(t, t + N, func)) {
                return Core::FailureInfo(
                    "No element satisfied the passed in condition",
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline std::optional<Core::FailureInfo>
        noneOf(const T& t, const Func& func, const char* file, const uint32_t line) {
            if (!std::none_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                return Core::FailureInfo(
                    "At least one element satisfied the passed in condition",
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        template <typename T, size_t N, typename Func>
        inline std::optional<Core::FailureInfo>
        noneOf(const T(& t)[N], const Func& func, const char* file, const uint32_t line) {
            if (!std::none_of(t, t + N, func)) {
                return Core::FailureInfo(
                    "At least one element satisfied the passed in condition",
                    file,
                    line
                );
            }

            return std::nullopt;
        }
    }
}

#endif