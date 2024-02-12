#pragma once

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "engine/entity.hpp"
#include "engine/render_2D.hpp"
#include "engine/IO.hpp"

class Engine;

class Game
{
protected:

    std::vector<EntityPtr> new_entities;
    std::string game_name;

public:

    Game(std::string _game_name)
    : game_name(_game_name)
    { }

    std::vector<EntityPtr> get_new_entities();

    std::string get_name() const;

    // Entities are processed after physics 
    //  and before deleting old entities
    void create_entity(EntityPtr entity);

    virtual std::shared_ptr<Camera2D> get_camera() const;

    // This is called right before event processing
    //  It is the first thing called in the loop
    virtual void on_loop_start(Engine& engine);

    // This is called at the end of the loop and 
    //  right before the draw call
    virtual void on_loop_end(Engine& engine);

    // Events are processed after on_loop_start
    virtual void on_event_down(Engine& engine, EngineIO::InputEvent event);
    virtual void on_event_up(Engine& engine, EngineIO::InputEvent event);

    // This are called before starting the main loop
    //  and after finishing it
    virtual void on_game_startup(Engine& engine);
    virtual void on_game_shutdown(Engine& engine);

    // Called when right before an entity is destroyed
    virtual void on_entity_destruction(Engine& engine, EntityPtr entity);
};
