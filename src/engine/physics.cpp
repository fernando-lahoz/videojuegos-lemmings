#include "engine/physics.hpp"
#include "engine/engine.hpp"

void Physics_engine::update_positions(Engine& engine)
{
    auto &entities = engine.get_entities();
    auto delta_time = engine.get_delta_time();
    Float gravity = engine.get_gravity();

    for (auto& entity : entities)
    {
        auto speed = entity->get_speed();
        auto max_speed = entity->get_max_speed();

        speed.y = std::clamp(Float(speed.y + gravity * delta_time), -max_speed.y, max_speed.y);
        entity->set_speed(speed);
    }

    for (auto& entity : entities)
    {
        auto position = entity->get_position2D();
        auto speed = entity->get_speed();
    
        Entity::update_position(delta_time, position, speed);
        entity->set_position2D(position);
    }
}


void hit_computation(Vector2f speed1, Vector2f speed2, 
    Float mass1, Float mass2,
    Point2f hit_point, Vector2f hit_normal,
    Vector2f &new_speed1, Vector2f &new_speed2)
{
    Vector2f relative_speed = speed1 - speed2;
    Float impulse = 2 * dot(relative_speed, hit_normal) / (mass1 + mass2);

    new_speed1 = speed1 - impulse * mass2 * hit_normal;
    new_speed2 = speed2 + impulse * mass1 * hit_normal;
}


void undo_movement(double delta_time, EntityPtr a, EntityPtr b)
{
    auto a_speed = a->get_speed();
    auto b_speed = b->get_speed();

    auto a_position = a->get_position2D();
    auto b_position = b->get_position2D();

    Entity::update_position(-delta_time, a_position, a_speed);
    Entity::update_position(-delta_time, b_position, b_speed);

    a->set_position2D(a_position);
    b->set_position2D(b_position);

}

void Physics_engine::compute_collisions(Engine& engine)
{
    //auto &huds = engine.get_hud_entities();
    auto &aabb_entities = engine.get_aabb_entities();
    auto &alpha_entities = engine.get_alpha_entities();
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
                undo_movement(delta_time, aabb, other);

                aabb->on_collision(engine, other, false, collision_point_id);
                other->on_collision(engine, aabb, false, collision_point_id);

                Vector2f new_speed1, new_speed2;

                hit_computation(aabb->get_speed(), other->get_speed(),
                    1.0f, 1.0f,
                    aabb->get_position2D(), Vector2f(1, 0),
                    new_speed1, new_speed2);

                aabb->set_speed(new_speed1);
                other->set_speed(new_speed2);
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
                if (aabb->alpha_collides(other, collision_point_id)) {
                    aabb->on_collision(engine, other, true, collision_point_id);
                }


                if (other->alpha_collides(aabb, collision_point_id)) {
                    other->on_collision(engine, aabb, true, collision_point_id);
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
                if (alpha->alpha_collides(other, collision_point_id)) {
                    alpha->on_collision(engine, other, true, collision_point_id);
                }


                if (other->alpha_collides(alpha, collision_point_id)) {
                    other->on_collision(engine, alpha, true, collision_point_id);
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