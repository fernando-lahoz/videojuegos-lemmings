#pragma once

#include "Text_image.hpp"
#include <cmath> // Para std::pow
#include <string>

class Dynamic_digit_image : public Text_image
{
private:
  int lastDigit;                               // Almacena el último dígito relevante para comparación
  int digitIndex;                              // Índice del dígito deseado
  int maxDigits;                               // Número máximo de dígitos del valor
  int (Level_info::*getValueFunction)() const; // Puntero a función miembro de Level_info
  bool is_static_n_digits;

public:
  Dynamic_digit_image(Point3f position, Vector2f diagonal, Level_info &_level_info, Engine &engine, int text_type, int _digitIndex, int _maxDigits, int (Level_info::*_getValueFunction)() const, bool _is_static_n_digits)
      : Text_image(position, diagonal, _level_info, engine, text_type, "0", true), lastDigit(-1), digitIndex(_digitIndex), maxDigits(_maxDigits), getValueFunction(_getValueFunction), is_static_n_digits(_is_static_n_digits)
  {
  }

  void update_texture(Engine &engine) override
  {
    if (!is_changeable)
      return;

    int currentValue = (level_info.*getValueFunction)(); // Invoca la función de Level_info
    int relevantDigit = extract_relevant_digit(currentValue);
    // Decide si este y todos los dígitos superiores son cero
    bool shouldHideDigit = (!is_static_n_digits) && (relevantDigit == 0) && are_all_higher_digits_zero(currentValue);

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
    int higherValue = value / std::pow(10, maxDigits - digitIndex);
    return higherValue == 0;
  }

  int extract_relevant_digit(int value)
  {
    int divisor = std::pow(10, maxDigits - digitIndex - 1);
    return (value / divisor) % 10;
  }
};
