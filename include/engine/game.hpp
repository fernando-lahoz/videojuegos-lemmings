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
    std::vector<std::shared_ptr<Camera2D>> new_cameras;
    std::string game_name;
    bool replace_main_cam = false;
    Vector2i _initial_window_size;

public:

    Game(std::string _game_name, Vector2i initial_window_size = Vector2i{-1, -1})
    : game_name(_game_name), _initial_window_size{initial_window_size}
    { }

    virtual ~Game() = default;

    Vector2i get_initial_window_size() const;

    std::vector<EntityPtr> get_new_entities();
    std::vector<std::shared_ptr<Camera2D>> get_new_cameras();

    std::string get_name() const;

    // Entities are processed after physics 
    //  and before deleting old entities
    virtual void create_entity(EntityPtr entity);

    void create_camera(std::shared_ptr<Camera2D> camera);
    void replace_main_camera(std::shared_ptr<Camera2D> camera);

    // Creates the initial main camera used at the begining of the game
    virtual std::shared_ptr<Camera2D> get_main_camera() const;

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

    virtual void on_preload_finished(Engine& engine, int batch_id);

    virtual void on_level_startup(int difficulty_number, int level_id) {};

    friend class Engine;
};
