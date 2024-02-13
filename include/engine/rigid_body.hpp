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
        Point2f origin = max_corner2D();
        origin.y -= 0.001;

        Ray ray(origin, Vector2f(0, 1));

        EntityPtr ground;
        Float hit_offset, hit_offset_max;
        bool intersected = engine.intesect_ray(ray, 
                get_entity_id(), 
                RIGID_BODY_ID,
                hit_offset, hit_offset_max,
                ground);

        if (intersected && hit_offset < 0.005)
            return true;
        else
            return false;
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

    // 0: right
    // 1: up
    // 2: left
    // 3: down
    int closest_intersection(Engine &engine, Float &closest_offset)
    {
        // Launch rays in four directions to check for collisions
        //  with other entities
        Point2f up = bound2f().pMin + Vector2f(diagonal.x / 2, 0);
        Point2f down = bound2f().pMin + Vector2f(diagonal.x / 2, diagonal.y);
        Point2f left = bound2f().pMin + Vector2f(0, diagonal.y / 2);
        Point2f right = bound2f().pMin + Vector2f(diagonal.x, diagonal.y / 2);
        
        Ray up_ray(up, Vector2f(0, -1));
        Ray down_ray(down, Vector2f(0, 1));
        Ray left_ray(left, Vector2f(-1, 0));
        Ray right_ray(right, Vector2f(1, 0));

        Float hit_offset_max;

        int closest = -1;
        closest_offset = INFINITY;

        for (int i = 0; i < 4; i++)
        {
            Ray ray;
            Float hit_offset;
            EntityPtr hit_entity;
            switch (i)
            {
                case 0:
                    ray = right_ray;
                    break;
                case 1:
                    ray = up_ray;
                    break;
                case 2:
                    ray = left_ray;
                    break;
                case 3:
                    ray = down_ray;
                    break;
            }

            bool intersected = engine.intesect_ray(ray, 
                    get_entity_id(),
                    RIGID_BODY_ID,
                    hit_offset, 
                    hit_offset_max,
                    hit_entity);

            if (intersected && hit_offset < closest_offset)
            {
                closest_offset = hit_offset;
                closest = i;
            }
        }

        return closest;
    }

    bool inverse_collision_distance(Engine &engine, int direction, Float &distance)
    {
        Ray ray;
        Float distance_min;
        EntityPtr hit_entity;

        if (direction == 0)
        {
            Point2f right = bound2f().pMin + Vector2f(diagonal.x, diagonal.y / 2);
            ray = Ray(right, Vector2f(-1, 0));    
        }
        else if (direction == 1)
        {
            Point2f up = bound2f().pMin + Vector2f(diagonal.x / 2, 0);
            ray = Ray(up, Vector2f(0, 1));
        }
        else if (direction == 2)
        {
            Point2f left = bound2f().pMin + Vector2f(0, diagonal.y / 2);
            ray = Ray(left, Vector2f(1, 0));
        }
        else if (direction == 3)
        {
            Point2f down = bound2f().pMin + Vector2f(diagonal.x / 2, diagonal.y);
            ray = Ray(down, Vector2f(0, -1));
        }

        bool intersected = engine.intesect_ray(ray, 
                    get_entity_id(),
                    RIGID_BODY_ID,
                    distance_min, 
                    distance,
                    hit_entity);

        return intersected;
    }

    void on_collision([[maybe_unused]]Engine& engine, 
            EntityPtr other) override
    {
        std::cout << "Collision with " << other->get_entity_name() << std::endl;
        // If the entity is not moving, collision will not move it
        // Only rigid bodies can collide with other rigid bodies
        if (speed.length_squared() == 0 ||
            other->get_class() != "Rigid_body")
        {
            return;
        }

        auto speed = get_speed();

        Float closest_offset, distance;

        int closest_side = closest_intersection(engine, closest_offset);
        bool got_distance = inverse_collision_distance(engine, closest_side, distance);

        std::cout << "Closest side: " << closest_side << std::endl;
        std::cout << "Distance inside: " << distance << std::endl;

        if (got_distance && closest_side == 0)
        {
            position.x -= distance;
            speed.x = 0;
        }
        else if (got_distance && closest_side == 1)
        {
            position.y += distance;
            speed.y = 0;
        }
        else if (got_distance && closest_side == 2)
        {
            position.x += distance;
            speed.x = 0;
        }
        else if (got_distance && closest_side == 3)
        {
            position.y -= distance;
            speed.y = 0;
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
};