#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"

#include "engine/render_2D.hpp"

class Static_camera : public Camera2D
{
public:
    Static_camera()
        : Camera2D(Bound2f(Point2f(0, 0), Point2f(1, 1.6)), Bound2f(Point2f(0, 0), Point2f(640, 400)))
    {
    }

    Static_camera(Bound2f _world_frame, Bound2f _window_frame)
    {
        this->world_frame = _world_frame;
        this->window_frame = _window_frame;
    }

    Static_camera(Bound2f frame)
    {
        this->world_frame = frame;
    }
};