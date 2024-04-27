#pragma once

#include "lemmings/structure/Structure.hpp"
#include "lemmings/structure/Pin_trigger.hpp"

class Pin : public Structure
{
public:
  Pin(Point3f position, Engine &engine, bool is_right, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(34, 52), engine, "assets/structure/structure", is_right ? 26 : 27, 7, animation_duration, "Pin", false /* is_loop */, true /* is_event_triggered */, game_info, is_debug)
  {
    engine.get_game().create_entity(std::make_shared<Pin_trigger>(Point3f(is_right ? position.x + diagonal.x - 8 : position.x + 2, position.y + 23, position.z - 1), Vector2f(2, 4), engine, *this));
  }
};
