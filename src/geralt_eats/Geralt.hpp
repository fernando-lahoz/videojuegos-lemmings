#pragma once

#include "engine/rigid_body.hpp"
#include "engine/render_2D.hpp"


class Geralt : public Rigid_body
{
    Texture txt_left, txt_right;
    Sound oof;
    EntityPtr ground;
    Float default_gravity = 3;

public:

    Geralt(Point3f position, Vector2f diagonal, Engine& engine)
        : Rigid_body(position, diagonal, 
        engine.load_texture("assets/geralt_right.png"),
        "Geralt")
    {
        set_max_speed(Vector2f(1.5, 1.5));
        gravity = default_gravity;

        txt_left = engine.load_texture("assets/geralt_left.png");
        txt_right = engine.load_texture("assets/geralt_right.png");

        auto& mixer = engine.get_sound_mixer();
        oof = mixer.load_sound("assets/sounds/explode.wav");
        disable_alpha_mouse();
        constructor_set_collision_type(Collision_type::CHARACTER);
    }


    void update_state(Engine& engine) override
    {
        if (is_grounded(engine))
        {
            disable_gravity();
        }
        else
        {
            set_gravity(default_gravity);
        }

        auto speed = get_speed();

        if (engine.is_up_arrow_down()
            && colliding_down())
        {
            speed.y = -1;
        }

        if (engine.is_down_arrow_down()
            && !colliding_down())
        {
            speed.y = speed.y + 1;
        }


        if (engine.is_left_arrow_down()
            && !colliding_left())
        {
            speed.x = -0.3;
            look_left();
        }

        if (engine.is_right_arrow_down()
            && !colliding_right())
        {
            speed.x = 0.3;
            look_right();
        }

        if (engine.is_right_arrow_down() && engine.is_left_arrow_down())
        {
            speed.x = 0;
        }

        if (!engine.is_right_arrow_down() && !engine.is_left_arrow_down())
        {
            speed.x = 0;
        }

        set_speed(speed);


        if (engine.is_key_down(EngineIO::ENTER)) // && is_grounded(engine))
        {
            Bound2f box;
            box.pMin = local_to_world(Point2f(0, 0.95));
            box.pMax = box.pMin + Vector2f(0.1, 0.1);

            bool destroyed = ground->destroy_box_alpha(engine, box);
            
            if (!destroyed)
            {
                std::cout << "Nothing destroyed\n";
            }
        }

        Rigid_body::update_state(engine);
    }

    void on_collision(Engine& engine, EntityPtr other) override
    {
        if (other->get_entity_name() == "Apple")
        {
            return;
        }

        if (check_collision_down(other))
        {
            ground = other;
        }

        Rigid_body::on_collision(engine, other);
    }

    void look_left()
    {
        set_active_texture(txt_left);
    }

    void look_right()
    {
        set_active_texture(txt_right);
    }

    void on_trigger_collision_event([[maybe_unused]]Engine& engine, 
        [[maybe_unused]]Entity *trigger, 
        [[maybe_unused]]std::shared_ptr<Entity> other) override
    {
        std::cout << "Geralt recieved trigger collision event with "+other->get_entity_name()+"\n";
    }

};
