#pragma once

#include "lemmings/structure/Structure.hpp"
#include "lemmings/structure/Antimatter_beam_trigger.hpp"

class Antimatter_beam : public Structure
{
public:
  Antimatter_beam(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(40, 30), engine, "assets/structure/structure", 28, 16, animation_duration, "Antimatter_beam", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug)
  {
    engine.get_game().create_entity(std::make_shared<Antimatter_beam_trigger>(Point3f(position.x + diagonal.x / 2 - 2, position.y + 18, position.z - 1), Vector2f(4, 6), engine, *this));
  }
};
