#pragma once

#include <string>
#include "engine/fixed_text.hpp"
#include "engine/rigid_body.hpp"
#include "lemmings/Game_info.hpp"

class Credit_text : public Rigid_body
{
private:
  std::string text;               // Texto prefijado
  Game_info &game_info;           // Referencia a Game_info para acceder a la variable que controla la posición
  int lateral_movement_extent;    // Extensión del movimiento lateral [0, x]
  float time_frame_credit = 0.0f; // Acumulador de tiempo para la animación del sprite

  int acumulator_frame_passed = 0;

  float animation_duration = 0.0f;
  float time_frame_wait = 0.0f; // Acumulador de tiempo para la animación del sprite
  float time_wait;
  std::shared_ptr<FixedText> text_ptr;

  using MappingFunction = Point2i (*)(char);

public:
  Credit_text(Point3f position, Vector2f letter_size, Engine &engine, Game_info &_game_info, float _animation_duration, float _time_wait, const Texture &font_texture,
              Vector2i texture_letter_size, MappingFunction map, std::string _text)
      : Rigid_body(position, letter_size, engine.load_texture("assets/menu/transparent.png"), engine, "Credits Handler"),
        text(_text),
        game_info(_game_info),
        animation_duration(_animation_duration),
        time_frame_wait(_time_wait),
        time_wait(_time_wait)
  {
    text_ptr = std::make_shared<FixedText>(position, letter_size, font_texture,
                                           texture_letter_size, map, _text, "TEXT");
    engine.get_game().create_entity(text_ptr);
    lateral_movement_extent = text.size() * letter_size.x;
    disable_collisions();
  }

  void update_state(Engine &engine) override
  {
    float delta_time = engine.get_delta_time();

    if (time_frame_wait > 0)
    {
      time_frame_wait -= delta_time;
      return;
    }

    time_frame_credit += delta_time;

    if (time_frame_credit >= animation_duration / 640)
    {
      int times = time_frame_credit / (animation_duration / 640);
      acumulator_frame_passed += times;
      time_frame_credit = time_frame_credit - (animation_duration / 640) * times;

      // Calcula la nueva posición en X basada en la variable de game_info
      int newX = ((game_info.get_credit_frame() + times) % lateral_movement_extent);
      if (acumulator_frame_passed >= 640)
      {
        time_frame_wait = time_wait;
        acumulator_frame_passed = acumulator_frame_passed % 640;
      }
      game_info.set_credit_frame(newX);
      // Actualiza la posición del texto
      text_ptr->set_position3D(Point3f(-newX + 10000, position.y, position.z));
    }
  }
};
