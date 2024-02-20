#pragma once

#include "lemmings/structure/Structure.hpp"

class Flamethrower : public Structure
{
public:
  // Constructor de Flamethrower
  Flamethrower(Point3f position, float size, Engine &engine, bool is_right, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(69 * size, 18 * size), engine, "assets/structure/structure", is_right ? 3 : 4, 10, animation_duration, "Flamethrower", true /* is_loop */, false /* is_event_triggered */, game_info, is_debug) {}
};
