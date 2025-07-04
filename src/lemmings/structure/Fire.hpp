#pragma once

#include "lemmings/structure/Structure.hpp"

class Fire : public Structure
{
public:
  // Constructor de Fire
  Fire(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(64, 34), engine, "assets/structure/structure", 1, 8, animation_duration, "Fire", true /* is_loop */, false /* is_event_triggered */, game_info, is_debug) {}
};
