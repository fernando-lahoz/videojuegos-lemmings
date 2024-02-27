#pragma once

#include <string>

#include "engine/rigid_body.hpp"

#include "lemmings/Game_info.hpp"

class Text_image : public Entity
{
protected:
  std::string base_path;
  int text_type = 0;
  bool is_changeable = false;
  Game_info &game_info;

public:
  Text_image(Point3f position, Vector2f diagonal, Game_info &_game_info, Engine &engine, int text_type, std::string base_path, bool is_changeable = false)
      //: Rigid_body(position, diagonal, engine.load_texture("assets/text/text_" + std::to_string(text_type) + "_" + base_path + ".png"), "TEXT"),
        : Entity(position, diagonal, engine.load_texture("assets/text/text_" + std::to_string(text_type) + "_" + base_path + ".png"), "TEXT"),
        base_path(base_path),
        text_type(text_type),
        is_changeable(is_changeable),
        game_info(_game_info)
  {
    disable_collisions();
  }

  virtual void update_texture(Engine &) {}

  void pre_physics(Engine &engine) override
  {
    update_texture(engine);
  }

  void on_collision(Engine &, EntityPtr) override
  {
  }
};
