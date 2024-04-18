#pragma once

#include <vector>
#include <unordered_set>

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/bounding_box.hpp"
#include "engine/entity.hpp"
#include "geometry/collision_point.hpp"

class Engine;

class Physics_engine
{
    std::vector<EntityPtr> aabb_entities;
    std::vector<EntityPtr> alpha_entities;
    std::vector<EntityPtr> charge_emitters;
    Float gravity = 0;
    size_t n_aabb_to_delete = 0;
    size_t n_alpha_to_delete = 0;
    size_t n_charge_emitters_to_delete = 0;

    Float max_electric_force = 1000;


    void update_physics(Engine& engine);
    void update_camera_positions(Engine& engine);
    void compute_collisions(Engine& engine);

    void pre_physics(Engine& engine);
    void post_physics(Engine& engine);
    void update_entities_state(Engine &engine);

    void electric_force(Engine&, EntityPtr emitter, EntityPtr other) const;

    void friction_collision(
        Float mass1, Float mass2,
        Float mu,
        Vector2f speed1, Vector2f speed2,
        Vector2f &new_speed1);

    void rigid_body_collision(bool collided1, bool collided2,
            bool compute_physics1, bool compute_physics2,
            EntityPtr entity1, EntityPtr entity2);

    void on_collision(Engine& engine,
            Float delta_time,
            EntityPtr entity1, EntityPtr entity2, 
            bool is_alpha, 
            Collision_point collision_point,
            size_t collision_point_id1, size_t collision_point_id2);

    void correct_collision(double delta_time, 
            EntityPtr body1, 
            EntityPtr body2, 
            Collision_point collision_point);

public:

    Physics_engine() = default;

    void compute_physics(Engine &engine);
    void add_entity(EntityPtr entity);

    Float get_gravity() const;
    void set_gravity(Float gravity);

    static void elastic_collision(Float mass1, Float mass2,
        Vector2f speed1, Vector2f speed2, 
        Point2f hit_point, Vector2f hit_normal,
        Vector2f &new_speed1, Vector2f &new_speed2);

    static void inelastic_collision(Float mass1, Float mass2,
        Vector2f speed1, Vector2f speed2,
        Point2f hit_point, Vector2f hit_normal,
        Vector2f &new_speed1, Vector2f &new_speed2);

    void delete_entities(const std::unordered_set<Entity*> &deleted_entities);
};