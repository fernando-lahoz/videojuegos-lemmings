#pragma once

#include "lemmings/structure/Structure.hpp"

class Bear_trap : public Structure
{
public:
  // Constructor de Flamethrower
  Bear_trap(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(32, 38), engine, "assets/structure/structure", 24, 15, animation_duration, "Bear_trap", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug) {}
};
