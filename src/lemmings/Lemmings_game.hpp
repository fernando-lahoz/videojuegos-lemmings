#pragma once

#include <memory>

#include "engine/game.hpp"
#include "engine/entity.hpp"

#include "Lemmings_camera.hpp"
#include "Lemming.hpp"
#include "Level_manager.hpp"

// Incluir otros archivos necesarios como Lemming, LevelManager, etc.

class Lemmings_game : public Game
{
private:
  int n_lemmings = 0;                   // Número actual de Lemmings en el nivel
  int max_lemmings = 100;               // Máximo número de Lemmings permitidos en el nivel
  float time_since_last_lemming = 0.0f; // Acumulador de tiempo

  // Otros miembros privados como LevelManager, UI/HUD, etc.

public:
  // Sobrescribe funciones de Game
  std::shared_ptr<Camera2D> get_camera() const override
  {
    return std::make_shared<Lemmings_camera>();
  }

  void on_game_startup(Engine &engine) override
  {
    auto t2 = engine.load_texture("assets/maps/bkg/1 - Just dig!.png");

    auto map = std::make_shared<Entity>(Point3f(0, 0.75, 1), Vector2f(1, 0.25), t2, "MAP");
    auto map1 = std::make_shared<Entity>(Point3f(0, 0.6, 1), Vector2f(0.1, 0.25), t2, "MAP");
    auto map2 = std::make_shared<Entity>(Point3f(0.9, 0.6, 1), Vector2f(0.1, 0.25), t2, "MAP");
    auto map3 = std::make_shared<Entity>(Point3f(0.45, 0.6, 1), Vector2f(0.1, 0.25), t2, "MAP");

    create_entity(map);
    create_entity(map1);
    create_entity(map2);
    create_entity(map3);
  }

  void on_loop_start([[maybe_unused]] Engine &engine) override
  {
    time_since_last_lemming += engine.get_delta_time(); // Acumula el tiempo transcurrido

    // Comprueba si ha pasado 1 segundo y si no se ha alcanzado el máximo de Lemmings
    if (time_since_last_lemming >= 1.0f && n_lemmings < max_lemmings)
    {
      auto lemming = std::make_shared<Lemming>(Point3f(0.47, 0.0, 0), Vector2f(0.08, 0.08), engine);
      create_entity(lemming);
      n_lemmings++;
      time_since_last_lemming = 0.0f; // Restablece el contador después de crear un Lemming
    }
  }

  void on_entity_destruction([[maybe_unused]] Engine &engine, EntityPtr entity) override
  {
    // Manejo de la destrucción de entidades, por ejemplo, reducir el contador de Lemmings si se destruye uno
    if (entity->get_entity_name() == "Lemming")
    {
      n_lemmings--;
      // Otros manejos específicos cuando se destruye un Lemming
    }
  }
};
