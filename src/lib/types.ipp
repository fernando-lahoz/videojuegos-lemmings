#pragma once

#include "lib/types.hpp"

inline constexpr ErrorFloat::ErrorFloat() noexcept
    : data(0.0), err(0.0) 
{}
    
inline constexpr ErrorFloat::ErrorFloat(Float data, Float err) noexcept
    : data(data), err(err) 
{}

inline constexpr ErrorFloat ErrorFloat::operator+(ErrorFloat rhs) const noexcept
{
    ErrorFloat ret;
    ret.data = data + rhs.data;
    ret.err = err + rhs.err;
    return ret;
}

inline constexpr ErrorFloat ErrorFloat::operator-(ErrorFloat rhs) const noexcept
{
    ErrorFloat ret;
    ret.data = data - rhs.data;
    ret.err = err + rhs.err;
    return ret;
}

inline constexpr ErrorFloat ErrorFloat::operator*(ErrorFloat rhs) const noexcept
{
    ErrorFloat ret;
    ret.data = data * rhs.data;
    ret.err = abs(ret.data) * rhs.err + abs(rhs.data) * err;
    return ret;
}

inline constexpr ErrorFloat ErrorFloat::operator*(Float rhs) const noexcept
{
    ErrorFloat ret;
    ret.data = data * rhs;
    ret.err = abs(ret.data) * err;
    return ret;
}

inline constexpr ErrorFloat ErrorFloat::operator/(ErrorFloat rhs) const noexcept
{
    ErrorFloat ret;
    ret.data = data / rhs.data;
    ret.err = (abs(ret.data) * rhs.err + abs(rhs.data) * err) / (rhs.data * rhs.data);
    return ret;
}

inline constexpr bool ErrorFloat::operator==(ErrorFloat rhs) const noexcept
{
    return data == rhs.data && err == rhs.err;
}

inline constexpr bool ErrorFloat::operator!=(ErrorFloat rhs) const noexcept
{
    return data != rhs.data || err != rhs.err;
}

inline constexpr bool ErrorFloat::operator<(ErrorFloat rhs) const noexcept
{
    return data < rhs.data;
}

inline constexpr Float ErrorFloat::upper_bound() const noexcept
{
    return data + err;
}

inline constexpr Float ErrorFloat::lower_bound() const noexcept
{
    return data - err;
}

inline constexpr ErrorFloat::operator float() const noexcept
{
    return data;
}

inline constexpr ErrorFloat::operator double() const noexcept
{
    return data;
}

inline constexpr ErrorFloat operator/(Float lhs, ErrorFloat rhs) noexcept
{
    ErrorFloat ret;
    ret.data = lhs / rhs.data;
    ret.err = (abs(ret.data) * rhs.err) / (rhs.data * rhs.data);
    return ret;
}

inline constexpr ErrorFloat operator*(Float lhs, ErrorFloat rhs) noexcept
{
    ErrorFloat ret;
    ret.data = lhs * rhs.data;
    ret.err = abs(ret.data) * rhs.err;
    return ret;
}

inline constexpr ErrorFloat sqrt(ErrorFloat f) noexcept
{
    ErrorFloat ret;
    ret.data = sqrt(f.data);
    ret.err = 0.5 * f.err / ret.data;
    return ret;
}
