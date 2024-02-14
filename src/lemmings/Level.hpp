#pragma once

#include <memory>

#include "engine/engine.hpp"
#include "Door.hpp"
#include "Gate.hpp"
#include "Liquid.hpp"
#include "Fire.hpp"
#include "Flamethrower.hpp"
#include "Spinner.hpp"
#include "Chain.hpp"
#include "HUDs.hpp"
#include "Level_info.hpp"
// Incluir otros archivos necesarios

class Level
{
private:
  std::string basic_path = "assets/maps/bkg/map_0_";
  Texture txt;
  HUDs hud;
  float size_map_x = 0;
  Level_info &level_info;

public:
  Level(Engine &engine, int levelNumber, Level_info &sharedLevelInfo) : hud(engine, sharedLevelInfo), level_info(sharedLevelInfo)
  {
    setupLevel(engine, levelNumber);
  }

private:
  void setupLevel(Engine &engine, int levelNumber)
  {
    txt = engine.load_texture(basic_path + std::to_string(levelNumber) + ".png");
    size_map_x = (0.713 / txt.get_height()) * txt.get_width();
    switch (levelNumber)
    {
    case 0:
    {
      auto map = std::make_shared<Entity>(Point3f(0, 0.35, 20), Vector2f(1, 0.25), txt, "MAP");
      auto map1 = std::make_shared<Entity>(Point3f(0, 0.2, 20), Vector2f(0.1, 0.25), txt, "MAP");
      auto map2 = std::make_shared<Entity>(Point3f(0.9, 0.2, 20), Vector2f(0.1, 0.25), txt, "MAP");
      auto map3 = std::make_shared<Entity>(Point3f(0.45, 0.2, 20), Vector2f(0.1, 0.25), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.5, 0.0, 21), (0.713f / txt.get_height()) / 2, engine, 1, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(0.8, 0.25, 21), (0.713f / txt.get_height()) / 2, engine, 1, 0.8f, level_info);
      auto liquid = std::make_shared<Liquid>(Point3f(0.4, 0.3, 19), (0.713f / txt.get_height()) / 2, engine, 1, 0.8f, level_info);
      auto fire = std::make_shared<Fire>(Point3f(0.4, 0.3, 19), (0.713f / txt.get_height()) / 2, engine, 0.8f, level_info);
      auto flamethrower = std::make_shared<Flamethrower>(Point3f(0.34, 0.68, 19), (0.713f / txt.get_height()) / 2, engine, false, 0.8f, level_info);
      auto spinner = std::make_shared<Spinner>(Point3f(0.4, 0.3, 19), (0.713f / txt.get_height()) / 2, engine, 0.8f, level_info);
      auto chain = std::make_shared<Chain>(Point3f(0.4, 0.26, 19), (0.713f / txt.get_height()) / 2, engine, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(map1);
      engine.get_game()->create_entity(map2);
      engine.get_game()->create_entity(map3);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      // engine.get_game()->create_entity(liquid);
      // engine.get_game()->create_entity(fire);
      // engine.get_game()->create_entity(flamethrower);
      // engine.get_game()->create_entity(spinner);
      engine.get_game()->create_entity(chain);
      break;
    }
    case 1:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.239501, 0.17319, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(0.890375, 0.379335, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 2:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.133339, 0.0629796, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(0.952723, 0.451196, 21), (0.713f / txt.get_height()), engine, 1, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 3:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.134475, 0.036891, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(0.0641581, 0.467688, 21), (0.713f / txt.get_height()), engine, 1, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 4:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.106264, 0.0684061, 21), (0.713f / txt.get_height()), engine, 4, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(0.818949, 0.00138562, 21), (0.713f / txt.get_height()), engine, 3, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 5:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.83787, 0.139829, 21), (0.713f / txt.get_height()), engine, 2, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(1.28679, 0.370999, 21), (0.713f / txt.get_height()), engine, 2, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 6:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.195214, 0.100042, 21), (0.713f / txt.get_height()), engine, 0, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(0.863883, 0.251191, 21), (0.713f / txt.get_height()), engine, 4, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 7:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.907686, 0.351528, 21), (0.713f / txt.get_height()), engine, 4, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(1.54319, 0.21605, 21), (0.713f / txt.get_height()), engine, 3, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 8:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.513304, 0.173287, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(-0.654648, 0.237958, 21), (0.713f / txt.get_height()), engine, 1, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 9:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.0780902, 0.371627, 21), (0.713f / txt.get_height()), engine, 4, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(0.730791, 0.339278, 21), (0.713f / txt.get_height()), engine, 3, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 10:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.409338, 0.0352269, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(0.127995, 0.432631, 21), (0.713f / txt.get_height()), engine, 1, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 11:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.11019, 0.338112, 21), (0.713f / txt.get_height()), engine, 4, 1.0f, 15, 1.0f, level_info);
      auto gate = std::make_shared<Gate>(Point3f(0.963747, 0.392647, 21), (0.713f / txt.get_height()), engine, 3, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 12:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 13:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 14:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 15:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 16:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 17:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 18:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 19:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 20:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 21:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 22:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 23:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 24:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 25:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 26:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 27:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 28:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 29:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 30:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2) + 0.5, 0.018, 20), Vector2f(size_map_x, 0.713), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), (0.713f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, level_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), (0.713f / txt.get_height()), engine, 0, 0.8f, level_info);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    // Agregar casos para otros niveles
    default:
      // Manejar nivel desconocido o cargar un nivel por defecto
      break;
    }
  }
};
