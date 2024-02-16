#pragma once

#include "engine/Rigid_body.hpp"
#include <string>

#include "Level_info.hpp"

class Text_image : public Rigid_body
{
protected:
  std::string base_path;
  int text_type = 0;
  bool is_changeable = false;
  Level_info &level_info;

public:
  Text_image(Point3f position, Vector2f diagonal, Level_info &_level_info, Engine &engine, int text_type, std::string base_path, bool is_changeable = false)
      : Rigid_body(position, diagonal, engine.load_texture("assets/text/text_" + std::to_string(text_type) + "_" + base_path + ".png"), "TEXT"),
        base_path(base_path),
        text_type(text_type),
        is_changeable(is_changeable),
        level_info(_level_info)
  {
  }

  virtual void update_texture(Engine &) {}

  void pre_physics(Engine &engine) override
  {
    update_texture(engine);
  }

  void update_position(Engine &engine) override
  {
    auto speed = get_speed();

    if (engine.is_a_down())
    {
      speed.x = -0.2;
    }

    if (engine.is_d_down())
    {
      speed.x = 0.2;
    }

    if (engine.is_a_down() && engine.is_d_down())
    {
      speed.x = 0;
    }

    if (!engine.is_a_down() && !engine.is_d_down())
    {
      speed.x = 0;
    }

    set_speed(speed);
    Rigid_body::update_position(engine);
  }

  void on_collision(Engine &, EntityPtr) override
  {
  }
};
