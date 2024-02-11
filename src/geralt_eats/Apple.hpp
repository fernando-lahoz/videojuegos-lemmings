#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"


class Apple : public Rigid_body
{
    public:

    Apple(Point3f position, Vector2f size, Texture texture) 
    : Rigid_body(position, size, texture,
        "Apple")
    {
        set_max_speed(1.5);
        set_gravity(0.3);
        enable_gravity();
    }

    void on_collision(Engine& engine, EntityPtr other) override
    {
        if (other->get_entity_name() == "Geralt")
        {
            destroy();
        }

        Rigid_body::on_collision(engine, other);
    }

    void update_position (Engine& engine) override
    {
        if (get_position3D().y > 1)
        {
            destroy();
        }

        Rigid_body::update_position(engine);
    }

    void on_event_down(Engine& engine, EngineIO::InputEvent event) override
    {
        if (event == EngineIO::InputEvent::MOUSE_LEFT
            && contains_the_mouse(engine))
        {
            destroy();
        }
    }
};