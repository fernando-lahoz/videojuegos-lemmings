#pragma once

#include "geometry/vector.hpp"
#include <algorithm>

template <typename T>
constexpr Vector3<T>::Vector3(T x, T y, T z)
    : x(x), y(y), z(z)
{
    assert(!has_NaNs());
}

template <typename T>
constexpr Vector3<T>::Vector3(T f)
    : x(f), y(f), z(f)
{
    assert(!has_NaNs());
}

template <typename T>
template <typename U>
constexpr Vector3<T>::Vector3(const Vector3<U> &v)
    : x((T)v.x), y((T)v.y), z((T)v.z)
{
}

template <typename T>
constexpr bool Vector3<T>::has_NaNs() const
{
    return std::isnan(x) || std::isnan(y) || std::isnan(z);
}

template <typename T>
constexpr bool Vector3<T>::has_Inf() const
{
    return std::isinf(x) || std::isinf(y) || std::isinf(z);
}

template <typename T>
constexpr Vector3<T>::Vector3(const Vector3<T> &v)
{
    assert(!v.has_NaNs());
    x = v.x;
    y = v.y;
    z = v.z;
}

template <typename T>
constexpr const T &Vector3<T>::operator[](int i) const
{
    assert(i >= 0 && i <= 2);

    // Better to have dataDivergence than different return points
    //  On GPU, the else will be indifferent
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else
        return z;
}

template <typename T>
constexpr T &Vector3<T>::operator[](int i)
{
    assert(i >= 0 && i <= 2);

    // Here, we must return the reference to the original value
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else
        return z;
}

template <typename T>
constexpr Vector3<T> &Vector3<T>::operator=(const Vector3<T> &v)
{
    assert(!v.has_NaNs());

    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

template <typename T>
constexpr T Vector3<T>::max_component() const
{
    return std::max(x, std::max(y, z));
}

template <typename T>
constexpr Vector3<T> Vector3<T>::operator+(const Vector3<T> &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

template <typename T>
constexpr Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

template <typename T>
constexpr Vector3<T> Vector3<T>::operator-(const Vector3<T> &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

template <typename T>
constexpr Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

template <typename T>
constexpr bool Vector3<T>::operator==(const Vector3<T> &v) const
{
    return x == v.x && y == v.y && z == v.z;
}

template <typename T>
constexpr bool Vector3<T>::operator!=(const Vector3<T> &v) const
{
    return x != v.x || y != v.y || z != v.z;
}

template <typename T>
constexpr Vector3<T> Vector3<T>::operator*(const Vector3<T> &v) const
{
    return Vector3(x * v.x, y * v.y, z * v.z);
}

template <typename T>
constexpr Vector3<T> Vector3<T>::operator*(T s) const
{
    return Vector3<T>(s * x, s * y, s * z);
}

template <typename T>
constexpr Vector3<T> &Vector3<T>::operator*=(T s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

template <typename T>
constexpr Vector3<T> Vector3<T>::operator/(T f) const
{
    assert(f != 0);
    Float inv = (Float)1 / f;

    return Vector3<T>(x * inv, y * inv, z * inv);
}

template <typename T>
constexpr Vector3<T> &Vector3<T>::operator/=(T f)
{
    assert(f != 0);

    Float inv = (Float)1 / f;

    x *= inv;
    y *= inv;
    z *= inv;

    return *this;
}


template <typename T>
constexpr Vector3<T> clamp(const Vector3<T> &v, const Vector3<T> &low, const Vector3<T> &high)
{
    return Vector3<T>(std::clamp(v.x, low.x, high.x), std::clamp(v.y, low.y, high.y), std::clamp(v.z, low.z, high.z));
}


template <typename T>
constexpr Vector3<T> Vector3<T>::operator-() const
{
    return Vector3<T>(-x, -y, -z);
}

template <typename T>
constexpr Float Vector3<T>::length_squared() const
{
    return x * x + y * y + z * z;
}

template <typename T>
constexpr Float Vector3<T>::length() const
{
    return sqrt(length_squared());
}

template <typename T>
void Vector3<T>::print() const
{
    std::printf("Vector3[%f, %f, %f]\n", x, y, z);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector3<T> &v)
{
    Vector3<T> v2(v[0], v[1], v[2]);
    std::string output;

    if (std::abs(v2[0]) < FLOAT_ERROR_MARGIN)
        v2[0] = 0;

    if (std::abs(v2[1]) < FLOAT_ERROR_MARGIN)
        v2[1] = 0;

    if (std::abs(v2[2]) < FLOAT_ERROR_MARGIN)
        v2[2] = 0;

    output = "vector[" + std::to_string(v2[0]) + ", " + std::to_string(v2[1]) + ", " + std::to_string(v2[2]) + "]";
    os << output;

    return os;
}

// Specialization for Float
template <>
constexpr bool Vector3<Float>::operator==(const Vector3<Float> &v) const
{
    return (std::abs(x - v.x) < FLOAT_ERROR_MARGIN) && (std::abs(y - v.y) < FLOAT_ERROR_MARGIN) && (std::abs(z - v.z) < FLOAT_ERROR_MARGIN);
}

template <>
constexpr bool Vector3<Float>::operator!=(const Vector3<Float> &v) const
{
    return (std::abs(x - v.x) > FLOAT_ERROR_MARGIN) || (std::abs(y - v.y) > FLOAT_ERROR_MARGIN) || (std::abs(z - v.z) > FLOAT_ERROR_MARGIN);
}

//------------------------------------------------------------------------------

template <typename T>
constexpr Vector2<T>::Vector2(T xx, T yy)
    : x(xx), y(yy)
{
    assert(!has_NaNs());
}


template <typename T>
constexpr Vector2<T>::Vector2(T f)
    : x(f), y(f)
{
    assert(!has_NaNs());
}

template <typename T>
template <typename U>
constexpr Vector2<T>::Vector2(const Vector2<U> &v)
    : x((T)v.x), y((T)v.y)
{
}

template <typename T>
constexpr bool Vector2<T>::has_NaNs() const
{
    return std::isnan(x) || std::isnan(y);
}

// The default versions of these are fine for release builds; for debug
// we define them so that we can add the assert checks.
template <typename T>
constexpr Vector2<T>::Vector2(const Vector2<T> &v)
{
    assert(!v.has_NaNs());

    x = v.x;
    y = v.y;
}

template <typename T>
constexpr Vector2<T> &Vector2<T>::operator=(const Vector2<T> &v)
{
    assert(!v.has_NaNs());
    x = v.x;
    y = v.y;

    return *this;
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator+(const Vector2<T> &v) const
{
    assert(!v.has_NaNs());
    return Vector2(x + v.x, y + v.y);
}

template <typename T>
constexpr Vector2<T> &Vector2<T>::operator+=(const Vector2<T> &v)
{
    assert(!v.has_NaNs());
    x += v.x;
    y += v.y;

    return *this;
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator-(const Vector2<T> &v) const
{
    assert(!v.has_NaNs());
    return Vector2(x - v.x, y - v.y);
}

template <typename T>
constexpr Vector2<T> &Vector2<T>::operator-=(const Vector2<T> &v)
{
    assert(!v.has_NaNs());
    x -= v.x;
    y -= v.y;

    return *this;
}

template <typename T>
constexpr bool Vector2<T>::operator==(const Vector2<T> &v) const
{
    return x == v.x && y == v.y;
}

template <typename T>
constexpr bool Vector2<T>::operator!=(const Vector2<T> &v) const
{
    return x != v.x || y != v.y;
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator*(T f) const
{
    return Vector2<T>(f * x, f * y);
}

template <typename T>
constexpr Vector2<T> &Vector2<T>::operator*=(T f)
{
    assert(!std::isnan(f));
    x *= f;
    y *= f;

    return *this;
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator/(T f) const
{
    assert(f != 0);
    Float inv = (Float)1 / f;

    return Vector2<T>(x * inv, y * inv);
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator/(const Vector2<T> &v) const
{
    assert(v.x != 0 && v.y != 0);
    return Vector2<T>(x / v.x, y / v.y);
}

template <typename T>
constexpr Vector2<T> &Vector2<T>::operator/=(T f)
{
    assert(f != 0);

    Float inv = (Float)1 / f;
    x *= inv;
    y *= inv;

    return *this;
}

template <typename T>
constexpr Vector2<T> Vector2<T>::operator-() const
{
    return Vector2<T>(-x, -y);
}

template <typename T>
constexpr const T &Vector2<T>::operator[](int i) const
{
    assert(i >= 0 && i <= 1);

    if (i == 0)
        return x;
    else
        return y;
}

template <typename T>
constexpr T &Vector2<T>::operator[](int i)
{
    assert(i >= 0 && i <= 1);

    if (i == 0)
        return x;
    else
        return y;
}

template <typename T>
constexpr Float Vector2<T>::length_squared() const
{
    return x * x + y * y;
}

template <typename T>
constexpr Float Vector2<T>::length() const
{
    return std::sqrt(length_squared());
}

template <typename T>
void Vector2<T>::print() const
{
    std::printf("Vector2[%f, %f]\n", x, y);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector2<T> &v)
{
    Vector2<T> v2(v[0], v[1]);

    if (std::abs(v2[0]) < FLOAT_ERROR_MARGIN)
        v2[0] = 0;

    if (std::abs(v2[1]) < FLOAT_ERROR_MARGIN)
        v2[1] = 0;

    os << "vector[" << v2[0] << ", " << v2[1] << "]";
    return os;
}

// Specialization for float
template <>
constexpr bool Vector2<Float>::operator==(const Vector2<Float> &v) const
{
    return (std::abs(x - v.x) < FLOAT_ERROR_MARGIN) && (std::abs(y - v.y) < FLOAT_ERROR_MARGIN);
}

template <>
constexpr bool Vector2<Float>::operator!=(const Vector2<Float> &v) const
{
    return (std::abs(x - v.x) > FLOAT_ERROR_MARGIN) || (std::abs(y - v.y) > FLOAT_ERROR_MARGIN);
}

//------------------------------------------------------------------------------

template <typename T>
constexpr T dot(const Vector3<T> &v1, const Vector3<T> &v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

template <typename T>
constexpr T abs_dot(const Vector3<T> &v1, const Vector3<T> &v2)
{
    return std::abs(dot(v1, v2));
}

// Cross product
template <typename T>
constexpr Vector3<T> cross(const Vector3<T> &v1, const Vector3<T> &v2)
{
    return Vector3<T>((v1.y * v2.z) - (v1.z * v2.y),
                      (v1.z * v2.x) - (v1.x * v2.z),
                      (v1.x * v2.y) - (v1.y * v2.x));
}

template <typename T>
constexpr Vector3<T> normalize(const Vector3<T> &v)
{
    return v / v.length();
}

template <typename T>
constexpr Vector3<T> abs(const Vector3<T> &v)
{
    return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template <typename T>
constexpr Vector3<T> face_forward(const Vector3<T> &n, const Vector3<T> &v)
{
    return (dot(n, v) < 0.f) ? -n : n;
}

// 2D versions
template <typename T>
constexpr T dot(const Vector2<T> &v1, const Vector2<T> &v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

template <typename T>
constexpr T absDot(const Vector2<T> &v1, const Vector2<T> &v2)
{
    return std::abs(dot(v1, v2));
}

// Cross
template <typename T>
constexpr T cross(const Vector2<T> &v1, const Vector2<T> &v2)
{
    return (v1.x * v2.y) - (v1.y * v2.x);
}

template <typename T>
constexpr Vector2<T> normalize(const Vector2<T> &v)
{
    return v / v.length();
}

template <typename T>
constexpr Vector2<T> abs(const Vector2<T> &v)
{
    return Vector2<T>(std::abs(v.x), std::abs(v.y));
}

template <typename T>
constexpr Vector2<T> face_forward(const Vector2<T> &n, const Vector2<T> &v)
{
    return (dot(n, v) < 0.f) ? -n : n;
}

// Inverse * for Vector3
template <typename T>
constexpr Vector3<T> operator*(T f, const Vector3<T> &v)
{
    return v * f;
}

// Inverse * for Vector2
template <typename T>
constexpr Vector2<T> operator*(T f, const Vector2<T> &v)
{
    return v * f;
}

template <typename T>
constexpr Vector2<T> clamp(const Vector2<T> &v, const Vector2<T> &low, const Vector2<T> &high)
{
    return Vector2<T>(std::clamp(v.x, low.x, high.x), std::clamp(v.y, low.y, high.y));
}

template <typename T>
constexpr void generate_coordinate_system(const Vector3<T> &v1,
                                          Vector3<T> &v2,
                                          Vector3<T> &v3)
{
    if (std::abs(v1.x) > std::abs(v1.y))
        v2 = Vector3<T>(-v1.z, 0, v1.x) / sqrt(v1.x * v1.x + v1.z * v1.z);
    else
        v2 = Vector3<T>(0, v1.z, -v1.y) / sqrt(v1.y * v1.y + v1.z * v1.z);

    v3 = cross(v1, v2);
}

template <typename T>
constexpr T max_component(Vector3<T> v)
{
    return max(v.x, max(v.y, v.z));
}

template <typename T>
constexpr T max_component(Vector2<T> v)
{
    return std::max(v.x, v.y);
}

namespace math
{

    template <typename T>
    constexpr Vector3<T> clamp(const Vector3<T> &v, const Vector3<T> &low, const Vector3<T> &high)
    {
        return Vector3<T>(math::clamp(v.x, low.x, high.x),
                          math::clamp(v.y, low.y, high.y),
                          math::clamp(v.z, low.z, high.z));
    }

    template <typename T>
    constexpr Vector3<T> min(const Vector3<T> &v1, const Vector3<T> &v2)
    {
        return Vector3<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
    }

    template <typename T>
    constexpr Vector3<T> max(const Vector3<T> &v1, const Vector3<T> &v2)
    {
        return Vector3<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
    }

    template <typename T>
    constexpr Vector2<T> clamp(const Vector2<T> &v, const Vector2<T> &low, const Vector2<T> &high)
    {
        return Vector2<T>(std::clamp(v.x, low.x, high.x), std::clamp(v.y, low.y, high.y));
    }

    template <typename T>
    constexpr Vector2<T> min(const Vector2<T> &v1, const Vector2<T> &v2)
    {
        return Vector2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
    }

    template <typename T>
    constexpr Vector2<T> max(const Vector2<T> &v1, const Vector2<T> &v2)
    {
        return Vector2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
    }

}