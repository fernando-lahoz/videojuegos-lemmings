#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"

#include "engine/render_2D.hpp"

class MainCamera : public Camera2D
{
public:

    MainCamera()
        : Camera2D(Bound2f(Point2f(100, 100), Point2f(101, 101)), Bound2f(Point2f(0, 0), Point2f(800, 800)), 1)
    { }

    MainCamera(Bound2f frame)
    {
        this->world_frame = frame;
    }

    void update_position([[maybe_unused]]Engine& engine) override
    {
        /* Float delta_time = engine.get_delta_time();

        auto p = engine.get_mouse_position_in_camera(*this);
        if (this->world_frame.is_near_border(p, Bound2f::Border::RIGHT, 0.01))
        {
            world_frame.pMin.x -= 0.3 * delta_time;
            world_frame.pMax.x -= 0.3 * delta_time;
        }
        else if (this->world_frame.is_near_border(p, Bound2f::Border::LEFT, 0.01))
        {
            world_frame.pMin.x += 0.3 * delta_time;
            world_frame.pMax.x += 0.3 * delta_time;
        } */


        // if (engine.is_a_down())
        // {
        //     world_frame.pMin.x -= 0.1 * delta_time;
        //     world_frame.pMax.x -= 0.1 * delta_time;
        // }

        // if (engine.is_d_down())
        // {
        //     world_frame.pMin.x += 0.1 * delta_time;
        //     world_frame.pMax.x += 0.1 * delta_time;
        // }
    }
};