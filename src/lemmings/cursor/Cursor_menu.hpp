#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class Cursor_menu : public Rigid_body

{
private:
  bool state = false;
  Game_info &game_info;
  float size;

public:
  Cursor_menu(Engine &engine, Game_info &_game_info, float _size)
      : Rigid_body(Point3f(-1, -1, -30), Vector2f(_size, _size * 1.04166666666), engine.load_texture("assets/cursor_menu.png"), 
        engine, "Cursor"), game_info(_game_info), size(_size) {}

  void update_state(Engine &engine) override
  {
    if (game_info.get_actual_state() == Utils::STATE::MENU)
    {
      Point2f pos = engine.get_mouse_position();
      set_position3D(Point3f(pos.x, pos.y, -30));
    }
    else
    {
      set_position3D(Point3f(0, 1000, -30));
    }
  }
};