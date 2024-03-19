#pragma once

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"

#include "lemmings/utils.hpp"

class Menu_animation : public Rigid_body
{
private:
  int type, n_frames;
  float time_wait, random_time_max, animation_duration;
  Texture txt;
  bool is_playing = true;

  float time_frame_sprite = 0.0f; // Acumulador de tiempo para la animación del sprite
  int current_frame = 0;          // Frame actual de la animación

  float time_frame_wait = 0.0f; // Acumulador de tiempo para la animación del sprite

  bool change = false, is_debug;

  float velocity = 3.0f;

public:
  Menu_animation(Point3f position, Vector2f size, Engine &engine, int _type, int _n_frames, float _animation_duration, float _time_wait = 0.0f, float _random_time_max = 0.0f, bool _is_debug = false)
      : Rigid_body(position, size, engine.load_texture("assets/menu/menu_animation_" + std::to_string(_type) + "_0.png"), engine, "Menu Animation"),
        type(_type), n_frames(_n_frames), time_wait(_time_wait), random_time_max(_random_time_max), animation_duration(_animation_duration), is_debug(_is_debug)
  {
    txt = engine.load_texture("assets/menu/menu_animation_" + std::to_string(_type) + "_0.png");
    time_frame_wait = time_wait;
    disable_collisions();
  }

  void update_animation(Engine &engine)
  {
    if (time_frame_wait > 0)
    {
      time_frame_wait -= engine.get_delta_time();
      return;
    }

    time_frame_sprite += engine.get_delta_time();
    if (time_frame_sprite >= animation_duration / n_frames)
    {
      time_frame_sprite = 0.0f;
      current_frame = (current_frame + 1) % n_frames;

      if (current_frame == 0)
      {
        time_frame_wait = time_wait + (Float)(rand() % (int)(random_time_max * 100)) / 100;
      }

      std::string frame_path = "assets/menu/menu_animation_" + std::to_string(type) + "_" + std::to_string(current_frame) + ".png";

      Texture txt = engine.load_texture(frame_path.c_str());
      set_active_texture(txt);
    }
  }

  void pre_physics(Engine &engine) override
  {
    update_animation(engine);
  }

  void debug_mode(Engine &engine)
  {
    auto speed = get_speed();

    if (engine.is_up_arrow_down())
    {
      speed.y = -velocity;
      change = true;
    }

    if (engine.is_down_arrow_down())
    {
      speed.y = velocity;
      change = true;
    }

    if (engine.is_left_arrow_down())
    {
      speed.x = -velocity;
      change = true;
    }

    if (engine.is_right_arrow_down())
    {
      speed.x = velocity;
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

  void update_state(Engine &engine) override
  {
    if (is_debug)
      debug_mode(engine);
    // std::cout << "State: " << state << "\n";

    Rigid_body::update_state(engine);
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
