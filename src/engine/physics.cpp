#include "engine/physics.hpp"
#include "engine/engine.hpp"

void Physics_engine::update_positions(Engine& engine)
{
    auto &entities = engine.get_entities();
    auto delta_time = engine.get_delta_time();

    for (auto& entity : entities)
    {
        auto speed = entity->get_speed();
        auto max_speed = entity->get_max_speed();

        if (entity->has_gravity())
        {
            speed.y = std::clamp(Float(speed.y + gravity * delta_time), -max_speed.y, max_speed.y);
            entity->set_speed(speed);
        }
    }

    for (auto& entity : entities)
    {
        auto position = entity->get_position();
        auto speed = entity->get_speed();
    
        Entity::update_position(delta_time, position, speed);
        entity->set_position(position);
    }
}

void elastic_collision(Float mass1, Float mass2,
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


void inelastic_collision(Float mass1, Float mass2,
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

    //std::cout << "Body centroid " << body_centroid << std::endl;
    //std::cout << "Collision point " << collision_point.point << std::endl;

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
    if (entity->get_collision_type() == Entity::Collision_type::AABB)
        aabb_entities.push_back(entity);
    else if (entity->get_collision_type() == Entity::Collision_type::ALPHA)
        alpha_entities.push_back(entity);
}


void Physics_engine::friction_collision(
    Float mass1, Float mass2,
    Float mu,
    Vector2f speed1, Vector2f speed2,
    Vector2f &new_speed1)
{
    // Compute force applied to o1
    auto force = mass2 * mu * gravity;
    auto deceleration = force / mass1;

    /*
    if (speed1.x > 0)
    {
        new_speed1.x = std::max(0.0f, speed1.x - deceleration);
    }
    else if (speed1.x < 0)
    {
        new_speed1.x = std::min(0.0f, speed1.x + deceleration);
    }
    else {
        new_speed1.x = 0;
    }
    */

    new_speed1.y = 0;

    std::cout << "Speed1: " << speed1 << " new_speed1: " << new_speed1 << std::endl;
}

void Physics_engine::rigid_body_collision(EntityPtr entity1, EntityPtr entity2)
{
    if (entity1->get_physics_type() == Entity::Physics_type::DYNAMIC_BODY
        &&
        entity2->get_physics_type()  == Entity::Physics_type::DYNAMIC_BODY)
    {
        Vector2f new_speed1, new_speed2;

        inelastic_collision(entity1->get_mass(), entity2->get_mass(),
            entity1->get_speed(), entity2->get_speed(),
            Point2f(0, 0), Vector2f(0, 0),
            new_speed1, new_speed2);

        entity1->set_speed(new_speed1);
        entity2->set_speed(new_speed2);

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

            size_t collision_point_id = 0;

            if (aabb->aabb_collides(other))
            {
                // Compute hit normal
                auto collision_point = aabb->bound2f().collision_point(other->bound2f());

                undo_movement(delta_time, aabb, collision_point);
                undo_movement(delta_time, other, collision_point);

                aabb->on_collision(engine, other, false, collision_point_id);
                other->on_collision(engine, aabb, false, collision_point_id);

                //rigid_body_collision(aabb, other);
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

            if (aabb->aabb_collides(other))
            {
                bool first_collided = aabb->alpha_collides(other, collision_point_id);
                bool second_collided = other->alpha_collides(aabb, collision_point_id);

                if (first_collided) 
                {
                    //undo_movement(delta_time, aabb);
                    aabb->on_collision(engine, other, true, collision_point_id);
                }

                if (second_collided)
                {
                    //undo_movement(delta_time, other);
                    other->on_collision(engine, aabb, true, collision_point_id);
                }

                if (first_collided || second_collided)
                {
                    rigid_body_collision(aabb, other);
                }
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

            if (alpha->aabb_collides(other))
            {
                bool first_collided = alpha->alpha_collides(other, collision_point_id);
                bool second_collided = other->alpha_collides(alpha, collision_point_id);

                if (first_collided) 
                {
                    //undo_movement(delta_time, alpha);
                    alpha->on_collision(engine, other, true, collision_point_id);
                }

                if (second_collided)
                {
                    //undo_movement(delta_time, other);
                    other->on_collision(engine, alpha, true, collision_point_id);
                }

                if (first_collided || second_collided)
                {
                    rigid_body_collision(alpha, other);
                }
            }
        }
    }

}

void Physics_engine::pre_physics(Engine& engine)
{
    auto &entities = engine.get_entities();

    for (auto& entity : entities)
    {
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

    compute_collisions(engine);


    update_camera_positions(engine);
    update_positions(engine);

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