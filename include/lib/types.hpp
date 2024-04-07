#pragma once

#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <atomic>
#include <numbers>

// Bibliotecas de depuración
//#include <execinfo.h>
//#include <cxxabi.h>

using Float = float;

static constexpr Float PI = std::numbers::pi_v<Float>;
static constexpr Float TAU = (2*PI);
static constexpr Float SQRT2 = std::numbers::sqrt2_v<Float>;
static constexpr Float INV_4_PI = 1.0 / (4.0 * PI);

static constexpr Float MACHINE_EPSILON = std::numeric_limits<Float>::epsilon();
static constexpr Float FLOAT_ERROR_MARGIN = 0.0000001;

//const Float ShadowEpsilon = 0.0001;

class ErrorFloat
{
public:
    Float data, err;

    inline constexpr ErrorFloat () noexcept;
    inline constexpr ErrorFloat (Float data, Float err = 0.0) noexcept;

    inline constexpr ErrorFloat operator+(ErrorFloat rhs) const noexcept;
    inline constexpr ErrorFloat operator-(ErrorFloat rhs) const noexcept;

    inline constexpr ErrorFloat operator*(ErrorFloat rhs) const noexcept;
    inline constexpr ErrorFloat operator*(Float rhs) const noexcept;
    inline constexpr ErrorFloat operator/(ErrorFloat rhs) const noexcept;

    inline constexpr bool operator==(ErrorFloat rhs) const noexcept;
    inline constexpr bool operator!=(ErrorFloat rhs) const noexcept;
    inline constexpr bool operator<(ErrorFloat rhs) const noexcept;

    inline constexpr Float upper_bound() const noexcept;
    inline constexpr Float lower_bound() const noexcept;

    inline constexpr operator float() const noexcept;
    inline constexpr operator double() const noexcept;
};

inline constexpr ErrorFloat operator/(Float lhs, ErrorFloat rhs) noexcept;
inline constexpr ErrorFloat operator*(Float lhs, ErrorFloat rhs) noexcept;
inline constexpr ErrorFloat sqrt(ErrorFloat f) noexcept;

// TODO: mirar bibliotecta de depuración
/*
void printStackCallTrace()
{
    const int maxFrames = 64; // Adjust this to the desired depth of the stack trace
    void* callStack[maxFrames];
    int numFrames = backtrace(callStack, maxFrames);

    char** symbols = backtrace_symbols(callStack, numFrames);

    for (int i = 0; i < numFrames; i++) {
        int status;
        char* demangled = abi::__cxa_demangle(symbols[i], 0, 0, &status);
        printf("#%d %s\n", i, (status == 0 ? demangled : symbols[i]));
        free(demangled);
    }

    free(symbols);
}
*/

// Implementation
#include <lib/types.ipp>
