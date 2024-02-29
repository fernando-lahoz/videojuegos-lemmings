#pragma once

#include "engine/engine.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/Level.hpp"
#include "lemmings/menu/Menu.hpp"
#include "lemmings/screen/Transition.hpp"

class Screen_manager
{
private:
  Level level;
  Menu menu;
  std::shared_ptr<Transition> transition;

  Game_info &game_info;

  int last_lemmings_hovered = 0;

public:
  Screen_manager(Game_info &_game_info) : level(_game_info), menu(_game_info), game_info(_game_info)
  {
  }

  void go_level(Engine &engine, int _level)
  {
    game_info.set_actual_state(Utils::STATE::GAME);
    game_info.set_do_action(Utils::ACTIONS::NO_ACTION);
    level.setup_level(engine, _level);
  }

  void go_menu(Engine &engine, int type, int _level)
  {
    game_info.set_is_camera_stopped(true);
    game_info.set_actual_state(Utils::STATE::MENU);
    game_info.set_do_action(Utils::ACTIONS::NO_ACTION);
    menu.setup_menu(engine, type, _level);
  }

  void clear_screen(Engine &engine)
  {
    // engine.destroy_all_entities();
    auto &entities = engine.get_entities();
    for (auto &entity : entities)
    {
      if (entity->get_entity_name() != "Cursor")
      {
        entity->destroy();
      }
    }
  }

  void update_game(Engine &engine)
  {
    if (game_info.get_do_action() == Utils::ACTIONS::GO_MENU && game_info.get_is_transition_done())
    {
      game_info.set_is_transition_done(false);
      clear_screen(engine);
      std::cout << "GO TO MENU" << std::endl;
      engine.get_sound_mixer().pause_all_sounds(); // TODO: this should be clear_sound_mixer but do not exist yet
      go_menu(engine, game_info.get_build_menu(), game_info.get_level());
    }
    else if (game_info.get_do_action() == Utils::ACTIONS::GO_LEVEL && game_info.get_is_transition_done())
    {
      game_info.set_is_transition_done(false);
      clear_screen(engine);
      std::cout << "GO TO LEVEL" << std::endl;
      engine.get_sound_mixer().pause_all_sounds(); // TODO: this should be clear_sound_mixer but do not exist yet
      go_level(engine, game_info.get_build_level());
    }
    else if (game_info.get_do_action() == Utils::ACTIONS::NO_ACTION)
    {
      if (game_info.get_actual_state() == Utils::STATE::GAME)
      {
        int actual_lemmings_hovered = game_info.get_lemmings_hovered();

        if (actual_lemmings_hovered != last_lemmings_hovered)
        {
          // std::cout << "Lemmings hovered: " << actual_lemmings_hovered << std::endl;
          last_lemmings_hovered = actual_lemmings_hovered;
        }

        if (game_info.get_time_left() > 0.0f && !game_info.get_level_ended())
        {

          if (!game_info.get_level_is_paused())
          {
            game_info.set_time_left(game_info.get_time_left() - engine.get_delta_time() * game_info.get_game_speed());
          }
        }
        else
        {
          std::cout << "LEMMINGS OUT: " << game_info.get_n_lemmings_out() << std::endl;
          std::cout << "GAME OVER" << std::endl;
          game_info.set_do_transition(true);
          game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_OUTRO);
          game_info.set_do_action(Utils::ACTIONS::GO_MENU);
          // game_info.set_build_level(game_info.get_build_level() + 1);
          // game_info.set_do_action(Utils::ACTIONS::GO_LEVEL);
        }
      }
    }
    else
    {
      if (game_info.get_do_transition())
      {
        game_info.set_do_transition(false);
        engine.get_game().create_entity(std::make_shared<Transition>(engine, game_info, 0.5f));
      }
    }
  }
};