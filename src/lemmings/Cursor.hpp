#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"
#include "Level_info.hpp"
#include "utils.hpp"

class Cursor : public Rigid_body

{
private:
  bool state = false;
  Level_info &level_info;
  float size;

public:
  Cursor(Engine &engine, Level_info &_level_info, float _size) : Rigid_body(Point3f(-1, -1, 0), Vector2f(_size, _size), engine.load_texture("assets/cursor.png"), "Cursor"), level_info(_level_info), size(_size) {}

  void update_position(Engine &engine) override
  {
    Point2f pos = engine.get_mouse_position();
    set_position3D(Point3f(pos.x - size / 2, pos.y - size / 2, 0));
    if (level_info.get_is_cursor_hover() != state)
    {
      state = !state;
      set_active_texture(level_info.get_cursor_txt());
    }
  }
};