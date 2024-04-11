#include "engine/physics.hpp"
#include "engine/engine.hpp"


void Physics_engine::elastic_collision(Float mass1, Float mass2,
    Vector2f speed1, Vector2f speed2, 

    Point2f hit_point, Vector2f hit_normal,
    Vector2f &new_speed1, Vector2f &new_speed2)
{
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


void apply_friction(Vector2f normal_force, EntityPtr body, EntityPtr ground, double dt)
{
    auto speed = body->get_speed();

    /************ Align friction with tangent speed **********/
    Vector2f friction = normal(ground->get_friction_coefficient() * normal_force);
    Vector2f acc = friction / body->get_mass();

    acc.x = -math::copy_sign(acc.x, speed.x);
    acc.y = -math::copy_sign(acc.y, speed.y);
    
    /*************** Apply fricton and stop body **************/
    Vector2f new_speed = clamp(speed + acc*dt, -body->get_max_speed(), body->get_max_speed());

    // If the body has changed direction because of the friction, stop it
    if (!math::same_sign(speed.x, new_speed.x))
        new_speed.x = 0;

    if (!math::same_sign(speed.y, new_speed.y))
        new_speed.y = 0;


    body->set_speed(new_speed);
}

void Physics_engine::correct_collision(double delta_time, EntityPtr body1, EntityPtr body2, Collision_point collision_point)
{
    /******************* Undo all the movement ********************/
    body1->set_position(body1->get_position() - body1->get_speed() * delta_time);
    body2->set_position(body2->get_position() - body2->get_speed() * delta_time);

    auto body_acceleration1 = body1->get_acceleration();
    auto body_acceleration2 = body2->get_acceleration();
    auto body_centroid1 = body1->centroid();
    auto body_centroid2 = body2->centroid();

    Vector2f collision_to_body1 = body_centroid1 - collision_point.point;
    Vector2f collision_normal1 = face_forward(collision_point.normal, collision_to_body1);
    Vector2f collision_normal2 = -collision_normal1;

    /********** Remove acceleration in the nomal direction **********/
    auto acc_normal1 = abs(dot(body_acceleration1, collision_normal1));
    auto acc_normal2 = abs(dot(body_acceleration2, collision_normal2));
    auto body_speed1 = body1->get_speed();
    auto body_speed2 = body2->get_speed();

    // Undo acceleration in the collision normal
    body_speed1 += collision_normal1 * acc_normal1 * delta_time;
    body_speed2 += collision_normal2 * acc_normal2 * delta_time;

    /****************** Compute collision physics *************/
    elastic_collision(body1->get_mass(), body2->get_mass(),
            body_speed1, body_speed2,
            collision_point.point, collision_point.normal,
            body_speed1, body_speed2);

    if (body1->get_collision_type() != Entity::Collision_type::STATIC_BODY)
        body1->set_speed(body_speed1);
    
    if (body2->get_collision_type() != Entity::Collision_type::STATIC_BODY)
        body2->set_speed(body_speed2);

    /************** Apply friction ***************/
    auto previous_forces1 = body1->get_previous_forces();
    auto previous_forces2 = body2->get_previous_forces();

    // Forces normal to the collision
    auto normal_force_modulus1 = dot(previous_forces1, collision_normal1);
    auto normal_force_modulus2 = dot(previous_forces2, collision_normal2);
    Vector2f normal_force1 = collision_normal1 * normal_force_modulus1;
    Vector2f normal_force2 = collision_normal2 * normal_force_modulus2;


    // Update the speed with the friction
    if (body1->get_collision_type() != Entity::Collision_type::STATIC_BODY)
        apply_friction(normal_force1, body1, body2, delta_time);
    
    if (body2->get_collision_type() != Entity::Collision_type::STATIC_BODY)
        apply_friction(normal_force2, body2, body1, delta_time);

    /****** Redo the movement without normal speed and friction ******/
    auto position1 = body1->get_position();
    auto position2 = body2->get_position();

    position1 += body1->get_speed() * delta_time;
    position2 += body2->get_speed() * delta_time;

    body1->set_position(position1);
    body2->set_position(position2);
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

void electric_force(Engine &engine, EntityPtr emitter, EntityPtr aabb)
{
    // Force vector
    Vector2f force_vector = (aabb->centroid() - emitter->centroid());

    // Force direction
    Vector2f force_direction = normalize(force_vector);
    

    Float charge1 = emitter->get_charge();
    Float charge2 = aabb->get_charge();
    
    Float force_length = force_vector.length();
    Float force_length_squared = force_vector.length_squared();

    // Force magnitude
    Float force_magnitude = charge1 * charge2 
            / force_length_squared;

    //std::cout << "Electric force on " << aabb->get_class() << ": " << force_direction*force_magnitude << std::endl;

    // Apply force
    aabb->apply_force(force_direction * force_magnitude);
    emitter->on_electric_field_interaction(engine, aabb, 
            force_length, force_length_squared, 
            engine.get_delta_time());
}

void Physics_engine::on_collision(Engine& engine,
        Float delta_time,
        EntityPtr entity1, EntityPtr entity2, 
        bool is_alpha, 
        Collision_point collision_point,
        size_t collision_point_id1, size_t collision_point_id2)
{
    const bool collision_matrix[4][4] = 
    {
        // THIS IS INDEXED TRANSPOSED IN THE CODE
        // Trigger, transparent, static, dynamic
        {false,       true,      true,   true},  // Trigger
        {false,       false,     true,   true},  // Transparent
        {false,       true,      true,   true},  // Static
        {false,       false,     true,   true}   // Dynamic
    }; 

    size_t entity1_type = (size_t)entity1->get_collision_type();
    size_t entity2_type = (size_t)entity2->get_collision_type();
    bool collision1 = collision_matrix[entity1_type][entity2_type];
    bool collision2 = collision_matrix[entity2_type][entity1_type];

    if (collision1 && collision2) {
        correct_collision(delta_time, entity1, entity2, collision_point);
    }

    if (collision1)
    {
        entity1->entity_collision(engine, entity2, is_alpha, collision_point_id1);
        entity1->on_collision(engine, entity2, is_alpha, collision_point_id1);
    }

    if (collision2)
    {
        entity2->entity_collision(engine, entity1, is_alpha, collision_point_id2);
        entity2->on_collision(engine, entity1, is_alpha, collision_point_id2);
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

                on_collision(engine, delta_time, 
                            aabb, other, false,
                            collision_point, 
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
            /*********** Apply forces ************/
            auto total_force = entity->get_forces();
            auto acc = total_force / entity->get_mass();
            entity->clear_forces(gravity);

            /*********** Apply acceleration ************/
            auto speed = entity->get_speed();
            auto max_speed = entity->get_max_speed();

            if (entity->get_entity_name() == "Geralt")
            {
                std::cout << "Speed: " << speed << std::endl;
            }

            speed = clamp(speed + acc * delta_time, -max_speed, max_speed);
            entity->set_acceleration(acc);
            entity->set_speed(speed);

            /*********** Apply speed ************/
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


    /******************* Delete charge emitters *******************/

    for (int i = charge_emitters.size()-1; i >= 0; i--)
    {
        size_t last_undeleted_position = charge_emitters.size()-1-n_charge_emitters_to_delete;

        if (deleted_entities.find(charge_emitters[i].get()) != deleted_entities.end())
        {
            if (i != (int)last_undeleted_position)
                std::swap(charge_emitters[i], charge_emitters[last_undeleted_position]);
            
            n_charge_emitters_to_delete++;
        }
    }

    if (n_charge_emitters_to_delete > 0)
    {
        charge_emitters.resize(charge_emitters.size() - n_charge_emitters_to_delete);
        n_charge_emitters_to_delete = 0;
    }


}