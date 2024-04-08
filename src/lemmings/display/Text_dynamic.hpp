#pragma once

#include <string>

#include "engine/fixed_text.hpp"

#include "lemmings/display/Text_displayer.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"
#include "lemmings/keyboard/Keyboard_manager.hpp"

class Text_dynamic : public Entity
{
  using MappingFunction = Point2i (*)(char);

private:
  Point3f position;
  Vector2f letter_size;
  Game_info &game_info;
  std::string justified;
  Texture font_texture;
  Vector2i texture_letter_size;
  MappingFunction map;

  std::string_view last_text;
  std::shared_ptr<Text_displayer> text;
  int type;
  int index;

public:
  Text_dynamic(Point3f _position, Vector2f _letter_size, Engine &engine, Game_info &_game_info, std::string _justified, Texture _font_texture,
               Vector2i _texture_letter_size, MappingFunction _map, std::string_view _text, int _type, int _index = -1)
      : Entity(_position, _letter_size,
               engine.load_texture("assets/menu/transparent.png"),
               engine,
               "Dynamic TEXT", "Dynamic TEXT"),
        position(_position),
        letter_size(_letter_size),
        game_info(_game_info),
        justified(_justified),
        font_texture(_font_texture),
        texture_letter_size(_texture_letter_size),
        map(_map),
        last_text(_text),
        type(_type),
        index(_index)
  {
    text = std::make_shared<Text_displayer>(position, letter_size, game_info, _justified, font_texture,
                                            texture_letter_size, map, _text, engine,
                                            "TEXT");
    engine.get_game().create_entity(text);
    disable_collisions();
  }

  ~Text_dynamic()
  {
    text->destroy();
  }

  void pre_physics(Engine &engine) override
  {
    if (type == 0 && last_text != Utils::DIFFICULTY_NAME[game_info.get_difficulty_selected()])
    {
      last_text = Utils::DIFFICULTY_NAME[game_info.get_difficulty_selected()];
      text->destroy();

      text = std::make_shared<Text_displayer>(position, letter_size, game_info, justified, font_texture,
                                              texture_letter_size, map, last_text, engine,
                                              "TEXT");
      engine.get_game().create_entity(text);
      return;
    }
    if (type == 1 && last_text != std::to_string(game_info.get_level_selected()))
    {
      last_text = std::to_string(game_info.get_level_selected());
      text->destroy();

      text = std::make_shared<Text_displayer>(position, letter_size, game_info, justified, font_texture,
                                              texture_letter_size, map, last_text, engine,
                                              "TEXT");
      engine.get_game().create_entity(text);
      return;
    }
    if (type == 2 && last_text != Utils::LEVEL_NAME[game_info.get_difficulty_selected()][game_info.get_level_selected()])
    {
      last_text = Utils::LEVEL_NAME[game_info.get_difficulty_selected()][game_info.get_level_selected()];
      text->destroy();

      text = std::make_shared<Text_displayer>(position, letter_size, game_info, justified, font_texture,
                                              texture_letter_size, map, last_text, engine,
                                              "TEXT");
      engine.get_game().create_entity(text);
      return;
    }
    if (type == 3 && last_text != game_info.get_lemming_hovered_type())
    {
      last_text = game_info.get_lemming_hovered_type();
      text->destroy();

      text = std::make_shared<Text_displayer>(position, letter_size, game_info, justified, font_texture,
                                              texture_letter_size, map, last_text, engine,
                                              "TEXT");
      engine.get_game().create_entity(text);
      return;
    }
    if(type == 4 && last_text != KeyBindings().InEvenToCh(game_info.get_conf_buttons(index)))
    {//No coincide el mensaje de tecla actual con el anterior
      last_text = KeyBindings().InEvenToCh(game_info.get_conf_buttons(index));
      text->destroy();

      text = std::make_shared<Text_displayer>(position, letter_size, game_info, justified, font_texture,
                                              texture_letter_size, map, last_text, engine,
                                              "TEXT");
      engine.get_game().create_entity(text);
      return;
    }
  }
};
