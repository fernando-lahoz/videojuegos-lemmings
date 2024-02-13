#pragma once

#include <memory>

#include "engine/game.hpp"
#include "engine/entity.hpp"

#include "Lemmings_camera.hpp"
#include "Lemming.hpp"
#include "Level.hpp"

class Lemmings_game : public Game
{
private:
  // Otros miembros privados como LevelManager, UI/HUD, etc.

public:
  Lemmings_game()
      : Game("Lemmings")
  {
    // Inicializar otros miembros privados
  }

  // Sobrescribe funciones de Game
  std::shared_ptr<Camera2D> get_camera() const override
  {
    return std::make_shared<Lemmings_camera>();
  }

  void on_game_startup(Engine &engine) override
  {
    Level level(engine, 0); // Crea el nivel correspondiente
  }
};