#pragma once

#include <string>

#include "lemmings/display/Text_image.hpp"

class Dynamic_text_image : public Text_image
{
private:
  std::string lastText;                              // Almacena el último texto para comparación
  std::string (Game_info::*getTextFunction)() const; // Puntero a función miembro de Game_info que devuelve un std::string

public:
  Dynamic_text_image(Point3f position, Vector2f diagonal, Game_info &_game_info, Engine &engine, int text_type, std::string (Game_info::*_getTextFunction)() const)
      : Text_image(position, diagonal, _game_info, engine, text_type, "", true), // "default" es el path inicial, ajusta según sea necesario
        getTextFunction(_getTextFunction)
  {
  }

  void update_texture(Engine &engine) override
  {
    if (!is_changeable)
      return;

    std::string currentText = (game_info.*getTextFunction)(); // Invoca la función de Game_info

    if (currentText != lastText) // Comprueba si el texto ha cambiado
    {
      std::string newPath = "assets/text/text_" + std::to_string(text_type) + "_" + currentText + ".png"; // Construye el nuevo path basado en el texto actual
      set_active_texture(engine.load_texture(newPath));                                                   // Actualiza la textura
      lastText = currentText;                                                                             // Actualiza el último texto almacenado
    }
  }
};
