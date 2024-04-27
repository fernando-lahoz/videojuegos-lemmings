#pragma once

#include "lemmings/structure/Structure.hpp"
#include "lemmings/structure/Rock_crusher_trigger.hpp"

class Rock_crusher : public Structure
{
public:
  // Constructor de Flamethrower
  Rock_crusher(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(32, 74), engine, "assets/structure/structure", 29, 17, animation_duration, "Rock_crusher", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug)
  {
    engine.get_game().create_entity(std::make_shared<Rock_crusher_trigger>(Point3f(position.x + diagonal.x / 2 - 2, position.y + 68, position.z - 1), Vector2f(3, 14), engine, *this));
  }
};
