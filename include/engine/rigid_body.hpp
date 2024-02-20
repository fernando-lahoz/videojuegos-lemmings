#pragma once

#include "engine/entity.hpp"

class Rigid_body : public Entity
{
protected:

    Vector2f speed;
    Float max_speed_sqr;
    Float max_speed = -1;

    Point2f down_point, up_point,
            left_point, right_point;

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
        Point2f origin = local_to_world(down_point);
        Ray ray(origin, Vector2f(0, 1));

        EntityPtr ground;
        Float hit_offset, hit_offset_min, hit_offset_max;
        bool intersected = engine.intesect_ray(ray, 
                get_entity_id(), 
                RIGID_BODY_ID,
                hit_offset_min, hit_offset_max,
                ground);

        if (hit_offset_min < 0) {
            hit_offset = hit_offset_max;
        }
        else {
            hit_offset = hit_offset_max;
        }

        if (intersected && ground->contains(origin))
        {
            hit_offset = 0;
        }

        if (intersected && hit_offset < 0.0005) {
            std::cout << "Grounded with min:" << hit_offset << ", max: " << hit_offset_max << std::endl;
            return true;
        }
        else {
            return false;
        }
    }

    void update_speed_gravity(Float gravity, Float delta_time);

    bool is_grounded(Engine& engine);

public:

    Rigid_body(Point3f position, Vector2f diagonal, Texture texture, 
        std::string _entity_name, 
        std::string _class_name=RIGID_BODY_ID)
        : Entity(position, diagonal, texture, 
                _entity_name, _class_name)
    {
        speed = Vector2f(0, 0);
        max_speed_sqr = -1;

        right_point = default_right_point();
        left_point = default_left_point();
        up_point = default_up_point();
        down_point = default_down_point();

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

    void override_right_point(Point2f new_p)
    {
        right_point = new_p;
    }

    void override_left_point(Point2f new_p)
    {
        left_point = new_p;
    }

    void override_up_point(Point2f new_p)
    {
        up_point = new_p;
    }

    void override_down_point(Point2f new_p)
    {
        down_point = new_p;
    }

    Point2f default_right_point() const
    {
        return Point2f(1, 0.5);
    }

    Point2f default_left_point() const
    {
        return Point2f(0, 0.5);
    }

    Point2f default_up_point() const
    {
        return Point2f(0.5, 0);
    }

    Point2f default_down_point() const
    {
        return Point2f(0.5, 1);
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
        Point2f p = local_to_world(up_point);
        Ray ray(p, Vector2f(0, -1));
        return distance(engine, ray, collided_entity, tmin, tmax, thit);
    }

    bool distance_down(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
    {
        Point2f p = local_to_world(down_point);
        Ray ray(p, Vector2f(0, 1));
        return distance(engine, ray, collided_entity, tmin, tmax, thit);
    }

    bool distance_left(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
    {
        Point2f p = local_to_world(left_point);
        Ray ray(p, Vector2f(-1, 0));
        return distance(engine, ray, collided_entity, tmin, tmax, thit);
    }

    bool distance_right(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
    {
        Point2f p = local_to_world(right_point);
        Ray ray(p, Vector2f(1, 0));
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
        double delta_time = engine.get_delta_time();
        if (has_gravity())
        {
            update_speed_gravity(gravity, delta_time);
        }
        
        position.x += speed.x * delta_time;
        position.y += speed.y * delta_time;
    }

    std::string _class_name = RIGID_BODY_ID);

    void set_gravity(Float new_gravity);

    void enable_gravity();

    void disable_gravity();

    bool has_gravity() const;

    Vector2f get_speed() const;

    void set_speed(Vector2f new_speed);

    void set_speedX(Float new_x_speed);

    void set_speedY(Float new_y_speed);

    Float get_max_speed_sqr() const;

    Float get_max_speed() const;

    void set_max_speed(Float new_max_speed);

    void on_collision(Engine& engine, EntityPtr other) override;

    void update_position(Engine& engine) override;
};