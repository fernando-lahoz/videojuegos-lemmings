#pragma once

#include "lib/types.hpp"
#include "math/math.hpp"

struct RGBA
{
    uint8_t r, g, b, a;
};

class SpectrumHDR
{
protected:
    Float r, g, b, a;

public:

    inline constexpr SpectrumHDR();    
    inline constexpr SpectrumHDR(Float r, Float g, Float b, Float a = 1.0);
    inline constexpr SpectrumHDR(Float v);

    inline constexpr Float get_r() const;
    inline constexpr Float get_g() const;
    inline constexpr Float get_b() const;
    inline constexpr Float get_a() const;

    inline constexpr void set_r(Float r);
    inline constexpr void set_g(Float g);
    inline constexpr void set_b(Float b);
    inline constexpr void set_a(Float a);

    inline constexpr bool is_black() const;

    RGBA to_rgba() const;

    inline constexpr Float brightness() const;

    inline constexpr SpectrumHDR operator+(const SpectrumHDR& s) const;
    inline constexpr SpectrumHDR& operator+=(const SpectrumHDR& s);

    inline constexpr SpectrumHDR operator-(const SpectrumHDR& s) const;
    inline constexpr SpectrumHDR& operator-=(const SpectrumHDR& s);

    inline constexpr SpectrumHDR operator*(const SpectrumHDR& s) const;
    inline constexpr SpectrumHDR operator*(Float s) const;
    inline constexpr SpectrumHDR& operator*=(const SpectrumHDR& s);
    inline constexpr SpectrumHDR& operator*=(Float s);

    inline constexpr SpectrumHDR operator/(const SpectrumHDR& s) const;
    inline constexpr SpectrumHDR operator/(Float s) const;
    inline constexpr SpectrumHDR& operator/=(const SpectrumHDR& s);
    inline constexpr SpectrumHDR& operator/=(Float s);

    inline constexpr bool operator==(const SpectrumHDR& s) const;
    inline constexpr bool operator!=(const SpectrumHDR& s) const;

    inline constexpr Float max_component() const;

    inline constexpr bool has_NaNs() const;
    inline constexpr bool has_Inf() const;

    Float squared_norm() const;
    Float norm() const;

    friend std::ostream& operator<<(std::ostream& os, const SpectrumHDR& s);
};

std::ostream& operator<<(std::ostream& os, const SpectrumHDR& s);

inline constexpr SpectrumHDR operator-(Float s, const SpectrumHDR& v);
inline constexpr SpectrumHDR operator*(Float s, const SpectrumHDR& v);
inline constexpr SpectrumHDR operator+(Float s, const SpectrumHDR& v);
inline constexpr SpectrumHDR operator/(Float s, const SpectrumHDR& v);

inline constexpr SpectrumHDR operator-(const SpectrumHDR& s);

inline constexpr SpectrumHDR sqrt(const SpectrumHDR& s);
inline constexpr SpectrumHDR exp(const SpectrumHDR& s);
inline constexpr SpectrumHDR pow(const SpectrumHDR& s, Float e);
inline constexpr Float sum(const SpectrumHDR& s);
inline constexpr SpectrumHDR abs(const SpectrumHDR& s);

//------------------------------------------------------------------------------

class SpectrumRGB
{
protected:
    uint8_t r, g, b, a;

public:

    inline constexpr SpectrumRGB();
    inline constexpr SpectrumRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a=255);
    inline constexpr SpectrumRGB(uint8_t v);

    inline constexpr uint8_t get_r() const;
    inline constexpr uint8_t get_g() const;
    inline constexpr uint8_t get_b() const;
    inline constexpr uint8_t get_a() const;

    inline constexpr void set_r(uint8_t r);
    inline constexpr void set_g(uint8_t g);
    inline constexpr void set_b(uint8_t b);
    inline constexpr void set_a(uint8_t a);

    inline constexpr bool is_black() const;

    inline constexpr RGBA to_rgba() const;

    inline constexpr Float brightness() const;

    inline constexpr SpectrumRGB operator+(const SpectrumRGB& s) const;
    inline constexpr SpectrumRGB& operator+=(const SpectrumRGB& s);

    inline constexpr SpectrumRGB operator-(const SpectrumRGB& s) const;
    inline constexpr SpectrumRGB& operator-=(const SpectrumRGB& s);

    inline constexpr SpectrumRGB operator*(const SpectrumRGB& s) const;
    inline constexpr SpectrumRGB operator*(Float s) const;
    inline constexpr SpectrumRGB& operator*=(const SpectrumRGB& s);
    inline constexpr SpectrumRGB& operator*=(Float s);

    inline constexpr SpectrumRGB operator/(const SpectrumRGB& s) const;
    inline constexpr SpectrumRGB operator/(Float s) const;
    inline constexpr SpectrumRGB& operator/=(const SpectrumRGB& s);
    inline constexpr SpectrumRGB& operator/=(Float s);

    inline constexpr bool operator==(const SpectrumRGB& s) const;
    inline constexpr bool operator!=(const SpectrumRGB& s) const;
    
    inline constexpr uint8_t max_component() const;

    inline constexpr bool has_NaNs() const;
    inline constexpr bool has_Inf() const;

    Float squared_norm() const;
    Float norm() const;

    friend std::ostream& operator<<(std::ostream& os, const SpectrumRGB& s);
};

std::ostream& operator<<(std::ostream& os, const SpectrumRGB& s);

inline constexpr SpectrumRGB operator-(Float s, const SpectrumRGB& v);
inline constexpr SpectrumRGB operator*(Float s, const SpectrumRGB& v);
inline constexpr SpectrumRGB operator+(Float s, const SpectrumRGB& v);
inline constexpr SpectrumRGB operator/(Float s, const SpectrumRGB& v);

inline constexpr SpectrumRGB sqrt(const SpectrumRGB& s);

inline constexpr SpectrumRGB exp(const SpectrumRGB& s);

inline constexpr SpectrumRGB operator-(const SpectrumRGB& s);

inline constexpr SpectrumRGB pow(const SpectrumRGB& s, Float e);

inline constexpr Float sum(const SpectrumRGB& s);

inline constexpr SpectrumRGB abs(const SpectrumRGB& s);

using Spectrum = SpectrumRGB;

#include "lib/spectrum.ipp"