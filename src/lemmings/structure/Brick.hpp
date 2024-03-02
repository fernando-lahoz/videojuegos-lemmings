#pragma once

#include "Directional_structure.hpp"

class Brick : public Directional_structure
{
private:
  int bricks = 1;

public:
  Brick(Point3f position, Vector2f diagonal, Engine &engine, const std::string &name, Game_info &_game_info, int _direction, bool is_debug = false)
      : Directional_structure(position, diagonal, engine, Utils::LEVEL_BRICKS_TYPE[_game_info.get_difficulty_selected()][_game_info.get_level_selected()] + 13, 12, 0.0f, name, false, _game_info, _direction, is_debug)
  {
  }

  bool add_brick(Engine &engine)
  {
    if (bricks >= 12)
      return false;
    std::string frame_path = "assets/structure/structure_" + std::to_string(structure_type) + "_" + std::to_string(bricks) + ".png";
    bricks++;
    Texture txt = engine.load_texture(frame_path.c_str());
    set_active_texture(txt);
    return true;
  }

  void pre_physics(Engine &) override
  {
  }
};