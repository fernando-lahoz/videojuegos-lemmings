#pragma once

#include "engine/engine.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/Level.hpp"
#include "lemmings/menu/Menu.hpp"
#include "lemmings/screen/Transition.hpp"
#include "lemmings/keyboard/Keyboard_manager.hpp"

class Screen_manager
{
private:
  Level level;
  Menu menu;
  std::shared_ptr<Transition> transition;

  Game_info &game_info;

  int last_lemmings_hovered = 0;
  float timer_transition = 0.0f;

public:
  Screen_manager(Game_info &_game_info, Keyboard_manager &_keyboard) : level(_game_info), menu(_game_info, _keyboard), game_info(_game_info)
  {
  }

  void go_level(Engine &engine, int _level, int _difficulty)
  {
    game_info.set_actual_state(Utils::STATE::GAME);
    game_info.set_do_action(Utils::ACTIONS::NO_ACTION);
    level.setup_level(engine, _level, _difficulty);
  }

  void go_menu(Engine &engine, int type, int _level, int _difficulty)
  {
    game_info.set_is_camera_stopped(true);
    game_info.set_actual_state(Utils::STATE::MENU);
    game_info.set_do_action(Utils::ACTIONS::NO_ACTION);
    menu.setup_menu(engine, type, _level, _difficulty);
  }

  void clear_screen(Engine &engine)
  {
    // engine.destroy_all_entities();
    auto &entities = engine.get_entities();
    for (auto &entity : entities)
    {
      if (entity->get_entity_name() != "Cursor" && entity->get_entity_name() != "Transition")
      {
        entity->destroy();
      }
    }
  }

  void update_game(Engine &engine)
  {
    if (game_info.get_do_action() == Utils::ACTIONS::GO_MENU && game_info.get_is_transition_done())
    {
      game_info.set_cursor_menu_visible();
      game_info.set_is_transition_done(false);
      clear_screen(engine);
      if (game_info.get_build_menu() == Utils::MENU_TYPE::IA)
      {
        game_info.set_ia(true);
      }
      std::cout << "GO TO MENU" << std::endl;
      go_menu(engine, game_info.get_build_menu(), game_info.get_level(), game_info.get_difficulty());
    }
    else if (game_info.get_do_action() == Utils::ACTIONS::GO_LEVEL && game_info.get_is_transition_done())
    {
      game_info.set_is_transition_done(false);
      clear_screen(engine);
      std::cout << "GO TO LEVEL" << std::endl;
      go_level(engine, game_info.get_build_level(), game_info.get_build_difficulty());
    }
    else if (game_info.get_do_action() == Utils::ACTIONS::NO_ACTION)
    {
      if (game_info.get_actual_state() == Utils::STATE::GAME)
      {
        int actual_lemmings_hovered = game_info.get_lemmings_hovered();

        if (actual_lemmings_hovered != last_lemmings_hovered)
        {
          std::cout << "Lemmings hovered: " << actual_lemmings_hovered << std::endl;
          last_lemmings_hovered = actual_lemmings_hovered;
        }

        if (game_info.get_time_left() > 0.0f && !game_info.get_level_ended())
        {

          if (!game_info.get_level_is_paused())
          {
            game_info.set_time_left(game_info.get_time_left() - engine.get_delta_time()); // * game_info.get_game_speed());
          }
        }
        else
        {
          std::cout << "LEMMINGS OUT: " << game_info.get_n_lemmings_out() << std::endl;
          std::cout << "GAME OVER" << std::endl;
          timer_transition = 2.f;
          game_info.manage_level_results();
          game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_OUTRO);
          game_info.set_do_action(Utils::ACTIONS::GO_MENU);
          // game_info.set_build_level(game_info.get_build_level() + 1);
          // game_info.set_do_action(Utils::ACTIONS::GO_LEVEL);
        }
      }
    }
    else
    {
      if (timer_transition > 0)
      {
        timer_transition -= engine.get_delta_time();
        if (timer_transition < 0)
        {
          engine.set_delta_time_factor(1.0);
          engine.get_game().create_entity(std::make_shared<Transition>(engine, game_info, 1.0f));
        }
      }

      if (game_info.get_do_transition() && game_info.get_can_do_transition())
      {
        game_info.set_do_transition(false);
        engine.get_game().create_entity(std::make_shared<Transition>(engine, game_info, 1.0f));
      }
    }

    // Update sound and music if its the start of level
    if (game_info.get_level_is_paused() || game_info.get_level_ended())
      return;

    // Hacemos sonar una puerta que chirria
    if (game_info.get_play_open_sound())
    {
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::DOOR_SOUND), game_info.get_effects_volume());
      game_info.set_play_open_sound(false);
    }

    if (!game_info.get_is_door_opening())
    { // Espera a que la animación termine para comenzar a invocar

      // Hacemos sonar el letsgo
      if (game_info.get_play_letsgo_sound())
      {
        engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::LETS_GO_SOUND), game_info.get_effects_volume());

        // FIXME: Necesito una función para saber cuando no esta sonando nigun sonido, aunque parece no ser necesaria
        // UPDATE: Usa esta: SoundMixer::is_playing_any_sound()
        // while(engine.get_sound_mixer().is_playing_music()); //Esperamos a que termine el let's go
        game_info.set_play_letsgo_sound(false);
      }
      else if (game_info.get_play_music() && !engine.get_sound_mixer().is_playing_any_sound())
      {
        game_info.set_let_lemmings_spawn(true);
        game_info.set_play_music(false);

        // Setup music
        auto &mixer = engine.get_sound_mixer();
        int difficulty = game_info.get_difficulty();
        int level = game_info.get_level();
        std::string music_file = [&]()
        {
          using namespace Utils;
          if (level == 0)
          {
            return MUSIC_DIRECTORY + LEVEL_MUSIC[11];
          }
          else if (difficulty == DIFFICULTY_LEVEL::FUN && level == 22)
          {
            return MUSIC_DIRECTORY + SPECIAL_MUSIC[0];
          }
          else if (difficulty == DIFFICULTY_LEVEL::TRICKY && level == 14)
          {
            return MUSIC_DIRECTORY + SPECIAL_MUSIC[1];
          }
          else if (difficulty == DIFFICULTY_LEVEL::TAXING && level == 15)
          {
            return MUSIC_DIRECTORY + SPECIAL_MUSIC[2];
          }
          else if (difficulty == DIFFICULTY_LEVEL::MAYHEM && level == 22)
          {
            return MUSIC_DIRECTORY + SPECIAL_MUSIC[3];
          }
          else
          {
            return MUSIC_DIRECTORY + LEVEL_MUSIC[((30 * difficulty + level - 1) % 17)];
          }
        }();

        mixer.play_music(mixer.load_music(music_file), true, game_info.get_music_volume());
      }
    }
  }
};