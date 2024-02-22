#pragma once

#include "lemmings/structure/Structure.hpp"

class Liquid : public Structure
{
public:
  // Constructor de Liquid
  Liquid(Point3f position, Engine &engine, int structure_type, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(128, 60), engine, "assets/liquid/liquid", structure_type, 6, animation_duration, "Liquid", true /* is_loop */, false /* is_event_triggered */, game_info, is_debug) {}
};
