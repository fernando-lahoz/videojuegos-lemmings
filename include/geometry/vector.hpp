#pragma once

#include <iostream>
#include <cstdio>
#include <concepts>

#include "lib/types.hpp"

template <typename T>
class Vector3
{
public:
    T x, y, z;

    constexpr Vector3() = default;
    constexpr Vector3(T x, T y, T z) ;
    constexpr Vector3(T f);

    template <typename U>
    constexpr explicit Vector3(const Vector3<U> &v);

    constexpr bool has_NaNs() const;
    constexpr bool has_Inf() const;

    constexpr Vector3(const Vector3<T> &v);

    constexpr const T &operator[](int i) const;
    constexpr T &operator[](int i);
       
    constexpr Vector3<T> &operator=(const Vector3<T> &v);

    constexpr T max_component() const;

    constexpr Vector3<T> operator+(const Vector3<T> &v) const;
    constexpr Vector3<T>& operator+=(const Vector3<T> &v);

    constexpr Vector3<T> operator-(const Vector3<T> &v) const;
    constexpr Vector3<T>& operator-=(const Vector3<T> &v);

    constexpr bool operator==(const Vector3<T> &v) const;
    constexpr bool operator!=(const Vector3<T> &v) const;

    // Multiplies each component (is not dot nor cross product)
    constexpr Vector3<T> operator*(const Vector3<T> &v) const;
    constexpr Vector3<T> operator*(T s) const;
    constexpr Vector3<T> &operator*=(T s);

    constexpr Vector3<T> operator/(T f) const;
    constexpr Vector3<T> &operator/=(T f);

    constexpr Vector3<T> operator-() const;

    constexpr Float length_squared() const;
    constexpr Float length() const;

    void print() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector3<T> &v);

using Vector3f = Vector3<Float>;
using Vector3i = Vector3<int>;

//------------------------------------------------------------------------------

template <typename T>
class Vector2
{
public:
    T x, y;

    constexpr Vector2() = default;
    constexpr Vector2(T xx, T yy);

    constexpr bool has_NaNs() const;
    constexpr bool has_Inf() const;

    constexpr Vector2(const Vector2<T> &v);

    template <typename U>
    constexpr explicit Vector2(const Vector2<U> &v);

    constexpr Vector2<T> &operator=(const Vector2<T> &v);
    
    constexpr Vector2<T> operator+(const Vector2<T> &v) const;
    constexpr Vector2<T>& operator+=(const Vector2<T> &v);

    constexpr Vector2<T> operator-(const Vector2<T> &v) const;
    constexpr Vector2<T>& operator-=(const Vector2<T> &v);

    constexpr Vector2<T> operator/(const Vector2<T> &v) const;

    constexpr bool operator==(const Vector2<T> &v) const;
    constexpr bool operator!=(const Vector2<T> &v) const;

    constexpr Vector2<T> operator*(T f) const;
    constexpr Vector2<T> &operator*=(T f);

    constexpr Vector2<T> operator/(T f) const;
    constexpr Vector2<T> &operator/=(T f);

    constexpr Vector2<T> operator-() const;

    constexpr const T& operator[](int i) const;
    constexpr T &operator[](int i);

    constexpr Float length_squared() const;
    constexpr Float length() const;

    void print() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T> &v);

using Vector2f = Vector2<Float>;
using Vector2i = Vector2<int>;

//------------------------------------------------------------------------------

template <typename T>
constexpr T dot (const Vector3<T> &v1, const Vector3<T> &v2);

template <typename T>
constexpr T absDot (const Vector3<T> &v1, const Vector3<T> &v2);

// Cross product
template <typename T>
constexpr Vector3<T> cross (const Vector3<T> &v1, const Vector3<T> &v2);

template <typename T>
constexpr Vector3<T> normalize (const Vector3<T> &v);

template <typename T>
constexpr Vector3<T> abs (const Vector3<T> &v);

template <typename T>
constexpr Vector3<T> face_forward(const Vector3<T> &n, const Vector3<T> &v);


// 2D versions
template <typename T>
constexpr T dot (const Vector2<T> &v1, const Vector2<T> &v2);

template <typename T>
constexpr T abs_dot (const Vector2<T> &v1, const Vector2<T> &v2);

// Cross
template <typename T>
constexpr T cross (const Vector2<T> &v1, const Vector2<T> &v2);

template <typename T>
constexpr Vector2<T> normalize (const Vector2<T> &v);

template <typename T>
constexpr Vector2<T> abs (const Vector2<T> &v);

template <typename T>
constexpr Vector2<T> face_forward(const Vector2<T> &n, const Vector2<T> &v);


//Inverse * for Vector3
template <typename T>
constexpr Vector3<T> operator*(T f, const Vector3<T> &v);

//Inverse * for Vector2
template <typename T>
constexpr Vector2<T> operator*(T f, const Vector2<T> &v);


template <typename T>
constexpr void generate_coordinate_system(const Vector3<T> &v1, 
        Vector3<T> &v2, Vector3<T> &v3);

template <typename T>
constexpr T max_component(Vector3<T> v);

#include "geometry/vector.ipp"