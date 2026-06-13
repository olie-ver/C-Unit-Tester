#pragma once

#ifndef ITER_ATTR_H
#define ITER_ATTR_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include <algorithm>
#include <optional>
#include <ranges>
#include <string>

namespace internal {
    namespace impl_iter {
        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::FailureInfo>
        empty(const T& container, const char* file, const uint32_t line)
        {
            if (container.size() != 0) {
                return Core::FailureInfo({
                    std::string("Expected container size to be 0, but wasn't. \n" 
                        "     size = " + Helpers::toString(container.size())),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::FailureInfo>
        notEmpty(const T& container, const char* file, const uint32_t line)
        {
            if (container.size() == 0) {
                return Core::FailureInfo({
                    std::string("Expected container size to be positive, but wasn't. \n      size = 0"),
                    file,
                    line
                });
            }
            
            return std::nullopt;
        }

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::FailureInfo>
        size(const T& container, const size_t size, const char* file, const uint32_t line)
        {
            if (container.size() != size) {
                return Core::FailureInfo({
                    std::string("Expected container size to be " 
                        + Helpers::toString(size) + ", but wasn't. \n      size = " 
                        + Helpers::toString(container.size())),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, typename U>
        requires std::ranges::range<T>
        inline std::optional<Core::FailureInfo>
        contains(const T& container, const U& find, const char* file, const uint32_t line)
        {
            static_assert(std::is_same<std::ranges::range_value_t<T>, U>::value);
            auto it = std::find(std::ranges::begin(container), std::ranges::end(container), find);

            if (it == std::ranges::end(container)) {
                return Core::FailureInfo({
                    std::string("The container did not contain the expected value: " 
                        + Helpers::toString(find)),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, typename U>
        requires std::ranges::range<T>
        inline std::optional<Core::FailureInfo>
        doesNotContain(const T& container, const U& find, const char* file, const uint32_t line)
        {
            static_assert(std::is_same<std::ranges::range_value_t<T>, U>::value);
            auto it = std::find(std::ranges::begin(container), std::ranges::end(container), find);

            if (it != std::ranges::end(container)) {
                return Core::FailureInfo({
                    std::string("The container did contained the value: " + Helpers::toString(find)),
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif