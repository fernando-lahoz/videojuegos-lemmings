#pragma once

#include "geometry/ray.hpp"

inline constexpr Ray::Ray() 
    : maximum_offset(INFINITY)
{ 

}

inline constexpr Ray::Ray(const Point3f &origin, const Vector3f &direction,
        Float maximum_offset, bool is_camera_ray)
    : origin(origin), direction(direction), 
      inv_direction(1 / direction.x, 1 / direction.y, 1 / direction.z),
      maximum_offset(maximum_offset),
      camera_ray(is_camera_ray) 
{ }

inline constexpr Ray::Ray(const Point2f &_origin, const Vector2f &_direction,
        Float _maximum_offset, bool _is_camera_ray)
    : origin(Point3f(_origin.x, _origin.y, 0)), direction(Vector3f(_direction.x, _direction.y, 0)),
        maximum_offset(_maximum_offset),
        camera_ray(_is_camera_ray)
{ 
    inv_direction = Vector3f(1 / direction.x, 1 / direction.y, 1 / direction.z);
}


// Returns a point along the ray at a given offset
inline constexpr Point3f Ray::operator()(Float offset) const { 
    return origin + direction * offset; 
}

inline constexpr bool Ray::has_NaNs() const {
    return (origin.has_NaNs() || direction.has_NaNs() || std::isnan(maximum_offset));
}

inline constexpr Float Ray::get_offset(Point3f p) const
{
    return (p.x - origin.x) * inv_direction.x;
}

inline constexpr bool Ray::is_camera_ray() const
{
    return camera_ray;
}
