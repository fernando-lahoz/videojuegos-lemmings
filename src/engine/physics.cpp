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
    auto &huds = engine.get_hud_entities();
    auto &structures = engine.get_structure_entities();
    auto &characters = engine.get_character_entities();


    for (auto &structure_id : structures)
    {
        auto structure = entities[structure_id];

        for (auto &character_id : characters)
        {
            auto character = entities[character_id];

            if (structure->collides(character))
            {
                structure->on_collision(engine, character);
            }

            if (character->collides(structure))
            {
                character->on_collision(engine, structure);
            }
        }
    }

    /*
    for(std::size_t i = 0; i < entities.size(); i++)
    {
        for(std::size_t j = i + 1; j < entities.size(); j++)
        {
            if (entities[i]->collides(entities[j])) {
                entities[i]->on_collision(engine, entities[j]);
            }

            if (entities[j]->collides(entities[i])) {
                entities[j]->on_collision(engine, entities[i]);
            }
        }
    }
    */
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