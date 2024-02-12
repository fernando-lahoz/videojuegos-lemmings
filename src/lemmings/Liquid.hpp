#include "Structure.hpp"

class Liquid : public Structure
{
public:
  // Constructor de Liquid
  Liquid(Point3f position, Vector2f diagonal, Engine &engine, int structure_type, float animation_duration)
      : Structure(position, diagonal, engine, "assets/liquid/liquid", structure_type, 6, animation_duration, "Liquid", true /* is_loop */, false /* is_event_triggered */) {}
};
