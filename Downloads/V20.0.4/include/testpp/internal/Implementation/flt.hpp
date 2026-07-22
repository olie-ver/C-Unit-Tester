#pragma once

#ifndef FLT_H
#define FLT_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_flt {
        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1>
        std::optional<const Core::FailureInfo> 
            absolutelyEqual(const A& a, const B& b, const T1& abs_tol, const char* file, uint32_t line);

        template <typename A, typename B, typename T1, typename T2>
        requires Concepts::CommonFloat<A, B, T1, T2>
        std::optional<const Core::FailureInfo> 
            nearlyEqual(const A& a, const B& b, const T1& abs_tol, const T2& rel_tol, const char* file, uint32_t line);
    
        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1>
        std::optional<const Core::FailureInfo>
            relativelyEqual(const A& a, const B& b, const T1& rel_tol, const char* file, uint32_t line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::FailureInfo> isNaN(const T& val, const char* file, uint32_t line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::FailureInfo> isNotNaN(const T& val, const char* file, uint32_t line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::FailureInfo> isInf(const T& val, const char* file, uint32_t line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::FailureInfo> isPosInf(const T& val, const char* file, uint32_t line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::FailureInfo> isNegInf(const T& val, const char* file, uint32_t line);
    }
}

#include "flt/equals.hpp"
#include "flt/inf.hpp"
#include "flt/nan.hpp"

#endif