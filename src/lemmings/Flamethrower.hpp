#pragma once

#include "Structure.hpp"

class Flamethrower : public Structure
{
public:
  // Constructor de Flamethrower
  Flamethrower(Point3f position, Vector2f diagonal, Engine &engine, bool is_right, float animation_duration)
      : Structure(position, diagonal, engine, "assets/structure/structure", is_right ? 3 : 4, 10, animation_duration, "Flamethrower", true /* is_loop */, false /* is_event_triggered */) {}
};
