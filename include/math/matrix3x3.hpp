#pragma once

#include "lib/types.hpp"
#include "geometry/vector.hpp"
#include "lib/spectrum.hpp"

template <typename T>
class Matrix3x3
{
public:
    T m00, m01, m02;
    T m10, m11, m12;
    T m20, m21, m22;

public:
    constexpr Matrix3x3() = default;

    constexpr Matrix3x3(T m00, T m01, T m02,
                        T m10, T m11, T m12,
                        T m20, T m21, T m22);

    constexpr Matrix3x3(const Matrix3x3<T>& other);
    constexpr Matrix3x3(Matrix3x3<T>&& other);
    constexpr Matrix3x3<T>& operator=(const Matrix3x3<T>& other);
    constexpr Matrix3x3<T>& operator=(Matrix3x3<T>&& other);

    constexpr Matrix3x3<T> operator*(const Matrix3x3<T>& other) const;
    constexpr Matrix3x3<T>& operator*=(const Matrix3x3<T>& other);
    constexpr Matrix3x3<T> operator*(T scalar) const;
    constexpr Matrix3x3<T>& operator*=(T scalar);

    constexpr Matrix3x3<T> operator+(const Matrix3x3<T>& other) const;
    constexpr Matrix3x3<T>& operator+=(const Matrix3x3<T>& other);

    constexpr Matrix3x3<T> operator-(const Matrix3x3<T>& other) const;

    // Multiply Vector3f
    constexpr Vector3<T> operator*(const Vector3<T>& vector) const;

    // Multiply spectrum
    constexpr Spectrum operator*(const Spectrum& v) const;
};

#include "math/matrix3x3.ipp"