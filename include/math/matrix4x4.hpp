#pragma once

#include "lib/types.hpp"

template <typename T>
class Matrix4x4
{
private:
    T m[4][4];

public:
    // TODO: método dedicado para crear la identidad, por defecto debería ser todo 0s
    constexpr Matrix4x4();
    constexpr Matrix4x4 (T other[]);
    constexpr Matrix4x4(T m00, T m01, T m02, T m03,
                        T m10, T m11, T m12, T m13,
                        T m20, T m21, T m22, T m23,
                        T m30, T m31, T m32, T m33);
    constexpr Matrix4x4(const Matrix4x4<T>& other);

    constexpr Matrix4x4<T>& operator=(const Matrix4x4<T>& other);

    constexpr Matrix4x4<T> operator*(Matrix4x4<T> const& obj) const;

    constexpr Matrix4x4<T> operator*(T const& obj) const;

    constexpr Matrix4x4<T> operator+(Matrix4x4<T> const& obj) const;
    constexpr Matrix4x4<T> operator+(T const& obj) const;

    constexpr Matrix4x4<T> operator-(Matrix4x4<T> const& obj) const;
    constexpr Matrix4x4<T> operator-(T const& obj) const;
    constexpr Matrix4x4<T> operator/(T const& obj) const;

    constexpr Matrix4x4<T> operator+=(Matrix4x4<T> const& obj) const;
    constexpr Matrix4x4<T> operator+=(T const& obj) const;

    constexpr Matrix4x4<T> operator-=(Matrix4x4<T> const& obj) const;
    constexpr Matrix4x4<T> operator-=(T const& obj) const;

    constexpr Matrix4x4<T> operator*=(Matrix4x4<T> const& obj) const;
    constexpr Matrix4x4<T> operator*=(T const& obj) const;

    constexpr Matrix4x4<T> operator/=(T const& obj) const;

    //TODO: m[] devuelve puntero -> que devuelva array?
    constexpr T* operator[](int i);

    constexpr const T* operator[](int i) const;

    constexpr bool operator==(Matrix4x4<T> const& obj) const;

    constexpr bool operator!=(Matrix4x4<T> const& obj) const;
    
    // Fills the array with the matrix data
    constexpr void get_array(T array[]) const;
};

template <typename T>
constexpr Matrix4x4<T> transpose(const Matrix4x4<T> &obj);

// From the MESA implementation of the GLU library
template <typename T>
constexpr Matrix4x4<T> inverse(const Matrix4x4<T> &matrix);

using Matrix4x4f = Matrix4x4<Float>;
using Matrix4x4i = Matrix4x4<int>;

#include "math/matrix4x4.ipp"