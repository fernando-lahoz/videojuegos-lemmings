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
        Float hit_offset;
        bool intersected = engine.intesect_ray(ray, false, 
                get_entity_id(), 
                RIGID_BODY_ID,
                hit_offset, ground);

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

    void on_collision([[maybe_unused]]Engine& engine, 
            EntityPtr other,
            Point2f intersection_point) override
    {
        // If the entity is not moving, collision will not move it
        // Only rigid bodies can collide with other rigid bodies
        if (speed.length_squared() == 0 ||
            other->get_class() != "Rigid_body")
        {
            return;
        }

        auto speed = get_speed();

        Point2f l_intersection_point = world_to_local(intersection_point);

        Point2f upper = Point2f(0.5, 0);
        Point2f lower = Point2f(0.5, 1);
        Point2f left = Point2f(0, 0.2);
        Point2f right = Point2f(1, 0.2);

        Float distance_up = distance(l_intersection_point, upper);
        Float distance_down = distance(l_intersection_point, lower);
        Float distance_left = distance(l_intersection_point, left);
        Float distance_right = distance(l_intersection_point, right);

        //std::cout << l_intersection_point << ", d_l" << distance_left << ", d_d" << distance_down << "\n";


        Float min_distance = std::min({distance_up, distance_down, 
            distance_left, distance_right});

        if (min_distance == distance_up)
        {
            speed.y = 0;
            position.y = other->bound2f().pMax.y;
        }
        else if (min_distance == distance_down)
        {
            speed.y = 0;
            position.y = other->bound2f().pMin.y - diagonal.y;
        }
        else if (min_distance == distance_left)
        {
            speed.x = 0;
            position.x = other->bound2f().pMax.x;
        }
        else if (min_distance == distance_right)
        {
            speed.x = 0;
            position.x = other->bound2f().pMin.x - diagonal.x;
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