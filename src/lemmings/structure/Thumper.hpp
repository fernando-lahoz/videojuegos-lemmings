#pragma once

#include "lemmings/structure/Structure.hpp"

class Thumper : public Structure
{
public:
  // Constructor de Flamethrower
  Thumper(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(64, 64), engine, "assets/structure/structure", 23, 15, animation_duration, "Thumper", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug) {}
};
