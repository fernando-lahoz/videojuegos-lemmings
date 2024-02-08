#pragma once

#include "types.h"
#include "../math/math.cpp"

struct RGBA
{
    u_int8_t r, g, b, a;

    RGBA(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
    : r(r), g(g), b(b), a(a) {}
};

class SpectrumHDR
{
    protected:
    double r, g, b, a;

    public:

    SpectrumHDR() : r(0), g(0), b(0), a(1) {}
    
    SpectrumHDR(double r, double g, double b, double a=1.0) : r(r), g(g), b(b), a(a) {}
    
    SpectrumHDR(double v) : r(v), g(v), b(v), a(1) {}

    
    double getR() const { return r; }
    
    double getG() const { return g; }
    
    double getB() const { return b; }

    double getA() const { return a; }


    void setR(double r) { this->r = r; }

    void setG(double g) { this->g = g; }

    void setB(double b) { this->b = b; }

    void setA(double a) { this->a = a; }

    bool isBlack() const
    {
        return r == 0 && g == 0 && b == 0;
    }

    RGBA toRGBA() const
    {
        // Escalate to 255
        double r = this->r * 255;
        double g = this->g * 255;
        double b = this->b * 255;

        // Truncate pixels to 255 and convert to unsigned char
        return RGBA{ (u_int8_t)(clamp(r, 0.0, 255.0)), 
                    (u_int8_t)(clamp(g, 0.0, 255.0)), 
                    (u_int8_t)(clamp(b, 0.0, 255.0)),
                    (u_int8_t)(clamp(a*255, 0.0, 255.0))};
    }

    double brightness() const
    {
        const double redWeight   =  0.212671f;
        const double greenWeight =  0.715160f;
        const double blueWeight  =  0.072169f;
        
        return redWeight * r + greenWeight * g + blueWeight * b;
    }

    SpectrumHDR operator+(const SpectrumHDR& s) const
    {
        return SpectrumHDR(r + s.r, g + s.g, b + s.b);
    }

    SpectrumHDR operator-(const SpectrumHDR& s) const
    {
        return SpectrumHDR(r - s.r, g - s.g, b - s.b);
    }

    SpectrumHDR operator*(const SpectrumHDR& s) const
    {
        return SpectrumHDR(r * s.r, g * s.g, b * s.b);
    }

    SpectrumHDR operator*(double s) const
    {
        return SpectrumHDR(r * s, g * s, b * s);
    }

    SpectrumHDR operator/(const SpectrumHDR& s) const
    {
        return SpectrumHDR(r / s.r, g / s.g, b / s.b);
    }

    SpectrumHDR operator/(double s) const
    {
        return SpectrumHDR(r / s, g / s, b / s);
    }

    SpectrumHDR& operator+=(const SpectrumHDR& s)
    {
        r += s.r;
        g += s.g;
        b += s.b;
        return *this;
    }

    SpectrumHDR& operator-=(const SpectrumHDR& s)
    {
        r -= s.r;
        g -= s.g;
        b -= s.b;
        return *this;
    }

    SpectrumHDR& operator*=(const SpectrumHDR& s)
    {
        r *= s.r;
        g *= s.g;
        b *= s.b;
        return *this;
    }

    SpectrumHDR& operator*=(double s)
    {
        r *= s;
        g *= s;
        b *= s;
        return *this;
    }

    SpectrumHDR& operator/=(const SpectrumHDR& s)
    {
        r /= s.r;
        g /= s.g;
        b /= s.b;
        return *this;
    }

    SpectrumHDR& operator/=(double s)
    {
        r /= s;
        g /= s;
        b /= s;
        return *this;
    }

    bool operator==(const SpectrumHDR& s) const
    {
        return r == s.r && g == s.g && b == s.b;
    }

    bool operator!=(const SpectrumHDR& s) const
    {
        return r != s.r || g != s.g || b != s.b;
    }

    // Operator <<
    friend std::ostream& operator<<(std::ostream& os, const SpectrumHDR& s)
    {
        os << "(" << s.r << ", " << s.g << ", " << s.b << ", " << s.a << ")";
        return os;
    }

    inline double maxComponent() const
    {
        return std::max(r, std::max(g, b));
    }

    bool hasNaNs() const
    {
        return std::isnan(r) || std::isnan(g) || std::isnan(b);
    }

    bool hasInf() const
    {
        return std::isinf(r) || std::isinf(g) || std::isinf(b);
    }

    Float squaredNorm() const
    {
        return r * r + g * g + b * b;
    }

    Float norm() const
    {
        return sqrt(squaredNorm());
    }
};

// Inverse int - operato
inline SpectrumHDR operator-(int s, const SpectrumHDR& v)
{
    return SpectrumHDR(s) - v;
}


//Inverse float * operato
inline SpectrumHDR operator*(Float s, const SpectrumHDR& v)
{
    return v * s;
}

//Inverse float + operato
inline SpectrumHDR operator+(Float s, const SpectrumHDR& v)
{
    return v + s;
}
inline SpectrumHDR pow2(SpectrumHDR s)
{
    return SpectrumHDR(s.getR() * s.getR(), s.getG() * s.getG(), s.getB() * s.getB());
}
inline SpectrumHDR pow3(SpectrumHDR s)
{
    return SpectrumHDR(s.getR() * s.getR() * s.getR(), s.getG() * s.getG() * s.getG(), s.getB() * s.getB() * s.getB());
}

// Inverse / operator (ej: 1 / SpectrumHDR
inline SpectrumHDR operator/(double s, const SpectrumHDR& v)
{
    return SpectrumHDR(s) / v;
}

// Sqr
inline SpectrumHDR sqrt(const SpectrumHDR& s)
{
    return SpectrumHDR(sqrt(s.getR()), sqrt(s.getG()), sqrt(s.getB()));
}

// ex
inline SpectrumHDR exp(const SpectrumHDR& s)
{
    return SpectrumHDR(exp(s.getR()), exp(s.getG()), exp(s.getB()));
}

// - operan
inline SpectrumHDR operator-(const SpectrumHDR& s)
{
    return SpectrumHDR(-s.getR(), -s.getG(), -s.getB());
}

// po
inline SpectrumHDR pow(const SpectrumHDR& s, double e)
{
    return SpectrumHDR(pow(s.getR(), e), pow(s.getG(), e), pow(s.getB(), e));
}
inline Float sum(const SpectrumHDR& s)
{
    return s.getR() + s.getG() + s.getB();
}
inline SpectrumHDR abs(const SpectrumHDR& s)
{
    return SpectrumHDR(abs(s.getR()), abs(s.getG()), abs(s.getB()));
}




/*****************************************************************************/
/****************************** Spectrum RGB *********************************/
/*****************************************************************************/


class SpectrumRGB
{
    protected:
    u_int8_t r, g, b, a;

    public:

    SpectrumRGB() : r(0), g(0), b(0), a(1) {}
    
    SpectrumRGB(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a=255) : r(r), g(g), b(b), a(a) {}
    
    SpectrumRGB(u_int8_t v) : r(v), g(v), b(v), a(1) {}

    
    u_int8_t getR() const { return r; }
    
    u_int8_t getG() const { return g; }
    
    u_int8_t getB() const { return b; }

    u_int8_t getA() const { return a; }


    void setR(u_int8_t r) { this->r = r; }

    void setG(u_int8_t g) { this->g = g; }

    void setB(u_int8_t b) { this->b = b; }

    void setA(u_int8_t a) { this->a = a; }

    bool isBlack() const
    {
        return r == 0 && g == 0 && b == 0;
    }

    RGBA toRGB() const
    {
        return RGBA(r, g, b, a);
    }

    double brightness() const
    {
        const double redWeight   =  0.212671f;
        const double greenWeight =  0.715160f;
        const double blueWeight  =  0.072169f;
        
        return redWeight * r + greenWeight * g + blueWeight * b;
    }

    SpectrumRGB operator+(const SpectrumRGB& s) const
    {
        return SpectrumRGB(r + s.r, g + s.g, b + s.b);
    }

    SpectrumRGB operator-(const SpectrumRGB& s) const
    {
        return SpectrumRGB(r - s.r, g - s.g, b - s.b);
    }

    SpectrumRGB operator*(const SpectrumRGB& s) const
    {
        return SpectrumRGB(r * s.r, g * s.g, b * s.b);
    }

    SpectrumRGB operator*(double s) const
    {
        return SpectrumRGB(r * s, g * s, b * s);
    }

    SpectrumRGB operator/(const SpectrumRGB& s) const
    {
        return SpectrumRGB(r / s.r, g / s.g, b / s.b);
    }

    SpectrumRGB operator/(double s) const
    {
        return SpectrumRGB(r / s, g / s, b / s);
    }

    SpectrumRGB& operator+=(const SpectrumRGB& s)
    {
        r += s.r;
        g += s.g;
        b += s.b;
        return *this;
    }

    SpectrumRGB& operator-=(const SpectrumRGB& s)
    {
        r -= s.r;
        g -= s.g;
        b -= s.b;
        return *this;
    }

    SpectrumRGB& operator*=(const SpectrumRGB& s)
    {
        r *= s.r;
        g *= s.g;
        b *= s.b;
        return *this;
    }

    SpectrumRGB& operator*=(double s)
    {
        r *= s;
        g *= s;
        b *= s;
        return *this;
    }

    SpectrumRGB& operator/=(const SpectrumRGB& s)
    {
        r /= s.r;
        g /= s.g;
        b /= s.b;
        return *this;
    }

    SpectrumRGB& operator/=(double s)
    {
        r /= s;
        g /= s;
        b /= s;
        return *this;
    }

    bool operator==(const SpectrumRGB& s) const
    {
        return r == s.r && g == s.g && b == s.b;
    }

    bool operator!=(const SpectrumRGB& s) const
    {
        return r != s.r || g != s.g || b != s.b;
    }

    // Operator <<
    friend std::ostream& operator<<(std::ostream& os, const SpectrumRGB& s)
    {
        os << "(" << (uint)s.r << ", " << (uint)s.g << ", " << (uint)s.b << ", " << (uint)s.a << ")";
        return os;
    }

    inline u_int8_t maxComponent() const
    {
        return std::max(r, std::max(g, b));
    }

    bool hasNaNs() const
    {
        return std::isnan(r) || std::isnan(g) || std::isnan(b);
    }

    bool hasInf() const
    {
        return std::isinf(r) || std::isinf(g) || std::isinf(b);
    }

    Float squaredNorm() const
    {
        return r * r + g * g + b * b;
    }

    Float norm() const
    {
        return sqrt(squaredNorm());
    }
};

// Inverse int - operato
inline SpectrumRGB operator-(int s, const SpectrumRGB& v)
{
    return SpectrumRGB(s) - v;
}


//Inverse float * operato
inline SpectrumRGB operator*(Float s, const SpectrumRGB& v)
{
    return v * s;
}

//Inverse float + operato
inline SpectrumRGB operator+(Float s, const SpectrumRGB& v)
{
    return v + s;
}
inline SpectrumRGB pow2(SpectrumRGB s)
{
    return SpectrumRGB(s.getR() * s.getR(), s.getG() * s.getG(), s.getB() * s.getB());
}
inline SpectrumRGB pow3(SpectrumRGB s)
{
    return SpectrumRGB(s.getR() * s.getR() * s.getR(), s.getG() * s.getG() * s.getG(), s.getB() * s.getB() * s.getB());
}

// Inverse / operator (ej: 1 / SpectrumRGB
inline SpectrumRGB operator/(double s, const SpectrumRGB& v)
{
    return SpectrumRGB(s) / v;
}

// Sqr
inline SpectrumRGB sqrt(const SpectrumRGB& s)
{
    return SpectrumRGB(sqrt(s.getR()), sqrt(s.getG()), sqrt(s.getB()));
}

// ex
inline SpectrumRGB exp(const SpectrumRGB& s)
{
    return SpectrumRGB(exp(s.getR()), exp(s.getG()), exp(s.getB()));
}

// - operan
inline SpectrumRGB operator-(const SpectrumRGB& s)
{
    return SpectrumRGB(-s.getR(), -s.getG(), -s.getB());
}

// po
inline SpectrumRGB pow(const SpectrumRGB& s, double e)
{
    return SpectrumRGB(pow(s.getR(), e), pow(s.getG(), e), pow(s.getB(), e));
}
inline Float sum(const SpectrumRGB& s)
{
    return s.getR() + s.getG() + s.getB();
}
inline SpectrumRGB abs(const SpectrumRGB& s)
{
    return SpectrumRGB(abs(s.getR()), abs(s.getG()), abs(s.getB()));
}


typedef SpectrumRGB Spectrum;