#pragma once

#include <iostream>

#include "Vector.cpp"
#include "Point.cpp"
#include "../lib/types.h"

#pragma once

class Ray
{
    public:
    Point3f origin;
    Vector3f direction;
    Vector3f invDirection;

    bool cameraRay = false;

    mutable Float maximumOffset;
    Float time;

    Ray() 
    : maximumOffset(INFINITY), time(0.f)
    { }

    Ray(const Point3f &origin, const Vector3f &direction, Float maximumOffset = INFINITY,
            Float time = 0.f,
            bool _cameraRay = false)
        : origin(origin), direction(direction), 
            maximumOffset(maximumOffset), time(time),
            invDirection(1 / direction.x, 1 / direction.y, 1 / direction.z),
            cameraRay(_cameraRay) 
    { }

    // Returns a point along the ray at a given offset
    Point3f operator()(Float offset) const { 
        return origin + direction * offset; 
    }

    bool hasNaNs() const {
        return (origin.hasNaNs() || direction.hasNaNs() || std::isnan(maximumOffset));
    }

    friend std::ostream& operator<<(std::ostream& os, const Ray &ray) 
    {
        os << "ray[origin=" << ray.origin << ", direction=" << ray.direction << ", maximumOffset="
            << ray.maximumOffset << ", time=" << ray.time << "]";
            
        return os;
    }

    void print() const
    {
        printf("Ray[origin=%f, %f, %f, direction=%f, %f, %f, maximumOffset=%f, time=%f]\n", 
                origin.x, origin.y, origin.z, direction.x, direction.y, direction.z, maximumOffset, time);
    }

    Float getOffset(Point3f p) const
    {
        return (p.x - origin.x) * invDirection.x;
    }

    bool isCameraRay() const
    {
        return cameraRay;
    }
};


/*
inline Point3f offsetRayOrigin(const Point3f &p, const Vector3f &pError,
                               const Normal3f &n, const Vector3f &w) 
{
    Float d = dot(abs(n), pError);

    Vector3f offset = Vector3f(n.x, n.y, n.z) * d;

    if (dot(w, n) < 0)
        offset = -offset;

    Point3f po = p + offset;

    // Round offset point po away from p>
    return po;
}
*/
