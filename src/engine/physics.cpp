#include "engine/physics.hpp"
#include "engine/engine.hpp"


void Physics_engine::elastic_collision(Float mass1, Float mass2,
    Vector2f speed1, Vector2f speed2, 

    Point2f hit_point, Vector2f hit_normal,
    Vector2f &new_speed1, Vector2f &new_speed2)
{
    // Collision between aabb
    if (hit_normal.x == 0 && hit_normal.y == 0)
    {
        new_speed1 = (speed1 * (mass1 - mass2) + 2 * mass2 * speed2) / (mass1 + mass2);
        new_speed2 = (speed2 * (mass2 - mass1) + 2 * mass1 * speed1) / (mass1 + mass2);

        return;
    }

    auto normal = hit_normal;
    auto tangent = Vector2f(-normal.y, normal.x);

    auto v1n = dot(normal, speed1);
    auto v1t = dot(tangent, speed1);

    auto v2n = dot(normal, speed2);
    auto v2t = dot(tangent, speed2);


    auto new_v1n = (v1n * (mass1 - mass2) + 2 * mass2 * v2n) / (mass1 + mass2);
    auto new_v2n = (v2n * (mass2 - mass1) + 2 * mass1 * v1n) / (mass1 + mass2);
 
    new_speed1 = normal * new_v1n + tangent * v1t;
    new_speed2 = normal * new_v2n + tangent * v2t;
}


void Physics_engine::inelastic_collision(Float mass1, Float mass2,
    Vector2f speed1, Vector2f speed2,
    Point2f hit_point, Vector2f hit_normal,
    Vector2f &new_speed1, Vector2f &new_speed2)
{
    // Collision between aabb
    new_speed1 = (speed1 * mass1 + speed2 * mass2) / (mass1 + mass2);
    new_speed2 = new_speed1;

}

void undo_movement(double delta_time, EntityPtr body, Collision_point collision_point)
{
    auto body_speed = body->get_speed();
    auto body_centroid = body->centroid();
    auto body_position = body->get_position();

    Vector2f collision_to_body = body_centroid - collision_point.point;
    collision_point.normal = face_forward(collision_point.normal, collision_to_body);
    
    // Speed in the direction of the normal
    auto speed_normal = abs(dot(body_speed, collision_point.normal));


    // Move the body in the normal direction
    body_position += collision_point.normal * speed_normal * delta_time;

    body->set_position(body_position);
}



void Physics_engine::add_entity(EntityPtr entity)
{
    if (entity->get_collision_check_type() == Entity::Collision_check::AABB)
        aabb_entities.push_back(entity);
    else if (entity->get_collision_check_type() == Entity::Collision_check::ALPHA)
        alpha_entities.push_back(entity);

    if (entity->get_physics_type() == Entity::Physics_type::CHARGE_EMITTER)
        charge_emitters.push_back(entity);
}


void Physics_engine::rigid_body_collision(
        bool collided1, bool collided2,
        bool compute_physics1, bool compute_physics2,
        EntityPtr entity1, EntityPtr entity2)
{
    if (compute_physics1 || compute_physics2)
    {
        Vector2f new_speed1, new_speed2;

        elastic_collision(entity1->get_mass(), entity2->get_mass(),
            entity1->get_speed(), entity2->get_speed(),
            Point2f(0, 0), Vector2f(0, 0),
            new_speed1, new_speed2);

        if (collided1 && compute_physics1)
            entity1->set_speed(new_speed1);
        
        if (collided2 && compute_physics2)
            entity2->set_speed(new_speed2);
    }
}

void electric_force(Engine &engine, EntityPtr emitter, EntityPtr aabb)
{
    // Force direction
    Vector2f force_direction = normalize(aabb->centroid() - emitter->centroid());
    

    Float charge1 = emitter->get_charge();
    Float charge2 = aabb->get_charge();

    // Force magnitude
    Float force_magnitude = charge1 * charge2 
            / (aabb->centroid() - emitter->centroid()).length_squared();

    // Apply force
    aabb->apply_force(engine, force_direction * force_magnitude);
}

void Physics_engine::on_collision(Engine& engine,
        Float delta_time,
        bool first_collided, bool second_collided,
        bool compute_physics1, bool compute_physics2,
        EntityPtr entity1, EntityPtr entity2, 
        bool is_alpha, 
        size_t collision_point_id1, size_t collision_point_id2)
{
    if (first_collided)
    {
        entity1->entity_collision(engine, entity2, is_alpha, collision_point_id1);
        entity1->on_collision(engine, entity2, is_alpha, collision_point_id1);
    }

    if (second_collided)
    {
        entity2->entity_collision(engine, entity1, is_alpha, collision_point_id2);
        entity2->on_collision(engine, entity1, is_alpha, collision_point_id2);
    }

    if (first_collided || second_collided)
    {
        rigid_body_collision(first_collided, second_collided, 
                compute_physics1, compute_physics2,
                entity1, entity2);
    }
}


void Physics_engine::compute_collisions(Engine& engine)
{
    //auto &huds = engine.get_hud_entities();
    auto delta_time = engine.get_delta_time();

    // Check for collisions between AABB entities
    for (size_t i = 0; i < aabb_entities.size(); i++)
    {
        for (size_t j = i + 1; j < aabb_entities.size(); j++)
        {
            auto &aabb = aabb_entities[i];
            auto &other = aabb_entities[j];

            if (aabb->aabb_check_collision(other))
            {
                // Compute hit normal
                auto collision_point = aabb->bound2f().collision_point(other->bound2f());
                size_t collision_point_id1 = aabb->bound2f().closest_side(collision_point.point);
                size_t collision_point_id2 = other->bound2f().closest_side(collision_point.point);

                bool first_collided = 
                    (
                        aabb->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        aabb->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                    )
                    &&
                    (
                        other->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        other->get_collision_type() == Entity::Collision_type::STATIC_BODY
                    );

                bool second_collided = 
                    (
                        other->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        other->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                    )
                    &&
                    (
                        aabb->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        aabb->get_collision_type() == Entity::Collision_type::STATIC_BODY
                    );

                bool compute_physics1 = aabb->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                                        || (aabb->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                                            && other->get_collision_type() == Entity::Collision_type::STATIC_BODY);

                bool compute_physics2 = other->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                                        || (other->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                                            && aabb->get_collision_type() == Entity::Collision_type::STATIC_BODY);


                if (first_collided && compute_physics1)
                    undo_movement(delta_time, aabb, collision_point);

                if (second_collided && compute_physics2)
                    undo_movement(delta_time, other, collision_point);
                

                on_collision(engine, delta_time, first_collided, second_collided, 
                            compute_physics1, compute_physics2,
                            aabb, other, false, 
                            collision_point_id1, collision_point_id2);
            }
        }
    }
    

    // Check for collisions between AABB and alpha entities
    for (size_t i = 0; i < aabb_entities.size(); i++)
    {
        for (size_t j = 0; j < alpha_entities.size(); j++)
        {
            auto &aabb = aabb_entities[i];
            auto &other = alpha_entities[j];

            size_t collision_point_id;

            if (aabb->aabb_check_collision(other))
            {
                bool first_collided = aabb->alpha_check_collision(other, collision_point_id);
                bool second_collided = other->alpha_check_collision(aabb, collision_point_id);

                first_collided = first_collided && 
                    (
                        aabb->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        aabb->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                    )
                    &&
                    (
                        other->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        other->get_collision_type() == Entity::Collision_type::STATIC_BODY
                    );

                second_collided = second_collided &&
                    (
                        other->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        other->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                    )
                    &&
                    (
                        aabb->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        aabb->get_collision_type() == Entity::Collision_type::STATIC_BODY
                    );


                bool compute_physics1 = aabb->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                                        || (aabb->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                                            && other->get_collision_type() == Entity::Collision_type::STATIC_BODY);

                bool compute_physics2 = other->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                                        || (other->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                                            && aabb->get_collision_type() == Entity::Collision_type::STATIC_BODY);


                on_collision(engine, delta_time, first_collided, second_collided, 
                        compute_physics1, compute_physics2,
                        aabb, other, false, 
                        collision_point_id, collision_point_id);
            }
        }
    }

    // Check for collisions between alpha entities
    for (size_t i = 0; i < alpha_entities.size(); i++)
    {
        for (size_t j = i + 1; j < alpha_entities.size(); j++)
        {
            auto &alpha = alpha_entities[i];
            auto &other = alpha_entities[j];

            size_t collision_point_id;

            if (alpha->aabb_check_collision(other))
            {
                bool first_collided = alpha->alpha_check_collision(other, collision_point_id);
                bool second_collided = other->alpha_check_collision(alpha, collision_point_id);

                first_collided = first_collided && 
                    (
                        alpha->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        alpha->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                    )
                    &&
                    (
                        other->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        other->get_collision_type() == Entity::Collision_type::STATIC_BODY
                    );

                second_collided = second_collided &&
                    (
                        other->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        other->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                    )
                    &&
                    (
                        alpha->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                        || 
                        alpha->get_collision_type() == Entity::Collision_type::STATIC_BODY
                    );

                
                bool compute_physics1 = alpha->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                                        || (alpha->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                                            && other->get_collision_type() == Entity::Collision_type::STATIC_BODY);

                bool compute_physics2 = other->get_collision_type() == Entity::Collision_type::DYNAMIC_BODY
                                        || (other->get_collision_type() == Entity::Collision_type::TRANSPARENT_BODY
                                            && alpha->get_collision_type() == Entity::Collision_type::STATIC_BODY);


                on_collision(engine, delta_time, first_collided, second_collided, 
                    compute_physics1, compute_physics2,
                    alpha, other, true, 
                    collision_point_id, collision_point_id);
            }
        }
    }
}


void Physics_engine::update_physics(Engine& engine)
{
    auto &entities = engine.get_entities();
    auto delta_time = engine.get_delta_time();

    /************* Apply electric forces ****************/
    for (size_t i = 0; i < charge_emitters.size(); i++)
    {
        auto &emitter = charge_emitters[i];

        for (size_t j = 0; j < aabb_entities.size(); j++)
        {
            auto &aabb = aabb_entities[j];
            
            if (aabb->get_physics_type() == Entity::Physics_type::RIGID_BODY)
                electric_force(engine, emitter, aabb);
        }
    }


    for (auto& entity : entities)
    {
        if (entity->get_physics_type() != Entity::Physics_type::NONE)
        {
            /*********** Update accelerations ************/
            auto acc = entity->get_acceleration();
            auto speed = entity->get_speed();
            auto max_speed = entity->get_max_speed();

            if (entity->has_gravity())
            {
                acc.y += gravity;
            }

            speed = clamp(speed + acc * delta_time, -max_speed, max_speed);
            entity->set_speed(speed);
            entity->clear_acceleration();      


            /*********** Update speed ************/
            auto position = entity->get_position();
        
            Entity::update_position(delta_time, position, speed);
            entity->set_position(position);
        }  
    }
}

void Physics_engine::pre_physics(Engine& engine)
{
    auto &entities = engine.get_entities();

    for (auto& entity : entities)
    {
        entity->entity_pre_physics(engine);
        entity->pre_physics(engine);
    }
}

void Physics_engine::post_physics(Engine& engine)
{
    auto &entities = engine.get_entities();

    for (auto& entity : entities)
    {
        entity->post_physics(engine);
    }
}

void Physics_engine::update_camera_positions(Engine& engine)
{
    auto &cameras = engine.get_cameras();
    auto delta_time = engine.get_delta_time();

    for (auto &camera : cameras)
    {
        camera->update_position(engine);
    }
}


void Physics_engine::update_entities_state(Engine& engine)
{
    auto &entities = engine.get_entities();

    for (auto &entity : entities)
    {
        if (!entity->is_deleted())
            entity->update_state(engine);
    }
}


void Physics_engine::compute_physics(Engine &engine)
{
    // Send pre-physics event to all entities
    pre_physics(engine);

    update_camera_positions(engine);
    update_physics(engine);
    compute_collisions(engine);


    update_entities_state(engine);

    // Send post-physics event to all entities
    post_physics(engine);
}


Float Physics_engine::get_gravity() const
{
    return gravity;
}

void Physics_engine::set_gravity(Float gravity)
{
    this->gravity = gravity;
}




void Physics_engine::delete_entities(const std::unordered_set<Entity*> &deleted_entities)
{
    if (deleted_entities.empty())
        return;


    /******************* Delete aabb entities *******************/
    for (int i = aabb_entities.size()-1; i >= 0; i--)
    {
        size_t last_undeleted_position = aabb_entities.size()-1-n_aabb_to_delete;

        if (deleted_entities.find(aabb_entities[i].get()) != deleted_entities.end())
        {
            if (i != (int)last_undeleted_position)
                std::swap(aabb_entities[i], aabb_entities[last_undeleted_position]);
            
            n_aabb_to_delete++;
        }
    }

    if (n_aabb_to_delete > 0)
    {
        aabb_entities.resize(aabb_entities.size() - n_aabb_to_delete);
        n_aabb_to_delete = 0;
    }


    /******************* Delete alpha entities *******************/

    for (int i = alpha_entities.size()-1; i >= 0; i--)
    {
        size_t last_undeleted_position = alpha_entities.size()-1-n_alpha_to_delete;

        if (deleted_entities.find(alpha_entities[i].get()) != deleted_entities.end())
        {
            if (i != (int)last_undeleted_position)
                std::swap(alpha_entities[i], alpha_entities[last_undeleted_position]);
            
            n_alpha_to_delete++;
        }
    }

    if (n_alpha_to_delete > 0)
    {
        alpha_entities.resize(alpha_entities.size() - n_alpha_to_delete);
        n_alpha_to_delete = 0;
    }
}