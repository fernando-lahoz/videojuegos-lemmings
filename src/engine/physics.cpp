#include "engine/physics.hpp"
#include "engine/engine.hpp"

void Physics_engine::update_positions(Engine &engine)
{
    auto &entities = engine.get_entities();
    auto delta_time = engine.get_delta_time();

    for (auto &entity : entities)
    {
        entity->update_gravity(delta_time);
    }

    for (auto &entity : entities)
    {
        entity->update_position(delta_time);
    }
}

void Physics_engine::compute_collisions(Engine &engine)
{
    // auto &huds = engine.get_hud_entities();
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

bool Physics_engine::alpha_box_collision(const Entity &entity, const Bound2f &box)
{
    Bound2f l_box = entity.world_to_local(box);
    Texture active_texture = entity.get_active_texture();

    if (!entity.is_alpha_collision())
    {
        return entity.bound2f().overlaps(box);
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

bool Physics_engine::alpha_box_collision_if_all(const Entity &entity, const Bound2f &box,
                                                ReturnedPixel horizontal_pixel,
                                                ReturnedPixel vertical_pixel,
                                                bool &is_valid, Point2f &pixel)
{
    Bound2f l_box = entity.world_to_local(box);
    Texture active_texture = entity.get_active_texture();

    if (!entity.is_alpha_collision())
    {
        return entity.bound2f().overlaps(box);
    }

    l_box = Bound2f(clamp(l_box.pMin, Point2f(0, 0), Point2f(1, 1)),
                    clamp(l_box.pMax, Point2f(0, 0), Point2f(1, 1)));

    Vector2f diagonal = l_box.diagonal();

    // int n_tests_x = std::round(diagonal.x * active_texture.get_width());
    // int n_tests_y = std::round(diagonal.y * active_texture.get_height());
    int n_tests_x = std::round(box.pMax.x - box.pMin.x) / 2;
    int n_tests_y = std::round(box.pMax.y - box.pMin.y) / 2;

    Float pixel_size_x = 1.0 / active_texture.get_width();
    Float pixel_size_y = 1.0 / active_texture.get_height();

    int min_loop_x = -1, min_loop_y = -1;

    bool some_alpha = false;
    bool none_solid = true;

    if (vertical_pixel == GET_FIRST)
    {
        for (int loop_x = 0; loop_x < n_tests_x; loop_x++)
        {
            int x = loop_x;
            for (int loop_y = 0; loop_y < n_tests_y; loop_y++)
            {
                const int y = loop_y;

                Point2f sample_point = l_box.pMin + Vector2f(x * pixel_size_x, y * pixel_size_y);
                if (!active_texture.is_alpha_pixel(sample_point))
                {
                    none_solid = false;
                    if ((min_loop_x < 0) || (loop_x <= min_loop_x && loop_y <= min_loop_y))
                    {
                        min_loop_x = loop_x;
                        min_loop_y = loop_y;
                        pixel = sample_point;
                    }

                    if (some_alpha)
                        break;
                }
                else
                {
                    some_alpha = true;

                    if (!none_solid)
                    {
                        break;
                    }
                }
            }
        }
    }
    else
    {
        for (int loop_x = 0; loop_x < n_tests_x; loop_x++)
        {
            const int x = n_tests_x - 1 - loop_x;
            for (int loop_y = 0; loop_y < n_tests_y; loop_y++)
            {
                const int y = n_tests_y - 1 - loop_y;

                Point2f sample_point = l_box.pMin + Vector2f(x * pixel_size_x, y * pixel_size_y);
                if (!active_texture.is_alpha_pixel(sample_point))
                {
                    none_solid = false;

                    min_loop_x = loop_x;
                    min_loop_y = loop_y;
                    pixel = sample_point;
                }
                else
                {
                    some_alpha = true;

                    if (!none_solid)
                    {
                        break;
                    }
                }
            }
        }
    }

    pixel = entity.local_to_world(pixel);

    is_valid = !none_solid;
    return !some_alpha;
}

void Physics_engine::pre_physics(Engine &engine)
{
    auto &entities = engine.get_entities();

    for (auto &entity : entities)
    {
        entity->pre_physics(engine);
    }
}

void Physics_engine::post_physics(Engine &engine)
{
    auto &entities = engine.get_entities();

    for (auto &entity : entities)
    {
        entity->post_physics(engine);
    }
}