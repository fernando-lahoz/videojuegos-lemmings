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

class Engine;

class Entity
{
private:
    Texture active_texture;    
    bool deleted_entity = false;
    int entity_id;

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
    std::string get_entity_name() const;

    // Returns the type of the entity
    //  Ex: Rigid body, generic entity
    std::string get_class() const;

    Point2f get_position2D() const;

    Point3f get_position3D() const;

    void set_position2D(Point2f p);

    void set_position3D(Point3f p);

    Point2f max_corner2D() const;

    Point3f max_corner3D() const;

    int get_entity_id() const;
    void set_entity_id(int id);

    Bound2f bound2f() const;

    Texture get_active_texture() const;

    void set_active_texture(Texture new_texture);

    bool is_deleted() const;

    void destroy();

    // Returns true if this entity collides with other
    //  uses excusive comparisons
    bool collides(std::shared_ptr<Entity> other) const;

    // Returns the side of this entity that is closest to other
    // 0: right
    // 1: left
    // 2: up
    // 3: down
    int closest_side(std::shared_ptr<Entity> other);

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    // It is warranteed that all key down events are sent
    //  AFTER all key up events
    virtual void on_key_down(Engine& engine, SDL_KeyboardEvent event);

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    // It is warranteed that all key up events are sent
    //  BEFORE all key down events
    virtual void on_key_up(Engine& engine, SDL_KeyboardEvent event);

    // This is called right before the physics are computed
    virtual void pre_physics(Engine& engine);

    // Moves the entity speed*delta_time units
    //  in the direction vector
    // This is called right after pre_physics
    //  and before collisions
    virtual void update_position(Engine& engine);

    // Collisions are called right after updating the positions,
    //  and before the end step
    virtual void on_collision(Engine& engine, std::shared_ptr<Entity> other);

    // This is called after all physics have finished
    virtual void post_physics(Engine& engine);
};

//TODO: custom names for pointers should not be equal for shared and raw
// shared_ptr<Entity> -> Entity_sp
// Entity* -> Entity_ptr (should be returned as reference though)
using EntityPtr = std::shared_ptr<Entity>;