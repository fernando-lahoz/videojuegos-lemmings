
#pragma once

#include "Structure.hpp"
#include "utils.hpp"

class Door : public Structure
{
private:
  float spawn_timer = 0.0f;
  int spawned_lemmings = 0;
  int level;
  Vector2f lemming_size;
  bool is_debug;
  bool change = false;

public:
  Door(Point3f position, float size, Engine &engine, int structure_type, float animation_duration, int level, Level_info &level_info, bool is_debug = false)
      : Structure(position, Vector2f(41 * size, 25 * size), engine, "assets/door/door", structure_type, 10, animation_duration, "Door", false, false, level_info, is_debug),
        level(level),
        lemming_size(Vector2f(20 * size, 20 * size))
  {
  }

  void pre_physics(Engine &engine) override
  {
    Structure::update_animation(engine); // Actualiza la animación

    if (!is_playing)
    { // Espera a que la animación termine para comenzar a invocar
      spawn_timer += engine.get_delta_time();
      if (spawn_timer >= 0.1 + (level_info.get_spawn_velocity() / 50.0f) && spawned_lemmings < Utils::LEVEL_N_LEMMINGS[level] && !level_info.get_dead_marked())
      {
        // Lógica para invocar Lemmings
        spawn_timer = 0.0f;
        spawned_lemmings++;
        level_info.add_n_lemmings_out();
        // Asume que hay una función para crear e inicializar un Lemming
        auto lemming = std::make_shared<Lemming>(calculate_spawn_position(lemming_size), lemming_size, engine, level_info);
        engine.get_game()->create_entity(lemming);
        if (spawned_lemmings == Utils::LEVEL_N_LEMMINGS[level])
        {
          level_info.set_spawn_ended();
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
    return Point3f(spawn_x, spawn_y, 18);
  }
};
