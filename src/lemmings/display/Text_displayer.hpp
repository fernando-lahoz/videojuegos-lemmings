#pragma once

#include <string>

#include "engine/fixed_text.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class Text_displayer : public FixedText
{
protected:
  std::string justified;
  Game_info &game_info;

public:
  Text_displayer(Point3f position, Vector2f letter_size, Game_info &_game_info, std::string _justified, const Texture &font_texture,
                 Vector2i texture_letter_size, MappingFunction map,
                 std::string_view text, Engine &engine, std::string_view _class_name)
      : FixedText(_justified == "center" ? Point3f(position.x - letter_size.x * text.size() / 2, position.y - letter_size.y / 2, position.z)
                 :_justified == "right"  ? Point3f(position.x - letter_size.x * text.size(), position.y - letter_size.y / 2, position.z)
                                         : position, letter_size, font_texture, texture_letter_size, map, text, engine, _class_name),
        justified(_justified),
        game_info(_game_info)
  {
    disable_collisions();
  }
};
