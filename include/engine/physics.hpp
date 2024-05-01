#pragma once

#include <vector>

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/bounding_box.hpp"
#include "engine/entity.hpp"

class Engine;

class Physics_engine
{
public:
    Physics_engine() = default;

    void update_positions(Engine &engine);

    void compute_collisions(Engine &engine);

    void pre_physics(Engine &engine);

    static bool alpha_box_collision(const Entity &entity, const Bound2f &box);

    enum ReturnedPixel
    {
        GET_FIRST,
        GET_LAST,
    };

    static bool alpha_box_collision_if_all(const Entity &entity, const Bound2f &box,
                                           ReturnedPixel horizontal_pixel,
                                           ReturnedPixel vertical_pixel,
                                           bool &none_solid, Point2f &pixel);

    void post_physics(Engine &engine);
};