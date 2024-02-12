#pragma once

#include "Structure.hpp"

class Fire : public Structure
{
public:
  // Constructor de Fire
  Fire(Point3f position, Vector2f diagonal, Engine &engine, float animation_duration)
      : Structure(position, diagonal, engine, "assets/structure/structure", 1, 8, animation_duration, "Fire", true /* is_loop */, false /* is_event_triggered */) {}
};
