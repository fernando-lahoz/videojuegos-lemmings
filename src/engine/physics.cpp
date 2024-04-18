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

bool Physics_engine::alpha_box_collision(const Entity& entity, const Bound2f& box)
{
    Bound2f l_box = entity.world_to_local(box);
    Texture active_texture = entity.get_active_texture();

    if (!entity.is_alpha_collision()
        && entity.bound2f().overlaps(box))
    {
        return true;
    }

    l_box = Bound2f(clamp(l_box.pMin, Point2f(0, 0), Point2f(1, 1)),
                    clamp(l_box.pMax, Point2f(0, 0), Point2f(1, 1)));

    Vector2f diagonal = l_box.diagonal();

    unsigned int n_tests_x = diagonal.x * active_texture.get_width();
    unsigned int n_tests_y = diagonal.y * active_texture.get_height();

    Float pixel_size_x = 1.0 / active_texture.get_width();
    Float pixel_size_y = 1.0 / active_texture.get_height();


    for (unsigned int x = 0; x < n_tests_x; x++)
    {
        for (unsigned int y = 0; y < n_tests_y; y++)
        {
            Point2f sample_point = l_box.pMin + Vector2f(x * pixel_size_x, y * pixel_size_y);
            if (!active_texture.is_alpha_pixel(sample_point))
            {
                return true;
            }
        }
    }

    return false;
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