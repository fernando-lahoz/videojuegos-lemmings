#pragma once

#include <string>

#include "engine/fixed_text.hpp"

#include "lemmings/Game_info.hpp"

class Text_displayer : public FixedText
{
protected:
  std::string justified;
  bool is_button = false;
  Game_info &game_info;

public:
  Text_displayer(Point3f position, Vector2f letter_size, Game_info &_game_info, std::string _justified, const Texture &font_texture,
                 Vector2i texture_letter_size, MappingFunction map,
                 std::string_view text, std::string_view _class_name, bool _is_button = false)
      : FixedText(_justified == "center" ? Point3f(position.x - letter_size.x * text.size() / 2, position.y - letter_size.y / 2, position.z) : position, letter_size, font_texture, texture_letter_size, map, text, _class_name),
        justified(_justified),
        is_button(_is_button),
        game_info(_game_info)
  {
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine) && is_button)
    {
      std::cout << "BUTTON TEXT PRESSED\n";
    }
  }
};
