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

  void setup_menu(Engine &engine, int type, int level)
  {

    if (type == Utils::TITLE)
    {
      auto background = std::make_shared<Entity>(Point3f(0, -500, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background1.png"), "Background");
      engine.get_game().create_entity(background);

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
      auto background = std::make_shared<Entity>(Point3f(0, -500, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background1.png"), "Background");
      engine.get_game().create_entity(background);
    }
    else if (type == Utils::LEVEL_INTRO)
    {
      auto background = std::make_shared<Entity>(Point3f(0, -500, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background2.png"), "Background");
      engine.get_game().create_entity(background);
      Texture txt = engine.load_texture("assets/maps/bkg/map_0_" + std::to_string(level) + ".png");

      // mapa 0,0  640,65 : 640px 65px
      auto map = std::make_shared<Entity>(Point3f(320 - (txt.get_width() * 65 / (2 * txt.get_height())), -480, 2), Vector2f(txt.get_width() * 65 / txt.get_height(), 65), txt, "MAP");
      engine.get_game().create_entity(map);

      // Level (number) // level name
      auto text = std::make_shared<Text_displayer>(Point3f(0, -370, 2), Vector2f(16, 30), game_info, "left",
                                                   engine.load_texture("assets/font/font-red.png"),
                                                   Vector2i(16, 30), lemmings_font_map, "Level " + std::to_string(level) + "  " + Utils::LEVEL_NAME[0][level],
                                                   "TEXT");
      engine.get_game().create_entity(text);

      // Number of Lemmings (number)
      text = std::make_shared<Text_displayer>(Point3f(160, -310, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Number of Lemmings " + std::to_string(Utils::LEVEL_N_LEMMINGS[level]),
                                              "TEXT");
      engine.get_game().create_entity(text);

      // (number) % To Be Saved
      text = std::make_shared<Text_displayer>(Point3f(160, -279, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-green.png"),
                                              Vector2i(16, 30), lemmings_font_map, std::to_string(Utils::LEVEL_SAVE_LEMMINGS[level] / Utils::LEVEL_N_LEMMINGS[level]) + "% To Be Saved",
                                              "TEXT");
      engine.get_game().create_entity(text);

      // Release Rate (number)
      text = std::make_shared<Text_displayer>(Point3f(160, -248, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-brown.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Release Rate " + std::to_string(Utils::LEVEL_SPAWN_VELOCITY[level]),
                                              "TEXT");
      engine.get_game().create_entity(text);

      // Time // (number) Minutes
      text = std::make_shared<Text_displayer>(Point3f(160, -217, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-cyan.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Time    " + std::to_string((int)(Utils::LEVEL_TIME_LIMIT[level] / 60)) + " Minutes",
                                              "TEXT");
      engine.get_game().create_entity(text);

      // Rating Fun
      text = std::make_shared<Text_displayer>(Point3f(160, -186, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-purple.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Rating  " + Utils::DIFICULTY_NAME[0],
                                              "TEXT");
      engine.get_game().create_entity(text);

      // Press mouse button to continue
      text = std::make_shared<Text_displayer>(Point3f(320, -115, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_BLUE_2[1],
                                              "TEXT");
      engine.get_game().create_entity(text);
    }
    else if (type == Utils::LEVEL_OUTRO)
    {
      auto background = std::make_shared<Entity>(Point3f(0, -500, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background2.png"), "Background");
      engine.get_game().create_entity(background);
      int idx_red, idx_blue;
      auto text = std::make_shared<Text_displayer>(Point3f(320, -485, 2), Vector2f(16, 30), game_info, "center",
                                                   engine.load_texture("assets/font/font-cyan.png"),
                                                   Vector2i(16, 30), lemmings_font_map, "All lemmings accounted for.",
                                                   "TEXT");
      engine.get_game().create_entity(text);

      int rescued = game_info.get_percen_lemmings_in();
      int needed = Utils::LEVEL_SAVE_LEMMINGS[game_info.get_level()] * 100 / Utils::LEVEL_N_LEMMINGS[game_info.get_level()];

      text = std::make_shared<Text_displayer>(Point3f(320, -425, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-purple.png"),
                                              Vector2i(16, 30), lemmings_font_map, "You needed  " + std::to_string(needed) + "%",
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(320, -395, 2), Vector2f(16, 30), game_info, "center",
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

      text = std::make_shared<Text_displayer>(Point3f(320, -335, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-red.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_RED_1[idx_red],
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(320, -305, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-red.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_RED_2[idx_red],
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(320, -145, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_BLUE_1[idx_blue],
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(320, -115, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_BLUE_2[idx_blue],
                                              "TEXT");
      engine.get_game().create_entity(text);
    }
  }
};