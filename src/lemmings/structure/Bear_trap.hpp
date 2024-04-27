#pragma once

#include "lemmings/structure/Structure.hpp"
#include "lemmings/structure/Bear_trap_trigger.hpp"

class Bear_trap : public Structure
{
public:
  // Constructor de Flamethrower
  Bear_trap(Point3f position, Engine &engine, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(32, 38), engine, "assets/structure/structure", 24, 15, animation_duration, "Bear_trap", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug)
  {
    engine.get_game().create_entity(std::make_shared<Bear_trap_trigger>(Point3f(position.x + diagonal.x / 2 - 2, position.y + 32, position.z - 1), Vector2f(4, 6), engine, *this));
  }
};
