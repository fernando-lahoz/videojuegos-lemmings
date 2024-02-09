#pragma once

#include "math/math.hpp"

namespace math {

template <typename T>
constexpr T lerp(T x, T a, T b) {
    //return fma(b, a, fma(-t, x, x));
    return (1 - x) * a + x * b;
}

template <typename Ty>
constexpr auto max(Ty n) { return n; }

template <typename Ty, typename ...Args>
constexpr auto max(Ty n, Args ...args) {
    auto m = max(args...);
    return n > m ? n : m;
}

template <typename Ty>
constexpr auto min(Ty n) { return n; }

template <typename Ty, typename ...Args>
constexpr auto min(Ty n, Args ...args) {
    auto m = min(args...);
    return n < m ? n : m;
}

template <typename T>  
constexpr T clamp(T x, T a, T b)
{
    return max(a, min(b, x));
}

inline constexpr Float radians(Float degrees) {
    return degrees * PI / 180.0;
} 

inline constexpr Float degrees(Float radians) {
    return radians * 180.0 / PI;
}

template <unsigned N, typename Ty>
constexpr Ty pow(Ty n)
{
    if constexpr (N == 0)
        return 1;
    else
        return n * pow<N - 1>(n);
}

inline Float next_float_up(Float x) {
    return std::nextafter(x, INFINITY);
}

inline Float next_float_down(Float x) {
    return std::nextafter(x, -INFINITY);
}

} // namespace math