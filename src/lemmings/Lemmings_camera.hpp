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
        : Camera2D(Bound2f(Point2f(0, 0), Point2f(1, 1)))
    {
    }

    Lemmings_camera(Bound2f frame)
    {
        this->frame = frame;
    }

    void on_key_down([[maybe_unused]] Engine &engine, SDL_KeyboardEvent key)
    {
        if (key.keysym.sym == SDLK_d)
        {
            moveRight(0.01);
        }
        else if (key.keysym.sym == SDLK_a)
        {
            moveLeft(0.01);
        }
    }
};