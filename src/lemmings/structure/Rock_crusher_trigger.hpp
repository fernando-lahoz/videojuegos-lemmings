#pragma once

#include "engine/trigger.hpp"

class Rock_crusher_trigger : public Trigger
{
  bool change = false;
  bool init = false;
  bool is_debug = false;

public:
  Structure &trap;

  Rock_crusher_trigger(Point3f position, Vector2f diagonal, Engine &engine, Structure &_trap, bool debug = false) : Trigger(position, diagonal, engine, "ROCK CRUSHER TRIGGER"), trap(_trap)
  {
    init = !debug;
    is_debug = debug;
  }

  void update_state(Engine &engine) override
  {
    if (!is_debug)
      return;
    if (!init)
    {
      init = true;
      set_active_texture(engine.load_texture("assets/menu/background_brown.png"));
    }

    if (engine.is_up_arrow_down())
    {
      position.y -= 1;
      change = true;
    }

    if (engine.is_down_arrow_down())
    {
      position.y += 1;
      change = true;
    }

    if (engine.is_left_arrow_down())
    {
      position.x -= 1;
      change = true;
    }

    if (engine.is_right_arrow_down())
    {
      position.x += 1;
      change = true;
    }

    if (engine.is_s_down())
    {
      diagonal.y += 1;
      change = true;
    }

    if (engine.is_w_down())
    {
      diagonal.y -= 1;
      change = true;
    }

    if (engine.is_a_down())
    {
      diagonal.x -= 1;
      change = true;
    }

    if (engine.is_d_down())
    {
      diagonal.x += 1;
      change = true;
    }

    Trigger::update_state(engine);
  }

  void post_physics(Engine &) override
  {
    if (change)
    {
      // std::cout << "Position = " << get_position2D() << std::endl;
      // std::cout << "Size = " << get_diagonal() << std::endl;
      change = false;
    }
  }
};
