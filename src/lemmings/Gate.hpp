#pragma once

#include "Structure.hpp"

class Gate : public Structure
{
public:
  // Constructor de Gate
  Gate(Point3f position, Vector2f diagonal, Engine &engine, int structure_type, float animation_duration)
      : Structure(position, diagonal, engine, "assets/gate/gate", structure_type, 6, animation_duration, "Gate", true /* is_loop */, false /* is_event_triggered */) {}
};
