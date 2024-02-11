#include "geometry/ray.hpp"

std::ostream& operator<<(std::ostream& os, const Ray &ray) 
{
    os << "ray[origin=" << ray.origin << ", direction=" << ray.direction << ", maximum_offset="
        << ray.maximum_offset << "]";
        
    return os;
}

void Ray::print() const
{
    printf("Ray[origin=%f, %f, %f, direction=%f, %f, %f, maximum_offset=%f, time=%f]\n", 
            origin.x, origin.y, origin.z, direction.x, direction.y, direction.z, maximum_offset);
}
