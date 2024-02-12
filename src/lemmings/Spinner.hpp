#include "Structure.hpp"

class Spinner : public Structure
{
public:
  // Constructor de Flamethrower
  Spinner(Point3f position, Vector2f diagonal, Engine &engine, float animation_duration)
      : Structure(position, diagonal, engine, "assets/structure/structure", 0, 16, animation_duration, "Spinner", true /* is_loop */, false /* is_event_triggered */) {}
};
