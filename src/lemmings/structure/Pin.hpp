#pragma once

#include "lemmings/structure/Structure.hpp"

class Pin : public Structure
{
public:
  // Constructor de Flamethrower
  Pin(Point3f position, Engine &engine, bool is_right, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(34, 52), engine, "assets/structure/structure", is_right ? 26 : 27, 7, animation_duration, "Pin", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug) {}
};
