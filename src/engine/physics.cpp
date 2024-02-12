#include "engine/physics.hpp"
#include "engine/engine.hpp"

void Physics_engine::update_positions(Engine& engine)
{
    auto &entities = engine.get_entities();

    // Should vectorize automatically
    for (auto& entity : entities)
    {
        entity->update_position(engine);
    }
}

void Physics_engine::compute_collisions(Engine& engine)
{
    auto &entities = engine.get_entities();

    // Should vectorize automatically
    for(std::size_t i = 0; i < entities.size(); i++)
    {
        for(std::size_t j = i + 1; j < entities.size(); j++)
        {
            Point2f intersection_point;

            if (entities[i]->collides(entities[j], intersection_point))
            {
                entities[i]->on_collision(engine, entities[j], intersection_point);
                entities[j]->on_collision(engine, entities[i], intersection_point);
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