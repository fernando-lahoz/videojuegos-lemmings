#include "engine/game.hpp"
#include "engine/engine.hpp"

std::vector<EntityPtr> Game::get_new_entities()
{
    std::vector<EntityPtr> new_entities_tmp;
    
    // Gets entities to local and clears the game vector
    new_entities_tmp.swap(new_entities);

    return new_entities_tmp;
}

void Game::create_entity(EntityPtr entity)
{
    new_entities.push_back(entity);
}

std::unique_ptr<Camera2D> Game::get_camera() const
{
    return std::make_unique<Camera2D>(Bound2f(Point2f(0, 0), Point2f(1, 1)));
}

void Game::on_loop_start(Engine&) {}

void Game::on_loop_end(Engine&) {}

void Game::on_key_down(Engine&, SDL_KeyboardEvent) {}

void Game::on_key_up(Engine&, SDL_KeyboardEvent) {}

void Game::on_game_startup(Engine&) {}

void Game::on_game_shutdown(Engine&) {}

void Game::on_entity_destruction(Engine&, EntityPtr) {}