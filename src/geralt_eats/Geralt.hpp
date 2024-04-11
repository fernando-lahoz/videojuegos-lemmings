#pragma once

#include "engine/entity.hpp"
#include "electric_field.hpp"
#include "engine/render_2D.hpp"


class Geralt : public Entity
{
    Texture txt_left, txt_right;
    Sound oof;
    EntityPtr ground;
    std::vector<std::shared_ptr<Electric_field>> electric_fields;
    std::mutex mtx_electric_fields;

    size_t COLLISION_POINT_DOWN, COLLISION_POINT_UP, COLLISION_POINT_LEFT, COLLISION_POINT_RIGHT;

    enum class Geralt_state
    {
        IDLE,
        WALKING_RIGHT,
        WALKING_LEFT,
        FORCING_DOWN,
        JUMPING,
        FALLING
    };

    Geralt_state state = Geralt_state::IDLE;

public:

    Geralt(Point2f position, Vector2f diagonal, Engine& engine)
        : Entity(position, 0, diagonal, 
        engine.load_texture("assets/geralt_right.png"),
        engine,
        "Geralt", "Geralt")
    {
        set_max_speed(Vector2f(30, 30));

        COLLISION_POINT_DOWN = add_collision_point(Collision_point(Point2f(0.5, 0.95), Vector2f(0, 1)));
        COLLISION_POINT_UP = add_collision_point(Collision_point(Point2f(0.5, 0.05), Vector2f(0, -1)));
        COLLISION_POINT_LEFT = add_collision_point(Collision_point(Point2f(0.05, 0.5), Vector2f(-1, 0)));
        COLLISION_POINT_RIGHT = add_collision_point(Collision_point(Point2f(0.95, 0.5), Vector2f(1, 0)));

        txt_left = engine.load_texture("assets/geralt_left.png");
        txt_right = engine.load_texture("assets/geralt_right.png");

        auto& mixer = engine.get_sound_mixer();
        oof = mixer.load_sound("assets/sounds/explode.wav");
        engine.subscribe_to_events(this);

        collision_check_type = Collision_check::AABB;
        physics_type = Physics_type::RIGID_BODY;
        collision_type = Collision_type::DYNAMIC_BODY;

        set_charge(1);
    }


    bool colliding_down() const
    {
        return alpha_is_colliding(COLLISION_POINT_DOWN) || aabb_is_colliding(2);
    }

    bool colliding_up() const
    {
        return alpha_is_colliding(COLLISION_POINT_UP) || aabb_is_colliding(0);
    }

    bool colliding_left() const
    {
        return alpha_is_colliding(COLLISION_POINT_LEFT) || aabb_is_colliding(3);
    }

    bool colliding_right() const
    {
        return alpha_is_colliding(COLLISION_POINT_RIGHT) || aabb_is_colliding(1);
    }



    void update_state(Engine& engine) override
    {
        Float dt = engine.get_delta_time();

        if (engine.is_a_down())
        {
            look_left();

            if (speed.x > -1)
            {
                apply_force(Vector2f(-10, 0));
            }
        }

        if (engine.is_d_down())
        {
            look_right();

            if (speed.x < 1)
            {
                apply_force(Vector2f(10, 0));
            }
        }

        if (engine.is_w_down() && colliding_down())
        {
            speed.y = -3;
        }

        if (engine.is_s_down())
        {
            apply_force(Vector2f(0, 30));
        }


        if (colliding_down() && force.y > 0)
        {
            Float friction = ground->get_friction_coefficient() * force.y;
            Float acc_x = friction / get_mass();

            if (speed.x > 0)
            {
                acc_x *= -1;
            }

            Float new_speed_x = math::clamp(speed.x + acc_x * dt, -max_speed.x, max_speed.x);

            if (math::sign(speed.x) != math::sign(new_speed_x)) {
                speed.x = 0;
            }
            else {
                speed.x = new_speed_x;
            }
        }
    }

    void on_collision(Engine& engine, EntityPtr other, bool is_alpha, size_t collision_point_id) override
    {
        if (is_alpha && collision_point_id == COLLISION_POINT_DOWN
            || !is_alpha && collision_point_id == 2)
        {
            ground = other;
        }
    }

    bool wasd_pressed(Engine &engine) const
    {
        return engine.is_w_down() || engine.is_a_down() || engine.is_s_down() || engine.is_d_down();
    }

    void on_event_down(Engine& engine, EngineIO::InputEvent event) override
    {
        if (event == EngineIO::InputEvent::ENTER)
        {
            if (wasd_pressed(engine))
            {
                std::unique_lock lock(mtx_electric_fields);

                // Create electric field
                auto electric_field = std::make_shared<Electric_field>(engine, get_position(), Vector2f(0.34, 0.3), 20, 10000);
                engine.create_entity(electric_field);
                electric_fields.push_back(electric_field);

                electric_field->set_speed(speed*1.5);
                electric_field->set_position(get_position()+speed*1.5*0.1);
            }
        }
        else if (event == EngineIO::InputEvent::BACKSPACE)
        {
            std::unique_lock lock(mtx_electric_fields);

            for (auto& electric_field : electric_fields)
            {
                electric_field->start_destruction(engine);
            }

            engine.start_timer(std::chrono::milliseconds(200), [this, &engine]()
            {
                this->destroy_electric_fields(engine);
            });
        }
    }

    void destroy_electric_fields(Engine &engine)
    {
        std::unique_lock lock(mtx_electric_fields);
    
        for (auto& electric_field : electric_fields)
        {
            electric_field->start_destruction(engine);
        }
        
        electric_fields.clear();
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
