#pragma once

#include "lemmings/structure/Structure.hpp"

class Gate : public Structure
{
private:
  std::shared_ptr<Rigid_body> hitbox;

public:
  // Constructor de Gate
  Gate(Point3f position, Engine &engine, int structure_type, float animation_duration, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(88, 104), engine, "assets/gate/gate", structure_type, 6, animation_duration, "Gate", true /* is_loop */, false /* is_event_triggered */, game_info, is_debug)
  {
    hitbox = std::make_shared<Rigid_body>(Point3f(position.x + 40, position.y + 60, position.z + 1), Vector2f(8, 44), engine.load_texture("assets/gate/gate_hitbox.png"), "Gate hitbox");
    engine.get_game().create_entity(hitbox);
  }
  ~Gate()
  {
    if (hitbox)
      hitbox->destroy();
  }
};
