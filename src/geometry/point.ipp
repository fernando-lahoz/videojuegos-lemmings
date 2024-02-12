#pragma once

#include "geometry/point.hpp"


template <typename T>
constexpr Point3<T>::Point3(T x, T y, T z)
    : x(x), y(y), z(z) 
{
    assert(!has_NaNs());
}

template <typename T>
constexpr  Point3<T>::Point3(T f)
    : x(f), y(f), z(f) 
{
    assert(!has_NaNs());
}

template <typename T>
template <typename U>
constexpr Point3<T>::Point3(const Point3<U> &p)
    : x((T)p.x), y((T)p.y), z((T)p.z) 
{
    assert(!has_NaNs());
}

template <typename T>
constexpr Point3<T>::Point3(const Vector3<T> &v)
    : x(v.x), y(v.y), z(v.z) 
{
    assert(!has_NaNs());
}

template <typename T>
constexpr Vector3<T> Point3<T>::to_vector() const {
    return Vector3<T>(x, y, z);
}

template <typename T>
constexpr bool Point3<T>::has_NaNs() const {
    return std::isnan(x) || std::isnan(y) || std::isnan(z);
}

template <typename T>
constexpr bool Point3<T>::has_Inf() const {
    return std::isinf(x) || std::isinf(y) || std::isinf(z);
}

template <typename T>
constexpr Point3<T>::Point3(const Point3<T> &p) {
    assert(!p.has_NaNs());
    x = p.x; y = p.y; z = p.z;
}

template <typename T>
constexpr const T &Point3<T>::operator[](int i) const 
{ 
    assert(i >= 0 && i <= 2);

    if (i == 0) 
        return x;
    else if (i == 1) 
        return y;
    else
        return z;
}

template <typename T>
constexpr T &Point3<T>::operator[](int i)
{ 
    assert(i >= 0 && i <= 2);

    if (i == 0) 
        return x;
    else if (i == 1) 
        return y;
    else
        return z;
}
    
template <typename T>
constexpr Point3<T> &Point3<T>::operator=(const Point3<T> &p)
{
    assert(!p.has_NaNs());

    x = p.x; 
    y = p.y; 
    z = p.z;

    return *this;
}

template <typename T>
constexpr T Point3<T>::max_component() const
{
    return std::max(x, std::max(y, z));
}

template <typename T>
constexpr bool Point3<T>::operator==(const Point3<T> &p) const {
    return x == p.x && y == p.y && z == p.z;
}
template <typename T>
constexpr bool Point3<T>::operator!=(const Point3<T> &p) const {
    return x != p.x || y != p.y || z != p.z;
}

template <typename T>
constexpr Point3<T> Point3<T>::operator+(const Vector3<T> &v) const {
    return Point3<T>(x + v.x, y + v.y, z + v.z);
}

template <typename T>
constexpr Point3<T> &Point3<T>::operator+=(const Vector3<T> &v) 
{
    x += v.x; 
    y += v.y; 
    z += v.z;

    return *this;
}

template <typename T>
constexpr Vector3<T> Point3<T>::operator-(const Point3<T> &p) const {
    return Vector3<T>(x - p.x, y - p.y, z - p.z);
}

template <typename T>
constexpr Point3<T> Point3<T>::operator-(const Vector3<T> &v) const {
    return Point3<T>(x - v.x, y - v.y, z - v.z);
}

template <typename T>
constexpr Point3<T> &Point3<T>::operator-=(const Vector3<T> &v) 
{
    x -= v.x; 
    y -= v.y; 
    z -= v.z;

    return *this;
}

template <typename T>
constexpr Point3<T> &Point3<T>::operator+=(const Point3<T> &p) 
{
    x += p.x; 
    y += p.y; 
    z += p.z;

    return *this;
}

template <typename T>
constexpr Point3<T> Point3<T>::operator+(const Point3<T> &p) const {
    return Point3<T>(x + p.x, y + p.y, z + p.z);
}

template <typename T>
constexpr Point3<T> Point3<T>::operator*(T f) const {
    return Point3<T>(f*x, f*y, f*z);
}

template <typename T>
constexpr Point3<T> &Point3<T>::operator*=(T f) 
{
    x *= f; 
    y *= f; 
    z *= f;

    return *this;
}

template <typename T>
constexpr Point3<T> Point3<T>::operator/(T f) const 
{
    Float inv = (Float)1 / f;
    return Point3<T>(inv*x, inv*y, inv*z);
}

template <typename T>
constexpr Point3<T> &Point3<T>::operator/=(T f) 
{
    Float inv = (Float)1 / f;
    x *= inv; 
    y *= inv; 
    z *= inv;

    return *this;
}

template <typename T>
constexpr Point3<T> Point3<T>::operator-() const { 
    return Vector3<T>(-x, -y, -z); 
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point3<T> &p) 
{
    Point3<T> p2 = p;

    if (std::abs(p2.x) < FLOAT_ERROR_MARGIN)
        p2.x = 0;

    if (std::abs(p2.y) < FLOAT_ERROR_MARGIN)
        p2.y = 0;
    
    if (std::abs(p2.z) < FLOAT_ERROR_MARGIN)
        p2.z = 0;


    os << "point[" << p2.x << ", " << p2.y << ", " << p2.z << "]";
    return os;
}

template <typename T>
void Point3<T>::print() const
{
    std::printf("Point3[%f, %f, %f]\n", x, y, z);
}

template <typename T>
constexpr Float distance(const Point3<T> &p1, const Point3<T> &p2) {
    return (p1 - p2).length();
}

template <typename T>
constexpr Float distance_squared(const Point3<T> &p1, const Point3<T> &p2) {
    return (p1 - p2).length_squared();
}

// Specialization for Float
template <>
constexpr bool Point3<Float>::operator==(const Point3<Float> &p) const 
{
    return (std::abs(x - p.x) < FLOAT_ERROR_MARGIN) 
            && (std::abs(y - p.y) < FLOAT_ERROR_MARGIN) 
            && (std::abs(z - p.z) < FLOAT_ERROR_MARGIN);
}

template <>
constexpr bool Point3<Float>::operator!=(const Point3<Float> &p) const 
{
    return (std::abs(x - p.x) > FLOAT_ERROR_MARGIN) 
            || (std::abs(y - p.y) > FLOAT_ERROR_MARGIN) 
            || (std::abs(z - p.z) > FLOAT_ERROR_MARGIN);
}

//------------------------------------------------------------------------------

template <typename T>
constexpr Point2<T>::Point2(T xx, T yy)
    : x(xx), y(yy) 
{
    assert(!has_NaNs());
}

template <typename T>
constexpr Point2<T>::Point2(const Vector2<T> &v)
    : x(v.x), y(v.y) 
{
    assert(!has_NaNs());
}

template <typename T>
template <typename U>
constexpr Point2<T>::Point2(const Point2<U> &p)
    : x((T)p.x), y((T)p.y) 
{
    assert(!has_NaNs());
}


template <typename T>
constexpr Vector2<T> Point2<T>::to_vector() const {
    return Vector2<T>(x, y);
}

template <typename T>
constexpr bool Point2<T>::has_NaNs() const {
    return std::isnan(x) || std::isnan(y); 
}

template <typename T>
constexpr bool Point2<T>::has_Inf() const {
    return std::isinf(x) || std::isinf(y); 
}

template <typename T>
constexpr Point2<T>::Point2(const Point2<T> &p)
    : x(p.x), y(p.y) 
{
    assert(!has_NaNs());
}

template <typename T>
constexpr bool Point2<T>::operator==(const Point2<T> &p) const {
    return x == p.x && y == p.y;
}

// Operator =
template <typename T>
constexpr Point2<T> &Point2<T>::operator=(const Point2<T> &p)
{
    assert(!p.has_NaNs());
    x = p.x; 
    y = p.y;

    return *this;
}

template <typename T>
constexpr bool Point2<T>::operator!=(const Point2<T> &p) const {
    return x != p.x || y != p.y;
}

template <typename T>
constexpr const T& Point2<T>::operator[](int i) const
{
    assert(i >= 0 && i <= 1);

    if (i == 0) 
        return x;
    else
        return y;
}

template <typename T>
constexpr T &Point2<T>::operator[](int i)
{
    assert(i >= 0 && i <= 1);

    if (i == 0) 
        return x;
    else
        return y;
}

template <typename T>
constexpr void Point2<T>::print() const
{
    std::printf("Point2[%f, %f]\n", x, y);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point2<T> &p) 
{
    Point2<T> p2 = p;

    if (std::abs(p2.x) < FLOAT_ERROR_MARGIN)
        p2.x = 0;
    
    if (std::abs(p2.y) < FLOAT_ERROR_MARGIN)
        p2.y = 0;

    os << "point[" << p2.x << ", " << p2.y << "]";
    return os;
}

template <typename T>
constexpr Point2<T> Point2<T>::operator+(const Vector2<T> &v) const 
{
    assert(!v.has_NaNs());
    return Point2<T>(x + v.x, y + v.y);
}


template <typename T>
constexpr Point2<T> &Point2<T>::operator+=(const Vector2<T> &v) 
{
    assert(!v.hasNaNs());
    x += v.x; 
    y += v.y;

    return *this;
}

template <typename T>
constexpr Vector2<T> Point2<T>::operator-(const Point2<T> &p) const 
{
    assert(!p.has_NaNs());
    return Vector2<T>(x - p.x, y - p.y);
}

template <typename T>
constexpr Point2<T> Point2<T>::operator-(const Vector2<T> &v) const 
{
    assert(!v.has_NaNs());
    return Point2<T>(x - v.x, y - v.y);
}

template <typename T>
constexpr Point2<T> Point2<T>::operator-() const { 
    return Point2<T>(-x, -y);
}

template <typename T>
constexpr Point2<T> &Point2<T>::operator-=(const Vector2<T> &v) 
{
    assert(!v.has_NaNs());
    x -= v.x; 
    y -= v.y;

    return *this;
}

template <typename T>
constexpr Point2<T> &Point2<T>::operator-=(const Point2<T> &p)
{
    assert(!p.has_NaNs());
    x -= p.x; 
    y -= p.y;

    return *this;
}

template <typename T>
constexpr Point2<T> &Point2<T>::operator+=(const Point2<T> &p) 
{
    assert(!p.has_NaNs());
    x += p.x; 
    y += p.y;

    return *this;
}

template <typename T>
constexpr Point2<T> Point2<T>::operator+(const Point2<T> &p) const 
{
    assert(!p.has_NaNs());
    return Point2<T>(x + p.x, y + p.y);
}


template <typename T>
constexpr Point2<T> Point2<T>::operator* (T f) const {
    return Point2<T>(f*x, f*y);
}

template <typename T>
constexpr Point2<T> &Point2<T>::operator*=(T f) 
{
    x *= f; 
    y *= f;

    return *this;
}

template <typename T>
constexpr Point2<T> Point2<T>::operator/ (T f) const 
{
    Float inv = (Float)1 / f;
    return Point2<T>(inv*x, inv*y);
}

template <typename T>
constexpr Point2<T> &Point2<T>::operator/=(T f) 
{
    Float inv = (Float)1 / f;
    x *= inv; 
    y *= inv;

    return *this;
}

// Specialization for float
template <>
constexpr bool Point2<Float>::operator==(const Point2<Float> &p) const 
{
    return (std::abs(x - p.x) < FLOAT_ERROR_MARGIN) 
            && (std::abs(y - p.y) < FLOAT_ERROR_MARGIN);
}

template <>
constexpr bool Point2<Float>::operator!=(const Point2<Float> &p) const 
{
    return (std::abs(x - p.x) > FLOAT_ERROR_MARGIN) 
            || (std::abs(y - p.y) > FLOAT_ERROR_MARGIN);
}