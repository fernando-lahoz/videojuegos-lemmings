#include "engine/physics.hpp"
#include "engine/engine.hpp"

void Physics_engine::update_positions(Engine& engine)
{
    auto &entities = engine.get_entities();
    auto delta_time = engine.get_delta_time();

    for (auto& entity : entities)
    {
        entity->update_gravity(delta_time);
    }

    for (auto& entity : entities)
    {
        entity->update_position(delta_time);
    }
}

void Physics_engine::compute_collisions(Engine& engine)
{
    //auto &huds = engine.get_hud_entities();
    auto &structures = engine.get_structure_entities();
    auto &characters = engine.get_character_entities();


    for (auto &structure : structures)
    {
        auto shared_structure = std::make_shared<Entity>(*structure);

        for (auto &character : characters)
        {
            auto shared_character = std::make_shared<Entity>(*character);

            if (structure->hitbox_collides(shared_character) &&
                structure->collides(shared_character))
            {
                structure->on_collision(engine, shared_character);
            }

            if (structure->hitbox_collides(shared_character) &&
                character->collides(shared_structure))
            {
                character->on_collision(engine, shared_structure);
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