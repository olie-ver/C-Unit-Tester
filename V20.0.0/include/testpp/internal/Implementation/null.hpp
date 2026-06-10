#pragma once

#ifndef NULL_H
#define NULL_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_null {
        template <typename T>
        requires Concepts::Nullable<T>
        inline std::optional<const Core::FailureInfo> 
            Null(const T& val, const char* file, const uint32_t line) 
        {
            if constexpr (std::is_pointer_v<T>) {
                if (val != nullptr) {
                    return Core::FailureInfo({
                        "Expected val to be nullptr.\n val = " + Helpers::toString(val),
                        file,
                        line
                    });
                }
            } else if constexpr (requires { val.get(); }) {
                if (val.get() != nullptr) {
                    return Core::FailureInfo({
                        "Expected val to be nullptr.\n val = " + Helpers::toString(val.get()),
                        file,
                        line
                    });
                }
            } else if constexpr (requires { val.has_value(); }) {
                if (val.has_value()) {
                    return Core::FailureInfo({
                        "Expected val to be nullptr.\n val = " + Helpers::toString(*val),
                        file,
                        line
                    });
                }
            }

            return std::nullopt;
        }

        template <typename T>
        requires Concepts::Nullable<T>
        inline std::optional<const Core::FailureInfo> 
            NotNull(const T& val, const char* file, const uint32_t line)
        {
            if constexpr (std::is_pointer_v<T>) {
                if (val == nullptr) {
                    return Core::FailureInfo(
                        "Expected val to be nullptr.\n val = nullptr",
                        file,
                        line
                    );
                }
            } else if constexpr (requires { val.get(); }) {
                if (val.get() == nullptr) {
                    return Core::FailureInfo(
                        "Expected val to be nullptr.\n val = nullptr",
                        file,
                        line
                    );
                }
            } else if constexpr (requires { val.has_value(); }) {
                if (!val.has_value()) {
                    return Core::FailureInfo(
                        "Expected val to be nullptr.\n val = nullopt",
                        file,
                        line
                    );
                }
            }

            return std::nullopt;
        }
    }
}

#endif