#pragma once

#include "engine/entity.hpp"

class Rigid_body : public Entity
{
protected:

    Vector2f speed;
    Float max_speed_sqr;
    Float max_speed = -1;

    bool _has_gravity;
    Float gravity = 0;

    enum Sides {RIGHT=1, UP=2, LEFT=4, DOWN=8};

    static constexpr char RIGID_BODY_ID[] = "Rigid_body";
    
    void update_speed_gravity(Float gravity, Float delta_time)
    {
        auto speed = get_speed();
        speed.y += gravity * delta_time;
        set_speed(speed);
    }

    bool is_grounded(Engine& engine)
    {
        // Spawn a ray from the bottom of the entity
        Point2f origin = bound2f().pMin + Vector2f(diagonal.x / 2, diagonal.y);
        Ray ray(origin, Vector2f(0, 1));

        EntityPtr ground;
        Float hit_offset, hit_offset_max;
        bool intersected = engine.intesect_ray(ray, 
                get_entity_id(), 
                RIGID_BODY_ID,
                hit_offset, hit_offset_max,
                ground);

        if (intersected && ground->contains(origin))
        {
            hit_offset = 0;
        }

        if (intersected && hit_offset < 0.0005) {
            return true;
        }
        else {
            return false;
        }
    }

    
public:

    Rigid_body(Point3f position, Vector2f diagonal, Texture texture, 
        std::string _entity_name, 
        std::string _class_name=RIGID_BODY_ID)
        : Entity(position, diagonal, texture, 
                _entity_name, _class_name)
    {
        speed = Vector2f(0, 0);
        max_speed_sqr = -1;

        disable_gravity();
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

    Vector2f get_speed() const
    {
        return speed;
    }

    void set_speed(Vector2f new_speed)
    {
        speed = new_speed;
        
        if (max_speed > 0 && 
            speed.length_squared() > max_speed_sqr)
        {
            speed = normalize(speed) * max_speed;
        }
    }

    void set_speedX(Float new_x_speed)
    {
        auto temp_speed = get_speed();
        temp_speed.x = new_x_speed;
        set_speed(temp_speed);
    }

    void set_speedY(Float new_y_speed)
    {
        auto temp_speed = get_speed();
        temp_speed.y = new_y_speed;
        set_speed(temp_speed);
    }

    Float get_max_speed_sqr() const
    {
        return max_speed_sqr;
    }

    Float get_max_speed() const
    {
        return max_speed;
    }

    void set_max_speed(Float new_max_speed)
    {
        max_speed = new_max_speed;
        max_speed_sqr = math::pow2(new_max_speed);
    }


    // Returns true if the ray intersected
    //  tmin contains the minimum hit offset
    //  and tmax contains the maximum hit offset
    bool distance(Engine &engine, Ray ray, EntityPtr collided_entity, 
            Float &tmin, Float &tmax, Float &thit)
    {
        bool intersected = engine.intesect_ray_entity(ray, 
                collided_entity,
                tmin, 
                tmax);

        intersected = intersected && tmax > 0;

        Point2f origin = Point2f(ray.origin.x, ray.origin.y);
        if (collided_entity->contains(origin))
        {
            thit = 0;
        }
        else if (tmin < 0) {
            thit = tmax;
        }
        else {
            thit = tmin;
        }

        if (intersected)
        {
            engine.ray_march_alpha_end(ray, tmax, 0, tmax, collided_entity);

            if (tmin < 0)
            {
                ray.direction = -ray.direction;
                tmin = -tmin;
                engine.ray_march_alpha_end(ray, tmin, 0, tmin, collided_entity);
                tmin = -tmin;
            }
            else
            {
                engine.ray_march_alpha_end(ray, tmin, 0, tmin, collided_entity);
            }

            return true;
        }

        return false;
    }

    bool distance_up(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
    {
        Point2f up = bound2f().pMin + Vector2f(diagonal.x / 2, 0);
        Ray ray(up, Vector2f(0, -1));
        return distance(engine, ray, collided_entity, tmin, tmax, thit);
    }

    bool distance_down(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
    {
        Point2f down = bound2f().pMin + Vector2f(diagonal.x / 2, diagonal.y);
        Ray ray(down, Vector2f(0, 1));
        return distance(engine, ray, collided_entity, tmin, tmax, thit);
    }

    bool distance_left(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
    {
        Point2f left = bound2f().pMin + Vector2f(0, diagonal.y / 2);
        Ray ray(left, Vector2f(-1, 0));
        return distance(engine, ray, collided_entity, tmin, tmax, thit);
    }

    bool distance_right(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
    {
        Point2f right = bound2f().pMin + Vector2f(diagonal.x, diagonal.y / 2);
        Ray ray(right, Vector2f(1, 0));
        return distance(engine, ray, collided_entity, tmin, tmax, thit);
    }



    void on_collision([[maybe_unused]]Engine& engine, 
            EntityPtr other) override
    {
        // If the entity is not moving, collision will not move it
        // Only rigid bodies can collide with other rigid bodies
        if (speed.length_squared() == 0 ||
            other->get_class() != "Rigid_body")
        {
            return;
        }

        auto speed = get_speed();

        //std::cout << "Closest side: " << closest_side << std::endl;

        Float tmin, tmax, thit;

        // Only will collide when tmin is negative
        if (distance_up(engine, other, tmin, tmax, thit) && 
            thit < 0.0005)
        {
            speed.y = 0;
            position.y += -tmin;
        }

        if (distance_down(engine, other, tmin, tmax, thit) && 
            thit < 0.0005)
        {
            speed.y = 0;
            position.y -= -tmin;
        }

        if (distance_left(engine, other, tmin, tmax, thit) && 
            thit < 0.0005)
        {
            speed.x = 0;
            position.x += -tmin;
        }

        if (distance_right(engine, other, tmin, tmax, thit) && 
            thit < 0.0005)
        {
            speed.x = 0;
            position.x -= -tmin;
        }       

        set_speed(speed);
    }

    void update_position(Engine& engine) override
    {
        if (is_grounded(engine)) {
            disable_gravity();
        }
        else {
            enable_gravity();
        }

        
        double delta_time = engine.get_delta_time();
        if (has_gravity())
        {
            update_speed_gravity(gravity, delta_time);
        }
        
        position.x += speed.x * delta_time;
        position.y += speed.y * delta_time;
    }
};