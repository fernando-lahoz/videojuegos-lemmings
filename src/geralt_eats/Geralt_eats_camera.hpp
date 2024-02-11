#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"

#include "engine/render_2D.hpp"

class Geralt_camera : public Camera2D
{
    public:

    Geralt_camera()
    : Camera2D(Bound2f(Point2f(0, 0), Point2f(1, 1)))
    { }

    Geralt_camera(Bound2f frame)
    {
        this->frame = frame;
    }

    void update_position(Engine& engine) override
    {
        Float delta_time = engine.get_delta_time();

        if (engine.is_a_down())
        {
            frame.pMin.x -= 0.1 * delta_time;
            frame.pMax.x -= 0.1 * delta_time;
        }

        if (engine.is_d_down())
        {
            frame.pMin.x += 0.1 * delta_time;
            frame.pMax.x += 0.1 * delta_time;
        }
    }
};