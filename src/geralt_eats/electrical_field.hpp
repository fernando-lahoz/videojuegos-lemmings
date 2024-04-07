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

    Electric_field(Point2f position, Vector2f size, Vector2f field_diagonal Texture txt, Engine& engine) 
    : Entity(position, 0, size, txt, engine, "electric_field", Entity::Physics_type::STATIC_BODY, Entity::Collision_type::AABB, Entity::Cursor_collision_type::AABB, "electric_field")
    {
        COLLISION_POINT_DOWN = add_collision_point(Collision_point(Point2f(0.5, 0.95), Vector2f(0, 1)));
        COLLISION_POINT_UP = add_collision_point(Collision_point(Point2f(0.5, 0.05), Vector2f(0, -1)));
        COLLISION_POINT_LEFT = add_collision_point(Collision_point(Point2f(0.05, 0.5), Vector2f(-1, 0)));
        COLLISION_POINT_RIGHT = add_collision_point(Collision_point(Point2f(0.95, 0.5), Vector2f(1, 0)));

        Point2f field_center = position + size/2;
        Point2f field_position = field_center - fiedl_diagonal/2;
        auto trigger = std::make_shared<Trigger>(field_position, 0, field_diagonal, engine);
        trigger->add_asociated_entity(std::make_shared<Electric_field>(field_position, field_diagonal, txt, engine));
        engine->add_entity(trigger);

        //set_max_speed(Vector2f(1.5, 1.5));
    }

    void on_collision(Engine& engine, EntityPtr other, bool is_alpha, size_t collision_point_id) override
    {
       
    }

    void update_state (Engine& engine) override
    {

    }

};