#pragma once

#include "engine/engine.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/menu/Menu_button.hpp"
#include "lemmings/utils.hpp"
#include "lemmings/display/Text_displayer.hpp"

class Menu
{
private:
  Game_info &game_info;

  static Point2i lemmings_font_map(char c)
  {
    if (c >= 'A' && c <= 'M')
      return {(c - 'A'), 0};
    else if (c >= 'N' && c <= 'Z')
      return {(c - 'N'), 1};
    else if (c >= 'a' && c <= 'm')
      return {(c - 'a'), 2};
    else if (c >= 'n' && c <= 'z')
      return {(c - 'n'), 3};
    else if (c >= '0' && c <= '9')
      return {(c - '0'), 4};
    else
    {
      switch (c)
      {
      case '.':
        return {0, 5};
      case '(':
        return {1, 5};
      case ')':
        return {2, 5};
      case '\'':
        return {3, 5};
      case '!':
        return {4, 5};
      case '%':
        return {5, 5};
      case '-':
        return {6, 5};
      default:
        return {12, 5}; // white space
      }
    }
  }

public:
  Menu(Game_info &_game_info) : game_info(_game_info)
  {
  }

  void setup_menu(Engine &engine, int type, int)
  {
    auto background = std::make_shared<Entity>(Point3f(0, -500, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background.png"), "Background");
    engine.get_game().create_entity(background);
    if (type == Utils::TITLE)
    {
      auto title = std::make_shared<Entity>(Point3f(3, -480, 2), Vector2f(633, 200), engine.load_texture("assets/menu/title.png"), "Title");
      engine.get_game().create_entity(title);

      auto button1 = std::make_shared<Menu_button>(Point3f(8, -270, 2), Vector2f(150, 86.2069), engine, game_info, Utils::BUTTON_TYPE::PLAYER_SOLO);
      engine.get_game().create_entity(button1);

      auto button2 = std::make_shared<Menu_button>(Point3f(166, -270, 2), Vector2f(150, 86.2069), engine, game_info, Utils::BUTTON_TYPE::PLAYER_VS_IA);
      engine.get_game().create_entity(button2);

      auto button3 = std::make_shared<Menu_button>(Point3f(324, -270, 2), Vector2f(150, 86.2069), engine, game_info, Utils::BUTTON_TYPE::SOUND_EFFECTS, true);
      engine.get_game().create_entity(button3);

      auto button4 = std::make_shared<Menu_button>(Point3f(482, -270, 2), Vector2f(150, 86.2069), engine, game_info, Utils::BUTTON_TYPE::EXIT);
      engine.get_game().create_entity(button4);
    }
    else if (type == Utils::LEVEL_SELECTOR)
    {
    }
    else if (type == Utils::LEVEL_INTRO)
    {
      // level info
    }
    else if (type == Utils::LEVEL_OUTRO)
    {
      int idx_red, idx_blue;
      auto text = std::make_shared<Text_displayer>(Point3f(320, -485, -1), Vector2f(16, 30), game_info, "center",
                                                   engine.load_texture("assets/font/font-cyan.png"),
                                                   Vector2i(16, 30), lemmings_font_map, "All lemmings accounted for.",
                                                   "TEXT");
      engine.get_game().create_entity(text);

      int rescued = game_info.get_percen_lemmings_in();
      int needed = Utils::LEVEL_SAVE_LEMMINGS[game_info.get_level()] * 100 / Utils::LEVEL_N_LEMMINGS[game_info.get_level()];

      text = std::make_shared<Text_displayer>(Point3f(320, -425, -1), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-purple.png"),
                                              Vector2i(16, 30), lemmings_font_map, "You needed  " + std::to_string(needed) + "%",
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(320, -395, -1), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-purple.png"),
                                              Vector2i(16, 30), lemmings_font_map, "You rescued " + std::to_string(rescued) + "%",
                                              "TEXT");
      engine.get_game().create_entity(text);

      if (rescued == 100)
      {
        idx_red = 3;
        idx_blue = 1;
      }
      else if (rescued > needed)
      {
        idx_red = 2;
        idx_blue = 1;
      }
      else if (rescued == needed)
      {
        idx_red = 1;
        idx_blue = 1;
      }
      else
      {
        idx_red = 0;
        idx_blue = 0;
      }

      text = std::make_shared<Text_displayer>(Point3f(320, -335, -1), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-red.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_RED_1[idx_red],
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(320, -305, -1), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-red.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_RED_2[idx_red],
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(320, -145, -1), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_BLUE_1[idx_blue],
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(320, -115, -1), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_BLUE_2[idx_blue],
                                              "TEXT");
      engine.get_game().create_entity(text);
    }
  }
};