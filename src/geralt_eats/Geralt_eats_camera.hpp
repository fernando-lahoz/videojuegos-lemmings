#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"

#include "engine/render_2D.hpp"

class Geralt_camera : public Camera2D
{
    std::shared_ptr<Entity> main_character;
    Bound2f margin = Bound2f(Point2f(0.25, 0.25), Point2f(0.75, 0.75));

public:

    Geralt_camera(std::shared_ptr<Entity> main_character)
        : Camera2D(Bound2f(Point2f(0, 0), Point2f(4, 2.25)), Bound2f(Point2f(0, 0), Point2f(1280, 720)))
    { 
        this->main_character = main_character;
    }

    void update_position(Engine& engine) override
    {
        Float delta_time = engine.get_delta_time();

        Bound2f character = main_character->bound2f();
        Bound2f l_character = world_to_local(character);

        std::cout << "l_character: " << l_character << std::endl;
        Vector2f offset = Vector2f(0, 0);

        // If the character is outside the margin, 
        if (l_character.pMin.x < margin.pMin.x)
            offset.x = l_character.pMin.x - margin.pMin.x;

        if (l_character.pMin.y < margin.pMin.y)
            offset.y = l_character.pMin.y - margin.pMin.y;

        if (l_character.pMax.x > margin.pMax.x)
            offset.x = l_character.pMax.x - margin.pMax.x;

        if (l_character.pMax.y > margin.pMax.y)
            offset.y = l_character.pMax.y - margin.pMax.y;

        world_frame.pMin += offset;
        world_frame.pMax += offset;
    }
};