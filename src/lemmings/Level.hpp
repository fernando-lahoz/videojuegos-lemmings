#pragma once

#include <memory>

#include "engine/engine.hpp"

// structure includes
#include "lemmings/structure/Door.hpp"
#include "lemmings/structure/Gate.hpp"
#include "lemmings/structure/Liquid.hpp"
#include "lemmings/structure/Fire.hpp"
#include "lemmings/structure/Flamethrower.hpp"
#include "lemmings/structure/Spinner.hpp"
#include "lemmings/structure/Chain.hpp"
#include "lemmings/structure/Brick.hpp"
#include "lemmings/structure/Directional_wall.hpp"
#include "lemmings/hud/HUDs.hpp"

#include "lemmings/Game_info.hpp"

class Level
{
private:
  HUDs hud;
  std::string basic_path = "assets/maps/bkg/map_0_";
  Texture txt;
  float size_map_x = 0;
  Game_info &game_info;

public:
  Level(Game_info &_game_info) : hud(_game_info), game_info(_game_info)
  {
  }

  void setup_level(Engine &engine, int levelNumber)
  {
    hud.setupElements(engine);
    game_info.start_game_info(levelNumber);
    txt = engine.load_texture(basic_path + std::to_string(levelNumber) + ".png");
    size_map_x = (0.713 / txt.get_height()) * txt.get_width();

    engine.get_game().create_entity(std::make_shared<Entity>(Point3f(0, 0, 100), Vector2f(3168, 320), engine.load_texture("assets/maps/background.png"), "BACKGROUND"));
    switch (levelNumber)
    {
    case 0:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(0, 160, 2), Vector2f(3168, 160), txt, "MAP");
      auto map1 = std::make_shared<Rigid_body>(Point3f(0, 80, 2), Vector2f(40, 80), txt, "MAP");
      auto map2 = std::make_shared<Rigid_body>(Point3f(400, 80, 2), Vector2f(40, 80), txt, "MAP");
      auto map3 = std::make_shared<Rigid_body>(Point3f(800, 80, 2), Vector2f(40, 80), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(420, 20, 4), engine, 1, 1.0f, levelNumber, game_info);
      // auto gate = std::make_shared<Gate>(Point3f(0.8, 0.25, 21), (0.713f / txt.get_height()) / 2, engine, 1, 0.8f, game_info);

      // auto liquid = std::make_shared<Liquid>(Point3f(0.4, 0.3, 19), (0.713f / txt.get_height()) / 2, engine, 1, 0.8f, game_info);
      // auto fire = std::make_shared<Fire>(Point3f(0.4, 0.3, 19), (0.713f / txt.get_height()) / 2, engine, 0.8f, game_info);
      // auto flamethrower = std::make_shared<Flamethrower>(Point3f(0.34, 0.68, 19), (0.713f / txt.get_height()) / 2, engine, false, 0.8f, game_info);
      // auto spinner = std::make_shared<Spinner>(Point3f(0.4, 0.3, 19), (0.713f / txt.get_height()) / 2, engine, 0.8f, game_info);
      auto chain = std::make_shared<Chain>(Point3f(0.4, 0.26, 4), engine, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(map1);
      engine.get_game().create_entity(map2);
      engine.get_game().create_entity(map3);
      engine.get_game().create_entity(door);
      // engine.get_game().create_entity(gate);

      // engine.get_game().create_entity(liquid);
      // engine.get_game().create_entity(fire);
      // engine.get_game().create_entity(flamethrower);
      // engine.get_game().create_entity(spinner);
      engine.get_game().create_entity(chain);
      break;
    }
    case 1:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1462.7, 73.5361, 4), engine, 8, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1756.88, 162.742, 4), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 2:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1302.94, 16.5413, 4), engine, 5, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1786.83, 194.386, 4), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 3:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1422.52, 9.87284, 4), engine, 5, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1394.18, 202.782, 4), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 4:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 3), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1403.21, 23.9217, 4), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1728.38, -8.13497, 4), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 0), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(levelNumber) + "_2.png"), "MAP"));

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1022, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1213, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1404, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1595, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1786, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));

      break;
    }
    case 5:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 0), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(987.409, 54.0332, 4), engine, 2, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1935.42, 158.481, 4), engine, 2, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1294, 262, 1), 1, engine, 0, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(913, 262, 1), 1, engine, 0, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1167, 262, -1), 1, engine, 0, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1040, 262, -1), 1, engine, 0, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1005, 249, 2), 1, engine, 0, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133, 249, 2), 1, engine, 0, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 249, 2), 1, engine, 0, 0.4f, game_info));
      break;
    }
    case 6:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 1), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1273.93, 43.2726, 4), engine, 3, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1746.58, 104.385, 4), engine, 4, 0.3f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1008, 260.04, 2), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1136, 260.04, 2), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1264, 260.04, 2), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1392, 260.04, 2), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1520, 260.04, 2), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1648, 260.04, 2), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1776, 260.04, 2), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1904, 260.04, 2), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2032, 260.04, 2), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1383, 42.5304, 2), engine, false, 0.5f, game_info));
      break;
    }
    case 7:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 1), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(965.748, 158.484, 4), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(2050.54, 88.5411, 4), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(547, 251, 2), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(738, 251, 2), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2143, 251, 2), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2334, 251, 2), 1.5, engine, 2, 0.4f, game_info));
      break;
    }
    case 8:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1129.81, 73.1607, 4), engine, 5, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1064.45, 98.347, 4), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 1), 1, engine, 1, 0.4f, game_info));
      break;
    }
    case 9:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 0), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1395.32, 160.534, 4), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1688.35, 144.29, 4), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(levelNumber) + "_2.png"), "MAP"));

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1364.93, 216.646, 4), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1554.78, 96.8136, 4), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1780.91, 216.646, 4), engine, 0.8f, game_info));

      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1293, 251, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1484, 251, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1675, 251, 1), 1.5, engine, 2, 0.4f, game_info));

      break;
    }
    case 10:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 0), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1544.38, 8.23047, 4), engine, 5, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1415.92, 186.71, 4), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(levelNumber) + "_2.png"), "MAP"));

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 271, 1), 1, engine, 1, 0.4f, game_info, true));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 271, 1), 1, engine, 1, 0.4f, game_info));
      break;
    }
    case 11:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1307.35, 146.715, 4), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1790.87, 168.578, 4), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1416.76, 112.478, 3), Vector2f(192, 160), engine, 0, game_info, true));

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 12:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1276.3, 157.29, 4), engine, 5, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1814.94, 138.479, 4), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 13:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(736.777, 24.0139, 4), engine, 3, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1947.22, 136.837, 4), engine, 4, 0.3f, game_info);

      engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 0), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(levelNumber) + "_2.png"), "MAP"));

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(496, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(623.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(878.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1006, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1388.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1516, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1643.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1771, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1898.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2026, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2153.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2281, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2408.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2536, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2663.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2791, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2918.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3046, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3173.5, 260.04, 1), 1, engine, 3, 0.4f, game_info));
      break;
    }
    case 14:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 0), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(814.29, 28.0416, 4), engine, 5, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(2323.65, 105.015, 4), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(667.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(795, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(922.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1050, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1177.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1305, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1432.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1560, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1687.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1815, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1942.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2070, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2197.5, 271, 1), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2325, 271, 1), 1, engine, 1, 0.4f, game_info));
      break;
    }
    case 15:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(442.924, 29.0666, 4), engine, 5, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(2617.62, 22.738, 4), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Chain>(Point3f(2450, 215, 1), engine, 0.8f, game_info));

      break;
    }
    case 16:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1203.84, 192.863, 4), engine, 3, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1873.84, 32.5396, 4), engine, 4, 0.3f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(880, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1008, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1136, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1264, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1392, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1520, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1648, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1776, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1904, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2032, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2160, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      break;
    }
    case 17:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1632.93, 71.9481, 4), engine, 4, 1.0f, levelNumber, game_info);
      engine.get_game().create_entity(door);
      door = std::make_shared<Door>(Point3f(1503.39, 71.9481, 4), engine, 4, 1.0f, levelNumber, game_info);
      engine.get_game().create_entity(door);
      door = std::make_shared<Door>(Point3f(1375.35, 71.9481, 4), engine, 4, 1.0f, levelNumber, game_info);
      engine.get_game().create_entity(door);
      door = std::make_shared<Door>(Point3f(1248.95, 71.9481, 4), engine, 4, 1.0f, levelNumber, game_info);

      auto gate = std::make_shared<Gate>(Point3f(1890.52, 167.937, 4), engine, 3, 0.8f, game_info);

      // CHOF

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 18:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1087.03, 2.41112, 4), engine, 3, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(2014.15, 174.778, 4), engine, 4, 0.3f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1339.32, 72.5155, 1), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1595.02, 72.5155, 1), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1404.91, 128.087, 1), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1633.2, 168.015, 1), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1403.21, 207.771, 1), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1595.22, 255.926, 1), engine, 0.8f, game_info));

      break;
    }
    case 19:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(941.84, 154.104, 4), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(2860.95, 64.5198, 4), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 20:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1275.41, 65.2479, 4), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1953.04, 105.043, 4), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 0), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(levelNumber) + "_2.png"), "MAP"));

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1239.94, 201.736, 4), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(942, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1324, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1515, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1706, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1897, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2088, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2279, 250.847, 1), 1.5, engine, 2, 0.4f, game_info));
      break;
    }
    case 21:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(549.387, 85.5787, 4), engine, 8, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(2537.51, 170.078, 4), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);

      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(578.884, 263.607, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1025.9, 263.607, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2335.95, 263.607, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2463.9, 263.607, 3), 1, engine, 1, 0.4f, game_info, true));
      break;
    }
    case 22:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(696.153, 160.226, 4), engine, 8, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(2171.01, 34.7064, 4), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 23:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1254.74, 134.628, 4), engine, 3, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(0.0158057, 8.93832, 4), engine, 4, 0.3f, game_info);
      engine.get_game().create_entity(gate);
      gate = std::make_shared<Gate>(Point3f(0.0158057, 184.844, 4), engine, 4, 0.3f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1521.51, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      break;
    }
    case 24:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1275.02, 4.23079, 4), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1822.42, 184.225, 4), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      // CHOF
      engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1462.52, 92, 3), Vector2f(64, 52), engine, 1, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1653.98, 114.874, 3), 1, engine, 2, 0.4f, game_info));
      break;
    }
    case 25:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1176.41, 200.15, 4), engine, 2, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1874.37, 206.627, 1), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 26:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1628.52, 18.1654, 4), engine, 5, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(2167.66, 90.55, 4), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);

      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 3), 1, engine, 1, 0.4f, game_info));

      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2197.5, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2325, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2452.5, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2580, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2707.5, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2835, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2952.5, 261, 3), 1, engine, 1, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3090, 261, 3), 1, engine, 1, 0.4f, game_info));

      engine.get_game().create_entity(std::make_shared<Chain>(Point3f(2352.1, 90.7265, 1), engine, 0.8f, game_info, true));

      break;
    }
    case 27:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1302.33, 72.6464, 4), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1657.57, 200.037, 4), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(-13, 250.847, 3), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(178, 250.847, 3), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(369, 250.847, 3), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(560, 250.847, 3), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 250.847, 3), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(942, 250.847, 3), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133, 250.847, 3), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1967, 250.847, 3), 1.5, engine, 2, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2158, 250.847, 3), 1.5, engine, 2, 0.4f, game_info));
      break;
    }
    case 28:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1732.57, 6.88284, 4), engine, 3, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1122.54, 24.2606, 4), engine, 4, 0.3f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1303, 98, 2), engine, false, 0.5f, game_info));
      engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1536, 98, 2), engine, true, 0.5f, game_info));

      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(768, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(896, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1024, 260.04, 3), 1, engine, 3, 0.4f, game_info));

      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1859, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1987, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2115, 260.04, 3), 1, engine, 3, 0.4f, game_info));

      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1408.5, 176, 1), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1504.5, 176, 1), engine, 0.8f, game_info));
      break;
    }
    case 29:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1976.31, 117.534, 4), engine, 5, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(859.625, 20.6917, 4), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);

      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1969.5, 261, 3), 1, engine, 1, 0.4f, game_info, true));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2097, 261, 3), 1, engine, 1, 0.4f, game_info));
      break;
    }
    case 30:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 2), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1533.2, 23.0913, 4), engine, 3, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1430.89, 192.7, 4), engine, 4, 0.3f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);

      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(-5, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(122.5, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(250, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(377.5, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(505, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(632.5, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(760, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(887.5, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1015, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1142.5, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1270, 260.04, 3), 1, engine, 3, 0.4f, game_info));

      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1571.64, 260.04, 3), 1, engine, 3, 0.4f, game_info));
      engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1699.64, 260.04, 3), 1, engine, 3, 0.4f, game_info));

      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1328, 65, 1), engine, 0.8f, game_info));
      engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1235, 224.75, 1), engine, 0.8f, game_info));
      break;
    }
    default:
      break;
    }
  }
};
