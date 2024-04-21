#pragma once

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"
#include "lemmings/keyboard/Keyboard_manager.hpp"

#include "lemmings/utils.hpp"

class Menu_option_button : public Rigid_body
{
private:
  Texture txt_off;
  Texture txt_on;
  bool is_pressed = false;
  uint8_t &var, desired;
  Game_info &game_info;
  Engine &engine;

public:
  Menu_option_button(Point3f position, Vector2f size, Engine &_engine, Game_info &_game_info, uint8_t& _var, uint8_t _desired)
      : Rigid_body(position, size, _engine.load_texture("assets/menu/option_button_off.png"), engine, "Menu Option Button"),
        var(_var), desired(_desired), game_info(_game_info), engine(_engine)
  {
    //std::cout << "Type: " << _type << std::endl;
    txt_on = engine.load_texture("assets/menu/option_button_on.png");
    txt_off = engine.load_texture("assets/menu/option_button_off.png");
    is_pressed = !_game_info.get_sound_effects();
    disable_collisions();
  }

  void pre_physics([[maybe_unused]]Engine &engine) override
  {
    if (var == desired)
        set_active_texture(txt_on);
    else
        set_active_texture(txt_off);
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine))
      var = desired;
      set_active_texture(txt_on);
  }

};
