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
// Incluir otros archivos necesarios

class Level
{
private:
  std::string basic_path = "assets/maps/bkg/map_0_";
  Texture txt;
  float size_map_x = 0;

public:
  Level(Engine &engine, int levelNumber)
  {
    setupLevel(engine, levelNumber);
  }

private:
  void setupLevel(Engine &engine, int levelNumber)
  {
    txt = engine.load_texture(basic_path + std::to_string(levelNumber) + ".png");
    size_map_x = (0.8 / txt.get_height()) * txt.get_width();
    switch (levelNumber)
    {
    case 0:
    {
      auto map = std::make_shared<Entity>(Point3f(0, 0.75, 1), Vector2f(1, 0.25), txt, "MAP");
      auto map1 = std::make_shared<Entity>(Point3f(0, 0.6, 1), Vector2f(0.1, 0.25), txt, "MAP");
      auto map2 = std::make_shared<Entity>(Point3f(0.9, 0.6, 1), Vector2f(0.1, 0.25), txt, "MAP");
      auto map3 = std::make_shared<Entity>(Point3f(0.45, 0.6, 1), Vector2f(0.1, 0.25), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(0.2, 0.5, 1), (0.8f / txt.get_height()) / 2, engine, 1, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.8, 0.65, 1), (0.8f / txt.get_height()) / 2, engine, 1, 0.8f);
      auto liquid = std::make_shared<Liquid>(Point3f(0.4, 0.7, 1), (0.8f / txt.get_height()) / 2, engine, 1, 0.8f);
      auto fire = std::make_shared<Fire>(Point3f(0.4, 0.7, 1), (0.8f / txt.get_height()) / 2, engine, 0.8f);
      auto flamethrower = std::make_shared<Flamethrower>(Point3f(0.34, 0.68, 1), (0.8f / txt.get_height()) / 2, engine, false, 0.8f);
      auto spinner = std::make_shared<Spinner>(Point3f(0.4, 0.7, 1), (0.8f / txt.get_height()) / 2, engine, 0.8f);
      auto chain = std::make_shared<Chain>(Point3f(0.4, 0.66, 1), (0.8f / txt.get_height()) / 2, engine, 0.8f);

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
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 2:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.694457, 0.0447037, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.50631, 0.486225, 2), (0.8f / txt.get_height()), engine, 1, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 3:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.399963, 0.0235361, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(-0.483425, 0.506176, 2), (0.8f / txt.get_height()), engine, 1, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 4:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f, true);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 5:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 6:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 7:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 8:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 9:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 10:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 11:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 12:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 13:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 14:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 15:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 16:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 17:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 18:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 19:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 20:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 21:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 22:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 23:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 24:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 25:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 26:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 27:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 28:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 29:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

      engine.get_game()->create_entity(map);
      engine.get_game()->create_entity(door);
      engine.get_game()->create_entity(gate);
      break;
    }
    case 30:
    {
      auto map = std::make_shared<Entity>(Point3f(-(size_map_x / 2), 0, 1), Vector2f(size_map_x, 0.8), txt, "MAP");
      auto door = std::make_shared<Door>(Point3f(-0.295, 0.18, 0), (0.8f / txt.get_height()), engine, 8, 1.0f, 15, 1.0f);
      auto gate = std::make_shared<Gate>(Point3f(0.436, 0.406, 2), (0.8f / txt.get_height()), engine, 0, 0.8f);

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
