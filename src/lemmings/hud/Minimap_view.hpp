#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/entity.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class Minimap_view : public Entity
{
private:
  Game_info &game_info;
  float last_position;
  float calculated_position;

  Float last_mouse_position;
  bool holded = false;
  

public:
  Minimap_view(Point3f position, Vector2f size, Game_info &_game_info, Engine &engine, float _last_position)
      : Entity(position, size, engine.load_texture("assets/hud/hud_minimap_view.png"), engine, "HUD"), game_info(_game_info), last_position(_last_position)
  {
    alpha_mouse = false;
  }

  void pre_physics(Engine &engine) override
  {
    if (holded)
    {
      if (engine.is_entity_hovered(*this))
      {
        const Float new_mouse_position = engine.get_mouse_position().x;
        const Float d = new_mouse_position - last_mouse_position;
        last_mouse_position = new_mouse_position;

        auto [x, y] = get_position2D();
        x = math::clamp(x + d, (Float)10412, (Float)10572);
        set_position2D(Point2f(x, y));

        Camera2D& cam = game_info.get_dynamic_camera();
        Bound2f& world_frame = cam.get_world_frame();
        //const Float diff = world_frame.pMin.x - world_frame.pMax.x;
        world_frame.pMin.x = ((x - 10412.0f) / 160.0f) * 2528.0f;
        world_frame.pMax.x = world_frame.pMin.x + 640.0f;

        last_position = world_frame.pMin.x + 320.0f;
        game_info.set_pos_camera(last_position);
      }
      else
      {
        holded = false;
        std::printf("ADIOS\n");
      }
    }
    
    if (!holded && last_position != game_info.get_pos_camera())
    {
      last_position = game_info.get_pos_camera();
      calculated_position = 10412.0f + ((last_position - 320.0f) / 2528.0f) * 160.0f;
      set_position2D(Point2f(calculated_position, -148));

      std::printf("position: %f \n", calculated_position);
    }
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && engine.is_entity_hovered(*this)) {
      holded = true;

      last_mouse_position = engine.get_mouse_position().x;

      std::printf("HOLAA\n");
    }
  }

  void on_event_up(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && holded) {
      holded = false;

      std::printf("ADIOS\n");
    }
  }
};