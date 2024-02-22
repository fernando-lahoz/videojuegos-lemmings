#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class Cursor : public Rigid_body

{
private:
  bool state = false;
  Game_info &game_info;
  float size;

public:
  Cursor(Engine &engine, Game_info &_game_info, float _size) : Rigid_body(Point3f(-1, -1, 0), Vector2f(_size, _size), engine.load_texture("assets/cursor.png"), "Cursor"), game_info(_game_info), size(_size) {}

  void update_position(Engine &engine) override
  {
    if (game_info.get_actual_state() == Utils::STATE::GAME)
    {
      Point2f pos = engine.get_mouse_position();
      set_position3D(Point3f(pos.x - size / 2, pos.y - size / 2, 0));
    }
    else
    {
      set_position3D(Point3f(0, 1000, 0));
    }

    if (game_info.get_is_cursor_hover() != state)
    {
      state = !state;
      set_active_texture(game_info.get_cursor_txt());
    }
  }
};