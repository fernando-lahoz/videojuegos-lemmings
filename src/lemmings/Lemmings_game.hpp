#pragma once

#include <memory>

#include "engine/game.hpp"
#include "engine/entity.hpp"
#include "engine/rigid_body.hpp"

#include "lemmings/camera/Dynamic_camera.hpp"
#include "lemmings/camera/Static_camera.hpp"
#include "lemmings/Lemming.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/cursor/Cursor.hpp"
#include "lemmings/cursor/Cursor_menu.hpp"
#include "lemmings/utils.hpp"
#include "lemmings/screen/Screen_manager.hpp"

// ASK: change _collides_up from bool to EntityPtr

// TODO: add movements to the lemming (BUILD, CLIMB, BASH, MINING)
// TODO: add player vs IA mode
// TODO: add sound effects
// TODO: fix lemming animations
// TODO: fix float animation
// TODO: change assets more similar to original amiga
// TODO: change update_position logic to update_animation

class Lemmings_game : public Game
{
private:
  Game_info game_info;
  Screen_manager screen;

public:
  Lemmings_game()
      : Game("Lemmings"), screen(game_info)
  {
  }

  // Sobrescribe funciones de Game
  std::shared_ptr<Camera2D> get_main_camera() const override
  {
    auto ptr = std::make_shared<Static_camera>(Bound2f(Point2f(10000, 0), Point2f(10640, 400)), Bound2f(Point2f(0, 0), Point2f(640, 400)), 8);

    return std::dynamic_pointer_cast<Camera2D>(ptr);
  }

  void on_game_startup(Engine &engine) override
  {
    engine.set_window_icon("assets/icon.png");

    // HUD CAMERA
    auto ptr = std::make_shared<Static_camera>(Bound2f(Point2f(10000, -500), Point2f(10640, -100)), Bound2f(Point2f(0, 0), Point2f(640, 400)), 8);
    create_camera(std::dynamic_pointer_cast<Camera2D>(ptr));

    // GAME CAMERA
    auto ptr2 = std::make_shared<Dynamic_camera>(game_info, Bound2f(Point2f(1884, 0), Point2f(2524, 320)), Bound2f(Point2f(0, 0), Point2f(640, 320)), 7);
    create_camera(std::dynamic_pointer_cast<Camera2D>(ptr2));

    // MINIMAP CAMERA
    create_camera(std::make_shared<Static_camera>(Bound2f(Point2f(0, 0), Point2f(3168, 320)), Bound2f(Point2f(416, 356), Point2f(616, 396)), 2));

    game_info.set_cursor_txt("assets/cursor.png", engine);
    engine.hide_cursor();

    auto cursor = std::make_shared<Cursor>(engine, game_info, 25);
    create_entity(cursor);
    create_entity(std::make_shared<Cursor_menu>(engine, game_info, 24));
    screen.go_menu(engine, Utils::MENU_TYPE::INTRO, 0, 0);
    // screen.go_level(engine, 25, 1);
  }

  void on_loop_start(Engine &engine) override
  {
    // std::cout << engine.get_delta_time() << std::endl;
    screen.update_game(engine);
  }
};