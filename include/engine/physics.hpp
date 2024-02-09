#pragma once

#include <vector>

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/bounding_box.hpp"
#include "engine/entity.hpp"
#include "engine/engine.hpp"

class Physics_engine
{
    public:

    Physics_engine()
    {}

    void update_positions(Engine_ptr engine, Float delta_time)
    {
        auto &entities = *engine->get_entities();

        // Should vectorize automatically
        for (auto& entity : entities)
        {
            entity->update_position(engine, delta_time);
        }
    }

    void compute_collisions(Engine_ptr engine)
    {
        auto &entities = *engine->get_entities();

        // Should vectorize automatically
        for(std::size_t i = 0; i < entities.size(); i++)
        {
            for(std::size_t j = i + 1; j < entities.size(); j++)
            {
                if (entities[i]->collides(entities[j]))
                {
                    entities[i]->on_collision(engine, entities[j]);
                    entities[j]->on_collision(engine, entities[i]);
                }
            }
        }
    }

    void pre_physics(Engine_ptr engine, Float delta_time)
    {
        auto &entities = *engine->get_entities();

        for (auto& entity : entities)
        {
            entity->pre_physics(engine, delta_time);
        }
    }

    void post_physics(Engine_ptr engine, Float delta_time)
    {
        auto &entities = *engine->get_entities();

        for (auto& entity : entities)
        {
            entity->post_physics(engine, delta_time);
        }
    }
};