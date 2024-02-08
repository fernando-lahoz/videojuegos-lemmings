#pragma once

#include "types.h"

template<typename T1, typename T2>
class Pair
{
    public:

    T1 x;
    T2 y;
 
    Pair(T1 first, T2 second) : x(first), y(second) {}

    Pair() : x(T1()), y(T2()) {}

    void swap() 
    {
        T1 temp = x;
        x = y;
        y = temp;
    }
};


typedef Pair<int, int> int2;
typedef Pair<unsigned int, unsigned int> uint2;
typedef Pair<Float, Float> Float2;