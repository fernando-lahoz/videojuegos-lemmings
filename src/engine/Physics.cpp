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

    void apply_gravity(std::vector<EntityPtr> &entities, Float delta_time)
    {
        Float g = 3;

        // Should vectorize automatically
        for (auto& entity : entities)
        {
            if (entity->has_gravity())
            {               
                auto speed = entity->getSpeed();
                auto direction = entity->getDirection();

                auto speedX = speed * direction.x;
                auto speedY = speed * direction.y;

                speedY += g * delta_time;

                entity->setSpeed(sqrt(pow2(speedX) + pow2(speedY)));
                entity->setDirection(Vector2f(speedX, speedY));
            }
            else
            {
                entity->deactivate_gravity();
            
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