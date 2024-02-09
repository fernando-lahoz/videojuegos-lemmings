#pragma once

#include "engine/rigid_entity.hpp"
#include "engine/render_2D.hpp"


class Geralt : public Rigid_entity
{
    bool on_ground = false;
    Texture txt_left, txt_right;

    enum State
    {
        IDLE=1,
        LEFT=2,
        RIGHT=4,
        UP=8,
        DOWN=16
    };

    int state = IDLE;
    bool right_pressed = false, left_pressed = false;
    bool up_pressed = false, down_pressed = false;


    void set_right()
    {
        state = state | RIGHT;
    }

    void set_left()
    {
        state = state | LEFT;
    }

    void set_up()
    {
        state = state | UP;
    }

    void set_down()
    {
        state = state | DOWN;
    }

    void unset_right()
    {
        state = state & ~RIGHT;
    }

    void unset_left()
    {
        state = state & ~LEFT;
    }

    void unset_up()
    {
        state = state & ~UP;
    }

    void unset_down()
    {
        state = state & ~DOWN;
    }

    void go_idle()
    {
        state = IDLE;
    }

    bool is_right()
    {
        return state & RIGHT;
    }

    bool is_left()
    {
        return state & LEFT;
    }

    bool is_up()
    {
        return state & UP;
    }

    bool is_down()
    {
        return state & DOWN;
    }

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

    void update_state()
    {
        auto speed = get_speed();

        if (is_up())
        {
            if (on_ground)
            {
                speed.y = -1;
                set_speed(speed);
                on_ground = false;
            }
        }

        if (is_down())
        {
            speed.y = speed.y + 1;
        }


        if (is_left())
        {
            speed.x = -0.3;
            look_left();
        }

        if (is_right())
        {
            speed.x = 0.3;
            look_right();
        }

        if (is_right() && is_left())
        {
            speed.x = 0;
        }

        if (!is_right() && !is_left())
        {
            speed.x = 0;
        }

        set_speed(speed);
    }

    void update_position(Engine_ptr engine, Float delta_time) override
    {
        update_state();
        //std::cout << "State: " << state << "\n";

        Rigid_entity::update_position(engine, delta_time);
    }

    void on_collision(Engine_ptr engine, EntityPtr other) override
    {
        if (other->get_type() == "Apple")
        {
            return;
        }

        //std::cout << "Geralt collided with " << other->get_type() << "\n";
        Rigid_entity::on_collision(engine, other);

        // Ground collision
        if (closest_side(other) == 3) {
            on_ground = true;
        }

    }

    void look_left()
    {
        set_active_texture(txt_left);
    }

    void look_right()
    {
        set_active_texture(txt_right);
    }

    void on_key_down(Engine_ptr engine, SDL_KeyboardEvent key) override
    {
        switch(key.keysym.sym)
        {
            case SDLK_UP:
                set_up();
                break;
            case SDLK_DOWN:
                set_down();
                break;
            case SDLK_LEFT:
                set_left();
                break;
            case SDLK_RIGHT:
                set_right();
                break;
        }
    }

    void on_key_up(Engine_ptr engine, SDL_KeyboardEvent key) override
    {
        switch(key.keysym.sym)
        {
            case SDLK_UP:
                unset_up();
                break;
            case SDLK_DOWN:
                unset_down();
                break;
            case SDLK_LEFT:
                unset_left();
                break;
            case SDLK_RIGHT:
                unset_right();
                break;
        }
    }
};
