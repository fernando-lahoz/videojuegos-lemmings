#pragma once

#include "Directional_structure.hpp"

class Directional_wall : public Directional_structure
{
private:
  bool going_forward = true;
  std::vector<Texture> textures;

public:
  Directional_wall(Point3f position, Vector2f diagonal, Engine &engine, int structure_type, Game_info &_game_info, bool is_debug = false)
      : Directional_structure(position, diagonal, engine, structure_type + 7, structure_type == 0 ? 4 : 5, 0.3f, "DIRECTIONAL WALL", true, _game_info, (structure_type == 1 && structure_type == 3 && structure_type == 6 && structure_type >= 8) ? 1 : -1, is_debug)
  {
    for (int i = 0; i < max_frames; i++)
    {
      textures.push_back(engine.load_texture(("assets/structure/structure_" + std::to_string(structure_type + 7) + "_" + std::to_string(i) + ".png").c_str()));
    }
  }

  void pre_physics(Engine &engine) override
  {
    if (game_info.get_level_is_paused())
      return;

    time_frame_sprite += engine.get_delta_time() * game_info.get_game_speed();
    if (time_frame_sprite >= animation_duration / max_frames)
    {
      time_frame_sprite = 0.0f;
      // Determine animation direction: forward (true) or backward (false)

      if (going_forward)
      {
        current_frame++;
        if (current_frame >= max_frames - 1)
        { // Reached the end, switch direction
          going_forward = false;
        }
      }
      else
      {
        current_frame--;
        if (current_frame <= 0)
        { // Reached the start, switch direction
          going_forward = true;
        }
      }

      // Set the new frame texture
      set_active_texture(textures[current_frame]);
    }
  }

  bool destroy_box_alpha(Engine &engine, Bound2f box, int direction)
  {
    bool res = false;
    if (is_same_direction(direction))
    {
      for (int i = 0; i < max_frames; i++)
      {
        if (textures[i].set_alpha_box(world_to_local(box), 0, engine.get_renderer()))
        {
          res = true;
        }
      }
    }
    return res;
  }
};