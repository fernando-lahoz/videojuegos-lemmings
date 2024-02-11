#pragma once

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "engine/entity.hpp"
#include "engine/render_2D.hpp"

class Engine;

class Game
{
protected:

    std::vector<EntityPtr> new_entities;

public:

    std::vector<EntityPtr> get_new_entities();

    // Entities are processed after physics 
    //  and before deleting old entities
    void create_entity(EntityPtr entity);

    virtual std::unique_ptr<Camera2D> get_camera() const;

    // This is called right before event processing
    //  It is the first thing called in the loop
    virtual void on_loop_start(Engine& engine);

    // This is called at the end of the loop and 
    //  right before the draw call
    virtual void on_loop_end(Engine& engine);

    // Events are processed after on_loop_start
    virtual void on_key_down(Engine& engine, SDL_KeyboardEvent event);
    virtual void on_key_up(Engine& engine, SDL_KeyboardEvent event);

    // This are called before starting the main loop
    //  and after finishing it
    virtual void on_game_startup(Engine& engine);
    virtual void on_game_shutdown(Engine& engine);

    // Called when right before an entity is destroyed
    virtual void on_entity_destruction(Engine& engine, EntityPtr entity);
};
