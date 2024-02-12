#include "Structure.hpp"

class Spinner : public Structure
{
public:
  // Constructor de Flamethrower
  Spinner(Point3f position, float size, Engine &engine, float animation_duration, bool is_debug = false)
      : Structure(position, Vector2f(29 * size, 19 * size), engine, "assets/structure/structure", 0, 16, animation_duration, "Spinner", true /* is_loop */, false /* is_event_triggered */, is_debug) {}
};
