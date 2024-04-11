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
#include "geometry/collision_point.hpp"

class Engine;

class Entity
{

public:

    enum class Cursor_type {AABB, ALPHA};

    enum class Collision_check {NONE, AABB, ALPHA};

    // Trigger: does not collide physically with anything, but can trigger events
    // Transparent_body: Other bodies can pass through it, but it can collide with them. Has physics only with static body
    // Static_body: Other bodies collide with it, but it does not get affected physically by them
    // Dynamic_body: Collides with other bodies and they collide with it
    enum class Collision_type {TRIGGER=0, TRANSPARENT_BODY=1, STATIC_BODY=2, DYNAMIC_BODY=3};

    // Rigid_body: Moves according to physics
    // Charge_emitter: Emits a charge field
    enum class Physics_type {NONE, RIGID_BODY, CHARGE_EMITTER};

private:
    Float mass = 1;
    Float inv_mass = 1;

    bool aabb_side_colliding[4] = {false, false, false, false};

    Texture active_texture;
    bool deleted_entity = false;
    int entity_id = -1;
    bool mouse_over = false;
    bool _has_gravity = true;

protected:
    Collision_type collision_type = Collision_type::DYNAMIC_BODY;
    Cursor_type cursor_type = Cursor_type::AABB;
    Physics_type physics_type = Physics_type::RIGID_BODY;
    Collision_check collision_check_type = Collision_check::AABB;

    Point2f position;
    Float depth = 0;
    Vector2f diagonal;

    std::vector<Collision_point> collision_points;
    std::vector<bool> vector_is_colliding;

    std::string class_name;
    std::string entity_name;


    Vector2f speed = Vector2f(0, 0);
    Vector2f acceleration = Vector2f(0, 0);
    Vector2f force = Vector2f(0, 0);
    Vector2f previous_force = Vector2f(0, 0);
    Vector2f max_speed = Vector2f(INFINITY, INFINITY);

    Float charge = 0;
    Float energy = 0;



    Entity(Point2f position, Float depth,
            Vector2f diagonal, 
            const Texture& texture, 
            Engine &engine,
            std::string_view _entity_name, 
            std::string_view _class_name);


public:


    Entity(Point2f position, Float depth,
            Vector2f diagonal, 
            const Texture& texture, 
            Engine &engine,
            std::string_view _entity_name, 
            Physics_type _physics_type = Physics_type::RIGID_BODY,
            Collision_check _collision_check = Collision_check::AABB,
            Collision_type _collision_type = Collision_type::DYNAMIC_BODY,
            Cursor_type _cursor_type = Cursor_type::AABB,
            std::string_view _class_name = "Entity");

    // Get the specific entity name
    //  Ex: Main character
    std::string get_entity_name() const;

    Collision_type get_collision_type() const;
    Cursor_type get_cursor_type() const;
    Physics_type get_physics_type() const;

    Point2f world_to_local(Point2f w_p) const;
    Vector2f world_to_local(Vector2f w_p) const;
    Bound2f world_to_local(Bound2f box) const;


    Point2i world_to_texture(Point2f w_p) const;
    Point2f texture_to_world(Point2i t_p) const;
    Point2f local_to_world(Point2f l_p) const;

    // Returns the type of the entity
    //  Ex: Rigid body, generic entity
    std::string get_class() const;

    void set_position(Point2f p);
    void set_depth(Engine &engine, Float new_depth);
    Float get_depth() const;

    Float get_mass() const;
    void set_mass(Float new_mass);
    bool has_gravity() const;
    void enable_gravity();
    void disable_gravity();

    Float get_charge() const { return charge; }
    void set_charge(Float new_charge) { charge = new_charge; }

    Collision_check get_collision_check_type() const { return collision_check_type; }

    Point2f centroid() const
    {
        return get_position() + diagonal/2;
    }


    virtual void on_electric_field_interaction(
            Engine &engine, std::shared_ptr<Entity> other, 
            Float distance, Float squared_distance, 
            Float delta_time) {}

    Point2f get_position() const
    {
        return position;
    }


    Vector2f get_speed() const
    {
        return speed;
    }

    Vector2f get_acceleration() const
    {
        return acceleration;
    }

    Float get_friction_coefficient() const
    {
        return 0.5;
    }

    void clear_acceleration()
    {
        acceleration = Vector2f(0, 0);
    }

    void set_acceleration(Vector2f new_acceleration)
    {
        acceleration = new_acceleration;
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

    void set_force(Vector2f new_force)
    {
        force = new_force;
    }

    void clear_forces(Float gravity)
    {
        previous_force = force;

        if (has_gravity())
            force = Vector2f(0, mass * gravity);
        else
            force = Vector2f(0, 0);
    }

    Vector2f get_previous_forces() const
    {
        return previous_force;
    }

    void apply_force(Vector2f new_force)
    {
        force += new_force;
    }

    Vector2f get_forces() const
    {   
        return force;
    }

    Vector2f get_max_speed() const
    {
        return max_speed;
    }

    void set_max_speed(Vector2f new_max_speed)
    {
        max_speed = new_max_speed;
    }

    inline static void update_position(Float delta_time, Point2f &position, Vector2f speed)
    {
        position.x += speed.x * delta_time;
        position.y += speed.y * delta_time;
    }

    inline bool aabb_check_collision(std::shared_ptr<Entity> other) const
    {
        return bound2f().overlaps(other->bound2f());
    }


    // Overrides an existing collision_point, 
    //  new_point in coordinates local to the entity
    //  Returns true if the point was successfully set
    bool set_collision_point(size_t point_id, Collision_point new_point);
    bool alpha_is_colliding(size_t point_id) const;
    bool aabb_is_colliding(size_t point_id) const;
    
    // Adds a new collision point,
    //  new_point is in coordinates local to the entity
    //  Returns the id of the new collision point
    size_t add_collision_point(Collision_point new_point);

    Vector2f get_diagonal() const;

    Point2f max_corner() const;

    int get_entity_id() const;
    void set_entity_id(int id);

    Texture get_active_texture() const;
    void set_active_texture(Texture new_texture);
    
    bool is_deleted() const;
    Bound2f bound2f() const;

    void destroy(Engine &engine);

    bool mouse_was_hovering() const;
    void enable_mouse_hover();
    void disable_mouse_hover();

    // Returns true if this entity collides with other.
    //  uses excusive comparisons
    bool alpha_check_collision(std::shared_ptr<Entity> other, size_t &collision_point_id) const;
    bool contains(Point2f point, bool is_mouse=false) const;

    // Returns true if the mouse is pointing inside the visible entity
    bool contains_the_mouse(Engine& engine);
    bool destroy_box_alpha(Engine &engine, Bound2f box);

    Collision_point get_collision_point(size_t point_id) const
    {
        if (point_id >= collision_points.size())
            throw std::out_of_range("Collision point id out of range");

        return collision_points[point_id];
    }
    
    void entity_collision(Engine&, std::shared_ptr<Entity> other, 
            bool is_alpha, size_t collision_point_id)
    {
        if (is_alpha)
        {
            vector_is_colliding[collision_point_id] = true;
        }
        else
        {
            aabb_side_colliding[collision_point_id] = true;
        }
    }


    void entity_pre_physics(Engine&)
    {
        for (size_t i = 0; i < vector_is_colliding.size(); i++)
        {
            vector_is_colliding[i] = false;
        }

        for (size_t i = 0; i < 4; i++)
        {
            aabb_side_colliding[i] = false;
        }
    }

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    virtual void on_event_down(Engine&, EngineIO::InputEvent) {}

    // Event processing is the second thing executed, 
    //  right after game->on_loop_start()
    virtual void on_event_up(Engine&, EngineIO::InputEvent) {}

    // This is called right before the physics are computed
    virtual void pre_physics(Engine&) {}

    // This is called at the end of physics, just before post_physics
    virtual void update_state(Engine&) {}

    // Collisions are called right after pre_physics and
    //  before update_position
    virtual void on_collision(Engine&, 
            std::shared_ptr<Entity>, // other
            bool, // is_alpha
            size_t // collision_point_id
            ) {}

    // This is called after all physics have finished
    virtual void post_physics(Engine&) {}

    // This is called right after the entity is inserted into the engine runtime
    virtual void on_creation(Engine&) {}

    virtual void on_trigger_collision_event(Engine&, Entity *, std::shared_ptr<Entity>) {}
    virtual void on_trigger_IO_event(Engine&, Entity *, EngineIO::InputEvent) {}
};

//TODO: custom names for pointers should not be equal for shared and raw
// shared_ptr<Entity> -> Entity_sp
// Entity* -> Entity_ptr (should be returned as reference though)
using EntityPtr = std::shared_ptr<Entity>;