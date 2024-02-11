#include <vector>
#include <chrono>

#include <SDL2/SDL.h>

#include "engine/render_2D.hpp"
#include "engine/entity.hpp"
#include "engine/physics.hpp"
#include "engine/game.hpp"
#include "engine/engine.hpp"
#include "lib/error.hpp"

void Engine::send_key_down_event(SDL_KeyboardEvent key)
{
    game->on_key_down(*this, key);
    camera->on_key_down(*this, key);

    for (auto& entity : entities)
    {
        entity->on_key_down(*this, key);
    }
}

void Engine::send_key_up_event(SDL_KeyboardEvent key)
{
    game->on_key_up(*this, key);
    camera->on_key_up(*this, key);

    for (auto& entity : entities)
    {
        entity->on_key_up(*this, key);
    }
}


// Returns true if the program should quit
bool Engine::process_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            return true;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_q)
            {
                return true;
            }

            Engine::send_key_down_event(event.key);
        }

        if (event.type == SDL_KEYUP)
        {
            Engine::send_key_up_event(event.key);
        }
    }

    return false;
}


// Returns delta time in seconds
void Engine::update_delta_time()
{
    TimePoint new_check_point = std::chrono::steady_clock::now();

    uint64_t new_delta = std::chrono::duration_cast<std::chrono::nanoseconds>(
            new_check_point - check_point).count();

    check_point = new_check_point;

    if (total_delta_ns > 0 && new_delta > 4 * total_delta_ns / total_measurements)
    {
        // Invalid delta time (game freezed) -> replace by mean delta time
        delta_ns = total_delta_ns / total_measurements;
    }
    else if ((total_measurements & 0xFFFF) == 0)
    {
        // Mean delta time can grow over time, so we reset after some thousand
        // measurements to the last valid delta time
        delta_ns = new_delta;
        total_delta_ns = new_delta;
        total_measurements = 1;
    }
    else
    {
        delta_ns = new_delta;
        total_delta_ns += new_delta;
        total_measurements++;
    }

    delta_time = (double)delta_ns / 1e9;
}

void Engine::compute_physics()
{
    // Send pre-physics event to all entities
    physics.pre_physics(*this);

    physics.update_positions(*this);
    physics.compute_collisions(*this);
    
    // Send post-physics event to all entities
    physics.post_physics(*this);
}

// Sorts the drawables in descending z order.
//  Dead entities are moved to the end of the list.
void Engine::sort_by_z_buffer()
{
    std::sort(entities.begin(), entities.end(), [](EntityPtr a, EntityPtr b) -> bool
    {
        return a->get_position3D().z > b->get_position3D().z && !a->is_deleted();
    });
}

// Removes all entities with a deleted flag, assuming an ordered vector with
//  all dead entities at the end
void Engine::delete_dead_entities()
{
    auto is_deleted = [](EntityPtr entity){return entity->is_deleted();};
    auto iterator = std::find_if(entities.begin(), entities.end(), is_deleted);
    
    std::for_each(iterator, entities.end(), [this](EntityPtr entity) {
        game->on_entity_destruction(*this, entity);
    });
    entities.resize(std::distance(entities.begin(), iterator));
}

void Engine::process_new_entities()
{
    auto new_entities = game->get_new_entities();

    for (auto& entity : new_entities) {
        entity->set_entity_id(entities.size());
        entities.push_back(entity);
    }
}

Engine::Engine(std::unique_ptr<Game>&& game)
    : game{std::move(game)}
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw error::sdl_exception(ERROR_CONTEXT);

    check_point = std::chrono::steady_clock::now();
    renderer = Render_2D(800, 800);
    physics = Physics_engine();
}

Engine::Engine(Game *game)
    : game{game}
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw error::sdl_exception(ERROR_CONTEXT);

    check_point = std::chrono::steady_clock::now();
    renderer = Render_2D(800, 800);
    physics = Physics_engine();
}

// Intersect a ray with all entities in the engine
// If check_z_axis is true, only entities with a z coordinate == than the
//  ray's intersection point will be considered 
//  (If the ray does not move on z axis, then only entities with 
//  z == than ray's origin will be considered)
bool Engine::intesect_ray(Ray &ray, bool check_z_axis, Float &hit_offset, EntityPtr &hit_entity)
{
    hit_offset = INFINITY;

    for (auto& entity : entities)
    {
        auto bounding_box = entity->bound2f();
        Float offset;

        if (bounding_box.intersects(ray, offset) 
            && (offset < hit_offset)
            && (!check_z_axis 
                || 
                (entity->get_position3D().z == ray(offset).z)))
        {
            hit_entity = entity;
            hit_offset = offset;
        }
    }

    return hit_offset < INFINITY;
}

bool Engine::intesect_ray(Ray &ray, 
            bool check_z_axis,
            int not_this_entity_id,
            Float &hit_offset, 
            EntityPtr &hit_entity)
{
    hit_offset = INFINITY;

    for (auto& entity : entities)
    {
        if (entity->get_entity_id() == not_this_entity_id)
            continue;

        auto bounding_box = entity->bound2f();
        Float offset;

        if (bounding_box.intersects(ray, offset) 
            && (offset < hit_offset)
            && (!check_z_axis 
                || 
                (entity->get_position3D().z == ray(offset).z)))
        {
            hit_entity = entity;
            hit_offset = offset;
        }
    }

    return hit_offset < INFINITY;

}

void Engine::start()
{
    camera = game->get_camera();
    game->on_game_startup(*this);

    bool quit = false;
    while(!quit)
    {
        update_delta_time();
        game->on_loop_start(*this);
        quit = process_events();

        // Update call to physics engine
        compute_physics();


        // Update entitie list
        process_new_entities();
        // Sort by z buffer, dead entities go to the end
        sort_by_z_buffer();
        // Delete old entities
        delete_dead_entities();


        game->on_loop_end(*this);

        // Draw call to renderer
        renderer.draw(entities, *camera);
    }

    game->on_game_shutdown(*this);

    SDL_Quit();
}

Engine::EntityCollection& Engine::get_entities()
{
    return entities;
}

Texture Engine::load_texture(const std::string& path)
{
    return renderer.load_texture(path);
}

double Engine::get_delta_time()
{
    return delta_time;
}