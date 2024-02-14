#pragma once

#include "lib/types.hpp"

namespace math {

// Linear interpolation
template <typename T> constexpr T lerp(T x, T a, T b);
 
/*
inline int common_prefix(int a, int b, unsigned int *sortedMortonCodes, unsigned int n)
{        
    if (b < 0 || b >= n)
        return -1;

    return __clz(sortedMortonCodes[a] ^ sortedMortonCodes[b]);
}

*/

template <typename Ty>
constexpr auto max(Ty n);
template <typename Ty, typename ...Args>
constexpr auto max(Ty n, Args ...args);

template <typename Ty>
constexpr auto min(Ty n);
template <typename Ty, typename ...Args>
constexpr auto min(Ty n, Args ...args);


// Clamp implementation
template <typename T> constexpr T clamp(T x, T a, T b);

inline constexpr Float radians(Float degrees);

inline constexpr Float degrees(Float radians);


bool quadratic (ErrorFloat a, ErrorFloat b, ErrorFloat c,
        ErrorFloat &solution0, ErrorFloat &solution1);

inline constexpr Float error_bound(int n) {
    return (n * MACHINE_EPSILON) / (1 - n * MACHINE_EPSILON);
}

template <unsigned N, typename Ty>
constexpr Ty pow(Ty n);

template <typename Ty>
constexpr Ty pow2(Ty n);

inline constexpr unsigned int roundup(Float x) {
    return (unsigned int)std::ceil(x);
}

inline Float next_float_up(Float x);

inline Float next_float_down(Float x);
inline Float truncate(Float x, int n);

// Using curand generator
/*
inline Float randFloatGPU(curandGenerator_t generator) 
{
    float result;
    curandGenerateUniform(generator, &result, 1);
    return result;
}
*/

// Heuristic that weights the contributions of two samples 
// to combine two sampling methods.
/*
inline Float power_heuristic(int nf, Float lightPdf, int ng, Float scatterPdf) 
{
    Float f = nf * lightPdf;
    Float g = ng * scatterPdf;
    return (f * f) / (f * f + g * g);
} */

} //namespace math 

#include "math/math.ipp"