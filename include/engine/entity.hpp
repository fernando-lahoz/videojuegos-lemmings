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

public:

    enum Collision_type {HUD, STRUCTURE, CHARACTER, CURSOR};

private:
    Collision_type collision_type = HUD;


private:
    Texture active_texture;
    bool deleted_entity = false;
    int entity_id;
    bool mouse_over = false;
        
    bool alpha_collision = true, alpha_mouse = true;
    bool collisions_active = true;

protected:
    Point3f position;
    Vector2f diagonal;

    std::vector<Point2f> collision_points;
    std::vector<bool> vector_is_colliding;

    std::string class_name;
    std::string entity_name;


    Vector2f speed;
    Vector2f max_speed;

    Float gravity = 0;

public:


    Entity(Point3f position, Vector2f diagonal, const Texture& texture, 
            Engine &engine,
            std::string_view _entity_name, 
            std::string_view _class_name = "Entity");

    // Get the specific entity name
    //  Ex: Main character
    std::string get_entity_name() const;

    Collision_type get_collision_type() const;

    void constructor_set_collision_type(Collision_type new_type);

    // This must only be used in the constructor of the entity 
    void change_collision_type(Engine &engine, Collision_type new_type);

    Point2f world_to_local(Point2f w_p) const;
    Vector2f world_to_local(Vector2f w_p) const;
    Bound2f world_to_local(Bound2f box) const;


    Point2f local_to_world(Point2f l_p) const;

    // Returns the type of the entity
    //  Ex: Rigid body, generic entity
    std::string get_class() const;

    Point2f get_position2D() const;
    Point3f get_position3D() const;

    void set_position2D(Point2f p);
    void set_position3D(Point3f p);


    void set_gravity(Float new_gravity)
    {
        this->gravity = new_gravity;
    }

    void disable_gravity()
    {
        set_gravity(0);
    }

    bool has_gravity() const
    {
        return gravity > 0;
    }


    Vector2f get_speed() const
    {
        return speed;
    }

    void set_speed(Vector2f new_speed)
    {
        speed = math::clamp(new_speed, -max_speed, max_speed);
    }

    void set_speedX(Float new_x_speed)
    {
        speed.x = math::clamp(new_x_speed, -max_speed.x, max_speed.x);
    }

    void set_speedY(Float new_y_speed)
    {
        speed.y = math::clamp(new_y_speed, -max_speed.y, max_speed.y);
    }

    Vector2f get_max_speed() const
    {
        return max_speed;
    }

    void set_max_speed(Vector2f new_max_speed)
    {
        max_speed = new_max_speed;
    }

    inline void update_gravity(Float delta_time)
    {
        speed.y = math::clamp(speed.y + gravity*delta_time, -max_speed.y, max_speed.y);
    }

    inline void update_position(Float delta_time)
    {
        position.x += speed.x * delta_time;
        position.y += speed.y * delta_time;
    }

    void enable_collisions();
    void disable_collisions();

    inline bool hitbox_collides(std::shared_ptr<Entity> other) const
    {
        return collisions_active && bound2f().overlaps(other->bound2f());
    }


    // Overrides an existing collision_point, 
    //  new_point in coordinates local to the entity
    //  Returns true if the point was successfully set
    bool set_collision_point(size_t point_id, Point2f new_point);
    bool is_colliding(size_t point_id) const;
    
    // Adds a new collision point,
    //  new_point is in coordinates local to the entity
    //  Returns the id of the new collision point
    size_t add_collision_point(Point2f new_point);

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

    void enable_alpha_collision();
    void disable_alpha_collision();
    void enable_alpha_mouse();
    void disable_alpha_mouse(); 

    // Returns true if this entity collides with other.
    //  uses excusive comparisons
    bool collides(std::shared_ptr<Entity> other, size_t &collision_point_id) const;
    bool contains(Point2f point, bool is_mouse=false) const;

    // Returns true if the mouse is pointing inside the visible entity
    bool contains_the_mouse(Engine& engine);

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    virtual void on_event_down(Engine& engine, EngineIO::InputEvent event);

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    virtual void on_event_up(Engine& engine, EngineIO::InputEvent event);

    bool destroy_box_alpha(Engine &engine, Bound2f box);

    // This is called right before the physics are computed
    virtual void pre_physics(Engine& engine);

    // This is called at the end of physics, just before post_physics
    virtual void update_state(Engine& engine);

    // Collisions are called right after pre_physics and
    //  before update_position
    virtual void on_collision(Engine& engine, 
            std::shared_ptr<Entity> other,
            size_t collision_point_id);

    // This is called after all physics have finished
    virtual void post_physics(Engine& engine);

    // This is called right after the entity is inserted into the engine runtime
    virtual void on_creation(Engine& engine);

    virtual void on_trigger_collision_event(Engine& engine, Entity *trigger, std::shared_ptr<Entity> other);
    virtual void on_trigger_IO_event(Engine& engine, Entity *trigger, EngineIO::InputEvent event);
};

//TODO: custom names for pointers should not be equal for shared and raw
// shared_ptr<Entity> -> Entity_sp
// Entity* -> Entity_ptr (should be returned as reference though)
using EntityPtr = std::shared_ptr<Entity>;