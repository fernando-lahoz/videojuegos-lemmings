#pragma once

#include <vector>
#include <unordered_set>

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/bounding_box.hpp"
#include "engine/entity.hpp"

class Engine;

class Physics_engine
{
    std::vector<EntityPtr> aabb_entities;
    std::vector<EntityPtr> alpha_entities;
    Float gravity = 0;
    size_t n_aabb_to_delete = 0;
    size_t n_alpha_to_delete = 0;


    void update_positions(Engine& engine);
    void update_camera_positions(Engine& engine);
    void compute_collisions(Engine& engine);

    void pre_physics(Engine& engine);
    void post_physics(Engine& engine);
    void update_entities_state(Engine &engine);


    
public:

    Physics_engine() = default;

    // TODO: Shouldn't these be static methods? or will this engine get members?

    void compute_physics(Engine &engine);
    void add_entity(EntityPtr entity);

    Float get_gravity() const;
    void set_gravity(Float gravity);

    void delete_entities(const std::unordered_set<Entity*> &deleted_entities);
};