#pragma once

#include <iostream>
#include <cstdio>

#include "geometry/vector.hpp"

template <typename T>
class Point3
{
public:
    T x, y, z;

    constexpr Point3() = default;
    constexpr Point3(T x, T y, T z) ;
    constexpr Point3(T f);

    template <typename U>
    constexpr explicit Point3(const Point3<U> &p);

    constexpr explicit Point3(const Vector3<T> &v);
    constexpr Vector3<T> to_vector() const;

    constexpr bool has_NaNs() const;
    constexpr bool has_Inf() const;

    constexpr Point3(const Point3<T> &v);

    constexpr const T &operator[](int i) const;
    constexpr T &operator[](int i);
       
    constexpr Point3<T> &operator=(const Point3<T> &p);

    constexpr T max_component() const;

    constexpr bool operator==(const Point3<T> &v) const;
    constexpr bool operator!=(const Point3<T> &v) const;

    constexpr Point3<T> operator+(const Vector3<T> &v) const;
    constexpr Point3<T> &operator+=(const Vector3<T> &v);

    constexpr Vector3<T> operator-(const Point3<T> &p) const;
    constexpr Point3<T> operator-(const Vector3<T> &v) const;
    constexpr Point3<T> &operator-=(const Vector3<T> &v);

    constexpr Point3<T> &operator+=(const Point3<T> &p);
    constexpr Point3<T> operator+(const Point3<T> &p) const;

    constexpr Point3<T> operator*(T f) const;
    constexpr Point3<T> &operator*=(T f);

    constexpr Point3<T> operator/(T f) const;
    constexpr Point3<T> &operator/=(T f);

    constexpr Point3<T> operator-() const;

    void print() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point3<T> &p);

using Point3f = Point3<Float>;
using Point3i = Point3<int>;

template <typename T>
constexpr Float distance(const Point3<T> &p1, const Point3<T> &p2);

template <typename T>
constexpr Float distance_squared(const Point3<T> &p1, const Point3<T> &p2);

//------------------------------------------------------------------------------

template <typename T>
class Point2
{
public:
    T x, y;

    constexpr Point2() = default;
    constexpr Point2(T xx, T yy);

    template <typename U>
    constexpr explicit Point2(const Point2<U> &p);

    constexpr explicit Point2(const Vector2<T> &v);
    constexpr Vector2<T> to_vector() const;

    constexpr bool has_NaNs() const;
    constexpr bool has_Inf() const;

    constexpr Point2(const Point2<T> &p);

    constexpr bool operator==(const Point2<T> &v) const;
    constexpr bool operator!=(const Point2<T> &v) const;

    constexpr const T& operator[](int i) const;
    constexpr T &operator[](int i);

    constexpr Point2<T> operator+(const Vector2<T> &v) const;
    constexpr Point2<T> &operator+=(const Vector2<T> &v);

    constexpr Vector2<T> operator-(const Point2<T> &p) const;
    constexpr Point2<T> operator-(const Vector2<T> &v) const;
    constexpr Point2<T> &operator-=(const Vector2<T> &v);

    constexpr Point2<T> operator-() const;

    constexpr Point2<T> &operator+=(const Point2<T> &p);
    constexpr Point2<T> operator+(const Point2<T> &p) const;

    constexpr Point2<T> operator* (T f) const;
    constexpr Point2<T> &operator*=(T f);

    constexpr Point2<T> operator/ (T f) const;
    constexpr Point2<T> &operator/=(T f);

    constexpr void print() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point2<T> &v);

using Point2f = Point2<Float>;
using Point2i = Point2<int>;

template <typename T>
inline Float distance(const Point2<T> &p1, const Point2<T> &p2) {
    return (p1 - p2).length();
}

template <typename T>
inline Float distance_squared(const Point2<T> &p1, const Point2<T> &p2) {
    return (p1 - p2).length_squared();
}

//------------------------------------------------------------------------------


//TODO: more operators (inverse[-, /], from literals...) for Point2-3 and Vector2-3

#include "geometry/point.ipp"