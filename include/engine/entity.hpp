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
    bool deleted_entity = false;

protected:
    Point3f position;
    Vector2f diagonal;

    std::string class_name;
    std::string entity_name;

public:
    Entity(Point3f position, Vector2f diagonal, Texture texture, 
            std::string_view _entity_name, 
            std::string_view _class_name="Entity");

    // Get the specific entity name
    //  Ex: Main character
    std::string get_entity_name() const
    {
        return entity_name;
    }

    // Returns the type of the entity
    //  Ex: Rigid body, generic entity
    std::string get_class() const
    {
        return class_name;
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
    virtual void on_key_down(Engine_ptr, SDL_KeyboardEvent)
    {
        // Do nothing by default
    }

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    // It is warranteed that all key up events are sent
    //  BEFORE all key down events
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
        // Do nothing by default
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