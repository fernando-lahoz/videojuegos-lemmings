#pragma once

#include <memory>

#include "engine/game.hpp"
#include "engine/entity.hpp"
#include "engine/rigid_body.hpp"

#include "lemmings/Lemmings_camera.hpp"
#include "lemmings/Lemming.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/Cursor.hpp"
#include "lemmings/utils.hpp"
#include "lemmings/Screen_manager.hpp"

// ASK: change_bkg() ???
// ASK: on_detect_border_cursor() when the cursor is moved around [0-0.05,-] and [0.95-1,-] executes a function

// cuando se intenta borrar mas de 10 entidades (en un for haciendo destroy) colapsa y se cierra el juego

// TODO: adapt lemming movement to alpha calculations
// TODO: add movements to the lemming (BUILD, CLIMB, BASH, MINING, CRASHING)
// TODO: add logic when the cursor is moved around [0-0.05,-] and [0.95-1,-] moves the camera
// TODO: process all text assets for level info in menus
// TODO: create animations for menus
// TODO: add credits animations with project contributors
// TODO: add a level selector menu
// TODO: add level intro & outro menu
// TODO: add player vs IA mode
// TODO: add sound effects
// TODO: add exit button functionality
// TODO: add counter explosion above the lemmings
// TODO: add 12-30 level

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
    return std::make_shared<Lemmings_camera>();
  }

  void on_game_startup(Engine &engine) override
  {
    game_info.set_cursor_txt("assets/cursor.png", engine);
    engine.hide_cursor();

    auto cursor = std::make_shared<Cursor>(engine, game_info, 0.05);
    engine.get_game().create_entity(cursor);
    screen.go_menu(engine, Utils::MENU_TYPE::TITLE, 0);
    // screen.go_level(engine, 0);
  }

  void on_loop_start(Engine &engine) override
  {
    screen.update_game(engine);
  }

  // void on_entity_destruction(Engine &engine, EntityPtr entity) override
  // {
  //   std::cout << "DELETED: " << entity->get_entity_name() << std::endl;
  //   std::cout << "N_ENTITIES: " << engine.get_entities().size() << std::endl;
  // }
};