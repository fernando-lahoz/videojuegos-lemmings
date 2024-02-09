#pragma once

#include "engine/rigid_entity.hpp"
#include "engine/render_2D.hpp"


class Geralt : public Rigid_entity
{
    bool on_ground = false;
    Texture txt_left, txt_right;

    public:

    Geralt(Point3f position, Vector2f diagonal, Engine_ptr engine)
        : Rigid_entity(position, diagonal, 
        engine->load_texture("assets/geralt_right.png"),
        "Geralt")
    {
        gravity = 3;
        enable_gravity();

        txt_left = engine->load_texture("assets/geralt_left.png");
        txt_right = engine->load_texture("assets/geralt_right.png");
    }

    void update_position(Engine_ptr engine, Float delta_time) override
    {
        //std::cout << "direction: " << getSpeed() << "\n";

        Rigid_entity::update_position(engine, delta_time);
    }

    void on_collision(Engine_ptr engine, EntityPtr other) override
    {
        if (other->get_type() == "Apple")
        {
            return;
        }

        Rigid_entity::on_collision(engine, other);

        // Ground collision
        if (other->bound2f().pMin.y >= bound2f().pMax.y)
        {
            setSpeedY(0);

            on_ground = true;
        }
        else
        {
            setSpeed(Vector2f(0, 0));
        }
    }

    bool jump(Float new_speed)
    {
        Vector2f speed = getSpeed();

        if (on_ground)
        {
            speed.y = -1;
            setSpeed(speed);
            on_ground = false;

            return true;
        }

        return false;
    }

    void pre_physics(Engine_ptr engine, Float delta_time) override
    {
    }

    void post_physics(Engine_ptr engine, Float delta_time) override
    {
        // Launch ray down to check if we are on ground
    }

    void look_left()
    {
        setActiveTexture(txt_left);
    }

    void look_right()
    {
        setActiveTexture(txt_right);
    }

    void on_key_down(Engine_ptr engine, SDL_KeyboardEvent key) override
    {
        Vector2f old_speed = getSpeed();

        if (key.keysym.sym == SDLK_UP)
        {
            jump(1);
            return;
        }
        else if (key.keysym.sym == SDLK_DOWN)
        {
            if (!on_ground)
            {
                old_speed.y = old_speed.y + 0.3;
            }
        }
        else if (key.keysym.sym == SDLK_LEFT)
        {
            look_left();
            old_speed.x = -0.3;
        }
        else if (key.keysym.sym == SDLK_RIGHT)
        {
            look_right();
            old_speed.x = 0.3;
        }

        setSpeed(old_speed);
    }

    void on_key_up(Engine_ptr engine, SDL_KeyboardEvent key) override
    {
        Vector2f old_speed = getSpeed();

        if (key.keysym.sym == SDLK_DOWN)
        {
            old_speed.y = 0;
        }
        else if (key.keysym.sym == SDLK_LEFT)
        {      
            old_speed.x = 0;
        }
        else if (key.keysym.sym == SDLK_RIGHT)
        {
            old_speed.x = 0;
        }

        setSpeed(old_speed);
    }
};
