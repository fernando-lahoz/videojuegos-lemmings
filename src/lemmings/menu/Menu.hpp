#pragma once

#include "engine/engine.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/menu/Menu_button.hpp"
#include "lemmings/menu/Menu_mouse_handler.hpp"
#include "lemmings/menu/Menu_animation.hpp"
#include "lemmings/menu/Credit_animation.hpp"
#include "lemmings/menu/Credit_text.hpp"
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
    engine.get_game().create_entity(std::make_shared<Menu_mouse_handler>(Point3f(0, -500, 4), Vector2f(640, 400), engine, game_info, type));

    if (type == Utils::TITLE)
    {
      auto background = std::make_shared<Entity>(Point3f(0, -500, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_brown.png"), "Background");
      engine.get_game().create_entity(background);

      auto title = std::make_shared<Entity>(Point3f(3, -480, 2), Vector2f(633, 200), engine.load_texture("assets/menu/title.png"), "Title");
      engine.get_game().create_entity(title);

      auto credits = std::make_shared<Credit_text>(Point3f(0, -125, 1), Vector2f(10, 19), engine, game_info, 2.5f, 3.0f,
                                                   engine.load_texture("assets/font/font-blue.png"),
                                                   Vector2i(16, 30), lemmings_font_map, Utils::CREDIT_NAMES);
      engine.get_game().create_entity(credits);

      engine.get_game().create_entity(std::make_shared<Credit_animation>(Point3f(0, -131, 2), Vector2f(640, 31), game_info, engine, 0, 10));
      engine.get_game().create_entity(std::make_shared<Credit_animation>(Point3f(-2.5, -131, 0), Vector2f(645, 31), game_info, engine, 1, 32));

      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(34.7657, -413.842, 1), Vector2f(31.33333, 40.7767), engine, 1, 10, 0.3f, 4.0f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(263.222, -409.441, 1), Vector2f(29.6666667, 29.1262), engine, 2, 8, 0.3f, 6.0f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(496.776, -421.824, 1), Vector2f(24, 29.1262), engine, 3, 7, 0.3f, 7.0f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(56.5432, -276.301, 1), Vector2f(65.014367, 55.625), engine, 4, 4, 0.3f, 8.0f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(209.5432, -276.301, 1), Vector2f(65.014367, 55.625), engine, 5, 6, 0.3f, 7.5f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(361.996, -275.508, 1), Vector2f(65.014367, 55.625), engine, 6, 10, 0.3f, 9.0f, 8.0f, true));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(515.5432, -276.301, 1), Vector2f(65.014367, 55.625), engine, 7, 10, 0.3f, 8.5f, 8.0f, false));

      auto button1 = std::make_shared<Menu_button>(Point3f(28, -280, 2), Vector2f(125, 125), engine, game_info, Utils::BUTTON_TYPE::PLAYER_SOLO);
      engine.get_game().create_entity(button1);

      auto button2 = std::make_shared<Menu_button>(Point3f(181, -280, 2), Vector2f(125, 125), engine, game_info, Utils::BUTTON_TYPE::PLAYER_VS_IA);
      engine.get_game().create_entity(button2);

      auto button3 = std::make_shared<Menu_button>(Point3f(334, -280, 2), Vector2f(125, 125), engine, game_info, Utils::BUTTON_TYPE::SOUND_EFFECTS, true);
      engine.get_game().create_entity(button3);

      auto button4 = std::make_shared<Menu_button>(Point3f(487, -280, 2), Vector2f(125, 125), engine, game_info, Utils::BUTTON_TYPE::EXIT);
      engine.get_game().create_entity(button4);
    }
    else if (type == Utils::LEVEL_SELECTOR)
    {
      auto background = std::make_shared<Entity>(Point3f(0, -500, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_brown.png"), "Background");
      engine.get_game().create_entity(background);
    }
    else if (type == Utils::LEVEL_INTRO)
    {
      auto background = std::make_shared<Entity>(Point3f(0, -500, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_green.png"), "Background");
      engine.get_game().create_entity(background);
      Texture txt = engine.load_texture("assets/maps/raw/map_0_" + std::to_string(level) + ".png");

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
      auto background = std::make_shared<Entity>(Point3f(0, -500, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_green.png"), "Background");
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