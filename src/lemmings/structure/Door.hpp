#pragma once

#include "lemmings/structure/Structure.hpp"
#include "lemmings/Lemming.hpp"
#include "lemmings/utils.hpp"

class Door : public Structure
{
private:
  float spawn_timer = 0.0f;
  int level, difficulty;
  Vector2f lemming_size;
  bool is_debug;
  bool change = false;

public:
  Door(Point3f position, Engine &engine, int structure_type, float animation_duration, int level, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(82, 50), engine, "assets/door/door", structure_type, 10, animation_duration, "Door", false, false, game_info, is_debug),
        level(level),
        difficulty(0),
        lemming_size(Vector2f(40, 40))
  {
  }

  Door(Point3f position, Engine &engine, int structure_type, float animation_duration, int level, Game_info &game_info, int difficulty, bool is_debug = false)
      : Structure(position, Vector2f(82, 50), engine, "assets/door/door", structure_type, 10, animation_duration, "Door", false, false, game_info, is_debug),
        level(level),
        difficulty(difficulty),
        lemming_size(Vector2f(40, 40))
  {
  }

  void pre_physics(Engine &engine) override
  {
    if (game_info.get_level_is_paused())
      return;
    Structure::update_animation(engine); // Actualiza la animación

    if (!is_playing)
    { // Espera a que la animación termine para comenzar a invocar
      spawn_timer += engine.get_delta_time() * game_info.get_game_speed();
      if (spawn_timer >= 0.1 + (game_info.get_spawn_velocity() / 50.0f) && game_info.get_spawned_lemmings() < Utils::LEVEL_N_LEMMINGS[difficulty][level] && !game_info.get_all_die())
      {
        // Lógica para invocar Lemmings
        spawn_timer = 0.0f;
        game_info.add_spawned_lemmings();
        game_info.add_n_lemmings_out();
        // Asume que hay una función para crear e inicializar un Lemming
        auto lemming = std::make_shared<Lemming>(calculate_spawn_position(lemming_size), lemming_size, engine, game_info);
        engine.get_game().create_entity(lemming);
        if (game_info.get_spawned_lemmings() == Utils::LEVEL_N_LEMMINGS[difficulty][level])
        {
          game_info.set_spawn_ended();
        }
      }
    }
  }

  Point3f calculate_spawn_position(Vector2f lemming_size) const
  {
    Point3f pos = get_position3D();
    // Calcula la posición central en el eje X de la estructura y ajusta en Y para que el Lemming aparezca encima
    float spawn_x = pos.x + (diagonal.x / 2) - (lemming_size.x / 2);
    float spawn_y = pos.y + (diagonal.y / 2) - (lemming_size.y / 2);
    return Point3f(spawn_x, spawn_y, -5);
  }
};
