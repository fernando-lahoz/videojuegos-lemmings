#pragma once

#include "Entity.cpp"

class Rigid_entity : public Entity
{
    protected:

    bool _has_gravity = false;
    Float gravity = 0;
    
    void update_speed_gravity(Float gravity, Float delta_time)
    {
        auto speed = get_speed();
        speed.y += gravity * delta_time;
        set_speed(speed);
    }


    public:

    Rigid_entity(Point3f position, Vector2f diagonal, Texture texture, std::string _type = "Rigid_entity", Float _max_speed = 1.5)
        : Entity(position, diagonal, texture, _type, _max_speed)
    {
    }

    void set_gravity(Float new_gravity)
    {
        this->gravity = new_gravity;
    }

    void enable_gravity()
    {
        _has_gravity = true;
    }

    void disable_gravity()
    {
        _has_gravity = false;
    }

    bool has_gravity() const
    {
        return _has_gravity;
    }

    void on_collision(Engine_ptr engine, EntityPtr other) override
    {
        auto speed = get_speed();

        // Get out of the other entity
        switch (closest_side(other))
        {
            case 0:
                position.x = other->bound2f().pMin.x - diagonal.x;
                speed.x = 0;
                break;
            case 1:
                position.x = other->bound2f().pMax.x;
                speed.x = 0;
                break;
            case 2:
                position.y = other->bound2f().pMax.y;
                speed.y = 0;
                break;
            case 3:
                position.y = other->bound2f().pMin.y - diagonal.y;
                speed.y = 0;
                break;
        }

        set_speed(speed);

        Entity::on_collision(engine, other);
    }

    void update_position(Engine_ptr engine, Float delta_time) override
    {
        if (has_gravity())
        {
            update_speed_gravity(gravity, delta_time);
        }

        Entity::update_position(engine, delta_time);
    }
};