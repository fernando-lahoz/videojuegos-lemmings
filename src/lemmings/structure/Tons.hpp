#pragma once

#include "lemmings/structure/Structure.hpp"

class Tons : public Structure
{
public:
  // Constructor de Flamethrower
  Tons(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(62, 84), engine, "assets/structure/structure", 22, 11, animation_duration, "Tons", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug) {}
};
