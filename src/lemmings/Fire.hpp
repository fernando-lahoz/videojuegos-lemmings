#include "Structure.hpp"

class Fire : public Structure
{
public:
  // Constructor de Fire
  Fire(Point3f position, Vector2f diagonal, Engine &engine, float animation_duration)
      : Structure(position, diagonal, engine, "assets/structure/structure", 1, 8, animation_duration, "Liquid", true /* is_loop */, false /* is_event_triggered */) {}

  void pre_physics(Engine &engine) override
  {
    // Dado que la animación está en bucle y no depende de eventos,
    // simplemente actualizamos la animación en cada llamada a pre_physics.
    Structure::update_animation(engine);
  }

  // No necesitamos implementar trigger_event_animation ya que la animación siempre está en bucle y no es disparada por eventos.
};
