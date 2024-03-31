#include "engine/game.hpp"
#include "engine/engine.hpp"
#include "engine/IO.hpp"

std::vector<EntityPtr> Game::get_new_entities()
{
    std::vector<EntityPtr> new_entities_tmp;
    
    // Gets entities to local and clears the game vector
    new_entities_tmp.swap(new_entities);

    return new_entities_tmp;
}

std::vector<std::shared_ptr<Camera2D>> Game::get_new_cameras()
{
    std::vector<std::shared_ptr<Camera2D>> new_cameras_tmp;
    
    // Gets cameras to local and clears the game vector
    new_cameras_tmp.swap(new_cameras);

    return new_cameras_tmp;
}

std::string Game::get_name() const
{
    return game_name;
}

void Game::create_entity(EntityPtr entity)
{
    new_entities.push_back(entity);
}

void Game::create_camera(std::shared_ptr<Camera2D> camera)
{
    new_cameras.push_back(camera);
}

void Game::replace_main_camera(std::shared_ptr<Camera2D> camera)
{
    if (replace_main_cam) {
        new_cameras[0] = camera;
    }
    else {
        new_cameras.insert(new_cameras.begin(), camera);
        replace_main_cam = true;
    }
}

std::shared_ptr<Camera2D> Game::get_main_camera() const
{
    return std::make_shared<Camera2D>(
        Bound2f(Point2f(0, 0), Point2f(1, 1)), //world_frame
        Bound2f(Point2f(0, 0), Point2f(800, 800))  //camera_frame
    );
}

void Game::on_loop_start(Engine&) {}

void Game::on_loop_end(Engine&) {}

void Game::on_event_down(Engine&, EngineIO::InputEvent) {}

void Game::on_event_up(Engine&, EngineIO::InputEvent) {}

void Game::on_game_startup(Engine&) {}

void Game::on_game_shutdown(Engine&) {}

void Game::on_entity_destruction(Engine&, EntityPtr) {}

void Game::on_async_task_finished(Engine&, long long) {}