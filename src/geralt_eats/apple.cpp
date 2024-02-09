#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "../engine/engine.cpp"
#include "../engine/rigid_entity.cpp"


class Apple : public Rigid_entity
{
    public:

    Apple(Point3f position, Vector2f size, Texture texture) 
    : Rigid_entity(position, size, texture,
        "Apple")
    {
        set_gravity(0.3);
        enable_gravity();
    }

    void on_collision(Engine_ptr engine, EntityPtr other) override
    {
        if (other->get_type() == "Geralt")
        {
            destroy();
        }

        Rigid_entity::on_collision(engine, other);
    }

    void update_position (Engine_ptr engine, Float delta_time) override
    {
        if (get_position3D().y > 1)
        {
            destroy();
        }

        Rigid_entity::update_position(engine, delta_time);
    }
};