#pragma once

#include "lemmings/structure/Structure.hpp"

class Gate : public Structure
{
public:
  // Constructor de Gate
  Gate(Point3f position, Engine &engine, int structure_type, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(88, 104), engine, "assets/gate/gate", structure_type, 6, animation_duration, "Gate", true /* is_loop */, false /* is_event_triggered */, game_info, is_debug) {}
};
