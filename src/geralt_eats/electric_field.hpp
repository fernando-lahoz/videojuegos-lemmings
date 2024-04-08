#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "engine/trigger.hpp"
#include "engine/physics.hpp"


class Electric_field : public Entity
{
    size_t COLLISION_POINT_DOWN, COLLISION_POINT_UP, COLLISION_POINT_LEFT, COLLISION_POINT_RIGHT;

    bool destroying = false;

    public:

    Electric_field(Engine& engine, Point2f position, Vector2f size, Float charge) 
    : Entity(position, 0, size, engine.load_texture("assets/energy_ball.png"), engine, "electric_field","electric_field")
    {
        COLLISION_POINT_DOWN = add_collision_point(Collision_point(Point2f(0.5, 0.95), Vector2f(0, 1)));
        COLLISION_POINT_UP = add_collision_point(Collision_point(Point2f(0.5, 0.05), Vector2f(0, -1)));
        COLLISION_POINT_LEFT = add_collision_point(Collision_point(Point2f(0.05, 0.5), Vector2f(-1, 0)));
        COLLISION_POINT_RIGHT = add_collision_point(Collision_point(Point2f(0.95, 0.5), Vector2f(1, 0)));

        set_charge(charge);
        disable_gravity();

        collision_check_type = Collision_check::AABB;
        physics_type = Physics_type::CHARGE_EMITTER;
        collision_type = Collision_type::TRANSPARENT_BODY;

        //set_max_speed(Vector2f(1.5, 1.5));
    }

    void update_state(Engine& engine) override
    {
    }

    void on_collision(Engine& engine, EntityPtr other, bool is_alpha, size_t collision_point_id) override
    {
        if (other->get_collision_type() == Collision_type::STATIC_BODY)
        {
            //Physics_engine::inelastic_collision(get_mass(), other->get_mass(),
            //    get_speed(), other->get_speed(),
            //    get_collision_point(collision_point_id).get_position(), 
            //    get_collision_point(collision_point_id).get_normal(),
            //    get_speed(), other->get_speed());
        }
    }

    void start_destruction(Engine &engine)
    {
        destroying = true;
        set_charge(get_charge()*3);
    }
};