#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/entity.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class Minimap_view : public Entity
{
private:
  Game_info &game_info;
  float last_position;
  float calculated_position;

public:
  Minimap_view(Point3f position, Vector2f size, Game_info &_game_info, Engine &engine, float _last_position)
      : Entity(position, size, engine.load_texture("assets/hud/hud_minimap_view.png"), "HUD"), game_info(_game_info), last_position(_last_position)
  {
  }

  void pre_physics(Engine &) override
  {
    if (last_position != game_info.get_pos_camera())
    {
      last_position = game_info.get_pos_camera();
      calculated_position = 412.0f + ((last_position - 320.0f) / 2528.0f) * 160.0f;
      set_position2D(Point2f(calculated_position, -148));
    }
  }
};