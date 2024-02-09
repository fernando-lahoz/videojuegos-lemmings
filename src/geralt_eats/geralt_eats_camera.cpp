#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "../engine/engine.cpp"
#include "../engine/entity.cpp"

#include "../engine/render_2D.cpp"

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

    void on_key_down(Engine_ptr engine, SDL_KeyboardEvent key)
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