#pragma once

#include "lemmings/structure/Structure.hpp"

class Chain : public Structure
{
public:
  // Constructor de Flamethrower
  Chain(Point3f position, float size, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(16 * size, 38 * size), engine, "assets/structure/structure", 2, 37, animation_duration, "Chain", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug) {}
};
