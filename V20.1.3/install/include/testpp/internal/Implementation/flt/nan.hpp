#pragma once

#ifndef FLT_NAN_H
#define FLT_NAN_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include <cmath>
#include <optional>
#include <string>

namespace internal {
    namespace impl_flt {
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline std::optional<const Core::FailureInfo> 
            isNaN(const T& val, const char* file, uint32_t line) 
        {
            if (!std::isnan(val)) {
                return Core::FailureInfo({
                    std::string("Expected val to be NaN") + "\n      val = " + Helpers::toString(val),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline std::optional<const Core::FailureInfo> 
            isNotNaN(const T& val, const char* file, uint32_t line)
        {
            if (std::isnan(val)) {
                return Core::FailureInfo({
                    "Expected val to not be NaN \n      val = NaN",
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif