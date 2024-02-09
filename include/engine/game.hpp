#pragma once

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "engine/entity.hpp"
#include "engine/engine.hpp"
#include "engine/render_2D.hpp"

class Game
{
    protected:

    std::vector<EntityPtr> new_entities;

    public:

    std::vector<EntityPtr> get_new_entities()
    {
        std::vector<EntityPtr> new_entities_tmp;
        
        // Gets entities to local and clears the game vector
        new_entities_tmp.swap(new_entities);

        return new_entities_tmp;
    }

    // Entities are processed after physics 
    //  and before deleting old entities
    void create_entity(EntityPtr entity)
    {
        new_entities.push_back(entity);
    }

    virtual Camera_ptr get_camera() const
    {
        return std::make_shared<Camera2D>(Bound2f(Point2f(0, 0), Point2f(1, 1)));
    }

    // This is called right before event processing
    //  It is the first thing called in the loop
    virtual void on_loop_start(Engine_ptr, Float) {}

    // This is called at the end of the loop and 
    //  right before the draw call
    virtual void on_loop_end(Engine_ptr, Float) {}

    // Events are processed after on_loop_start
    virtual void on_key_down(Engine_ptr, SDL_KeyboardEvent) {}
    virtual void on_key_up(Engine_ptr, SDL_KeyboardEvent) {}

    // This are called before starting the main loop
    //  and after finishing it
    virtual void on_game_startup(Engine_ptr) {}
    virtual void on_game_shutdown(Engine_ptr) {}

    // Called when right before an entity is destroyed
    virtual void on_entity_destruction(Engine_ptr, EntityPtr) {}
};


typedef std::shared_ptr<Game> Game_ptr;