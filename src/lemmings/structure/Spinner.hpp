#pragma once

#include "lemmings/structure/Structure.hpp"

class Spinner : public Structure
{
public:
  // Constructor de Flamethrower
  Spinner(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(58, 38), engine, "assets/structure/structure", 0, 16, animation_duration, "Spinner", true /* is_loop */, false /* is_event_triggered */, game_info, is_debug) {}
};
