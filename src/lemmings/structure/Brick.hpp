#pragma once

#include "Directional_structure.hpp"

class Brick : public Directional_structure
{
private:
  int bricks = 1;

public:
  Brick(Point3f position, Engine &engine, Game_info &_game_info, int _direction, bool is_debug = false)
      : Directional_structure(position, Vector2f(56, 24), engine, Utils::LEVEL_BRICKS_TYPE[_game_info.get_difficulty_selected()][_game_info.get_level_selected()] + 18, 12, 0.0f, "BRICKS", false, _game_info, _direction, is_debug)
  {
    std::string frame_path = "assets/structure/structure_" + std::to_string(structure_type) + "_" + std::to_string(direc) + "_0.png";
    Texture txt = engine.load_texture(frame_path.c_str());
    set_active_texture(txt);
  }

  bool add_brick(Engine &engine)
  {
    bool res = true;
    if (bricks >= 11)
      res = false;
    std::string frame_path = "assets/structure/structure_" + std::to_string(structure_type) + "_" + std::to_string(direc) + "_" + std::to_string(bricks) + ".png";
    bricks++;
    Texture txt = engine.load_texture(frame_path.c_str());
    set_active_texture(txt);
    return res;
  }

  bool check_bricks()
  {
    return !(bricks >= 11);
  }

  void pre_physics(Engine &) override
  {
  }
};