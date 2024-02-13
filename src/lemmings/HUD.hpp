#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"

class HUD : public Rigid_body
{
private:
  bool is_hovereable;
  bool is_clickable;
  bool is_changeable;
  std::string path;
  int n;
  bool changed = false;
  Texture txt;

public:
  HUD(Point3f position, Vector2f size, Engine &engine, std::string _path, int _n, bool _is_hovereable = false, bool _is_clickable = true, bool _is_changeable = false)
      : Rigid_body(position, size, engine.load_texture(_path + std::to_string(_n) + ".png"), "HUD")
  {
    is_hovereable = _is_hovereable;
    is_clickable = _is_clickable;
    is_changeable = _is_changeable;
    path = _path;
    n = _n;
    txt = engine.load_texture(_path + std::to_string(_n) + ".png");
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine) && is_clickable)
    {
      std::cout << "PULSADO: " << n << std::endl;
      if (is_changeable)
      {
        if (changed)
        {
          changed = false;
          n--;
          txt = engine.load_texture(path + std::to_string(n) + ".png");
          set_active_texture(txt);
        }
        else
        {
          changed = true;
          n++;
          txt = engine.load_texture(path + std::to_string(n) + ".png");
          set_active_texture(txt);
        }
      }
    }

    if (event == EngineIO::InputEvent::MOUSE_HOVER && is_hovereable)
    {
      txt = engine.load_texture(path + std::to_string(n) + "_hover.png");
      set_active_texture(txt);
    }
  }

  void on_event_up([[maybe_unused]] Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_HOVER)
    {
      txt = engine.load_texture(path + std::to_string(n) + ".png");
      set_active_texture(txt);
    }
  }

  void update_position(Engine &engine) override
  {
    auto speed = get_speed();

    if (engine.is_a_down())
    {
      speed.x = -0.2;
    }

    if (engine.is_d_down())
    {
      speed.x = 0.2;
    }

    if (engine.is_a_down() && engine.is_d_down())
    {
      speed.x = 0;
    }

    if (!engine.is_a_down() && !engine.is_d_down())
    {
      speed.x = 0;
    }

    set_speed(speed);
    Rigid_body::update_position(engine);
  }

  void on_collision(Engine &, EntityPtr) override
  {
  }
};
