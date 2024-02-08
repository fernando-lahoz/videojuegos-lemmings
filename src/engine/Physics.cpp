#pragma once

#include <vector>

#include "../geometry/Vector.cpp"
#include "../geometry/Point.cpp"
#include "../geometry/BoundingBox.cpp"
#include "../lib/Pair.cpp"
#include "Entity.cpp"

class Physics_engine
{
    public:

    Physics_engine()
    {}

    void update_positions(std::vector<EntityPtr> &entities, Float delta_time)
    {
        // Should vectorize automatically
        for (auto& entity : entities)
        {
            entity->update_position(delta_time);
        }
    }

    void compute_collisions(std::vector<EntityPtr> &entities)
    {
        // Should vectorize automatically
        for(int i = 0; i < entities.size(); i++)
        {
            for(int j = i + 1; j < entities.size(); j++)
            {
                if (entities[i]->collides(entities[j]))
                {
                    entities[i]->on_collision(entities[j]);
                    entities[j]->on_collision(entities[i]);
                }
            }
        }
    }

    void pre_physics(std::vector<EntityPtr> &entities, Float delta_time)
    {
        for (auto& entity : entities)
        {
            entity->pre_physics(delta_time);
        }
    }

    void post_physics(std::vector<EntityPtr> &entities, Float delta_time)
    {
        for (auto& entity : entities)
        {
            entity->post_physics(delta_time);
        }
    }
};