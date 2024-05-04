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
  bool in_transition = false;
  float timer_rand_wait = 0.0f;

public:
  Cursor_menu(Engine &engine, Game_info &_game_info)
      : Rigid_body(Point3f(-1, -1, -30), Vector2f(64, 64), engine.load_texture("assets/cursor_menu.png"),
                   engine, "Cursor"),
        game_info(_game_info), size(64)
  {
    constructor_set_collision_type(Entity::Collision_type::CURSOR);
  }

  void update_state(Engine &engine) override
  {
    if (!game_info.get_can_do_transition() && !in_transition)
    {
      in_transition = true;
      timer_rand_wait = (Float)(rand() % 400) / 1000 + 0.2f;
    }
    if (game_info.get_can_do_transition() && in_transition)
    {
      in_transition = false;
    }
    if (timer_rand_wait > 0)
    {
      timer_rand_wait -= engine.get_delta_time();
      set_active_texture(engine.load_texture("assets/cursor_menu_wait.png"));
    }
    else
    {
      set_active_texture(engine.load_texture("assets/cursor_menu.png"));
    }

    if (game_info.get_actual_state() == Utils::STATE::MENU)
    {
      Point2f pos = engine.get_mouse_position();
      set_position3D(Point3f(pos.x, pos.y, get_position3D().z));
    }
    else
    {
      set_position3D(Point3f(0, 1000, get_position3D().z));
    }
  }
};