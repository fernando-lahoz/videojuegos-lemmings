#pragma once

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "lemmings/utils.hpp"
#include "math/math.hpp"

class Transition : public Entity
{
private:
  enum class AnimationState
  {
    Forward,
    Action,
    Backward
  };

  int n_frames = 256;
  float animation_duration, time_frame_wait = 0.0f;
  Texture txt;

  float time_frame_sprite = 0.0f; // Acumulador de tiempo para la animación del sprite
  int current_frame = 255;        // Frame actual de la animación

  Game_info &game_info;

  AnimationState state = AnimationState::Forward; // Estado actual de la animación

public:
  Transition(Engine &engine, Game_info &_game_info, float _animation_duration)
      : Entity(Point3f(10000, -0, -100), Vector2f(641, 401), engine.load_texture("assets/transition/transition_255.png"), engine, "Transition"),
        animation_duration(_animation_duration), game_info(_game_info)
  {
    game_info.set_can_do_transition(false);
    txt = engine.load_texture("assets/transition/transition_255.png");
    disable_collisions();
  }

  void update_animation(Engine &engine)
  {

    float delta_time = engine.get_delta_time();
    if (time_frame_wait > 0)
    {
      time_frame_wait -= delta_time;
      return;
    }
    time_frame_sprite += delta_time;

    if (time_frame_sprite >= animation_duration / n_frames)
    {
      int times = time_frame_sprite / (animation_duration / n_frames);
      time_frame_sprite = time_frame_sprite - (animation_duration / n_frames) * times;

      if (state == AnimationState::Forward || state == AnimationState::Backward)
      {
        // Actualizar el frame de animación según el estado
        if (state == AnimationState::Forward)
        {
          current_frame = std::max(0, current_frame - times);
          if (current_frame == 0)
          {
            state = AnimationState::Action;
          }
        }
        if (state == AnimationState::Backward)
        {
          current_frame = std::min(n_frames - 1, current_frame + times);
          if (current_frame >= n_frames - 1)
          {
            // std::cout << "TRANSITION END" << std::endl;
            destroy();
            return;
          }
        }

        std::string frame_path = "assets/transition/transition_" + std::to_string(current_frame) + ".png";
        Texture txt = engine.load_texture(frame_path.c_str());
        set_active_texture(txt);
      }

      if (state == AnimationState::Action)
      {
        // time_frame_wait = 0.8f;
        // std::cout << "TRANSITION HALF" << std::endl;
        game_info.set_is_transition_done(true);
        game_info.set_can_do_transition(true);
        engine.get_sound_mixer().pause_all_sounds();
        engine.get_sound_mixer().pause_music();
        state = AnimationState::Backward;
      }
    }
  }

  void post_physics(Engine &engine) override
  {
    update_animation(engine);
  }
};
