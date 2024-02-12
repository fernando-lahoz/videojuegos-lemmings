#include "Structure.hpp"

class Liquid : public Structure
{
public:
  // Constructor de Liquid
  Liquid(Point3f position, float size, Engine &engine, int structure_type, float animation_duration, bool is_debug = false)
      : Structure(position, Vector2f(64 * size, 30 * size), engine, "assets/liquid/liquid", structure_type, 6, animation_duration, "Liquid", true /* is_loop */, false /* is_event_triggered */, is_debug) {}
};
