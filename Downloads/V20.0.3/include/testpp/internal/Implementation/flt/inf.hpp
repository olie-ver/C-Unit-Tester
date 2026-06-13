#pragma once

#ifndef FLT_INF_H
#define FLT_INF_H

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
            isInf(const T& val, const char* file, uint32_t line)
        {
            if (std::isnan(val)) {
                return Core::FailureInfo("First parameter is NaN", file, line);
            }

            if (!std::isinf(val)) {
                return Core::FailureInfo({
                    std::string("Expected val to be inf \n      val = " + Helpers::toString(val)),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline std::optional<const Core::FailureInfo> 
            isPosInf(const T& val, const char* file, uint32_t line)
        {
            if (std::isnan(val)) {
                return Core::FailureInfo("First parameter is NaN", file, line);
            }

            if (!std::isinf(val)) {
                return Core::FailureInfo({
                    std::string("Expected val to be positive infinity but it wasn't \n      val = " 
                        + Helpers::toString(val)),
                    file,
                    line
                });

            } else if (std::isinf(val) && val < 0.0) {
                return Core::FailureInfo({
                    std::string("Expected val to be positive infinity, but it wasn't \n      val = " 
                        + Helpers::toString(val)),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline std::optional<const Core::FailureInfo> 
            isNegInf(const T& val, const char* file, uint32_t line)
        {
            if (std::isnan(val)) {
                return Core::FailureInfo("First parameter is NaN", file, line);
            }

            if (!std::isinf(val)) {
                return Core::FailureInfo({
                    std::string("Expected val to be negative infinity but it wasn't \n      val = "
                        + Helpers::toString(val)),
                    file,
                    line
                });
            } else if (std::isinf(val) && val > 0.0) {
                return Core::FailureInfo({
                    std::string("Expected val to be negative infinity, but it wasn't \n      val = "
                        + Helpers::toString(val)),
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif