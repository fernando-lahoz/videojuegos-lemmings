#pragma once

#include <iostream>

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "lib/types.hpp"

class Ray
{
public:
    Point3f origin;
    Vector3f direction;
    Vector3f inv_direction;

    mutable Float maximum_offset;

    bool camera_ray = false;

    inline constexpr Ray();

    inline constexpr Ray(const Point3f &origin, const Vector3f &direction,
            Float maximum_offset = INFINITY, bool is_camera_ray = false);

    // Returns a point along the ray at a given offset
    inline constexpr Point3f operator()(Float offset) const;

    inline constexpr bool has_NaNs() const;

    inline constexpr Float get_offset(Point3f p) const;

    inline constexpr bool is_camera_ray() const;

    void print() const;
    friend std::ostream& operator<<(std::ostream& os, const Ray &ray);
};

std::ostream& operator<<(std::ostream& os, const Ray &ray);

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

#include "geometry/ray.ipp"