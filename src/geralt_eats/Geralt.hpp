#pragma once

#include "engine/entity.hpp"
#include "engine/render_2D.hpp"


class Geralt : public Entity
{
    Texture txt_left, txt_right;
    Sound oof;
    EntityPtr ground;

    size_t COLLISION_POINT_DOWN, COLLISION_POINT_UP, COLLISION_POINT_LEFT, COLLISION_POINT_RIGHT;

public:

    Geralt(Point2f position, Vector2f diagonal, Engine& engine)
        : Entity(position, 0, diagonal, 
        engine.load_texture("assets/geralt_right.png"),
        engine,
        "Geralt", Entity::Physics_type::DYNAMIC_BODY, Entity::Collision_type::AABB, Entity::Cursor_collision_type::AABB, "Geralt")
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
    }

    bool is_grounded(Engine& engine) const
    {
        return colliding_down();
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
        auto speed = get_speed();

        if (engine.is_up_arrow_down()
            && colliding_down())
        {
            speed.y = -3;
        }

        if (engine.is_down_arrow_down()
            && !colliding_down())
        {
            speed.y = speed.y + 1;
        }


        if (engine.is_left_arrow_down()
            && !colliding_left())
        {
            speed.x = -1;
            look_left();
        }

        if (engine.is_right_arrow_down()
            && !colliding_right())
        {
            speed.x = 1;
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

        Entity::update_state(engine);
    }

    void on_collision(Engine& engine, EntityPtr other, bool is_alpha, size_t collision_point_id) override
    {
        if (other->get_entity_name() == "Apple")
        {
            return;
        }

        if (is_alpha && collision_point_id == COLLISION_POINT_DOWN
            || !is_alpha && collision_point_id == 2)
        {
            ground = other;
        }

        Entity::on_collision(engine, other, is_alpha, collision_point_id);
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
