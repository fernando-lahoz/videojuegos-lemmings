#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"

#include "engine/render_2D.hpp"

class Lemmings_camera : public Camera2D
{
public:
    Lemmings_camera()
        : Camera2D(Bound2f(Point2f(0, 0), Point2f(1, 1)), Bound2f(Point2f(0, 0), Point2f(800, 800)))
    {
    }

    Lemmings_camera(Bound2f frame)
    {
        this->src = frame;
    }

    void update_position(Engine &engine) override
    {
        Float delta_time = engine.get_delta_time();

        if (engine.is_a_down())
        {
            src.pMin.x -= 0.2 * delta_time;
            src.pMax.x -= 0.2 * delta_time;
        }

        if (engine.is_d_down())
        {
            src.pMin.x += 0.2 * delta_time;
            src.pMax.x += 0.2 * delta_time;
        }
    }
};