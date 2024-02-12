#pragma once

#include "Structure.hpp"

class Chain : public Structure
{
public:
  // Constructor de Flamethrower
  Chain(Point3f position, Vector2f diagonal, Engine &engine, float animation_duration)
      : Structure(position, diagonal, engine, "assets/structure/structure", 2, 37, animation_duration, "Chain", false /* is_loop */, true /* is_event_triggered */) {}
};
