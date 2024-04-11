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
    Texture red_ball, dark_ball, blue_ball;

    Float internal_energy = 100; 
    Float initial_energy = 0;

    // Joules lost per coulomb^2 per second, when no interactions
    //    energy_lost = charge^2 * unloaded_discharge * delta_time
    const Float unloaded_discharge = 0.1; 
    // Joules lost per coulomb^2 per second, 
    //      when interacting with another charge 
    //      at minimum distance, decays with distance^2
    //      energy_lost = charge^2 * loaded_discharge * delta_time 
    //                      / distance^2
    const Float loaded_discharge = 1; 

    public:

    Electric_field(Engine& engine, Point2f position, Vector2f size, Float charge, Float _energy) 
    : Entity(position, 0, size, engine.load_texture("assets/energy_ball.png"), engine, "electric_field","electric_field")
    {
        this->COLLISION_POINT_DOWN = add_collision_point(Collision_point(Point2f(0.5, 0.95), Vector2f(0, 1)));
        this->COLLISION_POINT_UP = add_collision_point(Collision_point(Point2f(0.5, 0.05), Vector2f(0, -1)));
        this->COLLISION_POINT_LEFT = add_collision_point(Collision_point(Point2f(0.05, 0.5), Vector2f(-1, 0)));
        this->COLLISION_POINT_RIGHT = add_collision_point(Collision_point(Point2f(0.95, 0.5), Vector2f(1, 0)));

        this->set_charge(charge);
        this->disable_gravity();

        this->collision_check_type = Collision_check::AABB;
        this->physics_type = Physics_type::CHARGE_EMITTER;
        this->collision_type = Collision_type::TRANSPARENT_BODY;

        this->red_ball = engine.load_texture("assets/energy_ball_red.png");
        this->dark_ball = engine.load_texture("assets/energy_ball_dark.png");
        this->blue_ball = engine.load_texture("assets/energy_ball_blue.png");

        this->energy = _energy;
        this->initial_energy = _energy;
        //set_max_speed(Vector2f(1.5, 1.5));
    }

    void start_destruction(Engine &engine)
    {
        destroying = true;

        charge = 0;
        energy = 0;

        set_active_texture(dark_ball);

        engine.start_timer(std::chrono::milliseconds(1000), 
            [this, &engine]()
            {
                engine.delete_entity(this);
            });
    }


    void on_electric_field_interaction(
            Engine &engine, std::shared_ptr<Entity> other, 
            Float distance, Float squared_distance, 
            Float delta_time) override
    {
        if (charge == 0 || energy <= 0 || destroying)
            return;

        // Lose energy proportional to the distance
        Float energy_lost = charge * charge * loaded_discharge * delta_time / squared_distance;
        energy -= energy_lost;

        if (energy <= 0 && !destroying)
        {
            start_destruction(engine);
            destroying = true;
        }
    }

    void update_state(Engine& engine) override
    {
        if (energy <= 0 || destroying)
        {
            if (!destroying)
            {
                start_destruction(engine);
                destroying = true;
            }

            return;
        }

        energy -= charge*charge * unloaded_discharge * engine.get_delta_time();

        if (energy < initial_energy*0.5)
        {
            set_active_texture(red_ball);
        }
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
};