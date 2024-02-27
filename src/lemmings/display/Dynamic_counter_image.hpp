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

    if (observedValue != lastDigit && (observedValue > 0 && observedValue < 6))
    {
      set_active_texture(engine.load_texture("assets/text/text_" + std::to_string(text_type) + "_" + std::to_string(observedValue) + ".png"));
      lastDigit = observedValue;
    }
    else if (observedValue == 0)
    {
      destroy();
    }
  }
};
