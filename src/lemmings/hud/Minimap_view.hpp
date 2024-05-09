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
  Point2f last_position;
  float calculated_position;

  Float last_mouse_position;
  bool holded = false;

  Float last_zoom = 1.0f;

  Vector2f original_diagonal;
  
  bool is_mouse_over_minimap(Engine &engine)
  {
    return Bound2f(Point2f(416, 356), Point2f(616, 396)).contains(engine.get_main_camera().world_to_screen(engine.get_mouse_position()));
  }

  void update_diagonal([[maybe_unused]]Engine &engine)
  {
    Dynamic_camera *cam = (Dynamic_camera*)&game_info.get_dynamic_camera();
    auto map = game_info.get_map_ptr();
    //auto cam_pos = map->world_to_local(cam->get_world_frame());
    Float zoom = cam->get_zoom();

    if (last_zoom != zoom)
    {
      int offset = 13;

      auto pos = get_position2D();
      pos.x -= offset * (last_zoom-1);
      pos.x += offset * (zoom-1);

      set_position2D(pos);
    }

    set_diagonal(Vector2f(original_diagonal.x / zoom, original_diagonal.y / zoom));
  }

  Point2f build_last_position(Float p)
  {
    return Point2f (p, 0);
  }

public:
  Minimap_view(Point3f position, Vector2f size, Game_info &_game_info, Engine &engine, float _last_position)
      : Entity(position, size, engine.load_texture("assets/hud/hud_minimap_view.png"), engine, "HUD"), game_info(_game_info), last_position(build_last_position(_last_position))
  {
    alpha_mouse = false;
    original_diagonal = size;
  }

  void pre_physics(Engine &engine) override
  {
    Dynamic_camera *cam = (Dynamic_camera*)&game_info.get_dynamic_camera();

    if (holded && cam->get_zoom() == 1.0f)
    {
      if (is_mouse_over_minimap(engine))
      {
        const Float new_mouse_position = engine.get_mouse_position().x;
        const Float d = new_mouse_position - last_mouse_position;
        last_mouse_position = new_mouse_position;

        auto cam = game_info.get_dynamic_camera();
        auto map = game_info.get_map_ptr();

        auto [x, y] = get_position2D();
        x = math::clamp(x + d, (Float)10412, (Float)10572);
        set_position2D(Point2f(x, y));

        Bound2f& world_frame = game_info.get_dynamic_camera().get_world_frame();
        world_frame.pMin.x = ((x - 10412.0f) / 160.0f) * 2528.0f;
        world_frame.pMax.x = world_frame.pMin.x + 640.0f;

        last_position.x = world_frame.pMin.x + 320.0f;

        auto cam_pos = map->world_to_local(cam.get_world_frame());
        last_position.y = cam_pos.pMin.y * 40.0f;

        game_info.set_pos_camera(last_position);
      }
      else
      {
        holded = false;
      }
    }
    else
    {
      auto cam = game_info.get_dynamic_camera();
      auto map = game_info.get_map_ptr();
      auto cam_pos = map->world_to_local(cam.get_world_frame());
      
      last_position.x = cam.get_world_frame().centroid().x;
      calculated_position = 10412.0f + ((last_position.x - 320.0f) / 2528.0f) * 160.0f;

      last_position.y = cam_pos.pMin.y * 40.0f;

      set_position2D(Point2f(calculated_position, -148 + last_position.y));
    }

    update_diagonal(engine);
  }

  void on_event_down([[maybe_unused]]Engine &engine, EngineIO::InputEvent event) override
  {
    Dynamic_camera *cam = (Dynamic_camera*)&game_info.get_dynamic_camera();

    if (event == EngineIO::InputEvent::MOUSE_LEFT 
        && is_mouse_over_minimap(engine)
        && cam->get_zoom() == 1.0f)
    {
      holded = true;

      last_mouse_position = engine.get_mouse_position().x;

      auto [x, y] = get_position2D();
      x = math::clamp(last_mouse_position - 24, (Float)10412, (Float)10572);
      set_position2D(Point2f(x, y));

      auto cam = game_info.get_dynamic_camera();
      auto map = game_info.get_map_ptr();

      Bound2f& world_frame = game_info.get_dynamic_camera().get_world_frame();
      world_frame.pMin.x = ((x - 10412.0f) / 160.0f) * 2528.0f;
      world_frame.pMax.x = world_frame.pMin.x + 640.0f;

      last_position.x = world_frame.pMin.x + 320.0f;

      auto cam_pos = map->world_to_local(cam.get_world_frame());
      last_position.y = cam_pos.pMin.y * 40.0f;


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