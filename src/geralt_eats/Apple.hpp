#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"


class Apple : public Entity
{
    size_t COLLISION_POINT_DOWN, COLLISION_POINT_UP, COLLISION_POINT_LEFT, COLLISION_POINT_RIGHT;

    public:

    Apple(Point3f position, Vector2f size, Texture txt, Engine& engine, bool is_rb = true) 
    : Entity(position, size, txt, engine, "Apple", is_rb, Entity::Collision_type::AABB, Entity::Cursor_collision_type::AABB, "Apple")
    {
        COLLISION_POINT_DOWN = add_collision_point(Point2f(0.5, 0.95));
        COLLISION_POINT_UP = add_collision_point(Point2f(0.5, 0.05));
        COLLISION_POINT_LEFT = add_collision_point(Point2f(0.05, 0.5));
        COLLISION_POINT_RIGHT = add_collision_point(Point2f(0.95, 0.5));


        //set_max_speed(Vector2f(1.5, 1.5));
    }

    void on_collision(Engine& engine, EntityPtr other, bool is_alpha, size_t collision_point_id) override
    {
        Entity::on_collision(engine, other, is_alpha, collision_point_id);
    

        if (get_mass() > other->get_mass())
        {
            destroy(engine);
        }

    }

    void update_state (Engine& engine) override
    {
        Entity::update_state(engine);
    }

};