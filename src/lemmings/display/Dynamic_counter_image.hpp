#pragma once

#include <cmath> // for std::pow
#include <string>

#include "lemmings/display/Text_image.hpp"

class Dynamic_counter_image : public Text_image
{
private:
  int lastDigit;            // Almacena el último dígito relevante para comparación
  int digitIndex;           // Índice del dígito deseado
  int maxDigits;            // Número máximo de dígitos del valor
  const int &observedValue; // Referencia al valor observado para cambios
  bool is_static_n_digits;

public:
  Dynamic_counter_image(Point3f position, Vector2f diagonal, Game_info &_game_info, Engine &engine, int text_type, int _digitIndex, int _maxDigits, const int &_observedValue, bool _is_static_n_digits)
      : Text_image(position, diagonal, _game_info, engine, text_type, "5", true), lastDigit(-1), digitIndex(_digitIndex), maxDigits(_maxDigits), observedValue(_observedValue), is_static_n_digits(_is_static_n_digits)
  {
  }

  void update_texture(Engine &engine) override
  {
    if (!is_changeable)
      return;

    int currentValue = observedValue; // Usa la referencia al valor observado
    int relevantDigit = extract_relevant_digit(currentValue);
    // Decide si este y todos los dígitos superiores son cero
    bool shouldHideDigit = (!is_static_n_digits) && (relevantDigit == 0) && are_all_higher_digits_zero(currentValue);

    if (relevantDigit != lastDigit && (relevantDigit != 0 && relevantDigit != 6 && relevantDigit != -1))
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
    else if (relevantDigit == 0)
    {
      destroy();
    }
  }

private:
  bool are_all_higher_digits_zero(int value)
  {
    int higherValue = value / std::pow(10, maxDigits - digitIndex);
    return higherValue == 0;
  }

  int extract_relevant_digit(int value)
  {
    int divisor = std::pow(10, maxDigits - digitIndex - 1);
    return (value / divisor) % 10;
  }
};
