#pragma once

#include "engine/engine.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/Level.hpp"
#include "lemmings/menu/Menu.hpp"

class Screen_manager
{
private:
  Level level;
  Menu menu;

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
    if (game_info.get_do_action() == Utils::ACTIONS::GO_MENU)
    {
      clear_screen(engine);
      std::cout << "GO TO MENU" << std::endl;
      go_menu(engine, game_info.get_build_menu(), game_info.get_level());
    }
    else if (game_info.get_do_action() == Utils::ACTIONS::GO_LEVEL)
    {
      clear_screen(engine);
      std::cout << "GO TO LEVEL" << std::endl;
      go_level(engine, game_info.get_build_level());
    }
    else // Utils::ACTIONS::NO_ACTION
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
          game_info.set_time_left(game_info.get_time_left() - engine.get_delta_time());
        }
        else
        {
          std::cout << "GAME OVER" << std::endl;
          game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_OUTRO);
          game_info.set_do_action(Utils::ACTIONS::GO_MENU);
          // game_info.set_build_level(game_info.get_build_level() + 1);
          // game_info.set_do_action(Utils::ACTIONS::GO_LEVEL);
        }

        if (game_info.update_explode_countdown(engine))
        {
          auto &entities = engine.get_entities();
          for (std::size_t i = 0; i < entities.size(); i++)
          {
            if (entities[i]->get_entity_name() == "Lemming")
            {
              std::shared_ptr<Lemming> lemming_ptr = std::dynamic_pointer_cast<Lemming>(entities[i]);
              if (lemming_ptr)
              {
                lemming_ptr->add_skill_explode_all();
              }
            }
          }
        }
      }
    }
  }
};