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
#include "engine/IO.hpp"

class Engine;

class Entity
{
private:
    Texture active_texture;    
    bool deleted_entity = false;
    int entity_id;
    bool mouse_over = false;

protected:
    Point3f position;
    Vector2f diagonal;

    std::string class_name;
    std::string entity_name;

public:
    Entity(Point3f position, Vector2f diagonal, Texture texture, 
            std::string_view _entity_name, 
            std::string_view _class_name = "Entity");

    // Get the specific entity name
    //  Ex: Main character
    std::string get_entity_name() const;

    Point2f world_to_local(Point2f w_p) const;
    Vector2f world_to_local(Vector2f w_p) const;

    Point2f local_to_world(Point2f l_p) const;

    // Returns the type of the entity
    //  Ex: Rigid body, generic entity
    std::string get_class() const;

    Point2f get_position2D() const;
    Point3f get_position3D() const;

    void set_position2D(Point2f p);
    void set_position3D(Point3f p);

    Vector2f get_diagonal() const;

    Point2f max_corner2D() const;
    Point3f max_corner3D() const;

    int get_entity_id() const;
    void set_entity_id(int id);

    Texture get_active_texture() const;
    void set_active_texture(Texture new_texture);
    
    bool is_deleted() const;
    Bound2f bound2f() const;

    void destroy();

    bool mouse_was_hovering() const;
    void enable_mouse_hover();
    void disable_mouse_hover();


    // Returns true if this entity collides with other.
    //  uses excusive comparisons, 
    //  and returns the closes side 
    //  of the entity to the intersection
    // 0: right
    // 1: up
    // 2: left
    // 3: down
    bool collides(std::shared_ptr<Entity> other, Point2f &intersection_point) const;
    bool contains(Point2f point) const;

    // Returns true if the mouse is pointing inside the visible entity
    bool contains_the_mouse(Engine& engine) const;
    bool contains_the_mouse(Engine& engine, Point2f mouse_position) const;

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    virtual void on_event_down(Engine& engine, EngineIO::InputEvent event);

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    virtual void on_event_up(Engine& engine, EngineIO::InputEvent event);

    // This is called right before the physics are computed
    virtual void pre_physics(Engine& engine);

    // Moves the entity speed*delta_time units
    //  in the direction vector
    // This is called right after pre_physics
    //  and before collisions
    virtual void update_position(Engine& engine);

    // Collisions are called right after updating the positions,
    //  and before the end step
    virtual void on_collision(Engine& engine, 
            std::shared_ptr<Entity> other, 
            Point2f intersection_point);

    // This is called after all physics have finished
    virtual void post_physics(Engine& engine);
};

//TODO: custom names for pointers should not be equal for shared and raw
// shared_ptr<Entity> -> Entity_sp
// Entity* -> Entity_ptr (should be returned as reference though)
using EntityPtr = std::shared_ptr<Entity>;