#pragma once

#include "engine/rigid_body.hpp"
#include "engine/render_2D.hpp"


class Geralt : public Rigid_body
{
    bool on_ground = false;
    Texture txt_left, txt_right;
    Sound oof;

public:

    Geralt(Point3f position, Vector2f diagonal, Engine& engine)
        : Rigid_body(position, diagonal, 
        engine.load_texture("assets/geralt_right.png"),
        "Geralt")
    {
        set_max_speed(1.5);
        gravity = 3;
        enable_gravity();

        txt_left = engine.load_texture("assets/geralt_left.png");
        txt_right = engine.load_texture("assets/geralt_right.png");

        auto& mixer = engine.get_sound_mixer();
        oof = mixer.load_sound("assets/sounds/explode.wav");
    }

    void update_state(Engine &engine)
    {
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
    }

    void update_position(Engine& engine) override
    {
        //std::cout << "State: " << state << "\n";

        if (is_grounded(engine))
        {
            std::cout << "gravity disabled\n";
            disable_gravity();
            on_ground = true;
        }
        else
        {
            std::cout << "gravity enabled\n";
            enable_gravity();
            on_ground = false;
        }

        update_state(engine);
    
        Rigid_body::update_position(engine);
    }

    void on_collision(Engine& engine, EntityPtr other) override
    {
        if (other->get_entity_name() == "Apple")
        {
            return;
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
};
