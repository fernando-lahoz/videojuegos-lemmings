#pragma once

#include "lemmings/structure/Structure.hpp"
#include "lemmings/utils.hpp"

class Liquid : public Structure
{
public:
  // Constructor de Liquid
  Liquid(Point3f position, float size, Engine &engine, int structure_type, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(128.5 * size, 60 * size), engine, "assets/liquid/liquid", structure_type, Utils::LIQUID_N_FRAMES[structure_type], animation_duration, "Liquid", true /* is_loop */, false /* is_event_triggered */, game_info, is_debug) {}
};
