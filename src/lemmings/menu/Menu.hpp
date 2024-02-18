#pragma once

#include "engine/engine.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/menu/Menu_button.hpp"
#include "lemmings/utils.hpp"

class Menu
{
private:
  Game_info &game_info;

public:
  Menu(Game_info &_game_info) : game_info(_game_info)
  {
  }

  void setup_menu(Engine &engine, int type, int level)
  {
    auto background = std::make_shared<Entity>(Point3f(0, 0, 3), Vector2f(1, 1), engine.load_texture("assets/menu/background.png"), "Background");
    engine.get_game()->create_entity(background);
    if (type == Utils::TITLE)
    {
      auto title = std::make_shared<Entity>(Point3f(0.05, 0.1, 2), Vector2f(0.9, 0.1464454976), engine.load_texture("assets/menu/title.png"), "Title");
      engine.get_game()->create_entity(title);

      auto button1 = std::make_shared<Menu_button>(Point3f(0.1013333, 0.35, 2), Vector2f(0.348, 0.2), engine, game_info, Utils::BUTTON_TYPE::PLAYER_SOLO);
      engine.get_game()->create_entity(button1);

      auto button2 = std::make_shared<Menu_button>(Point3f(0.55066666, 0.35, 2), Vector2f(0.348, 0.2), engine, game_info, Utils::BUTTON_TYPE::PLAYER_VS_IA);
      engine.get_game()->create_entity(button2);

      auto button3 = std::make_shared<Menu_button>(Point3f(0.1013333, 0.65, 2), Vector2f(0.348, 0.2), engine, game_info, Utils::BUTTON_TYPE::SOUND_EFFECTS, true);
      engine.get_game()->create_entity(button3);

      auto button4 = std::make_shared<Menu_button>(Point3f(0.55066666, 0.65, 2), Vector2f(0.348, 0.2), engine, game_info, Utils::BUTTON_TYPE::EXIT);
      engine.get_game()->create_entity(button4);
    }
    else if (type == Utils::LEVEL_SELECTOR)
    {
      // auto button1 = std::make_shared<Menu_button>(Point3f(0.1, 0.4, 2), Vector2f(0.348, 0.2), engine, game_info, Utils::BUTTON_TYPE::PLAYER_SOLO);
      // engine.get_game()->create_entity(button1);

      // auto button2 = std::make_shared<Menu_button>(Point3f(0.6, 0.4, 2), Vector2f(0.348, 0.2), engine, game_info, Utils::BUTTON_TYPE::PLAYER_VS_IA);
      // engine.get_game()->create_entity(button2);

      auto button3 = std::make_shared<Menu_button>(Point3f(0.1, 0.7, 2), Vector2f(0.348, 0.2), engine, game_info, Utils::BUTTON_TYPE::SOUND_EFFECTS, true);
      engine.get_game()->create_entity(button3);

      auto button4 = std::make_shared<Menu_button>(Point3f(0.6, 0.7, 2), Vector2f(0.348, 0.2), engine, game_info, Utils::BUTTON_TYPE::EXIT);
      engine.get_game()->create_entity(button4);
    }
    else if (type == Utils::LEVEL_INTRO)
    {
      // level info
    }
    else if (type == Utils::LEVEL_OUTRO)
    {
      // level results
    }
  }
};