#pragma once

#include "lemmings/structure/Structure.hpp"

class Antimatter_beam : public Structure
{
public:
  // Constructor de Flamethrower
  Antimatter_beam(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(40, 30), engine, "assets/structure/structure", 28, 16, animation_duration, "Antimatter_beam", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug) {}
};
