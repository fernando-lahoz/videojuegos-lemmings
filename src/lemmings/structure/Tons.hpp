#pragma once

#include "lemmings/structure/Structure.hpp"
#include "lemmings/structure/Tons_trigger.hpp"

class Tons : public Structure
{
public:
  Tons(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(62, 84), engine, "assets/structure/structure", 22, 11, animation_duration, "Tons", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug)
  {
    engine.get_game().create_entity(std::make_shared<Tons_trigger>(Point3f(position.x + diagonal.x / 2 - 2, position.y + 70, position.z - 1), Vector2f(4, 14), engine, *this));
  }
};
