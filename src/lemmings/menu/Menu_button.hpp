#pragma once

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"

#include "lemmings/utils.hpp"

class Menu_button : public Rigid_body
{
private:
  int type;
  Texture txt_off;
  Texture txt_on;
  bool is_pressed = false;
  bool is_changeable;
  Game_info &game_info;
  Engine &engine;

public:
  Menu_button(Point3f position, Vector2f size, Engine &_engine, Game_info &_game_info, int _type, bool _is_changeable = false)
      : Rigid_body(position, size, !_game_info.get_sound_effects() && _is_changeable ? _engine.load_texture("assets/menu/menu_button_" + std::to_string(_type + 1) + ".png") : _engine.load_texture("assets/menu/menu_button_" + std::to_string(_type) + ".png"), "Menu Button"),
        type(_type), game_info(_game_info), engine(_engine)
  {
    txt_on = engine.load_texture("assets/menu/menu_button_" + std::to_string(_type) + ".png");
    if (_is_changeable)
    {
      txt_off = engine.load_texture("assets/menu/menu_button_" + std::to_string(_type + 1) + ".png");
    }
    is_pressed = !_game_info.get_sound_effects();
    is_changeable = _is_changeable;
  }

  void button_handler(int button_type)
  {
    if (button_type == Utils::PLAYER_SOLO)
    {
      game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_INTRO, 8);
      game_info.set_do_action(Utils::ACTIONS::GO_MENU);
    }
    else if (button_type == Utils::PLAYER_VS_IA)
    {
      game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_INTRO, 0);
      game_info.set_do_action(Utils::ACTIONS::GO_MENU);
    }
    else if (button_type == Utils::SOUND_EFFECTS)
    {
      game_info.set_sound_effects(!game_info.get_sound_effects());
    }
    else if (button_type == Utils::EXIT)
    {
      engine.quit();
    }
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine))
    {
      button_handler(type);
      if (is_changeable)
      {
        if (is_pressed)
        {
          set_active_texture(txt_on);
          is_pressed = false;
        }
        else
        {
          set_active_texture(txt_off);
          is_pressed = true;
        }
      }
    }
  }
};
