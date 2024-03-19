#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"


class Apple : public Rigid_body
{
    Texture black_apple;
    Texture red_apple;

    public:

    Apple(Point3f position, Vector2f size, Engine& engine) 
    : Rigid_body(position, size, engine.load_texture("assets/apple.png"),
        "Apple")
    {
        black_apple = engine.load_texture("assets/apple.png");
        red_apple = engine.load_texture("assets/red_apple.png");

        set_max_speed(Vector2f(1.5, 1.5));
        set_gravity(0.3);
    }

    void on_collision(Engine& engine, EntityPtr other) override
    {
        if (other->get_entity_name() == "Geralt")
        {
            destroy();
        }

        Rigid_body::on_collision(engine, other);
    }

    void update_state (Engine& engine) override
    {
        if (get_position3D().y > 1)
        {
            destroy();
        }

        Rigid_body::update_state(engine);
    }

    void on_event_down(Engine& engine, EngineIO::InputEvent event) override
    {
        if (event == EngineIO::InputEvent::MOUSE_LEFT
            && contains_the_mouse(engine))
        {
            destroy();
        }

        if (event == EngineIO::InputEvent::MOUSE_HOVER)
        {
            set_active_texture(red_apple);
        }
    }

    void on_event_up([[maybe_unused]] Engine& engine, EngineIO::InputEvent event) override
    {
        if (event == EngineIO::InputEvent::MOUSE_HOVER)
        {
            set_active_texture(black_apple);
        }
    }
};