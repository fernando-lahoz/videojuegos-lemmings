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

    void update_positions(Engine& engine);

    void compute_collisions(Engine& engine);

    void pre_physics(Engine& engine);

    void post_physics(Engine& engine);
};