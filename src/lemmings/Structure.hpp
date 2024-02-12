#pragma once

#include "engine/entity.hpp"
#include <string>

class Structure : public Rigid_body
{
protected:
  float time_frame_sprite = 0.0f;  // Acumulador de tiempo para la animación del sprite
  std::string base_path;           // Base para el path de las texturas de animación
  bool is_loop;                    // Indica si la animación es en bucle
  bool is_event_triggered;         // Indica si la animación se dispara por un evento
  bool is_playing;                 // Indica si la animación está actualmente en reproducción
  int current_frame = 0;           // Frame actual de la animación
  int structure_type = 0;          // Identifier for the type of structure
  int max_frames;                  // Número máximo de frames de la animación
  float animation_duration = 0.0f; // Duración total de la animación
  bool is_debug;
  bool change = false;

public:
  Structure(Point3f position, Vector2f diagonal, Engine &engine, std::string base_path, int structure_type, int max_frames, float animation_duration, std::string name = "Structure", bool is_loop = false, bool is_event_triggered = false, bool is_debug = false)
      : Rigid_body(position, diagonal, engine.load_texture(base_path + "_" + std::to_string(structure_type) + "_0.png"), name),
        base_path(base_path),
        is_loop(is_loop),
        is_event_triggered(is_event_triggered),
        is_playing(!is_event_triggered), // Si no se dispara por evento, comienza a reproducir inmediatamente
        structure_type(structure_type),
        max_frames(max_frames),
        animation_duration(animation_duration),
        is_debug(is_debug)
  {
  }

  bool get_is_playing()
  {
    return is_playing;
  }

  void update_animation(Engine &engine)
  {
    if (!is_playing)
      return;

    time_frame_sprite += engine.get_delta_time();
    if (time_frame_sprite >= animation_duration / max_frames)
    {
      time_frame_sprite = 0.0f;
      current_frame = (current_frame + 1) % max_frames;

      if (!is_loop && current_frame == 0)
      {
        is_playing = false; // Detiene la animación si no es en bucle
        if (!is_event_triggered)
          return;
      }

      std::string frame_path = base_path + "_" + std::to_string(structure_type) + "_" + std::to_string(current_frame) + ".png";
      Texture txt = engine.load_texture(frame_path.c_str());
      set_active_texture(txt);
    }
  }

  // Método para disparar la animación si esta es por evento
  void trigger_event_animation()
  {
    if (is_event_triggered && !is_playing)
    {
      is_playing = true;
      current_frame = 0;
      time_frame_sprite = 0.0f;
    }
  }

  void pre_physics(Engine &engine) override
  {
    Structure::update_animation(engine);
  }

  void debug_mode(Engine &engine)
  {
    auto speed = get_speed();

    if (engine.is_up_arrow_down())
    {
      speed.y = -0.1;
      change = true;
    }

    if (engine.is_down_arrow_down())
    {
      speed.y = 0.1;
      change = true;
    }

    if (engine.is_left_arrow_down())
    {
      speed.x = -0.1;
      change = true;
    }

    if (engine.is_right_arrow_down())
    {
      speed.x = 0.1;
      change = true;
    }

    if (engine.is_down_arrow_down() && engine.is_up_arrow_down())
    {
      speed.y = 0;
    }

    if (!engine.is_down_arrow_down() && !engine.is_up_arrow_down())
    {
      speed.y = 0;
    }

    if (engine.is_right_arrow_down() && engine.is_left_arrow_down())
    {
      speed.x = 0;
    }

    if (!engine.is_right_arrow_down() && !engine.is_left_arrow_down())
    {
      speed.x = 0;
    }

    set_speed(speed);
  }

  void update_position(Engine &engine) override
  {
    if (is_debug)
      debug_mode(engine);
    // std::cout << "State: " << state << "\n";

    Rigid_body::update_position(engine);
  }

  void post_physics(Engine &) override
  {
    if (change)
    {
      std::cout << "Position = " << get_position2D() << std::endl;
      change = false;
    }
  }
};
