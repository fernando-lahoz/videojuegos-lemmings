#include "math/math.hpp"

namespace math {

bool quadratic (ErrorFloat a, ErrorFloat b, ErrorFloat c,
        ErrorFloat &solution0, ErrorFloat &solution1)
{
    ErrorFloat discriminant = b*b - (Float)4.0*a*c;

    if (discriminant < ErrorFloat(0.0)) 
        return false;
        
    ErrorFloat root_discriminant = sqrt(discriminant);

    ErrorFloat q;

    if (b < ErrorFloat(0.0)) 
        q = Float(-0.5) * (b - root_discriminant);
    else
        q = Float(-0.5) * (b + root_discriminant);

    solution0 = q / a;
    solution1 = c / q;

    if (solution0.data > solution1.data) 
        std::swap(solution0, solution1);

    return !std::isnan(solution0.data) && !std::isnan(solution1.data);
}

} //namespace math