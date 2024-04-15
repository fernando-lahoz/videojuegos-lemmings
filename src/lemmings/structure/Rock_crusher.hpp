#pragma once

#include "lemmings/structure/Structure.hpp"

class Rock_crusher : public Structure
{
public:
  // Constructor de Flamethrower
  Rock_crusher(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(32, 38), engine, "assets/structure/structure", 29, 17, animation_duration, "Rock_crusher", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug) {}
};
