#pragma once

#include "engine/rigid_body.hpp"
#include "engine/render_2D.hpp"


class Geralt : public Rigid_body
{
    bool on_ground = false;
    Texture txt_left, txt_right;

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
    }

    void update_state(Engine &engine)
    {
        auto speed = get_speed();

        if (engine.is_up_arrow_down())
        {
            if (on_ground)
            {
                speed.y = -1;
                set_speed(speed);
                on_ground = false;
            }
        }

        if (engine.is_down_arrow_down())
        {
            speed.y = speed.y + 1;
        }


        if (engine.is_left_arrow_down())
        {
            speed.x = -0.3;
            look_left();
        }

        if (engine.is_right_arrow_down())
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
        update_state(engine);
        //std::cout << "State: " << state << "\n";

        Rigid_body::update_position(engine);

        if (is_grounded(engine))
            on_ground = true;
        else
            on_ground = false;
    }

    void on_collision(Engine& engine, EntityPtr other) override
    {
        if (other->get_entity_name() == "Apple")
        {
            return;
        }

        //std::cout << "Geralt collided with " << other->get_type() << "\n";
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
