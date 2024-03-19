#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class Menu_arrow : public Rigid_body
{
private:
  int n;
  Texture txt;
  Game_info &game_info;

public:
  Menu_arrow(Point3f position, Vector2f size, Game_info &_game_info, Engine &engine, int _n)
      : Rigid_body(position, size, engine.load_texture("assets/menu/menu_arrow_" + std::to_string(_n % 2) + ".png"), engine, "HUD"), game_info(_game_info)
  {
    n = _n;
    txt = engine.load_texture("assets/menu/menu_arrow_" + std::to_string(_n % 2) + ".png");
    disable_collisions();
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine))
    {

      if (n == 0)
      {
        game_info.add_difficulty_selected();
        // std::cout << "DIFFICULTY: " << game_info.get_difficulty_selected() << std::endl;
      }
      else if (n == 1)
      {
        game_info.sub_difficulty_selected();
        // std::cout << "DIFFICULTY: " << game_info.get_difficulty_selected() << std::endl;
      }
      else if (n == 2)
      {
        game_info.add_level_selected();
        // std::cout << "LEVEL: " << game_info.get_level_selected() << std::endl;
      }
      else if (n == 3)
      {
        game_info.sub_level_selected();
        // std::cout << "LEVEL: " << game_info.get_level_selected() << std::endl;
      }
    }

    if (event == EngineIO::InputEvent::MOUSE_HOVER)
    {
      game_info.set_is_arrow_hovered(true);
      txt = engine.load_texture("assets/menu/menu_arrow_" + std::to_string(n % 2) + "_hover.png");
      set_active_texture(txt);
    }
  }

  void on_event_up([[maybe_unused]] Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_HOVER)
    {
      game_info.set_is_arrow_hovered(false);
      txt = engine.load_texture("assets/menu/menu_arrow_" + std::to_string(n % 2) + ".png");
      set_active_texture(txt);
    }
  }
};
