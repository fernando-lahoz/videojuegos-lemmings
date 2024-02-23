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
#include "lemmings/Screen_manager.hpp"

// TODO: adapt lemming movement to alpha calculations
// TODO: add movements to the lemming (BUILD, CLIMB, BASH, MINING, CRASHING)
// TODO: create animations for menus
// TODO: add credits animations with project contributors
// TODO: add a level selector menu
// TODO: add player vs IA mode
// TODO: add sound effects
// TODO: add exit button functionality
// TODO: add counter explosion above the lemmings
// TODO: add 16-30 level

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
    auto ptr = std::make_shared<Static_camera>(Bound2f(Point2f(0, -500), Point2f(640, -100)), Bound2f(Point2f(0, 0), Point2f(640, 400)), 8);

    return std::dynamic_pointer_cast<Camera2D>(ptr);
  }

  void on_game_startup(Engine &engine) override
  {
    auto ptr = std::make_shared<Static_camera>(Bound2f(Point2f(0, -500), Point2f(640, -100)), Bound2f(Point2f(0, 0), Point2f(640, 400)), 8);
    auto ptr2 = std::make_shared<Dynamic_camera>(game_info, Bound2f(Point2f(1884, 0), Point2f(2524, 320)), Bound2f(Point2f(0, 0), Point2f(640, 320)), 7);

    create_camera(std::dynamic_pointer_cast<Camera2D>(ptr));
    create_camera(std::dynamic_pointer_cast<Camera2D>(ptr2));
    // create_camera(std::make_shared<Static_camera>(Bound2f(Point2f(0, 0), Point2f(3168, 320)), Bound2f(Point2f(416, 356), Point2f(616, 396)), 2));
    // get_main_camera();
    game_info.set_cursor_txt("assets/cursor.png", engine);
    engine.hide_cursor();

    auto cursor = std::make_shared<Cursor>(engine, game_info, 25);
    create_entity(cursor);
    create_entity(std::make_shared<Cursor_menu>(engine, game_info, 24));
    screen.go_menu(engine, Utils::MENU_TYPE::TITLE, 0);
    // screen.go_level(engine, 1);
  }

  void on_loop_start(Engine &engine) override
  {
    if (engine.is_cursor_visible()) {
      engine.hide_cursor();
    }
    else {
      engine.show_cursor();
    }
    screen.update_game(engine);
  }
};