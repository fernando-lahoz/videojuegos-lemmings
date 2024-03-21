#pragma once

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "lemmings/utils.hpp"
#include "math/math.hpp"

class Intro : public Entity
{
private:
  enum class AnimationState
  {
    Forward,
    Action
  };

  int n_frames = 991;
  float animation_duration, time_frame_wait;
  Texture txt;

  float time_frame_sprite = 0.0f; // Acumulador de tiempo para la animación del sprite
  int current_frame = 0;          // Frame actual de la animación
  bool is_playing = false;

  Music intro;

  Game_info &game_info;

  AnimationState state = AnimationState::Forward; // Estado actual de la animación

public:
  Intro(Engine &engine, Game_info &_game_info)
      : Entity(Point3f(10000, -0, -50), Vector2f(640, 400), engine.load_texture("assets/intro/intro_0.jpg"), engine, "Intro"),
        game_info(_game_info)
  {
    txt = engine.load_texture("assets/intro/intro_0.jpg");
    disable_collisions();
    time_frame_wait = 0.0f;
    animation_duration = 36.0f;

    auto &mixer = engine.get_sound_mixer();
    intro = mixer.load_music("assets/music/01_March of the Mods (Intro Theme).mp3");
  }

  void update_animation(Engine &engine)
  {

    float delta_time = engine.get_delta_time();
    if (time_frame_wait > 0)
    {
      time_frame_wait -= delta_time;
      return;
    }
    if (!is_playing && game_info.get_sound_effects())
    {
      auto &mixer = engine.get_sound_mixer();
      mixer.play_music(intro, false);
      is_playing = true;
    }
    time_frame_sprite += delta_time;

    if (time_frame_sprite >= animation_duration / n_frames)
    {
      int times = time_frame_sprite / (animation_duration / n_frames);
      time_frame_sprite = time_frame_sprite - (animation_duration / n_frames) * times;

      if (state == AnimationState::Action)
      {
        // time_frame_wait = 0.8f;
        std::cout << "INTRO ENDED" << std::endl;
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::TITLE, 0, 0);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
      }

      if (state == AnimationState::Forward)
      {
        // Actualizar el frame de animación según el estado
        if (state == AnimationState::Forward)
        {
          current_frame = std::min(n_frames - 1, current_frame + times);
          if (current_frame >= n_frames - 1)
          {
            time_frame_wait = 2.0f;
            current_frame = n_frames - 1;
            state = AnimationState::Action;
          }
        }

        std::string frame_path = "assets/intro/intro_" + std::to_string(current_frame) + ".jpg";
        Texture txt = engine.load_texture(frame_path.c_str());
        set_active_texture(txt);
      }
    }
  }

  void post_physics(Engine &engine) override
  {
    update_animation(engine);
  }
};
