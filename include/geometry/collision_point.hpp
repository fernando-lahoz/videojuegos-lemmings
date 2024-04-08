#pragma once

#include "geometry/vector.hpp"
#include "geometry/point.hpp"

struct Collision_point {
    Point2f point;
    Vector2f normal;

    Collision_point() = default;

    Collision_point(Point2f point, Vector2f normal)
        : point(point), normal(normal) {}
};
