#include "lib/spectrum.hpp"

std::ostream& operator<<(std::ostream& os, const SpectrumHDR& s)
{
    os << "(" << s.r << ", " << s.g << ", " << s.b << ", " << s.a << ")";
    return os;
}

RGBA SpectrumHDR::to_rgba() const
{
    // Escalate to 255
    Float r = this->r * 255;
    Float g = this->g * 255;
    Float b = this->b * 255;

    // Truncate pixels to 255 and convert to unsigned char
    return RGBA{(uint8_t)(math::clamp(r, (Float)0.0, (Float)255.0)), 
                (uint8_t)(math::clamp(g, (Float)0.0, (Float)255.0)), 
                (uint8_t)(math::clamp(b, (Float)0.0, (Float)255.0)),
                (uint8_t)(math::clamp(a * 255, (Float)0.0, (Float)255.0))};
}

Float SpectrumHDR::squared_norm() const
{
    return r * r + g * g + b * b;
}

Float SpectrumHDR::norm() const
{
    return std::sqrt(squared_norm());
}


//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const SpectrumRGB& s)
{
    os << "(" << (unsigned)s.r << ", " << (unsigned)s.g << ", " << (unsigned)s.b << ", " << (unsigned)s.a << ")";
    return os;
}

Float SpectrumRGB::squared_norm() const
{
    return r * r + g * g + b * b;
}

Float SpectrumRGB::norm() const
{
    return std::sqrt(squared_norm());
}