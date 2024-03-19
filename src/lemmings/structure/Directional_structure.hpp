#pragma once

#include "Structure.hpp"

class Directional_structure : public Structure
{
protected:
  int direc; // -1 for left, +1 for right

public:
  // Directional_structure constructor with direction initialization
  Directional_structure(Point3f position, Vector2f diagonal, Engine &engine, int structure_type, int max_frames, float animation_duration, const std::string &name, bool is_loop, Game_info &_game_info, int _direction, bool is_debug = false)
      : Structure(position, diagonal, engine, "assets/structure/structure", structure_type, max_frames, animation_duration, name, is_loop, false, _game_info, is_debug), direc(_direction)
  {
    if (animation_duration == -1)
    {
      is_playing = false;
    }
  }

  // Method to check if the passed direction is the same as the structure's
  bool is_same_direction(int dir) const
  {
    return direc == dir || dir == 0;
  }

  // Getter for direction
  int get_direction() const
  {
    return direc;
  }

  // Setter for direction
  void set_direction(int dir)
  {
    direc = dir;
  }
};
