#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"


class Test_obj : public Entity
{
    size_t COLLISION_POINT_DOWN, COLLISION_POINT_UP, COLLISION_POINT_LEFT, COLLISION_POINT_RIGHT;

    public:

    Test_obj(Point2f position, Vector2f size, Texture txt, Engine& engine) 
    : Entity(position, 0, size, txt, engine, "Apple", "Apple")
    {
        COLLISION_POINT_DOWN = add_collision_point(Collision_point(Point2f(0.5, 0.95), Vector2f(0, 1)));
        COLLISION_POINT_UP = add_collision_point(Collision_point(Point2f(0.5, 0.05), Vector2f(0, -1)));
        COLLISION_POINT_LEFT = add_collision_point(Collision_point(Point2f(0.05, 0.5), Vector2f(-1, 0)));
        COLLISION_POINT_RIGHT = add_collision_point(Collision_point(Point2f(0.95, 0.5), Vector2f(1, 0)));

        collision_check_type = Collision_check::AABB;
        physics_type = Physics_type::RIGID_BODY;
        collision_type = Collision_type::DYNAMIC_BODY;

        engine.subscribe_to_events(this);

        //set_max_speed(Vector2f(1.5, 1.5));
    }

    // Movement
    void on_event_down(Engine& engine, EngineIO::InputEvent e)
    {
        if (e == EngineIO::InputEvent::DOWN_ARROW)
        {
            speed.y = 0.5;
        }
        else if (e == EngineIO::InputEvent::UP_ARROW)
        {
            speed.y = -0.5;
        }
        else if (e == EngineIO::InputEvent::LEFT_ARROW)
        {
            speed.x = -0.5;
        }
        else if (e == EngineIO::InputEvent::RIGHT_ARROW)
        {
            speed.x = 0.5;
        }
        else if (e == EngineIO::InputEvent::SPACE)
        {
            speed = Vector2f(0, 0);
        }
    }

    void update_state (Engine& engine) override
    {
        Entity::update_state(engine);
    }

};