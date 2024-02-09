#pragma once

#include "lib/spectrum.hpp"

constexpr SpectrumHDR::SpectrumHDR() : r(0), g(0), b(0), a(1) {}

constexpr SpectrumHDR::SpectrumHDR(Float r, Float g, Float b, Float a) : r(r), g(g), b(b), a(a) {}

constexpr SpectrumHDR::SpectrumHDR(Float v) : r(v), g(v), b(v), a(1) {}


constexpr Float SpectrumHDR::get_r() const { return r; }

constexpr Float SpectrumHDR::get_g() const { return g; }

constexpr Float SpectrumHDR::get_b() const { return b; }

constexpr Float SpectrumHDR::get_a() const { return a; }


constexpr void SpectrumHDR::set_r(Float r) { this->r = r; }

constexpr void SpectrumHDR::set_g(Float g) { this->g = g; }

constexpr void SpectrumHDR::set_b(Float b) { this->b = b; }

constexpr void SpectrumHDR::set_a(Float a) { this->a = a; }

constexpr bool SpectrumHDR::is_black() const
{
    return r == 0 && g == 0 && b == 0;
}

constexpr Float SpectrumHDR::brightness() const
{
    const Float redWeight   =  0.212671f;
    const Float greenWeight =  0.715160f;
    const Float blueWeight  =  0.072169f;
    
    return redWeight * r + greenWeight * g + blueWeight * b;
}

constexpr SpectrumHDR SpectrumHDR::operator+(const SpectrumHDR& s) const
{
    return SpectrumHDR(r + s.r, g + s.g, b + s.b);
}

constexpr SpectrumHDR SpectrumHDR::operator-(const SpectrumHDR& s) const
{
    return SpectrumHDR(r - s.r, g - s.g, b - s.b);
}

constexpr SpectrumHDR SpectrumHDR::operator*(const SpectrumHDR& s) const
{
    return SpectrumHDR(r * s.r, g * s.g, b * s.b);
}

constexpr SpectrumHDR SpectrumHDR::operator*(Float s) const
{
    return SpectrumHDR(r * s, g * s, b * s);
}

constexpr SpectrumHDR SpectrumHDR::operator/(const SpectrumHDR& s) const
{
    return SpectrumHDR(r / s.r, g / s.g, b / s.b);
}

constexpr SpectrumHDR SpectrumHDR::operator/(Float s) const
{
    return SpectrumHDR(r / s, g / s, b / s);
}

constexpr SpectrumHDR& SpectrumHDR::operator+=(const SpectrumHDR& s)
{
    r += s.r;
    g += s.g;
    b += s.b;
    return *this;
}

constexpr SpectrumHDR& SpectrumHDR::operator-=(const SpectrumHDR& s)
{
    r -= s.r;
    g -= s.g;
    b -= s.b;
    return *this;
}

constexpr SpectrumHDR& SpectrumHDR::operator*=(const SpectrumHDR& s)
{
    r *= s.r;
    g *= s.g;
    b *= s.b;
    return *this;
}

constexpr SpectrumHDR& SpectrumHDR::operator*=(Float s)
{
    r *= s;
    g *= s;
    b *= s;
    return *this;
}

constexpr SpectrumHDR& SpectrumHDR::operator/=(const SpectrumHDR& s)
{
    r /= s.r;
    g /= s.g;
    b /= s.b;
    return *this;
}

constexpr SpectrumHDR& SpectrumHDR::operator/=(Float s)
{
    r /= s;
    g /= s;
    b /= s;
    return *this;
}

constexpr bool SpectrumHDR::operator==(const SpectrumHDR& s) const
{
    return r == s.r && g == s.g && b == s.b;
}

constexpr bool SpectrumHDR::operator!=(const SpectrumHDR& s) const
{
    return r != s.r || g != s.g || b != s.b;
}

constexpr Float SpectrumHDR::max_component() const
{
    return std::max(r, std::max(g, b));
}

constexpr bool SpectrumHDR::has_NaNs() const
{
    return std::isnan(r) || std::isnan(g) || std::isnan(b);
}

constexpr bool SpectrumHDR::has_Inf() const
{
    return std::isinf(r) || std::isinf(g) || std::isinf(b);
}


constexpr SpectrumHDR operator-(Float s, const SpectrumHDR& v)
{
    return SpectrumHDR(s) - v;
}

constexpr SpectrumHDR operator*(Float s, const SpectrumHDR& v)
{
    return v * s;
}

constexpr SpectrumHDR operator+(Float s, const SpectrumHDR& v)
{
    return v + s;
}

constexpr SpectrumHDR operator/(Float s, const SpectrumHDR& v)
{
    return SpectrumHDR(s) / v;
}

constexpr SpectrumHDR sqrt(const SpectrumHDR& s)
{
    return SpectrumHDR(std::sqrt(s.get_r()), std::sqrt(s.get_g()), std::sqrt(s.get_b()));
}

constexpr SpectrumHDR exp(const SpectrumHDR& s)
{
    return SpectrumHDR(std::exp(s.get_r()), std::exp(s.get_g()), std::exp(s.get_b()));
}

constexpr SpectrumHDR operator-(const SpectrumHDR& s)
{
    return SpectrumHDR(-s.get_r(), -s.get_g(), -s.get_b());
}

constexpr SpectrumHDR pow(const SpectrumHDR& s, Float e)
{
    return SpectrumHDR(std::pow(s.get_r(), e), std::pow(s.get_g(), e), std::pow(s.get_b(), e));
}

constexpr Float sum(const SpectrumHDR& s)
{
    return s.get_r() + s.get_g() + s.get_b();
}

constexpr SpectrumHDR abs(const SpectrumHDR& s)
{
    return SpectrumHDR(std::abs(s.get_r()), std::abs(s.get_g()), std::abs(s.get_b()));
}

//------------------------------------------------------------------------------


constexpr SpectrumRGB::SpectrumRGB() : r(0), g(0), b(0), a(1) {}

constexpr SpectrumRGB::SpectrumRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

constexpr SpectrumRGB::SpectrumRGB(uint8_t v) : r(v), g(v), b(v), a(1) {}


constexpr uint8_t SpectrumRGB::get_r() const { return r; }

constexpr uint8_t SpectrumRGB::get_g() const { return g; }

constexpr uint8_t SpectrumRGB::get_b() const { return b; }

constexpr uint8_t SpectrumRGB::get_a() const { return a; }


constexpr void SpectrumRGB::set_r(uint8_t r) { this->r = r; }

constexpr void SpectrumRGB::set_g(uint8_t g) { this->g = g; }

constexpr void SpectrumRGB::set_b(uint8_t b) { this->b = b; }

constexpr void SpectrumRGB::set_a(uint8_t a) { this->a = a; }

constexpr bool SpectrumRGB::is_black() const
{
    return r == 0 && g == 0 && b == 0;
}

constexpr RGBA SpectrumRGB::to_rgba() const
{
    return RGBA(r, g, b, a);
}

constexpr Float SpectrumRGB::brightness() const
{
    const Float redWeight   =  0.212671f;
    const Float greenWeight =  0.715160f;
    const Float blueWeight  =  0.072169f;
    
    return redWeight * r + greenWeight * g + blueWeight * b;
}

constexpr SpectrumRGB SpectrumRGB::operator+(const SpectrumRGB& s) const
{
    return SpectrumRGB(r + s.r, g + s.g, b + s.b);
}

constexpr SpectrumRGB SpectrumRGB::operator-(const SpectrumRGB& s) const
{
    return SpectrumRGB(r - s.r, g - s.g, b - s.b);
}

constexpr SpectrumRGB SpectrumRGB::operator*(const SpectrumRGB& s) const
{
    return SpectrumRGB(r * s.r, g * s.g, b * s.b);
}

constexpr SpectrumRGB SpectrumRGB::operator*(Float s) const
{
    return SpectrumRGB(r * s, g * s, b * s);
}

constexpr SpectrumRGB SpectrumRGB::operator/(const SpectrumRGB& s) const
{
    return SpectrumRGB(r / s.r, g / s.g, b / s.b);
}

constexpr SpectrumRGB SpectrumRGB::operator/(Float s) const
{
    return SpectrumRGB(r / s, g / s, b / s);
}

constexpr SpectrumRGB& SpectrumRGB::operator+=(const SpectrumRGB& s)
{
    r += s.r;
    g += s.g;
    b += s.b;
    return *this;
}

constexpr SpectrumRGB& SpectrumRGB::operator-=(const SpectrumRGB& s)
{
    r -= s.r;
    g -= s.g;
    b -= s.b;
    return *this;
}

constexpr SpectrumRGB& SpectrumRGB::operator*=(const SpectrumRGB& s)
{
    r *= s.r;
    g *= s.g;
    b *= s.b;
    return *this;
}

constexpr SpectrumRGB& SpectrumRGB::operator*=(Float s)
{
    r *= s;
    g *= s;
    b *= s;
    return *this;
}

constexpr SpectrumRGB& SpectrumRGB::operator/=(const SpectrumRGB& s)
{
    r /= s.r;
    g /= s.g;
    b /= s.b;
    return *this;
}

constexpr SpectrumRGB& SpectrumRGB::operator/=(Float s)
{
    r /= s;
    g /= s;
    b /= s;
    return *this;
}

constexpr bool SpectrumRGB::operator==(const SpectrumRGB& s) const
{
    return r == s.r && g == s.g && b == s.b;
}

constexpr bool SpectrumRGB::operator!=(const SpectrumRGB& s) const
{
    return r != s.r || g != s.g || b != s.b;
}

constexpr uint8_t SpectrumRGB::max_component() const
{
    return std::max(r, std::max(g, b));
}

constexpr bool SpectrumRGB::has_NaNs() const
{
    return std::isnan(r) || std::isnan(g) || std::isnan(b);
}

constexpr bool SpectrumRGB::has_Inf() const
{
    return std::isinf(r) || std::isinf(g) || std::isinf(b);
}

constexpr SpectrumRGB operator-(Float s, const SpectrumRGB& v)
{
    return SpectrumRGB(s) - v;
}

constexpr SpectrumRGB operator*(Float s, const SpectrumRGB& v)
{
    return v * s;
}

constexpr SpectrumRGB operator+(Float s, const SpectrumRGB& v)
{
    return v + s;
}

constexpr SpectrumRGB operator/(Float s, const SpectrumRGB& v)
{
    return SpectrumRGB(s) / v;
}

constexpr SpectrumRGB sqrt(const SpectrumRGB& s)
{
    return SpectrumRGB(std::sqrt(s.get_r()), std::sqrt(s.get_g()), std::sqrt(s.get_b()));
}

constexpr SpectrumRGB exp(const SpectrumRGB& s)
{
    return SpectrumRGB(std::exp(s.get_r()), std::exp(s.get_g()), std::exp(s.get_b()));
}

constexpr SpectrumRGB operator-(const SpectrumRGB& s)
{
    return SpectrumRGB(-s.get_r(), -s.get_g(), -s.get_b());
}

constexpr SpectrumRGB pow(const SpectrumRGB& s, Float e)
{
    return SpectrumRGB(std::pow(s.get_r(), e), std::pow(s.get_g(), e), std::pow(s.get_b(), e));
}

constexpr Float sum(const SpectrumRGB& s)
{
    return s.get_r() + s.get_g() + s.get_b();
}

constexpr SpectrumRGB abs(const SpectrumRGB& s)
{
    return SpectrumRGB(std::abs(s.get_r()), std::abs(s.get_g()), std::abs(s.get_b()));
}
