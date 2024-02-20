#pragma once

#include <vector>
#include <memory>

#include "lemmings/display/Dynamic_digit_image.hpp"

class Dynamic_value_display
{
private:
  Game_info &game_info;
  Engine &engine;
  int max_digits;
  int text_type;
  float startX, startY;
  float digit_width, digit_height, paddingX;
  int (Game_info::*getValueFunction)() const;
  bool is_static_n_digits;

public:
  Dynamic_value_display(Game_info &_game_info, Engine &_engine, int _text_type, int _max_digits, float _startX, float _startY, float _digit_width, float _digit_height, float _paddingX, int (Game_info::*_getValueFunction)() const, bool _is_static_n_digits = true)
      : game_info(_game_info), engine(_engine), max_digits(_max_digits), text_type(_text_type), startX(_startX), startY(_startY), digit_width(_digit_width), digit_height(_digit_height), paddingX(_paddingX), getValueFunction(_getValueFunction), is_static_n_digits(_is_static_n_digits)
  {
    create_digit_images();
  }

  void create_digit_images()
  {
    for (int i = 0; i < max_digits; ++i)
    {
      auto position = Point3f(startX - (max_digits - 1 - i) * (digit_width + paddingX), startY, 0); // Ajusta la posición según tus necesidades
      auto digit_image = std::make_shared<Dynamic_digit_image>(
          position,
          Vector2f(digit_width, digit_height),
          game_info,
          engine,
          text_type,
          i,
          max_digits,
          getValueFunction,
          is_static_n_digits);
      engine.get_game().create_entity(digit_image);
    }
  }
};
