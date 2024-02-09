#pragma once

#include "math/matrix3x3.hpp"

template <typename T>
constexpr Matrix3x3<T>::Matrix3x3(T m00, T m01, T m02,
                     T m10, T m11, T m12,
                     T m20, T m21, T m22)
    : m00(m00), m01(m01), m02(m02),
      m10(m10), m11(m11), m12(m12),
      m20(m20), m21(m21), m22(m22)
{
}

template <typename T>
constexpr Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& other)
    : m00(other.m00), m01(other.m01), m02(other.m02),
        m10(other.m10), m11(other.m11), m12(other.m12),
        m20(other.m20), m21(other.m21), m22(other.m22)
{
}

template <typename T>
constexpr Matrix3x3<T>::Matrix3x3(Matrix3x3<T>&& other)
    : m00(other.m00), m01(other.m01), m02(other.m02),
        m10(other.m10), m11(other.m11), m12(other.m12),
        m20(other.m20), m21(other.m21), m22(other.m22)
{
}

template <typename T>
constexpr Matrix3x3<T>& Matrix3x3<T>::operator=(const Matrix3x3<T>& other)
{
    m00 = other.m00;
    m01 = other.m01;
    m02 = other.m02;
    m10 = other.m10;
    m11 = other.m11;
    m12 = other.m12;
    m20 = other.m20;
    m21 = other.m21;
    m22 = other.m22;
    return *this;
}

template <typename T>
constexpr Matrix3x3<T>& Matrix3x3<T>::operator=(Matrix3x3<T>&& other)
{
    m00 = other.m00;
    m01 = other.m01;
    m02 = other.m02;
    m10 = other.m10;
    m11 = other.m11;
    m12 = other.m12;
    m20 = other.m20;
    m21 = other.m21;
    m22 = other.m22;
    return *this;
}

template <typename T>
constexpr Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T>& other) const
{
    return Matrix3x3<T>(
        m00 * other.m00 + m01 * other.m10 + m02 * other.m20,
        m00 * other.m01 + m01 * other.m11 + m02 * other.m21,
        m00 * other.m02 + m01 * other.m12 + m02 * other.m22,
        m10 * other.m00 + m11 * other.m10 + m12 * other.m20,
        m10 * other.m01 + m11 * other.m11 + m12 * other.m21,
        m10 * other.m02 + m11 * other.m12 + m12 * other.m22,
        m20 * other.m00 + m21 * other.m10 + m22 * other.m20,
        m20 * other.m01 + m21 * other.m11 + m22 * other.m21,
        m20 * other.m02 + m21 * other.m12 + m22 * other.m22);
}

template <typename T>
constexpr Matrix3x3<T>& Matrix3x3<T>::operator*=(const Matrix3x3<T>& other)
{
    *this = *this * other;
    return *this;
}

template <typename T>
constexpr Matrix3x3<T> Matrix3x3<T>::operator*(T scalar) const
{
    return Matrix3x3<T>(
        m00 * scalar, m01 * scalar, m02 * scalar,
        m10 * scalar, m11 * scalar, m12 * scalar,
        m20 * scalar, m21 * scalar, m22 * scalar);
}

template <typename T>
constexpr Matrix3x3<T>& Matrix3x3<T>::operator*=(T scalar)
{
    *this = *this * scalar;
    return *this;
}

template <typename T>
constexpr Matrix3x3<T> Matrix3x3<T>::operator+(const Matrix3x3<T>& other) const
{
    return Matrix3x3<T>(
        m00 + other.m00, m01 + other.m01, m02 + other.m02,
        m10 + other.m10, m11 + other.m11, m12 + other.m12,
        m20 + other.m20, m21 + other.m21, m22 + other.m22);
}

template <typename T>
constexpr Matrix3x3<T>& Matrix3x3<T>::operator+=(const Matrix3x3<T>& other)
{
    *this = *this + other;
    return *this;
}

template <typename T>
constexpr Matrix3x3<T> Matrix3x3<T>::operator-(const Matrix3x3<T>& other) const
{
    return Matrix3x3<T>(
        m00 - other.m00, m01 - other.m01, m02 - other.m02,
        m10 - other.m10, m11 - other.m11, m12 - other.m12,
        m20 - other.m20, m21 - other.m21, m22 - other.m22);
}

// Multiply Vector3f
template <typename T>
constexpr Vector3<T> Matrix3x3<T>::operator*(const Vector3<T>& vector) const
{
    return Vector3<T>(
        m00 * vector.x + m01 * vector.y + m02 * vector.z,
        m10 * vector.x + m11 * vector.y + m12 * vector.z,
        m20 * vector.x + m21 * vector.y + m22 * vector.z);
}

// Multiply spectrum
template <typename T>
constexpr Spectrum Matrix3x3<T>::operator*(const Spectrum& v) const
{
    double x = m00 * v.get_r() + m01 * v.get_g() + m02 * v.get_b();
    double y = m10 * v.get_r() + m11 * v.get_g() + m12 * v.get_b();
    double z = m20 * v.get_r() + m21 * v.get_g() + m22 * v.get_b();
    return Spectrum(x, y, z);
}
