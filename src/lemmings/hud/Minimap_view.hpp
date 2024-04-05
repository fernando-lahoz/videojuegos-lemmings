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
  
  bool is_mouse_over_minimap(Engine &engine)
  {
    return Bound2f(Point2f(416, 356), Point2f(616, 396)).contains(engine.get_main_camera().world_to_screen(engine.get_mouse_position()));
  }

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
      if (is_mouse_over_minimap(engine))
      {
        const Float new_mouse_position = engine.get_mouse_position().x;
        const Float d = new_mouse_position - last_mouse_position;
        last_mouse_position = new_mouse_position;

        auto [x, y] = get_position2D();
        x = math::clamp(x + d, (Float)10412, (Float)10572);
        set_position2D(Point2f(x, y));

        Bound2f& world_frame = game_info.get_dynamic_camera().get_world_frame();
        world_frame.pMin.x = ((x - 10412.0f) / 160.0f) * 2528.0f;
        world_frame.pMax.x = world_frame.pMin.x + 640.0f;

        last_position = world_frame.pMin.x + 320.0f;
        game_info.set_pos_camera(last_position);
      }
      else
      {
        holded = false;
      }
    }
    
    if (!holded && last_position != game_info.get_pos_camera())
    {
      last_position = game_info.get_pos_camera();
      calculated_position = 10412.0f + ((last_position - 320.0f) / 2528.0f) * 160.0f;
      set_position2D(Point2f(calculated_position, -148));
    }
  }

  void on_event_down([[maybe_unused]]Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && is_mouse_over_minimap(engine))
    {
      holded = true;

      last_mouse_position = engine.get_mouse_position().x;

      auto [x, y] = get_position2D();
      x = math::clamp(last_mouse_position - 24, (Float)10412, (Float)10572);
      set_position2D(Point2f(x, y));

      Bound2f& world_frame = game_info.get_dynamic_camera().get_world_frame();
      world_frame.pMin.x = ((x - 10412.0f) / 160.0f) * 2528.0f;
      world_frame.pMax.x = world_frame.pMin.x + 640.0f;

      last_position = world_frame.pMin.x + 320.0f;
      game_info.set_pos_camera(last_position);
    }
  }

  void on_event_up(Engine&, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && holded) {
      holded = false;
    }
  }
};