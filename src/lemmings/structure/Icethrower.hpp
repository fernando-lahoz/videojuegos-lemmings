#pragma once

#include "lemmings/structure/Structure.hpp"

class Icethrower : public Structure
{
public:
  // Constructor de Icethrower
  Icethrower(Point3f position, Engine &engine, bool is_right, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(128, 46), engine, "assets/structure/structure", is_right ? 5 : 6, 11, animation_duration, "Icethrower", true /* is_loop */, false /* is_event_triggered */, game_info, is_debug) {}
};
