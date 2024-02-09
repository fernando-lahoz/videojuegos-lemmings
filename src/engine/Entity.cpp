#pragma once

#include "../geometry/Vector.cpp"
#include "../geometry/Point.cpp"
#include "../geometry/BoundingBox.cpp"
#include "../lib/Spectrum.cpp"
#include "../lib/Pair.cpp"
#include "../lib/Texture.cpp"
#include "Engine.hpp"

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <algorithm>

class Entity
{
    private:
    Texture active_texture;
    Vector2f speed;
    Float max_speed_sqr;
    Float max_speed;
    
    bool deleted_entity = false;

    protected:

    Point3f position;
    Vector2f diagonal;

    std::string type;


    public:

    Entity(Point3f position, Vector2f diagonal, 
            Texture texture, 
            std::string _type = "Default_entity",
            Float _max_speed=1.5)
    {
        this->position = position;
        this->diagonal = diagonal;
        this->active_texture = texture;
        this->max_speed = _max_speed;
        this->max_speed_sqr = pow2(_max_speed);

        this->type = _type;

        speed = Vector2f(0, 0);
    }

    std::string get_type() const
    {
        return type;
    }

    Point2f get_position2D() const
    {
        return Point2f(position.x, position.y);
    }

    Point3f get_position3D() const
    {
        return position;
    }

    void set_position2D(Point2f p)
    {
        position.x = p.x;
        position.y = p.y;
    }

    void set_position3D(Point3f p)
    {
        position = p;
    }

    Point2f max_corner2D() const
    {
        return get_position2D() + diagonal;
    }

    Point3f max_corner3D() const
    {
        auto maxCorner = max_corner2D();
        return Point3f(maxCorner.x, maxCorner.y, position.z);
    }

    Bound2f bound2f() const
    {
        return Bound2f(get_position2D(), max_corner2D());
    }

    Texture get_active_texture() const
    {
        return active_texture;
    }

    void set_active_texture(Texture new_texture)
    {
        active_texture = new_texture;
    }

    Vector2f get_speed() const
    {
        return speed;
    }

    void set_speed(Vector2f new_speed)
    {
        speed = new_speed;
    }

    void set_speedX(Float new_x_speed)
    {
        speed.x = new_x_speed;
    }

    void set_speedY(Float new_y_speed)
    {
        speed.y = new_y_speed;
    }

    bool is_deleted() const
    {
        return deleted_entity;
    }

    void destroy()
    {
        deleted_entity = true;
    }

    // Returns true if this entity collides with other
    //  uses excusive comparisons
    bool collides(std::shared_ptr<Entity> other) const
    {
        return bound2f().overlaps(other->bound2f());
    }

    // Returns the side of this entity that is closest to other
    // 0: right
    // 1: left
    // 2: up
    // 3: down
    int closest_side(std::shared_ptr<Entity> other)
    {
        Float distance_right = other->bound2f().pMax.x - bound2f().pMin.x;
        Float distance_left = bound2f().pMax.x - other->bound2f().pMin.x;
        Float distance_up = other->bound2f().pMax.y - bound2f().pMin.y;
        Float distance_down = bound2f().pMax.y - other->bound2f().pMin.y;

        Float min_distance = std::min({distance_right, distance_left, distance_up, distance_down});

        if (min_distance == distance_right)
        {
            return 0;
        }
        else if (min_distance == distance_left)
        {
            return 1;
        }
        else if (min_distance == distance_up)
        {
            return 2;
        }
        else // Down
        {
            return 3;
        }
    }

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    // It is warranteed that all key down events are sent
    //  AFTER all key up events
    virtual void on_key_down(Engine_ptr engine, SDL_KeyboardEvent key)
    {
        // Do nothing by default
    }

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    // It is warranteed that all key up events are sent
    //  BEFORE all key down events
    virtual void on_key_up(Engine_ptr engine, SDL_KeyboardEvent key)
    {
        // Do nothing by default
    }

    // This is called right before the physics are computed
    virtual void pre_physics(Engine_ptr engine, Float delta_time)
    {
        // Do nothing by default
    }

    // Moves the entity speed*delta_time units
    //  in the direction vector
    // This is called right after pre_physics
    //  and before collisions
    virtual void update_position(Engine_ptr engine, Float delta_time)
    {
        if (speed.length_squared() > max_speed_sqr)
        {
            speed = normalize(speed) * max_speed;
        }
        
        position.x += speed.x * delta_time;
        position.y += speed.y * delta_time;
    }

    // Collisions are called right after updating the positions,
    //  and before the end step
    virtual void on_collision(Engine_ptr engine, std::shared_ptr<Entity> other)
    {
        // Do nothing by default
    }

    // This is called after all physics have finished
    virtual void post_physics(Engine_ptr engine, Float delta_time)
    {
        // Do nothing by default
    }
};


void swap(Entity &a, Entity &b)
{
    Entity temp = a;
    a = b;
    b = temp;
}



typedef std::shared_ptr<Entity> EntityPtr;