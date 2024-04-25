#pragma once

#include <memory>

#include "engine/engine.hpp"
#include "engine/trigger.hpp"

#include "lemmings/structure/Door.hpp"
#include "lemmings/structure/Gate.hpp"
#include "lemmings/structure/Liquid.hpp"
#include "lemmings/structure/Fire.hpp"
#include "lemmings/structure/Flamethrower.hpp"
#include "lemmings/structure/Spinner.hpp"
#include "lemmings/structure/Chain.hpp"
#include "lemmings/structure/Brick.hpp"
#include "lemmings/structure/Directional_wall.hpp"
#include "lemmings/structure/Liquid_trigger.hpp"
#include "lemmings/structure/Ball_zapper.hpp"
#include "lemmings/structure/Pin.hpp"
#include "lemmings/structure/Thumper.hpp"
#include "lemmings/structure/Antimatter_beam.hpp"
#include "lemmings/hud/HUDs.hpp"

#include "lemmings/Game_info.hpp"

class Level
{
private:
  HUDs hud;
  std::string basic_path = "assets/maps/bkg/map_";
  Texture txt;
  float size_map_x = 0;
  Game_info &game_info;

public:
  Level(Game_info &_game_info) : hud(_game_info), game_info(_game_info)
  {
  }

  void update_sounds()
  {
  }

  void setup_level(Engine &engine, int level_number, int difficulty_number = 0)
  {
    hud.setupElements(engine);
    game_info.start_game_info(level_number, difficulty_number);
    txt = engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + ".png");
    size_map_x = (0.713 / txt.get_height()) * txt.get_width();

    engine.get_game().on_level_startup(difficulty_number, level_number);

    engine.get_game().create_entity(std::make_shared<Entity>(Point3f(0, 0, 1000), Vector2f(3168, 320), engine.load_texture("assets/maps/background_" + std::to_string(Utils::LEVEL_BACKGROUND_TYPE[difficulty_number][level_number]) + ".png"), engine, "BACKGROUND"));
    auto gate_type = Utils::LEVEL_GATE_TYPE[difficulty_number][level_number];
    engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), txt, engine, "MAP", "BkgMap"));
    engine.get_game().create_entity(std::make_shared<Door>(Utils::LEVEL_DOOR_POSITION[difficulty_number][level_number], engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
    engine.get_game().create_entity(std::make_shared<Gate>(Utils::LEVEL_GATE_POSITION[difficulty_number][level_number], engine, gate_type, Utils::LEVEL_GATE_TIME_ANIMATION[gate_type], game_info));
    switch (difficulty_number)
    {
    case 0:
      switch (level_number)
      {
      case 0:
      {
        auto map = std::make_shared<Rigid_body>(Point3f(0, 160, 300), Vector2f(3168, 160), txt, engine, "MAP");
        auto map1 = std::make_shared<Rigid_body>(Point3f(0, 80, 300), Vector2f(40, 80), txt, engine, "MAP");
        auto map2 = std::make_shared<Rigid_body>(Point3f(400, 80, 300), Vector2f(40, 80), txt, engine, "MAP");
        auto map3 = std::make_shared<Rigid_body>(Point3f(800, 80, 300), Vector2f(40, 80), txt, engine, "MAP");
        auto chain = std::make_shared<Chain>(Point3f(0.4, 0.26, 400), engine, 1.5f, game_info);

        engine.get_game().create_entity(map);
        engine.get_game().create_entity(map1);
        engine.get_game().create_entity(map2);
        engine.get_game().create_entity(map3);
        engine.get_game().create_entity(chain);
        break;
      }
      case 1:
      {
        break;
      }
      case 2:
      {
        break;
      }
      case 3:
      {
        break;
      }
      case 4:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 0), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1022, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1213, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1404, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1595, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1786, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1096, 292.847, 100), Vector2f(876, 29), engine));

        break;
      }
      case 5:
      {
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1294, 262, 301), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(913, 262, 301), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1167, 262, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1040, 262, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1005, 249, 302), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133, 249, 302), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 249, 302), 1, engine, 0, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(995, 289.847, 100), Vector2f(359, 30), engine));

        break;
      }
      case 6:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1008, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1136, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1264, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1392, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1520, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1648, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1776, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1904, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2032, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1003, 301.847, 100), Vector2f(1164, 24), engine));

        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1383, 42.5304, 301), engine, false, 0.5f, game_info));
        break;
      }
      case 7:
      {
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(547, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(738, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2143, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2334, 251, 301), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(642, 291.847, 100), Vector2f(246, 29), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(2243, 291.847, 100), Vector2f(246, 29), engine));
        break;
      }
      case 8:
      {
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(3181, 24), engine));
        break;
      }
      case 9:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 302), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1364.93, 216.646, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1554.78, 96.8136, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1780.91, 216.646, 303), engine, 0.8f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1293, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1484, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1675, 251, 301), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1301, 294.847, 100), Vector2f(568, 29), engine));

        break;
      }
      case 10:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 302), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 271, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 310.847, 100), Vector2f(1334, 11), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 271, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1736, 310.847, 100), Vector2f(1437, 11), engine));
        break;
      }
      case 11:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1416.76, 112.478, 301), Vector2f(192, 160), engine, 0, game_info));

        break;
      }
      case 12:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        break;
      }
      case 13:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(496, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(623.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(878.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1006, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1388.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1516, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1643.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1771, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1898.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2026, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2153.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2281, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2408.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2536, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2663.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2791, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2918.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3046, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3173.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(508, 301.847, 100), Vector2f(2664, 24), engine));
        break;
      }
      case 14:
      {
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(667.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(795, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(922.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1050, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1177.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1305, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1432.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1560, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1687.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1815, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1942.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2070, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2197.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2325, 271, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(733, 309.847, 100), Vector2f(1696, 12), engine));
        break;
      }
      case 15:
      {
        engine.get_game().create_entity(std::make_shared<Chain>(Point3f(2450, 215, 299), engine, 1.5f, game_info));

        break;
      }
      case 16:
      {
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(880, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1008, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1136, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1264, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1392, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1520, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1648, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1776, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1904, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2032, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2160, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(885, 301.847, 100), Vector2f(1399, 24), engine));
        break;
      }
      case 17:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        auto door = std::make_shared<Door>(Point3f(1503.39, 71.9481, 500), engine, 4, 1.0f, level_number, game_info);
        engine.get_game().create_entity(door);
        door = std::make_shared<Door>(Point3f(1375.35, 71.9481, 500), engine, 4, 1.0f, level_number, game_info);
        engine.get_game().create_entity(door);
        door = std::make_shared<Door>(Point3f(1248.95, 71.9481, 500), engine, 4, 1.0f, level_number, game_info);
        engine.get_game().create_entity(door);
        engine.get_game().create_entity(std::make_shared<Thumper>(Point3f(1258.77, 255, 500), engine, 0.75f, game_info));

        break;
      }
      case 18:
      {
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1339.32, 72.5155, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1595.02, 72.5155, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1404.91, 128.087, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1633.2, 168.015, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1403.21, 207.771, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1595.22, 255.926, 299), engine, 0.8f, game_info));
        break;
      }
      case 19:
      {
        break;
      }
      case 20:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1239.94, 201.736, 301), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(942, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1324, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1515, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1706, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1897, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2088, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2279, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(756, 290.847, 100), Vector2f(1607, 31), engine));
        break;
      }
      case 21:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(578.884, 263.607, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1025.9, 263.607, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2335.95, 263.607, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2463.9, 263.607, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1012, 302.847, 100), Vector2f(114, 21), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(589, 302.847, 100), Vector2f(114, 21), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(2356, 302.847, 100), Vector2f(114, 21), engine));
        break;
      }
      case 22:
      {
        break;
      }
      case 23:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        auto gate = std::make_shared<Gate>(Point3f(0.0158057, 184.844, 500), engine, 4, Utils::LEVEL_GATE_TIME_ANIMATION[gate_type], game_info);

        engine.get_game().create_entity(gate);
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1521.51, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1519, 298.847, 100), Vector2f(131, 24), engine));
        break;
      }
      case 24:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Thumper>(Point3f(1878, 160, 299), engine, 0.75f, game_info));

        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1462.52, 92, 300), Vector2f(64, 52), engine, 1, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1653.98, 114.874, 301), 1, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1636, 142.847, 100), Vector2f(159, 32), engine));
        break;
      }
      case 25:
      {
        break;
      }
      case 26:
      {
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-20, 301.847, 100), Vector2f(1240, 24), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2197.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2325, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2452.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2580, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2707.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2835, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2952.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3090, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(2240, 301.847, 100), Vector2f(1255, 24), engine));

        engine.get_game().create_entity(std::make_shared<Chain>(Point3f(2352.1, 90.7265, 299), engine, 1.5f, game_info));

        break;
      }
      case 27:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(-13, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(178, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(369, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(560, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(942, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1967, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2158, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-10, 290.847, 100), Vector2f(878, 30), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1082, 290.847, 100), Vector2f(268, 30), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1990, 290.847, 100), Vector2f(364, 30), engine));
        break;
      }
      case 28:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1303, 98, 299), engine, false, 0.5f, game_info));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1536, 98, 299), engine, true, 0.5f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(768, 260.04, 301), 1.02, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(896, 260.04, 301), 1.02, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1024, 260.04, 301), 1.02, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(753, 301.847, 100), Vector2f(417, 24), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1859, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1986.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2114, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1850, 301.847, 100), Vector2f(417, 24), engine));

        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1408.5, 176, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1504.5, 176, 299), engine, 0.8f, game_info));
        break;
      }
      case 29:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1969.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2097, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1937, 301.847, 100), Vector2f(323, 24), engine));
        break;
      }
      case 30:
      {
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(-5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(122.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(250, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(377.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(505, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(632.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(760, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(887.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1015, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1142.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1270, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-70, 301.847, 100), Vector2f(1474, 24), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1571.64, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1698, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1552, 301.847, 100), Vector2f(300, 24), engine));

        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1328, 65, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1235, 224.75, 299), engine, 0.8f, game_info));
        break;
      }
      default:
        break;
      }
      break;
    case 1:
      switch (level_number)
      {
      case 0:
        break;
      case 1:
        break;
      case 2:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(496, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(623.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(878.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1006, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1388.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1516, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1643.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1771, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1898.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2026, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2153.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2281, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2408.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2536, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2663.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2791, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2918.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3046, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3173.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(508, 301.847, 100), Vector2f(2664, 24), engine));
        break;
      case 3:
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1432.5, 260.931, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1560, 260.931, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1687.5, 260.931, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1429, 300.847, 100), Vector2f(378, 20), engine));

        break;
      case 4:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1523.34, 32.8401, 300), Vector2f(94, 144), engine, 4, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(3181, 24), engine));
        break;
      case 5:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 0, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(971, 301.847, 100), Vector2f(2200, 24), engine));

        break;
      case 6:
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1144.05, 186.309, 299), engine, true, 0.5f, game_info));
        break;
      case 7:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(3181, 24), engine));
        break;
      case 8:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1388.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1516, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1643.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1771, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1289, 301.847, 100), Vector2f(604, 24), engine));
        break;
      case 9:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-4, 301.847, 100), Vector2f(768, 24), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(2422, 301.847, 100), Vector2f(1000, 24), engine));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(2118.59, 57, 302), Vector2f(78, 74), engine, 2, game_info));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(2101.1, 9, 301), Vector2f(78, 74), engine, 2, game_info));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(2131.5, 10, 303), Vector2f(78, 74), engine, 2, game_info));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(989, 212, 303), Vector2f(87.12, 59.4), engine, 3, game_info));
        break;
      case 10:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(713.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(841, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(968.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1096, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1223.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1351, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1673.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1801, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1928.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2056, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2183.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2311, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(726, 301.847, 100), Vector2f(759, 24), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1690, 301.847, 100), Vector2f(745, 24), engine));

        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1497.16, 281.505, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1597.71, 281.505, 299), engine, 0.8f, game_info));
        break;
      case 11:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1704.29, 260.232, 301), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1829.88, 260.232, 301), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1955.47, 260.232, 301), 1, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1700, 291.847, 100), Vector2f(339, 33), engine));
        break;
      case 12:
        break;
      case 13:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1835, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1962.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2090, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2217.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2345, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2472.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2600, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2727.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2855, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2982.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3110, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(1548, 19), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1839, 301.847, 100), Vector2f(1343, 24), engine));
        break;
      case 14:
        break;
      case 15:
        break;
      case 16:
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1294, 262, 301), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(913, 262, 301), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1167, 262, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1040, 262, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1005, 249, 302), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133, 249, 302), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 249, 302), 1, engine, 0, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(995, 289.847, 100), Vector2f(359, 30), engine));

        break;
      case 17:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1008, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1136, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1264, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1392, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1520, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1648, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1776, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1904, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2032, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1003, 301.847, 100), Vector2f(1164, 24), engine));

        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1383, 42.5304, 301), engine, false, 0.5f, game_info));
        break;
      case 18:
        break;
      case 19:
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(547, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(738, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2143, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2334, 251, 301), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(642, 291.847, 100), Vector2f(246, 29), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(2243, 291.847, 100), Vector2f(246, 29), engine));
        break;
      case 20:
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(891, 272.405, 301), engine, true, 0.5f, game_info));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1607, 105, 303), Vector2f(100, 144), engine, 5, game_info));
        break;
      case 21:

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(3181, 24), engine));
        break;
      case 22:
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(3181, 24), engine));
        break;
      case 23:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        break;
      case 24:
        break;
      case 25:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(555.003, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(682.192, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1597.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1724.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1851.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1978.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2105.5, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(583, 301.847, 100), Vector2f(275, 24), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1724, 301.847, 100), Vector2f(510, 24), engine));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(808.5, 128, 300), Vector2f(68.2, 192), engine, 6, game_info, true));
        engine.get_game().create_entity(std::make_shared<Chain>(Point3f(1972.88, 146.452, 301), engine, 1.5f, game_info));
        break;
      case 26:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1364.93, 216.646, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1554.78, 96.8136, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1780.91, 216.646, 303), engine, 0.8f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1293, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1484, 251, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1675, 251, 301), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1301, 294.847, 100), Vector2f(568, 29), engine));

        break;
      case 27:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(403, 301.847, 100), Vector2f(2481, 24), engine));
        // WALL
        break;
      case 28:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(533, 301.847, 100), Vector2f(2146, 24), engine));
        break;
      case 29:
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(827.273, 78.311, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1027.91, 6.51737, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));

        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(950.237, 231.702, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1337.03, 233.381, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1525.14, 167.872, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1492.57, 15.6003, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1878.81, 153.101, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1944.34, 56.7524, 303), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(2232.34, 144.384, 303), engine, 0.8f, game_info));
        break;
      case 30:
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(667.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(795, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(922.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1050, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1177.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1305, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1432.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1560, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1687.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1815, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1942.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2070, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2197.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2325, 271, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(733, 309.847, 100), Vector2f(1696, 12), engine));
        break;
      default:
        break;
      }
      break;
    case 2:
      switch (level_number)
      {
      case 0:
        break;
      case 1:
        engine.get_game().create_entity(std::make_shared<Chain>(Point3f(2450, 215, 299), engine, 1.5f, game_info));
        break;
      case 2:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1577.51, 72.7012, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1578, 113.847, 100), Vector2f(133, 15), engine));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1782.08, 16.2617, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
        // TONS WEIGHT
        break;
      case 3:
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(880, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1008, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1136, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1264, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1392, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1520, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1648, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1776, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1904, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2032, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2160, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(885, 301.847, 100), Vector2f(1399, 24), engine));
        break;
      case 4:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1626.22, 199.952, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));

        engine.get_game().create_entity(std::make_shared<Chain>(Point3f(1777.46, 214.24, 301), engine, 1.5f, game_info));
        engine.get_game().create_entity(std::make_shared<Pin>(Point3f(1363.65, 142.55, 301), engine, true, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Pin>(Point3f(1392.9, 96.3817, 301), engine, false, 0.8f, game_info));
        break;
      case 5:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Gate>(Point3f(1802.29, 185.353, 500), engine, gate_type, Utils::LEVEL_GATE_TIME_ANIMATION[gate_type], game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1362.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1489.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1616.5, 261, 299), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1453, 301.847, 100), Vector2f(295, 24), engine));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1608.38, 90.0814, 301), engine, true, 0.5f, game_info));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1608.38, 155.169, 301), engine, true, 0.5f, game_info));
        break;
      case 6:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1503.39, 71.9481, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1375.35, 71.9481, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1248.95, 71.9481, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));

        engine.get_game().create_entity(std::make_shared<Thumper>(Point3f(1258.77, 255, 500), engine, 0.75f, game_info));

        break;
      case 7:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1523.34, 32.8401, 300), Vector2f(94, 144), engine, 4, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(3181, 24), engine));
        break;
      case 8:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 0, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(971, 301.847, 100), Vector2f(2200, 24), engine));
        break;
      case 9:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 271, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 310.847, 100), Vector2f(1334, 11), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 271, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 271, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1736, 310.847, 100), Vector2f(1437, 11), engine));
        break;
      case 10:
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1144.05, 186.309, 299), engine, true, 0.5f, game_info));
        break;
      case 11:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(3181, 24), engine));
        break;
      case 12:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1120.18, 90.434, 299), engine, true, 0.5f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1441.5, 80, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1632.5, 40, 299), engine, 0.8f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(3181, 24), engine));
        break;
      case 13:
        // WALL
        // WALL
        break;
      case 14:
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1785, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1912.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2167.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2295, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(3181, 24), engine));
        break;
      case 15:
        break;
      case 16:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        break;
      case 17:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1521.51, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1519, 298.847, 100), Vector2f(131, 24), engine));
        break;
      case 18:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1416.76, 112.478, 301), Vector2f(192, 160), engine, 0, game_info));
        break;
      case 19:
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1339.32, 72.5155, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1595.02, 72.5155, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1404.91, 128.087, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1633.2, 168.015, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1403.21, 207.771, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1595.22, 255.926, 299), engine, 0.8f, game_info));
        break;
      case 20:
        break;
      case 21:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1532.43, 184.795, 299), engine, true, 0.5f, game_info));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1682.5, 184.795, 299), engine, false, 0.5f, game_info));
        break;
      case 22:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(-13, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(178, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(369, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(560, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(942, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1967, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2158, 250.847, 301), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-10, 290.847, 100), Vector2f(878, 30), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1082, 290.847, 100), Vector2f(268, 30), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1990, 290.847, 100), Vector2f(364, 30), engine));
        break;
      case 23:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1388.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1516, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1643.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1771, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1289, 301.847, 100), Vector2f(604, 24), engine));
        break;
      case 24:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1021, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1148, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1913, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2040, 261, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1098, 301.847, 100), Vector2f(299, 24), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1987, 301.847, 100), Vector2f(188, 24), engine));
        break;
      case 25:
        break;
      case 26:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1807.32, 43.5267, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1296.23, 42, 299), engine, true, 0.5f, game_info));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1783.7, 200.889, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1557, 0, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1530, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1657.5, 261, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1398, 301.847, 100), Vector2f(399, 24), engine));
        break;
      case 27:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1068.83, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1195.83, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1322.83, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1449.83, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1576.83, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1703.83, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1830.83, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1957.83, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1053, 301.847, 100), Vector2f(1035, 24), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(927, -26.9015, 305), 1.15, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1074, -26.7963, 305), 1.15, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1221, -26.7963, 305), 1.15, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1368, -26.7963, 305), 1.15, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1515, -26.7963, 305), 1.15, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1662, -26.7963, 305), 1.15, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1809, -26.7963, 305), 1.15, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1956, -26.7963, 305), 1.15, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(926.808, 20.158, 301), 1.2, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(926.808, -6, 303), 1.2, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(969.236, 20.158, 302), 1.2, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(969.236, -6, 304), 1.2, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1889.23, 20.158, 301), 1.2, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1889.23, -6, 303), 1.2, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1948.36, 20.158, 302), 1.2, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1948.36, -6, 304), 1.2, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(913, 21.847, 100), Vector2f(1175, 24), engine));
        break;
      case 28:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(999.562, 261, 302), 1, engine, 0, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1011, 302.847, 100), Vector2f(107, 19), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1792.5, 261, 299), 1.01, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1921.2, 261, 299), 1.01, engine, 0, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2050, 261, 299), 1.01, engine, 0, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1776, 302.847, 100), Vector2f(417, 19), engine));
        engine.get_game().create_entity(std::make_shared<Antimatter_beam>(Point3f(1995.77, 126.242, 299), engine, 0.8f, game_info));
        break;
      case 29:
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1432.5, 260.931, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1560, 260.931, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1687.5, 260.931, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1429, 300.847, 100), Vector2f(378, 20), engine));
        break;
      case 30:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(496, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(623.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(878.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1006, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1388.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1516, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1643.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1771, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1898.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2026, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2153.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2281, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2408.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2536, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2663.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2791, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2918.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3046, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3173.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(508, 301.847, 100), Vector2f(2664, 24), engine));
        break;
      default:
        break;
      }
      break;
    case 3:
      switch (level_number)
      {
      case 0:
        break;
      case 1:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1513, 260.931, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1640, 260.931, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1484, 300.847, 100), Vector2f(308, 20), engine));
        break;
      case 2:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1425.35, 106.158, 299), engine, true, 0.5f, game_info));

        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1713, 287.781, 301), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1778.91, 287.781, 301), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1842.3, 287.781, 301), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1905.61, 287.781, 301), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1968.86, 287.781, 301), engine, 0.8f, game_info));
        break;
      case 3:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Thumper>(Point3f(1878, 160, 299), engine, 0.75f, game_info));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1462.52, 92, 300), Vector2f(64, 52), engine, 1, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1653.98, 114.874, 301), 1, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1636, 142.847, 100), Vector2f(159, 32), engine));
        break;
      case 4:
        break;
      case 5:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1303, 98, 299), engine, false, 0.5f, game_info));
        engine.get_game().create_entity(std::make_shared<Flamethrower>(Point3f(1536, 98, 299), engine, true, 0.5f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(768, 260.04, 301), 1.02, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(896, 260.04, 301), 1.02, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1024, 260.04, 301), 1.02, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(753, 301.847, 100), Vector2f(417, 24), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1859, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1986.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2114, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1850, 301.847, 100), Vector2f(417, 24), engine));

        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1408.5, 176, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1504.5, 176, 299), engine, 0.8f, game_info));
        break;
      case 6:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2422.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2550, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2677.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2805, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2932.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3060, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-4, 301.847, 100), Vector2f(768, 24), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(2422, 301.847, 100), Vector2f(1000, 24), engine));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(2118.59, 57, 302), Vector2f(78, 74), engine, 2, game_info));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(2101.1, 9, 301), Vector2f(78, 74), engine, 2, game_info));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(2131.5, 10, 303), Vector2f(78, 74), engine, 2, game_info));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(989, 212, 303), Vector2f(87.12, 59.4), engine, 3, game_info));
        break;
      case 7:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1239.94, 201.736, 301), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(942, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1324, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1515, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1706, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1897, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2088, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2279, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(756, 290.847, 100), Vector2f(1607, 31), engine));
        break;
      case 8:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1552.5, 105, 301), Vector2f(100, 144), engine, 5, game_info));
        engine.get_game().create_entity(std::make_shared<Directional_wall>(Point3f(1552.5, 8.59163, 302), Vector2f(100, 144), engine, 5, game_info));
        break;
      case 9:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1969.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2097, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1937, 301.847, 100), Vector2f(323, 24), engine));
        break;
      case 10:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Gate>(Point3f(2119.27, 8.37817, 301), engine, gate_type, Utils::LEVEL_GATE_TIME_ANIMATION[gate_type], game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1276.61, 239.939, 301), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1401.53, 239.939, 301), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1636.26, 239.939, 301), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1765.34, 239.939, 301), 1, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1270, 266.847, 100), Vector2f(635, 38), engine));
        break;
      case 11:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(496, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(623.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(751, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(878.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1006, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1133.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1261, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1388.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1516, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1643.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1771, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1898.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2026, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2153.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2281, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2408.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2536, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2663.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2791, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2918.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3046, 260.04, 299), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3173.5, 260.04, 299), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(508, 301.847, 100), Vector2f(2664, 24), engine));
        break;
      case 12:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        break;
      case 13:
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-20, 301.847, 100), Vector2f(1240, 24), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2197.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2325, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2452.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2580, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2707.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2835, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2952.5, 261, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3080, 261, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(2240, 301.847, 100), Vector2f(1255, 24), engine));

        engine.get_game().create_entity(std::make_shared<Chain>(Point3f(2352.1, 90.7265, 299), engine, 1.5f, game_info));
        break;
      case 14:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1281, 190.23, 299), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1406.73, 190.23, 299), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1532.46, 190.23, 299), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1658.19, 190.23, 299), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1783.92, 190.23, 299), 1, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1280, 217.847, 100), Vector2f(589, 38), engine));
        break;
      case 15:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(713.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(841, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(968.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1096, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1223.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1351, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1673.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1801, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1928.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2056, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2183.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2311, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(726, 301.847, 100), Vector2f(759, 24), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1690, 301.847, 100), Vector2f(745, 24), engine));

        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1497.16, 281.505, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1597.71, 281.505, 299), engine, 0.8f, game_info));
        break;
      case 16:
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1257.41, 160.677, 301), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1932.51, 192.433, 301), engine, 0.8f, game_info));
        break;
      case 17:
        break;
      case 18:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1637.88, 0, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1637.88, 216.32, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(1444.5, 216.32, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1249.57, 260.931, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1266, 300.847, 100), Vector2f(114, 20), engine));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1823.08, 260.931, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1813, 300.847, 100), Vector2f(114, 20), engine));
        break;
      case 19:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1704.29, 260.232, 301), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1829.88, 260.232, 301), 1, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1955.47, 260.232, 301), 1, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1700, 291.847, 100), Vector2f(339, 33), engine));
        break;
      case 20:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 0), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_2.png"), engine, "MAP", "BkgMap"));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1022, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1213, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1404, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1595, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1786, 250.847, 299), 1.5, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1096, 292.847, 100), Vector2f(876, 29), engine));
        break;
      case 21:
        break;
      case 22:
        break;
      case 23:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Ball_zapper>(Point3f(1167.3, 0.0333582, 301), engine, 0.8f, game_info));

        break;
      case 24:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(-5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(122.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(250, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(377.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(505, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(632.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(760, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(887.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1015, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1142.5, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1270, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-70, 301.847, 100), Vector2f(1474, 24), engine));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1571.64, 260.04, 301), 1, engine, 3, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1698, 260.04, 301), 1, engine, 3, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1552, 301.847, 100), Vector2f(300, 24), engine));

        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1328, 65, 299), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Fire>(Point3f(1235, 224.75, 299), engine, 0.8f, game_info));
        break;
      case 25:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 298), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(0, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(127.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(255, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(382.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(510, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(637.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(765, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(892.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1020, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1147.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1275, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1402.5, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1835, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1962.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2090, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2217.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2345, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2472.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2600, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2727.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2855, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2982.5, 261, 299), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(3110, 261, 299), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(-3, 301.847, 100), Vector2f(1548, 19), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1839, 301.847, 100), Vector2f(1343, 24), engine));
        break;
      case 26:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(578.884, 263.607, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1025.9, 263.607, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2335.95, 263.607, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(2463.9, 263.607, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1012, 302.847, 100), Vector2f(114, 21), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(589, 302.847, 100), Vector2f(114, 21), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(2356, 302.847, 100), Vector2f(114, 21), engine));
        break;
      case 27:
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1257.41, 160.677, 301), engine, 0.8f, game_info));
        engine.get_game().create_entity(std::make_shared<Spinner>(Point3f(1932.51, 192.433, 301), engine, 0.8f, game_info));
        break;
      case 28:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(891.088, 263.341, 301), 1, engine, 2, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(857, 292.847, 100), Vector2f(163, 29), engine));
        engine.get_game().create_entity(std::make_shared<Thumper>(Point3f(1560, 120, 301), engine, 0.75f, game_info));
        break;
      case 29:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        break;
      case 30:
        engine.get_game().create_entity(std::make_shared<Rigid_body>(Point3f(-(txt.get_width()) + 3168 / 2, 0, 300), Vector2f(txt.get_width() * 2, txt.get_height() * 2), engine.load_texture(basic_path + std::to_string(difficulty_number) + "_" + std::to_string(level_number) + "_metal.png"), engine, "METAL", "BkgMap"));
        engine.get_game().create_entity(std::make_shared<Door>(Point3f(3078.1, 161.593, 500), engine, Utils::LEVEL_DOOR_TYPE[difficulty_number][level_number], 1.0f, level_number, game_info, difficulty_number));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1210.79, 263.607, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1799.55, 263.607, 301), 1, engine, 1, 0.4f, game_info));
        engine.get_game().create_entity(std::make_shared<Liquid>(Point3f(1926.1, 263.607, 301), 1, engine, 1, 0.4f, game_info));

        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1219, 302.847, 100), Vector2f(114, 21), engine));
        engine.get_game().create_entity(std::make_shared<Liquid_trigger>(Point3f(1788, 302.847, 100), Vector2f(271, 21), engine));
        // TONS WEIGHT
        // WALL
        break;
      default:
        break;
      }
      break;
    default:
      break;
    }
  }
};
