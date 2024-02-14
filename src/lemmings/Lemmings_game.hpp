#pragma once

#include <memory>

#include "engine/game.hpp"
#include "engine/entity.hpp"

#include "Lemmings_camera.hpp"
#include "Lemming.hpp"
#include "Level.hpp"
#include "Level_info.hpp"
#include "Cursor.hpp"

// ASK: change_bkg() ???
// ASK: when entity destroy() MOUSE_HOVER doesn't change
// ASK: destroy_all_entities() with a filter for a specific _entity_name (CURSOR)
// ASK: on_detect_border_cursor() when the cursor is moved around [0-0.05,-] and [0.95-1,-] executes a function
// ASK: do_action_all_entities() with a filter for a specific _entity_name (Lemming)
class Lemmings_game : public Game
{
private:
  Level_info level_info;

public:
  Lemmings_game()
      : Game("Lemmings")
  {
  }

  // Sobrescribe funciones de Game
  std::shared_ptr<Camera2D> get_camera() const override
  {
    return std::make_shared<Lemmings_camera>();
  }

  void on_game_startup(Engine &engine) override
  {
    level_info.set_txt("assets/cursor.png", engine);

    auto cursor = std::make_shared<Cursor>(engine, level_info, 0.05);
    engine.get_game()->create_entity(cursor);
    Level level(engine, 0, level_info); // Crea el nivel correspondiente
  }
};