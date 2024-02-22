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
    switch (levelNumber)
    {
    case 0:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(0, 160, 20), Vector2f(3168, 160), txt, "MAP");
      auto map1 = std::make_shared<Entity>(Point3f(0, 80, 20), Vector2f(40, 80), txt, "MAP");
      auto map2 = std::make_shared<Entity>(Point3f(400, 80, 20), Vector2f(40, 80), txt, "MAP");
      auto map3 = std::make_shared<Entity>(Point3f(800, 80, 20), Vector2f(40, 80), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(420, 20, 21), engine, 1, 1.0f, levelNumber, game_info);
      // auto gate = std::make_shared<Gate>(Point3f(0.8, 0.25, 21), (0.713f / txt.get_height()) / 2, engine, 1, 0.8f, game_info);

      // auto liquid = std::make_shared<Liquid>(Point3f(0.4, 0.3, 19), (0.713f / txt.get_height()) / 2, engine, 1, 0.8f, game_info);
      // auto fire = std::make_shared<Fire>(Point3f(0.4, 0.3, 19), (0.713f / txt.get_height()) / 2, engine, 0.8f, game_info);
      // auto flamethrower = std::make_shared<Flamethrower>(Point3f(0.34, 0.68, 19), (0.713f / txt.get_height()) / 2, engine, false, 0.8f, game_info);
      // auto spinner = std::make_shared<Spinner>(Point3f(0.4, 0.3, 19), (0.713f / txt.get_height()) / 2, engine, 0.8f, game_info);
      auto chain = std::make_shared<Chain>(Point3f(0.4, 0.26, 19), engine, 0.8f, game_info);

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
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 18), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(1981.83, 53.4943, 21), engine, 8, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(2258.91, 160.251, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 2:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.133339, 0.0629796, 21), engine, 8, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(0.952723, 0.451196, 21), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 3:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.134475, 0.036891, 21), engine, 8, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(0.0641581, 0.467688, 21), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 4:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.106264, 0.0684061, 21), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(0.818949, 0.00138562, 21), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 5:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.83787, 0.139829, 21), engine, 2, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1.28679, 0.370999, 21), engine, 2, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 6:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.195214, 0.100042, 21), engine, 0, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(0.863883, 0.251191, 21), engine, 4, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 7:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.907686, 0.351528, 21), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(1.54319, 0.21605, 21), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 8:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.513304, 0.173287, 21), engine, 8, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(-0.654648, 0.237958, 21), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 9:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.0780902, 0.371627, 21), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(0.730791, 0.339278, 21), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 10:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.409338, 0.0352269, 21), engine, 8, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(0.127995, 0.432631, 21), engine, 1, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 11:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.11019, 0.338112, 21), engine, 4, 1.0f, levelNumber, game_info);
      auto gate = std::make_shared<Gate>(Point3f(0.963747, 0.392647, 21), engine, 3, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 12:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 13:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 14:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 15:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 16:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 17:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 18:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 19:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 20:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 21:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 22:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 23:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 24:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 25:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 26:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 27:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 28:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 29:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    case 30:
    {
      auto map = std::make_shared<Rigid_body>(Point3f(-(size_map_x / 2) + 3168 / 2, 0, 20), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 21), engine, 8, 1.0f, levelNumber, game_info, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 21), engine, 0, 0.8f, game_info);

      engine.get_game().create_entity(map);
      engine.get_game().create_entity(door);
      engine.get_game().create_entity(gate);
      break;
    }
    // Agregar casos para otros niveles
    default:
      // Manejar nivel desconocido o cargar un nivel por defecto
      break;
    }
  }
};
