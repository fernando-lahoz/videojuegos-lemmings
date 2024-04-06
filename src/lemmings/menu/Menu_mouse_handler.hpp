#pragma once

#include "engine/entity.hpp"
#include "engine/engine.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class Menu_mouse_handler : public Entity
{
private:
  Game_info &game_info;
  int menu_type;

public:
  Menu_mouse_handler(Point3f position, Vector2f diagonal, Engine &_engine, Game_info &_game_info, int _menu_type)
      : Entity(position, diagonal,
               _engine.load_texture("assets/menu/transparent.png"),
               _engine,
               "Menu Handler", "Menu Handler"),
        game_info(_game_info),
        menu_type(_menu_type)
  {
    disable_collisions();
  }
  void on_event_down(Engine &, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT)
    {
      // std::cout << "MENU HANDLER: Left mouse pressed" << std::endl;
      if (menu_type == Utils::MENU_TYPE::TITLE)
      {
        return;
      }
      if (menu_type == Utils::MENU_TYPE::LEVEL_INTRO)
      {
        game_info.set_do_transition(true);
        game_info.set_build_level(game_info.get_level());
        game_info.set_build_difficulty(game_info.get_difficulty());
        game_info.set_do_action(Utils::ACTIONS::GO_LEVEL);
        return;
      }
      if (menu_type == Utils::MENU_TYPE::LEVEL_OUTRO)
      {
        int rescued = game_info.get_percen_lemmings_in();
        int needed = Utils::LEVEL_SAVE_LEMMINGS[game_info.get_difficulty()][game_info.get_level()] * 100 / Utils::LEVEL_N_LEMMINGS[game_info.get_difficulty()][game_info.get_level()];

        if (rescued < needed)
        {
          game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_INTRO, game_info.get_level(), game_info.get_difficulty());
        }
        else
        {
          game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_INTRO, game_info.get_level() + 1, game_info.get_difficulty());
        }

        game_info.set_do_transition(true);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        return;
      }
      if (menu_type == Utils::MENU_TYPE::LEVEL_SELECTOR && !game_info.get_is_arrow_hovered())
      {
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_INTRO, game_info.get_level_selected(), game_info.get_difficulty_selected());
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        return;
      }
      if (menu_type == Utils::MENU_TYPE::INTRO)
      {
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::TITLE, 0, 0);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        return;
      }
    }

    if (event == EngineIO::InputEvent::MOUSE_RIGHT)
    {
      // std::cout << "MENU HANDLER: Right mouse pressed" << std::endl;
      if (menu_type == Utils::MENU_TYPE::TITLE)
      {
        /* code */
        return;
      }
      if (menu_type == Utils::MENU_TYPE::LEVEL_INTRO)
      {
        game_info.set_do_transition(true);
        game_info.set_build_level(game_info.get_level());
        game_info.set_build_difficulty(game_info.get_difficulty());
        game_info.set_do_action(Utils::ACTIONS::GO_LEVEL);
        return;
      }
      if (menu_type == Utils::MENU_TYPE::LEVEL_OUTRO)
      {
        int rescued = game_info.get_percen_lemmings_in();
        int needed = Utils::LEVEL_SAVE_LEMMINGS[game_info.get_difficulty()][game_info.get_level()] * 100 / Utils::LEVEL_N_LEMMINGS[game_info.get_difficulty()][game_info.get_level()];

        if (rescued < needed)
        {
          game_info.set_build_menu(Utils::MENU_TYPE::TITLE);
        }
        else
        {
          game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_INTRO, game_info.get_level() + 1, game_info.get_difficulty());
        }
        game_info.set_do_transition(true);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        return;
      }
      if (menu_type == Utils::MENU_TYPE::LEVEL_SELECTOR)
      {
        game_info.set_build_menu(Utils::MENU_TYPE::TITLE);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        game_info.set_do_transition(true);
        return;
      }
      if (menu_type == Utils::MENU_TYPE::INTRO)
      {
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::TITLE, 0, 0);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        return;
      }
      if (menu_type == Utils::MENU_TYPE::CONFIG)
      {
        game_info.set_build_menu(Utils::MENU_TYPE::TITLE);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        game_info.set_do_transition(true);
        game_info.set_is_buton_conf(false);//No hay boton seleccionado en menu configuración
        return;
      }

    }
  }
};