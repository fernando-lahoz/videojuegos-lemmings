#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/bounding_box.hpp"
#include "lib/spectrum.hpp"
#include "lib/texture.hpp"
#include "engine/engine.hpp"

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
    Entity(Point3f position, Vector2f diagonal, Texture texture, 
            std::string_view _type = "Default_entity", Float _max_speed = 1.5);

    std::string get_type() const
    {
        return type;
    }

    Point2f getPosition2D() const
    {
        return Point2f(position.x, position.y);
    }

    Point3f getPosition3D() const
    {
        return position;
    }

    void setPosition2D(Point2f p)
    {
        position.x = p.x;
        position.y = p.y;
    }

    void setPosition3D(Point3f p)
    {
        position = p;
    }

    Point2f maxCorner2D() const
    {
        return getPosition2D() + diagonal;
    }

    Point3f maxCorner3D() const
    {
        auto maxCorner = maxCorner2D();
        return Point3f(maxCorner.x, maxCorner.y, position.z);
    }

    Bound2f bound2f() const
    {
        return Bound2f(getPosition2D(), maxCorner2D());
    }

    Texture getActiveTexture() const
    {
        return active_texture;
    }

    void setActiveTexture(Texture new_texture)
    {
        active_texture = new_texture;
    }

    Vector2f getSpeed() const
    {
        return speed;
    }

    void setSpeed(Vector2f new_speed)
    {
        speed = new_speed;
    }

    void setSpeedX(Float new_x_speed)
    {
        speed.x = new_x_speed;
    }

    void setSpeedY(Float new_y_speed)
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
        Float distance_up = bound2f().pMax.y - other->bound2f().pMin.y;
        Float distance_down = other->bound2f().pMax.y - bound2f().pMin.y;

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
    virtual void on_key_down(Engine_ptr, SDL_KeyboardEvent)
    {
        // Do nothing by default
    }

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    virtual void on_key_up(Engine_ptr, SDL_KeyboardEvent)
    {
        // Do nothing by default
    }

    // This is called right before the physics are computed
    virtual void pre_physics(Engine_ptr, Float)
    {
        // Do nothing by default
    }

    // Moves the entity speed*delta_time units
    //  in the direction vector
    // This is called right after pre_physics
    //  and before collisions
    virtual void update_position(Engine_ptr, Float delta_time)
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
    virtual void on_collision(Engine_ptr, std::shared_ptr<Entity>)
    {
        // Do nothing by default
    }

    // This is called after all physics have finished
    virtual void post_physics(Engine_ptr, Float)
    {
        // Do nothing by default
    }
};

//TODO: custom names for pointers should not be equal for shared and raw
// shared_ptr<Entity> -> Entity_sp
// Entity* -> Entity_ptr (should be returned as reference though)
using EntityPtr = std::shared_ptr<Entity>;