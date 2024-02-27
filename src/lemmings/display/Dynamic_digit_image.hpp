#pragma once

#include <cmath> // for std::pow
#include <string>

#include "lemmings/display/Text_image.hpp"

class Dynamic_digit_image : public Text_image
{
private:
  int lastDigit;                              // Almacena el último dígito relevante para comparación
  int digitIndex;                             // Índice del dígito deseado
  int maxDigits;                              // Número máximo de dígitos del valor
  int (Game_info::*getValueFunction)() const; // Puntero a función miembro de Game_info
  bool is_static_n_digits;
  bool hide_first_digit;

public:
  Dynamic_digit_image(Point3f position, Vector2f diagonal, Game_info &_game_info, Engine &engine, int text_type, int _digitIndex, int _maxDigits, int (Game_info::*_getValueFunction)() const, bool _is_static_n_digits, bool _hide_first_digit = false)
      : Text_image(position, diagonal, _game_info, engine, text_type, "0", true), lastDigit(-1), digitIndex(_digitIndex), maxDigits(_maxDigits), getValueFunction(_getValueFunction), is_static_n_digits(_is_static_n_digits), hide_first_digit(_hide_first_digit)
  {
    disable_collisions(); 
  }

  void update_texture(Engine &engine) override
  {
    if (!is_changeable)
      return;

    int currentValue = (game_info.*getValueFunction)(); // Invoca la función de Game_info
    int relevantDigit = extract_relevant_digit(currentValue);
    // Decide si este y todos los dígitos superiores son cero
    bool shouldHideDigit = (!is_static_n_digits) && (relevantDigit == 0) && !(!hide_first_digit && (digitIndex == maxDigits - 1)) && are_all_higher_digits_zero(currentValue);

    if (relevantDigit != lastDigit)
    {
      std::string newPath;
      if (shouldHideDigit)
      {
        newPath = "assets/text/text_0_.png";
      }
      else
      {
        newPath = "assets/text/text_" + std::to_string(text_type) + "_" + std::to_string(relevantDigit) + ".png";
      }

      set_active_texture(engine.load_texture(newPath));
      lastDigit = relevantDigit;
    }
  }

private:
  bool are_all_higher_digits_zero(int value)
  {
    // Verifica si todos los dígitos superiores al actual son cero
    int divisor = std::pow(10, maxDigits - digitIndex - 1);
    return (value / divisor) == 0;
  }

  int extract_relevant_digit(int value)
  {
    int divisor = std::pow(10, maxDigits - digitIndex - 1);
    return (value / divisor) % 10;
  }
};
