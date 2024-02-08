#pragma once

#include <assert.h>
#include <float.h>

#include <cmath>
#include <iostream>
#include <execinfo.h>
#include <cstdlib>
#include <cxxabi.h>

#include <atomic>

#define Float float
#define MachineEpsilon (FLT_EPSILON * 0.5)  // Change for double precission

#define PI 3.14159265358979323846
constexpr Float INV_PI = (1/PI);
constexpr Float INV_FOUR_PI = (1/(4*PI));
constexpr Float PIhalf = (PI/2);
constexpr Float PIquarter = (PI/4);
constexpr Float TAU = (2*PI);
#define SQRT2 1.41421356237309504880168872420969807856967187537694807317667973799

#define FLOAT_ERROR_MARGIN 0.0000001

#ifdef DEBUG
#define N_THREADS 1
#else
#define N_THREADS 128
#endif


const Float ShadowEpsilon = 0.0001;

class ErrorFloat
{
    public:
    Float data, err;

    ErrorFloat () 
        : data(0.0), err(0.0) 
    {}
    
    ErrorFloat (Float data, Float err = 0.0) 
        : data(data), err(err) 
    {}

    inline ErrorFloat operator+(ErrorFloat rhs) const
    {
        ErrorFloat ret;
        ret.data = data + rhs.data;
        ret.err = err + rhs.err;
        return ret;
    }

    inline ErrorFloat operator-(ErrorFloat rhs) const
    {
        ErrorFloat ret;
        ret.data = data - rhs.data;
        ret.err = err + rhs.err;
        return ret;
    }

    inline ErrorFloat operator*(ErrorFloat rhs) const
    {
        ErrorFloat ret;
        ret.data = data * rhs.data;
        ret.err = abs(ret.data) * rhs.err + abs(rhs.data) * err;
        return ret;
    }

    inline ErrorFloat operator*(Float rhs) const
    {
        ErrorFloat ret;
        ret.data = data * rhs;
        ret.err = abs(ret.data) * err;
        return ret;
    }

    inline ErrorFloat operator/(ErrorFloat rhs) const
    {
        ErrorFloat ret;
        ret.data = data / rhs.data;
        ret.err = (abs(ret.data) * rhs.err + abs(rhs.data) * err) / (rhs.data * rhs.data);
        return ret;
    }

    inline bool operator==(ErrorFloat rhs) const
    {
        return data == rhs.data && err == rhs.err;
    }

    inline bool operator!=(ErrorFloat rhs) const
    {
        return data != rhs.data || err != rhs.err;
    }

    inline bool operator<(ErrorFloat rhs) const
    {
        return data < rhs.data;
    }

    inline Float upperBound()
    {
        return data + err;
    }

    inline Float lowerBound()
    {
        return data - err;
    }

    inline operator float() const
    {
        return data;
    }

    inline operator double() const
    {
        return data;
    }
};
inline ErrorFloat operator/(Float lhs, ErrorFloat rhs)
{
    ErrorFloat ret;
    ret.data = lhs / rhs.data;
    ret.err = (abs(ret.data) * rhs.err) / (rhs.data * rhs.data);
    return ret;
}
inline ErrorFloat operator*(Float lhs, ErrorFloat rhs)
{
    ErrorFloat ret;
    ret.data = lhs * rhs.data;
    ret.err = abs(ret.data) * rhs.err;
    return ret;
}
inline ErrorFloat sqrt (ErrorFloat f)
{
    ErrorFloat ret;
    ret.data = sqrt(f.data);
    ret.err = 0.5 * f.err / ret.data;
    return ret;
}


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
