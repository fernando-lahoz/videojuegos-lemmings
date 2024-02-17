#pragma once

#include <vector>
#include <memory>
#include "Dynamic_digit_image.hpp" // Asegúrate de incluir la ubicación correcta de este archivo

class Dynamic_value_display
{
private:
  std::vector<std::shared_ptr<Dynamic_digit_image>> digit_images;
  Level_info &level_info;
  Engine &engine;
  int max_digits;
  int text_type;
  float startX, startY;
  float digit_width, digit_height;
  int (Level_info::*getValueFunction)() const;
  bool is_static_n_digits;

public:
  Dynamic_value_display(Level_info &_level_info, Engine &_engine, int _text_type, int _max_digits, float _startX, float _startY, float _digit_width, float _digit_height, int (Level_info::*_getValueFunction)() const, bool _is_static_n_digits = true)
      : level_info(_level_info), engine(_engine), max_digits(_max_digits), text_type(_text_type), startX(_startX), startY(_startY), digit_width(_digit_width), digit_height(_digit_height), getValueFunction(_getValueFunction), is_static_n_digits(_is_static_n_digits)
  {
    create_digit_images();
  }

  void create_digit_images()
  {
    for (int i = 0; i < max_digits; ++i)
    {
      auto position = Point3f(startX - (max_digits - 1 - i) * digit_width, startY, 0); // Ajusta la posición según tus necesidades
      auto digit_image = std::make_shared<Dynamic_digit_image>(
          position,
          Vector2f(digit_width, digit_height),
          level_info,
          engine,
          text_type,
          i,
          max_digits,
          getValueFunction,
          is_static_n_digits);
      digit_images.push_back(digit_image);
    }
  }

  void add_to_game()
  {
    for (auto &digit_image : digit_images)
    {
      engine.get_game()->create_entity(digit_image);
    }
  }
};
