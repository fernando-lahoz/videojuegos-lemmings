    #pragma once

    #include "../lib/types.h"
    
    template <typename T>
    inline T lerp(T x, T a, T b) {
        //return fma(b, a, fma(-t, x, x));
        return (1 - x) * a + x * b;
    }
 
/*
    inline int common_prefix(int a, int b, unsigned int *sortedMortonCodes, unsigned int n)
    {        
        if (b < 0 || b >= n)
            return -1;

        return __clz(sortedMortonCodes[a] ^ sortedMortonCodes[b]);
    }


    template <typename T>
    inline Float max(T a, Float b) {
        return max((Float)a, b);
    }


    template <typename T>
    inline Float max(Float a, T b) {
        return max(a, (Float)b);
    }
*/

    template <typename T>
    inline T min (T a, T b) {
        return std::min(a, b);
    }

    template <typename T>
    inline T max (T a, T b) {
        return std::max(a, b);
    }

    // Clamp implementation
    template <typename T>  
    inline T clamp(T x, T a, T b)
    {
        return max(a, min(b, x));
    }

    inline float clamp (float x, double a, double b)
    {
        return std::max(a, std::min(b, (double)x));
    }

    // Swaps two objects
    template <typename T>
    inline void swap(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    inline Float radians(Float degrees) {
        return degrees * PI / 180.0;
    } 

    inline Float degrees(Float radians) {
        return radians * 180.0 / PI;
    }


    template <typename T>
    inline bool isNaN(T f) 
    {
        return f != f;
    }

    template <typename T>
    inline bool isInf(T f) 
    {
        return f == INFINITY;
    }

    
    inline bool quadratic (ErrorFloat a, ErrorFloat b, ErrorFloat c, ErrorFloat &solution0, ErrorFloat &solution1)
    {
        ErrorFloat discriminant = b*b - (Float)4.0*a*c;

        if (discriminant < ErrorFloat(0.0)) 
            return false;
            
        ErrorFloat rootDiscriminant = sqrt(discriminant);

        ErrorFloat q;

        if (b < ErrorFloat(0.0)) 
            q = Float(-0.5) * (b - rootDiscriminant);
        else
            q = Float(-0.5) * (b + rootDiscriminant);

        solution0 = q / a;
        solution1 = c / q;

        if (solution0.data > solution1.data) 
            swap(solution0, solution1);

        return !isNaN(solution0) && !isNaN(solution1);
    }

    inline constexpr Float errorBound(int n) {
        return (n * MachineEpsilon) / (1 - n * MachineEpsilon);
    }

    inline constexpr unsigned int pow2(unsigned int n) {
        return 1 << n;
    }

    inline constexpr Float pow2(Float x) {
        return x * x;
    }

    inline constexpr Float pow3(Float x) {
        return x * x * x;
    }

    inline constexpr Float pow5(Float x) {
        return (x * x) * (x * x) * x;
    }

    inline constexpr unsigned int roundup(Float x) {
        return (unsigned int)ceil(x);
    }

    Float nextFloatUp(Float x)
    {
        // If it is +infinity, return +infinity
        if (isInf(x) && x > 0.0)
            return x;

        if (x == -0.0)
            x = 0.0;

        unsigned long long ui;

        if (sizeof(Float) == sizeof(float))
            ui = reinterpret_cast<unsigned int&>(x);
        else
            ui = reinterpret_cast<unsigned long long&>(x);

        if (x >= 0.0)
            ++ui;
        else
            --ui;

        return reinterpret_cast<Float&>(ui);
    }   
    
    Float nextFloatDown(Float x)
    {
        if (isInf(x) && x < 0.0)
            return x;

        if (x == 0.0)
            x = -0.0;

        unsigned long long ui;

        if (sizeof(Float) == sizeof(float))
            ui = reinterpret_cast<unsigned int&>(x);
        else
            ui = reinterpret_cast<unsigned long long&>(x);

        if (x > 0.0)
            --ui;
        else
            ++ui;

        return reinterpret_cast<Float&>(ui);
    }

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
    //  to combine two sampling methods.
    inline Float powerHeuristic(int nf, Float lightPdf, int ng, Float scatterPdf) 
    {
        Float f = nf * lightPdf;
        Float g = ng * scatterPdf;
        return (f * f) / (f * f + g * g);
    }