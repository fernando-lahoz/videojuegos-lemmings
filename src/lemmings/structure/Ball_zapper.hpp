#pragma once

#include "lemmings/structure/Structure.hpp"

class Ball_zapper : public Structure
{
public:
  // Constructor de Flamethrower
  Ball_zapper(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(32, 142), engine, "assets/structure/structure", 25, 8, animation_duration, "Ball_zapper", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug) {}
};
