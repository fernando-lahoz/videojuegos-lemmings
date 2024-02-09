#include <vector>
#include <chrono>

#include <SDL2/SDL.h>

#include "engine/render_2D.hpp"
#include "engine/entity.hpp"
#include "engine/physics.hpp"
#include "engine/game.hpp"
#include "engine/engine.hpp"

namespace chr = std::chrono;

using TimePoint = chr::time_point<chr::steady_clock, chr::nanoseconds>;

std::vector<EntityPtr> entities;

static Game_ptr game;
static Camera_ptr camera;
static Render_2D renderer;
static Physics_engine physics;

TimePoint check_point;

void Engine::send_key_down_event(SDL_KeyboardEvent key)
{
    game->on_key_down(this, key);
    camera->on_key_down(this, key);

    for (auto& entity : entities)
    {
        entity->on_key_down(this, key);
    }
}

void Engine::send_key_up_event(SDL_KeyboardEvent key)
{
    game->on_key_up(this, key);
    camera->on_key_up(this, key);

    for (auto& entity : entities)
    {
        entity->on_key_up(this, key);
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
double Engine::get_delta_time()
{
    TimePoint new_check_point = chr::steady_clock::now();

    uint64_t delta = chr::duration_cast<chr::nanoseconds>(
            new_check_point - check_point).count();

    check_point = new_check_point;

    return (double)delta / 1e9;
}

void Engine::compute_physics(double delta_time)
{
    // Send pre-physics event to all entities
    physics.pre_physics(this, delta_time);

    physics.update_positions(this, delta_time);
    physics.compute_collisions(this);
    
    // Send post-physics event to all entities
    physics.post_physics(this, delta_time);
}

// Sorts the drawables in descending z order.
//  Dead entities are moved to the end of the list.
void Engine::sort_by_z_buffer()
{
    std::sort(entities.begin(), entities.end(), [](EntityPtr a, EntityPtr b) -> bool
    {
        return a->getPosition3D().z > b->getPosition3D().z && !a->is_deleted();
    });
}

void Engine::delete_dead_entities()
{
    // Reverse iterator loop
    for (auto it = entities.rbegin(); it != entities.rend(); ++it)
    {
        // Since we are deleting from the end, it should be fast
        if ((*it)->is_deleted()) {
            game->on_entity_destruction(this, *it);
            entities.erase(std::next(it).base());
        }
        // No more entities to delete (since they are sorted)
        else {
            break;
        }
    }
}

void Engine::process_new_entities()
{
    auto new_entities = game->get_new_entities();

    if (new_entities.size() > 0)
        entities.insert(entities.end(), new_entities.begin(), new_entities.end());
}

Engine::Engine(Game_ptr _game)
{
    SDL_Init(SDL_INIT_VIDEO);
    check_point = chr::steady_clock::now();
    renderer = Render_2D(800, 800);
    physics = Physics_engine();


    game = _game;
}

void Engine::start()
{
    camera = game->get_camera();
    game->on_game_startup(this);

    bool quit = false;
    while(!quit)
    {
        double delta_time = get_delta_time();
        game->on_loop_start(this, delta_time);
        quit = process_events();

        // Update call to physics engine
        compute_physics(delta_time);


        // Update entitie list
        process_new_entities();
        // Sort by z buffer, dead entities go to the end
        sort_by_z_buffer();
        // Delete old entities
        delete_dead_entities();


        game->on_loop_end(this, delta_time);

        // Draw call to renderer
        renderer.draw(entities, camera);
    }

    game->on_game_shutdown(this);

    SDL_Quit();
}

std::vector<EntityPtr>* Engine::get_entities()
{
    return &entities;
}

Texture Engine::load_texture(const char* path)
{
    return renderer.loadTexture(path);
}