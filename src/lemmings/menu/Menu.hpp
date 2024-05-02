#pragma once

#include "engine/engine.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/menu/Intro.hpp"
#include "lemmings/menu/Menu_button.hpp"
#include "lemmings/menu/Menu_option_button.hpp"
#include "lemmings/menu/Menu_arrow.hpp"
#include "lemmings/menu/Menu_mouse_handler.hpp"
#include "lemmings/menu/Menu_animation.hpp"
#include "lemmings/menu/Menu_slider.hpp"
#include "lemmings/menu/Credit_animation.hpp"
#include "lemmings/menu/Credit_text.hpp"
#include "lemmings/utils.hpp"
#include "lemmings/display/Text_displayer.hpp"
#include "lemmings/display/Text_dynamic.hpp"
#include "lemmings/display/Map_dynamic.hpp"
#include "lemmings/keyboard/Keyboard_manager.hpp"

const std::string ASPECT_STRING[4][2] = {
    {"640", "400"},
    {"960", "600"},
    {"1280", "800"},
    {"Full", "screen"}};

class Menu
{
private:
  Game_info &game_info;
  Keyboard_manager &keyboard;

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

  // create a const static member to store some strings in a 4x2 matrix

public:
  Menu(Game_info &_game_info, Keyboard_manager &_keyboard) : game_info(_game_info), keyboard(_keyboard)
  {
  }

  void setup_menu(Engine &engine, int type, int level, int difficulty)
  {
    engine.get_game().create_entity(std::make_shared<Menu_mouse_handler>(Point3f(10000, 0, 4), Vector2f(640, 400), engine, game_info, type));

    if (type == Utils::TITLE)
    {
      engine.flush_texture_cache();
      game_info.set_credit_frame(0);
      auto background = std::make_shared<Entity>(Point3f(10000, -0, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_brown.png"), engine, "Background");
      engine.get_game().create_entity(background);

      auto title = std::make_shared<Entity>(Point3f(10003, 20, 2), Vector2f(633, 200), engine.load_texture("assets/menu/title.png"), engine, "Title");
      engine.get_game().create_entity(title);

      auto credits = std::make_shared<Credit_text>(Point3f(10000, 375, 1), Vector2f(10, 19), engine, game_info, 2.5f, 3.0f,
                                                   engine.load_texture("assets/font/font-blue.png"),
                                                   Vector2i(16, 30), lemmings_font_map, Utils::CREDIT_NAMES);
      engine.get_game().create_entity(credits);

      engine.get_game().create_entity(std::make_shared<Credit_animation>(Point3f(10000, 369, 2), Vector2f(640, 31), game_info, engine, 0, 10));
      engine.get_game().create_entity(std::make_shared<Credit_animation>(Point3f(10000, 369, 0), Vector2f(640, 31), game_info, engine, 1, 32));

      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(10034.7657, 86.158, 1), Vector2f(31.33333, 40.7767), engine, 1, 10, 0.3f, 4.0f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(10263.222, 90.559, 1), Vector2f(29.6666667, 29.1262), engine, 2, 8, 0.3f, 6.0f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(10496.776, 78.176, 1), Vector2f(24, 29.1262), engine, 3, 7, 0.3f, 7.0f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(10056.5432, 224.492, 1), Vector2f(65.014367, 55.625), engine, 4, 4, 0.3f, 8.0f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(10209.5432, 224.492, 1), Vector2f(65.014367, 55.625), engine, 5, 6, 0.3f, 7.5f, 8.0f, false));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(10361.996, 224.492, 1), Vector2f(65.014367, 55.625), engine, 6, 10, 0.3f, 9.0f, 8.0f, true));
      engine.get_game().create_entity(std::make_shared<Menu_animation>(Point3f(10515.5432, 224.492, 1), Vector2f(65.014367, 55.625), engine, 7, 10, 0.3f, 8.5f, 8.0f, false));

      auto button1 = std::make_shared<Menu_button>(Point3f(10028, 220, 2), Vector2f(125, 125), engine, game_info, keyboard, Utils::BUTTON_TYPE::PLAYER_SOLO);
      engine.get_game().create_entity(button1);

      auto button2 = std::make_shared<Menu_button>(Point3f(10181, 220, 2), Vector2f(125, 125), engine, game_info, keyboard, Utils::BUTTON_TYPE::PLAYER_VS_IA);
      engine.get_game().create_entity(button2);

      auto button3 = std::make_shared<Menu_button>(Point3f(10334, 220, 2), Vector2f(125, 125), engine, game_info, keyboard, Utils::BUTTON_TYPE::SETTINGS);
      engine.get_game().create_entity(button3);

      auto button4 = std::make_shared<Menu_button>(Point3f(10487, 220, 2), Vector2f(125, 125), engine, game_info, keyboard, Utils::BUTTON_TYPE::EXIT);
      engine.get_game().create_entity(button4);
    }
    else if (type == Utils::LEVEL_SELECTOR)
    {
      game_info.set_ia(false);
      auto background = std::make_shared<Entity>(Point3f(10000, 0, 4), Vector2f(640, 400), engine.load_texture("assets/menu/background_brown.png"), engine, "Background", "Background");
      engine.get_game().create_entity(background);
      Texture txt = engine.load_texture("assets/maps/raw/map_0_" + std::to_string(level) + ".png");
      auto map_background = std::make_shared<Map_dynamic>(Point3f(10000, 20, 3), Vector2f(640, 65), engine, game_info, true);
      engine.get_game().create_entity(map_background);

      // mapa 0,0  640,65 : 640px 65px
      auto map = std::make_shared<Map_dynamic>(Point3f(10320 - (txt.get_width() * 65 / (2 * txt.get_height())), 20, 2), Vector2f(txt.get_width() * 65 / txt.get_height(), 65), engine, game_info);
      engine.get_game().create_entity(map);

      // Level (number) // level name

      auto dynamic_text = std::make_shared<Text_dynamic>(Point3f(10320, 120, 2), Vector2f(16, 30), engine, game_info, "center",
                                                         engine.load_texture("assets/font/font-red.png"),
                                                         Vector2i(16, 30), lemmings_font_map, Utils::LEVEL_NAME[game_info.get_difficulty_selected()][game_info.get_level_selected()], 2);
      engine.get_game().create_entity(dynamic_text);

      engine.get_game().create_entity(std::make_shared<Menu_arrow>(Point3f(10255, 165, 2), Vector2f(30, 30), game_info, engine, 0));
      engine.get_game().create_entity(std::make_shared<Menu_arrow>(Point3f(10055, 165, 2), Vector2f(30, 30), game_info, engine, 1));

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10170, 180, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-green.png"),
                                                    Vector2i(16, 30), lemmings_font_map, Utils::DIFFICULTY_NAME[game_info.get_difficulty_selected()], 0);
      engine.get_game().create_entity(dynamic_text);

      engine.get_game().create_entity(std::make_shared<Menu_arrow>(Point3f(10555, 165, 2), Vector2f(30, 30), game_info, engine, 2));
      engine.get_game().create_entity(std::make_shared<Menu_arrow>(Point3f(10355, 165, 2), Vector2f(30, 30), game_info, engine, 3));

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10470, 180, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-green.png"),
                                                    Vector2i(16, 30), lemmings_font_map, std::to_string(game_info.get_level_selected()), 1);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10170, 235, 2), Vector2f(8, 15), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-blue.png"),
                                                    Vector2i(16, 30), lemmings_font_map, "Saved Lemmings", 7);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10470, 235, 2), Vector2f(8, 15), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-blue.png"),
                                                    Vector2i(16, 30), lemmings_font_map, "Time", 7);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10170, 265, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-blue.png"),
                                                    Vector2i(16, 30), lemmings_font_map, game_info.get_selected_level_best_perc(), 5);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10470, 265, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-blue.png"),
                                                    Vector2i(16, 30), lemmings_font_map, game_info.get_selected_level_best_time(), 6);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10320, 250, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-purple.png"),
                                                    Vector2i(16, 30), lemmings_font_map, "Be ready to save those lemmings!", 8);
      engine.get_game().create_entity(dynamic_text);

      // Boton de vuelta al menu
      auto b_back = std::make_shared<Menu_button>(Point3f(10020, 340, 2), Vector2f(70, 37), engine, game_info, keyboard, Utils::BUTTON_TYPE::BACK);
      engine.get_game().create_entity(b_back);

      auto b_play = std::make_shared<Menu_button>(Point3f(10267, 320, 2), Vector2f(105, 55), engine, game_info, keyboard, Utils::BUTTON_TYPE::PLAY);
      engine.get_game().create_entity(b_play);
    }
    else if (type == Utils::LEVEL_INTRO)
    {
      auto background = std::make_shared<Entity>(Point3f(10000, 0, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_green.png"), engine, "Background");
      engine.get_game().create_entity(background);
      int level_map_num = game_info.get_ia() ? game_info.conversion_level_ia() : level;
      std::cout << "Nivel mapa: " << level_map_num << "\n";
      Texture txt = engine.load_texture("assets/maps/raw/map_" + std::to_string(difficulty) + "_" + std::to_string(level_map_num) + ".png");
      auto map_background = std::make_shared<Entity>(Point3f(10000, 20, 3), Vector2f(640, 65), engine.load_texture("assets/maps/background_" + std::to_string(Utils::LEVEL_BACKGROUND_TYPE[difficulty][level_map_num]) + ".png"), engine, "Background", "Background");
      engine.get_game().create_entity(map_background);
      // mapa 0,0  640,65 : 640px 65px
      auto map = std::make_shared<Entity>(Point3f(10320 - (txt.get_width() * 65 / (2 * txt.get_height())), 20, 2), Vector2f(txt.get_width() * 65 / txt.get_height(), 65), txt, engine, "MAP");
      engine.get_game().create_entity(map);

      // Level (number) // level name
      std::string levelName = game_info.get_ia() ? Utils::LEVEL_NAME_IA[difficulty][level] : Utils::LEVEL_NAME[difficulty][level];
      auto text = std::make_shared<Text_displayer>(Point3f(10000, 130, 2), Vector2f(16, 30), game_info, "left",
                                                   engine.load_texture("assets/font/font-red.png"),
                                                   Vector2i(16, 30), lemmings_font_map, "Level " + std::to_string(level) + "  " + levelName, engine,
                                                   "TEXT");
      engine.get_game().create_entity(text);

      // Number of Lemmings (number)
      int numberLemmings = game_info.get_ia() ? Utils::LEVEL_N_LEMMINGS_IA[difficulty][level] : Utils::LEVEL_N_LEMMINGS[difficulty][level];
      text = std::make_shared<Text_displayer>(Point3f(10160, 190, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Number of Lemmings " + std::to_string(numberLemmings), engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      int numberSaveLemmings = game_info.get_ia() ? Utils::LEVEL_SAVE_LEMMINGS_IA[difficulty][level] : Utils::LEVEL_SAVE_LEMMINGS[difficulty][level];
      // (number) % To Be Saved
      text = std::make_shared<Text_displayer>(Point3f(10160, 221, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-green.png"),
                                              Vector2i(16, 30), lemmings_font_map, std::to_string(numberSaveLemmings * 100 / numberLemmings) + "% To Be Saved", engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      // Release Rate (number)
      int spawn_velocity = game_info.get_ia() ? Utils::LEVEL_SPAWN_VELOCITY_IA[difficulty][level] : Utils::LEVEL_SPAWN_VELOCITY[difficulty][level];
      text = std::make_shared<Text_displayer>(Point3f(10160, 252, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-brown.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Release Rate " + std::to_string(spawn_velocity), engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      double time_limit = game_info.get_ia() ? Utils::LEVEL_TIME_LIMIT_IA[difficulty][level] : Utils::LEVEL_TIME_LIMIT[difficulty][level];
      time_limit = time_limit / 60;
      // Time // (number) Minutes
      text = std::make_shared<Text_displayer>(Point3f(10160, 283, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-cyan.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Time    " + std::to_string(int(time_limit)) + " Minutes", engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      if (game_info.get_ia())
      {
        text = std::make_shared<Text_displayer>(Point3f(10050, 10, 2), Vector2f(8, 15), game_info, "center",
                                                engine.load_texture("assets/font/font-red.png"),
                                                Vector2i(16, 30), lemmings_font_map, "Autoplay", engine, "TEXT");

        engine.get_game().create_entity(text);
      }

      // Rating Fun
      text = std::make_shared<Text_displayer>(Point3f(10160, 314, 2), Vector2f(16, 30), game_info, "left",
                                              engine.load_texture("assets/font/font-purple.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Rating  " + Utils::DIFFICULTY_NAME[difficulty], engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      // Press mouse button to continue
      text = std::make_shared<Text_displayer>(Point3f(10320, 385, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_BLUE_2[1], engine,
                                              "TEXT");
      engine.get_game().create_entity(text);
    }
    else if (type == Utils::LEVEL_OUTRO)
    {
      auto background = std::make_shared<Entity>(Point3f(10000, 0, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_green.png"), engine, "Background");
      engine.get_game().create_entity(background);
      int idx_red, idx_blue;
      auto text = std::make_shared<Text_displayer>(Point3f(10320, 15, 2), Vector2f(16, 30), game_info, "center",
                                                   engine.load_texture("assets/font/font-cyan.png"),
                                                   Vector2i(16, 30), lemmings_font_map, "All lemmings accounted for.", engine,
                                                   "TEXT");
      engine.get_game().create_entity(text);

      int rescued = game_info.get_percen_lemmings_in();
      int needed;
      if (game_info.get_ia())
      {
        needed = Utils::LEVEL_SAVE_LEMMINGS_IA[game_info.get_difficulty()][game_info.get_level()] * 100 / Utils::LEVEL_N_LEMMINGS_IA[game_info.get_difficulty()][game_info.get_level()];
      }
      else
      {
        needed = Utils::LEVEL_SAVE_LEMMINGS[game_info.get_difficulty()][game_info.get_level()] * 100 / Utils::LEVEL_N_LEMMINGS[game_info.get_difficulty()][game_info.get_level()];
      }

      text = std::make_shared<Text_displayer>(Point3f(10320, 75, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-purple.png"),
                                              Vector2i(16, 30), lemmings_font_map, "You needed  " + std::to_string(needed) + "%", engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(10320, 105, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-purple.png"),
                                              Vector2i(16, 30), lemmings_font_map, "You rescued " + std::to_string(rescued) + "%", engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      engine.get_game().create_entity(text);

      if (game_info.get_ia())
      {
        text = std::make_shared<Text_displayer>(Point3f(10050, 10, 2), Vector2f(8, 15), game_info, "center",
                                                engine.load_texture("assets/font/font-red.png"),
                                                Vector2i(16, 30), lemmings_font_map, "Autoplay", engine, "TEXT");

        engine.get_game().create_entity(text);
      }

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

      text = std::make_shared<Text_displayer>(Point3f(10320, 165, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-red.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_RED_1[idx_red], engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(10320, 195, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-red.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_RED_2[idx_red], engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(10320, 355, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_BLUE_1[idx_blue], engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      text = std::make_shared<Text_displayer>(Point3f(10320, 385, 2), Vector2f(16, 30), game_info, "center",
                                              engine.load_texture("assets/font/font-blue.png"),
                                              Vector2i(16, 30), lemmings_font_map, Utils::TEXT_BLUE_2[idx_blue], engine,
                                              "TEXT");
      engine.get_game().create_entity(text);
    }
    else if (type == Utils::MENU_TYPE::INTRO)
    {
      game_info.set_ia(false);
      engine.get_game().create_entity(std::make_shared<Intro>(engine, game_info));
    }
    else if (type == Utils::MENU_TYPE::GAME_COMPLETE)
    {
      game_info.set_ia(false);
      engine.get_game().create_entity(std::make_shared<Entity>(Point3f(10000, 0, 3), Vector2f(640, 400), engine.load_texture("assets/menu/win.png"), engine, "GAME COMPLETED", "GAME COMPLETED"));
    }
    else if (type == Utils::MENU_TYPE::CONFIG)
    {
      game_info.set_ia(false);
      game_info.set_config_screen();

      auto background = std::make_shared<Entity>(Point3f(10000, 0, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_brown.png"), engine, "Background", "Background");
      engine.get_game().create_entity(background);

      // Título de menu de configuracion
      auto text = std::make_shared<Text_displayer>(Point3f(10320, 25, 2), Vector2f(16 * 1.25, 30 * 1.25), game_info, "center",
                                                   engine.load_texture("assets/font/font-red.png"),
                                                   Vector2i(16, 30), lemmings_font_map, "Settings", engine,
                                                   "TEXT");
      engine.get_game().create_entity(text);

      // Botones de control de juego(habilidades, pausa, etc)
      float size_x = 150.0, size_y = 25.0, size_t = 0.5; // Tamaño de botones
      float x_b = 10050, y_b = 55;                       // Posiciones x e y de los botones
      float i_bot = size_y + 2;                          // Incremento de posición en y entre los botones
      float i_tx = 87;                                   // Incremento de posición en x del texto del boton

      // Ajustes de sonido
      auto b_sonido = std::make_shared<Entity>(Point3f(x_b, 35, 2), Vector2f(200, 80), engine.load_texture("assets/menu/menu_wide_volume.png"), engine, "Background", "Background");
      engine.get_game().create_entity(b_sonido);

      auto s_musica = std::make_shared<Menu_slider>(Point3f(x_b + 90, 74, 1), 86, Vector2f(12, 12), 0, engine, game_info);
      engine.get_game().create_entity(s_musica);
      auto s_efectos = std::make_shared<Menu_slider>(Point3f(x_b + 90, 90, 1), 86, Vector2f(12, 12), 1, engine, game_info);
      engine.get_game().create_entity(s_efectos);
      text = std::make_shared<Text_displayer>(Point3f(x_b + 85, 80, 0), Vector2f(5, 10), game_info, "right",
                                              engine.load_texture("assets/font/font-cyan.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Music", engine,
                                              "TEXT");
      engine.get_game().create_entity(text);
      text = std::make_shared<Text_displayer>(Point3f(x_b + 85, 96, 0), Vector2f(5, 10), game_info, "right",
                                              engine.load_texture("assets/font/font-cyan.png"),
                                              Vector2i(16, 30), lemmings_font_map, "Effects", engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      // Ajustes de resolucion
      auto b_aspect = std::make_shared<Entity>(Point3f(x_b, 127, 2), Vector2f(200, 80), engine.load_texture("assets/menu/menu_wide_aspect.png"), engine, "Background", "Background");
      engine.get_game().create_entity(b_aspect);

      for (int i = 0; i < 3; i++)
      {
        auto b_asp = std::make_shared<Menu_option_button>(Point3f(x_b + 55 + 30 * i, 163, 1), Vector2f(25, 30), engine, game_info, game_info.get_conf_var(2), i);
        engine.get_game().create_entity(b_asp);
        text = std::make_shared<Text_displayer>(Point3f(x_b + 67.5 + 30 * i, 172, 0), Vector2f(5, 10), game_info, "center",
                                                engine.load_texture("assets/font/font-cyan.png"),
                                                Vector2i(16, 30), lemmings_font_map, ASPECT_STRING[i][0], engine,
                                                "TEXT");
        engine.get_game().create_entity(text);
        text = std::make_shared<Text_displayer>(Point3f(x_b + 67.5 + 30 * i, 186, 0), Vector2f(5, 10), game_info, "center",
                                                engine.load_texture("assets/font/font-cyan.png"),
                                                Vector2i(16, 30), lemmings_font_map, ASPECT_STRING[i][1], engine,
                                                "TEXT");
        engine.get_game().create_entity(text);
      }
      auto b_asp = std::make_shared<Menu_option_button>(Point3f(x_b + 145, 163, 1), Vector2f(40, 30), engine, game_info, game_info.get_conf_var(2), 3);
      engine.get_game().create_entity(b_asp);
      text = std::make_shared<Text_displayer>(Point3f(x_b + 165, 172, 0), Vector2f(5, 10), game_info, "center",
                                              engine.load_texture("assets/font/font-cyan.png"),
                                              Vector2i(16, 30), lemmings_font_map, ASPECT_STRING[3][0], engine,
                                              "TEXT");
      engine.get_game().create_entity(text);
      text = std::make_shared<Text_displayer>(Point3f(x_b + 165, 186, 0), Vector2f(5, 10), game_info, "center",
                                              engine.load_texture("assets/font/font-cyan.png"),
                                              Vector2i(16, 30), lemmings_font_map, ASPECT_STRING[3][1], engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      // Reset de botones del teclado
      auto b_reset = std::make_shared<Menu_button>(Point3f(x_b, 219, 2), Vector2f(80, 80), engine, game_info, keyboard, Utils::BUTTON_TYPE::RESET_KEYB);
      engine.get_game().create_entity(b_reset);

      // Reset de informacion
      auto b_restall = std::make_shared<Menu_button>(Point3f(x_b += 120, 219, 2), Vector2f(80, 80), engine, game_info, keyboard, Utils::BUTTON_TYPE::RESET_ALL);
      engine.get_game().create_entity(b_restall);

      // Boton de guardar, en el centro de la pantalla y abajo
      auto b_save = std::make_shared<Menu_button>(Point3f(10280, 300, 2), Vector2f(80, 80), engine, game_info, keyboard, Utils::BUTTON_TYPE::SAVE);
      engine.get_game().create_entity(b_save);

      // Boton de vuelta al menu
      auto b_back = std::make_shared<Menu_button>(Point3f(10020, 340, 2), Vector2f(70, 37), engine, game_info, keyboard, Utils::BUTTON_TYPE::BACK);
      engine.get_game().create_entity(b_back);

      auto b_ability1 = std::make_shared<Menu_button>(Point3f(x_b += 110, y_b, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_1);
      engine.get_game().create_entity(b_ability1);
      auto dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                      engine.load_texture("assets/font/font-red.png"),
                                                      Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_1 - 9)),
                                                      4, Utils::BUTTON_TYPE::ABILITY_1 - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_ability2 = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_2);
      engine.get_game().create_entity(b_ability2);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_2 - 9)),
                                                 4, Utils::BUTTON_TYPE::ABILITY_2 - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_ability3 = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_3);
      engine.get_game().create_entity(b_ability3);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_3 - 9)),
                                                 4, Utils::BUTTON_TYPE::ABILITY_3 - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_ability4 = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_4);
      engine.get_game().create_entity(b_ability4);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_4 - 9)),
                                                 4, Utils::BUTTON_TYPE::ABILITY_4 - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_ability5 = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_5);
      engine.get_game().create_entity(b_ability5);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_5 - 9)),
                                                 4, Utils::BUTTON_TYPE::ABILITY_5 - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_ability6 = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_6);
      engine.get_game().create_entity(b_ability6);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_6 - 9)),
                                                 4, Utils::BUTTON_TYPE::ABILITY_6 - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_ability7 = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_7);
      engine.get_game().create_entity(b_ability7);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_7 - 9)),
                                                 4, Utils::BUTTON_TYPE::ABILITY_7 - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_ability8 = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_8);
      engine.get_game().create_entity(b_ability8);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_8 - 9)),
                                                 4, Utils::BUTTON_TYPE::ABILITY_8 - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_explode_all = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::EXPLODE_ALL);
      engine.get_game().create_entity(b_explode_all);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::EXPLODE_ALL - 9)),
                                                 4, Utils::BUTTON_TYPE::EXPLODE_ALL - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_ability_up = std::make_shared<Menu_button>(Point3f(x_b += 170, y_b = 55, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_UP);
      engine.get_game().create_entity(b_ability_up);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_UP - 9)),
                                                 4, Utils::BUTTON_TYPE::ABILITY_UP - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_ability_down = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::ABILITY_DOWN);
      engine.get_game().create_entity(b_ability_down);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::ABILITY_DOWN - 9)),
                                                 4, Utils::BUTTON_TYPE::ABILITY_DOWN - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_speed_up = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::SPEED_UP);
      engine.get_game().create_entity(b_speed_up);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::SPEED_UP - 9)),
                                                 4, Utils::BUTTON_TYPE::SPEED_UP - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_speed_down = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::SPEED_DOWN);
      engine.get_game().create_entity(b_speed_down);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::SPEED_DOWN - 9)),
                                                 4, Utils::BUTTON_TYPE::SPEED_DOWN - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_spawn_up = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::SPAWN_UP);
      engine.get_game().create_entity(b_spawn_up);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::SPAWN_UP - 9)),
                                                 4, Utils::BUTTON_TYPE::SPAWN_UP - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_spawn_down = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::SPAWN_DOWN);
      engine.get_game().create_entity(b_spawn_down);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::SPAWN_DOWN - 9)),
                                                 4, Utils::BUTTON_TYPE::SPAWN_DOWN - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_map_left = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::MAP_LEFT);
      engine.get_game().create_entity(b_map_left);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::MAP_LEFT - 9)),
                                                 4, Utils::BUTTON_TYPE::MAP_LEFT - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_map_right = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::MAP_RIGHT);
      engine.get_game().create_entity(b_map_right);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::MAP_RIGHT - 9)),
                                                 4, Utils::BUTTON_TYPE::MAP_RIGHT - 9);
      engine.get_game().create_entity(dynamic_t);

      auto b_pause = std::make_shared<Menu_button>(Point3f(x_b, y_b += i_bot, 2), Vector2f(size_x, size_y), engine, game_info, keyboard, Utils::BUTTON_TYPE::PAUSE);
      engine.get_game().create_entity(b_pause);
      dynamic_t = std::make_shared<Text_dynamic>(Point3f(x_b + i_tx, y_b + 15, 1), Vector2f(16 * size_t, 30 * size_t), engine, game_info, "center",
                                                 engine.load_texture("assets/font/font-red.png"),
                                                 Vector2i(16, 30), lemmings_font_map, KeyBindings().InEvenToCh(game_info.get_conf_buttons(Utils::BUTTON_TYPE::PAUSE - 9)),
                                                 4, Utils::BUTTON_TYPE::PAUSE - 9);
      engine.get_game().create_entity(dynamic_t);
    }
    else if (type == Utils::MENU_TYPE::IA)
    {
      game_info.set_ia(true);
      auto background = std::make_shared<Entity>(Point3f(10000, 0, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_brown.png"), engine, "Background", "Background");
      engine.get_game().create_entity(background);
      int level_map_num = game_info.get_ia() ? game_info.conversion_level_selected_ia() : level;
      std::cout << "Nivel mapa: " << level_map_num << "\n";
      Texture txt = engine.load_texture("assets/maps/raw/map_0_" + std::to_string(level_map_num) + ".png");

      auto map_background = std::make_shared<Map_dynamic>(Point3f(10000, 20, 3), Vector2f(640, 65), engine, game_info, true);
      engine.get_game().create_entity(map_background);
      // mapa 0,0  640,65 : 640px 65px
      auto map = std::make_shared<Map_dynamic>(Point3f(10320 - (txt.get_width() * 65 / (2 * txt.get_height())), 20, 2), Vector2f(txt.get_width() * 65 / txt.get_height(), 65), engine, game_info);
      engine.get_game().create_entity(map);

      // Level (number) // level name

      auto dynamic_text = std::make_shared<Text_dynamic>(Point3f(10320, 120, 2), Vector2f(16, 30), engine, game_info, "center",
                                                         engine.load_texture("assets/font/font-red.png"),
                                                         Vector2i(16, 30), lemmings_font_map, Utils::LEVEL_NAME_IA[game_info.get_difficulty_selected()][game_info.get_level_selected()], 2);
      engine.get_game().create_entity(dynamic_text);

      engine.get_game().create_entity(std::make_shared<Menu_arrow>(Point3f(10255, 165, 2), Vector2f(30, 30), game_info, engine, 0));
      engine.get_game().create_entity(std::make_shared<Menu_arrow>(Point3f(10055, 165, 2), Vector2f(30, 30), game_info, engine, 1));

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10170, 180, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-green.png"),
                                                    Vector2i(16, 30), lemmings_font_map, Utils::DIFFICULTY_NAME_IA[game_info.get_difficulty_selected()], 0);
      engine.get_game().create_entity(dynamic_text);

      engine.get_game().create_entity(std::make_shared<Menu_arrow>(Point3f(10555, 165, 2), Vector2f(30, 30), game_info, engine, 2));
      engine.get_game().create_entity(std::make_shared<Menu_arrow>(Point3f(10355, 165, 2), Vector2f(30, 30), game_info, engine, 3));

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10470, 180, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-green.png"),
                                                    Vector2i(16, 30), lemmings_font_map, std::to_string(game_info.get_level_selected()), 1);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10170, 235, 2), Vector2f(8, 15), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-blue.png"),
                                                    Vector2i(16, 30), lemmings_font_map, "Saved Lemmings", 7);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10050, 10, 2), Vector2f(8, 15), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-blue.png"),
                                                    Vector2i(16, 30), lemmings_font_map, "Autoplay", 7);

      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10470, 235, 2), Vector2f(8, 15), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-blue.png"),
                                                    Vector2i(16, 30), lemmings_font_map, "Time", 7);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10170, 265, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-blue.png"),
                                                    Vector2i(16, 30), lemmings_font_map, game_info.get_selected_level_best_perc(), 5);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10470, 265, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-blue.png"),
                                                    Vector2i(16, 30), lemmings_font_map, game_info.get_selected_level_best_time(), 6);
      engine.get_game().create_entity(dynamic_text);

      dynamic_text = std::make_shared<Text_dynamic>(Point3f(10320, 250, 2), Vector2f(16, 30), engine, game_info, "center",
                                                    engine.load_texture("assets/font/font-purple.png"),
                                                    Vector2i(16, 30), lemmings_font_map, "Be ready to save those lemmings!", 8);
      engine.get_game().create_entity(dynamic_text);

      // Boton de vuelta al menu
      auto b_back = std::make_shared<Menu_button>(Point3f(10020, 340, 2), Vector2f(70, 37), engine, game_info, keyboard, Utils::BUTTON_TYPE::BACK);
      engine.get_game().create_entity(b_back);

      auto b_play = std::make_shared<Menu_button>(Point3f(10267, 320, 2), Vector2f(105, 55), engine, game_info, keyboard, Utils::BUTTON_TYPE::PLAY);
      engine.get_game().create_entity(b_play);
    }
    else if (type == Utils::MENU_TYPE::RESET_DATA)
    {
      game_info.set_ia(false);
      auto background = std::make_shared<Entity>(Point3f(10000, 0, 3), Vector2f(640, 400), engine.load_texture("assets/menu/background_brown.png"), engine, "Background", "Background");
      engine.get_game().create_entity(background);

      auto text = std::make_shared<Text_displayer>(Point3f(10320, 115, 2), Vector2f(12, 22.5), game_info, "center",
                                                   engine.load_texture("assets/font/font-red.png"),
                                                   Vector2i(16, 30), lemmings_font_map, "You're about to erase all the saved data", engine,
                                                   "TEXT");
      engine.get_game().create_entity(text);
      text = std::make_shared<Text_displayer>(Point3f(10320, 150, 2), Vector2f(12, 22.5), game_info, "center",
                                              engine.load_texture("assets/font/font-red.png"),
                                              Vector2i(16, 30), lemmings_font_map, "If you're sure then press the button below", engine,
                                              "TEXT");
      engine.get_game().create_entity(text);

      // Boton de reset de datos
      auto b_reset = std::make_shared<Menu_button>(Point3f(10280, 215, 2), Vector2f(80, 80), engine, game_info, keyboard, Utils::BUTTON_TYPE::RESET_ALL_CONFIRM);
      engine.get_game().create_entity(b_reset);

      // Boton de vuelta al menu
      auto b_back = std::make_shared<Menu_button>(Point3f(10020, 340, 2), Vector2f(70, 37), engine, game_info, keyboard, Utils::BUTTON_TYPE::BACK_TO_CONFIG);
      engine.get_game().create_entity(b_back);
    }
  }
};