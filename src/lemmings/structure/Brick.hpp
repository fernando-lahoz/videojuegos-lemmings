#pragma once

#include "Directional_structure.hpp"

class Brick : public Directional_structure
{
private:
  int bricks = 1;
  std::vector<Texture> textures;

public:
  Brick(Point3f position, Engine &engine, Game_info &_game_info, int _direction, bool is_debug = false)
      : Directional_structure(position, Vector2f(56, 24.5), engine, Utils::LEVEL_BRICKS_TYPE[_game_info.get_difficulty_selected()][_game_info.get_level_selected()] + 18, 12, 0.0f, "BRICKS", false, _game_info, _direction, is_debug)
  {
    std::string frame_path = "assets/structure/structure_" + std::to_string(structure_type) + "_" + std::to_string(direc) + "_0.png";
    Texture txt = engine.load_texture(frame_path.c_str());
    set_active_texture(txt);

    for (int i = 1; i < 12; i++)
    {
      textures.push_back(engine.load_texture(("assets/structure/structure_" + std::to_string(structure_type) + "_" + std::to_string(direc) + "_" + std::to_string(i) + ".png").c_str()));
    }
  }

  bool add_brick(Engine &engine)
  {
    bool res = true;
    if (bricks >= 12)
      res = false;
    if (bricks >= 9)
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::TING_SOUND), game_info.get_effects_volume());

    set_active_texture(textures[bricks - 1]);
    bricks++;
    return res;
  }

  bool check_bricks()
  {
    return !(bricks >= 12);
  }

  void pre_physics(Engine &) override
  {
  }

  bool destroy_box_alpha(Engine &engine, Bound2f box, int direction)
  {
    bool destroy = false;
    if (is_same_direction(direction))
    {
      float fraction = (12.0f - bricks) / 12.0f;
      float affectedHeight = diagonal.y * fraction;
      Bound2f affectedBox = box;
      affectedBox.pMin.y = position.y + affectedHeight;

      for (int i = 0; i < max_frames; i++)
      {
        if (textures[i].set_alpha_box(world_to_local(affectedBox), 0, engine.get_renderer()))
          destroy = true;
      }
      if (destroy)
        set_active_texture(textures[bricks - 2]);
    }
    return destroy;
  }
};