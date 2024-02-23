#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class HUD : public Rigid_body
{
private:
  bool is_hovereable;
  bool is_clickable;
  bool is_changeable;
  bool is_selectable;
  bool is_cursor;
  std::string path;
  int n;
  bool changed = false;
  Texture txt;
  Game_info &game_info;
  int option_selected = 11;
  float last_position;

public:
  HUD(Point3f position, Vector2f size, Game_info &_game_info, Engine &engine, std::string _path, int _n, bool _is_hovereable = false, bool _is_clickable = true, bool _is_changeable = false, bool _is_selectable = true)
      : Rigid_body(position, size, engine.load_texture(_path + std::to_string(_n) + ".png"), "HUD"), game_info(_game_info) //, HUDs &_huds
  {
    is_hovereable = _is_hovereable;
    is_clickable = _is_clickable;
    is_changeable = _is_changeable;
    is_selectable = _is_selectable;
    is_cursor = false;
    path = _path;
    n = _n;
    txt = engine.load_texture(_path + std::to_string(_n) + ".png");
  }

  HUD(Point3f position, Vector2f size, Game_info &_game_info, Engine &engine, std::string _path, int _n, bool _is_hovereable, bool _is_clickable, bool _is_changeable, bool _is_selectable, bool _is_cursor)
      : Rigid_body(position, size, engine.load_texture(_path + std::to_string(_n) + ".png"), "HUD"), game_info(_game_info) //, HUDs &_huds
  {
    is_hovereable = _is_hovereable;
    is_clickable = _is_clickable;
    is_changeable = _is_changeable;
    is_selectable = _is_selectable;
    is_cursor = _is_cursor;
    path = _path;
    n = _n;
    txt = engine.load_texture(_path + std::to_string(_n) + ".png");
    last_position = position.x;
  }

  void pre_physics(Engine &) override
  {
    if (is_cursor && option_selected != game_info.get_option_selected())
    {
      option_selected = game_info.get_option_selected();
      Point3f actual_position = get_position3D();
      auto new_position = Utils::positions[option_selected].x + actual_position.x - last_position;
      last_position = Utils::positions[option_selected].x;
      set_position3D(Point3f(new_position, Utils::positions[option_selected].y, 2));
    }
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine) && is_clickable)
    {
      std::cout << "PULSADO: " << n << std::endl;
      if (is_selectable)
      {
        game_info.set_option_selected(n);
      }

      if (n == Utils::HUD_ALL_EXPLODE)
      {
        game_info.set_spawn_ended();
        game_info.set_dead_marked(true);
      }
      else if (n == Utils::HUD_ADD_SPAWN_VELOCITY)
      {
        game_info.add_spawn_velocity();
      }
      else if (n == Utils::HUD_SUB_SPAWN_VELOCITY)
      {
        game_info.sub_spawn_velocity();
      }

      if (is_changeable)
      {
        if (changed)
        {
          changed = false;
          n--;
          txt = engine.load_texture(path + std::to_string(n) + ".png");
          set_active_texture(txt);
        }
        else
        {
          changed = true;
          n++;
          txt = engine.load_texture(path + std::to_string(n) + ".png");
          set_active_texture(txt);
        }
      }
    }

    if (event == EngineIO::InputEvent::MOUSE_HOVER && is_hovereable)
    {
      txt = engine.load_texture(path + std::to_string(n) + "_hover.png");
      set_active_texture(txt);
    }
  }

  void on_event_up([[maybe_unused]] Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_HOVER)
    {
      txt = engine.load_texture(path + std::to_string(n) + ".png");
      set_active_texture(txt);
    }
  }

  void on_collision(Engine &, EntityPtr) override
  {
  }
};
