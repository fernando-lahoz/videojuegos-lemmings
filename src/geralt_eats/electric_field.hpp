#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "engine/trigger.hpp"


class Electric_field : public Entity
{
    size_t COLLISION_POINT_DOWN, COLLISION_POINT_UP, COLLISION_POINT_LEFT, COLLISION_POINT_RIGHT;

    public:

    Electric_field(Point2f position, Vector2f size, Texture txt, Engine& engine) 
    : Entity(position, 0, size, txt, engine, "electric_field","electric_field")
    {
        COLLISION_POINT_DOWN = add_collision_point(Collision_point(Point2f(0.5, 0.95), Vector2f(0, 1)));
        COLLISION_POINT_UP = add_collision_point(Collision_point(Point2f(0.5, 0.05), Vector2f(0, -1)));
        COLLISION_POINT_LEFT = add_collision_point(Collision_point(Point2f(0.05, 0.5), Vector2f(-1, 0)));
        COLLISION_POINT_RIGHT = add_collision_point(Collision_point(Point2f(0.95, 0.5), Vector2f(1, 0)));

        set_charge(10);
        disable_gravity();

        collision_check_type = Collision_check::AABB;
        physics_type = Physics_type::CHARGE_EMITTER;
        collision_type = Collision_type::STATIC_BODY;

        //set_max_speed(Vector2f(1.5, 1.5));
    }

    void on_collision(Engine& engine, EntityPtr other, bool is_alpha, size_t collision_point_id) override
    {

    }


    void update_state (Engine& engine) override
    {

    }

};