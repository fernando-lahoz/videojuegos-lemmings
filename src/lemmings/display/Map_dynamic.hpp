#pragma once

#include <string>

#include "engine/entity.hpp"

#include "lemmings/Game_info.hpp"

class Map_dynamic : public Entity
{

private:
  Point3f position;
  Vector2f diagonal;
  Game_info &game_info;
  Texture txt;
  bool is_bkg_map;

  int last_difficulty, last_level;
  std::shared_ptr<Entity> map;

public:
  Map_dynamic(Point3f _position, Vector2f _diagonal, Engine &engine, Game_info &_game_info, bool _is_bkg_map = false)
      : Entity(_position, _diagonal,
               engine.load_texture("assets/menu/transparent.png"),
               engine,
               "Dynamic MAP", "Dynamic MAP"),
        position(_position),
        diagonal(_diagonal),
        game_info(_game_info),
        last_difficulty(0),
        last_level(0),
        is_bkg_map(_is_bkg_map)
  {
    int level_map_num = game_info.get_ia() ? game_info.conversion_level_selected_ia() : game_info.get_level_selected();
    txt = engine.load_texture("assets/maps/raw/map_" + std::to_string(game_info.get_difficulty_selected()) + "_" + std::to_string(level_map_num) + ".png");
    map = std::make_shared<Entity>(Point3f(10320 - (txt.get_width() * 65 / (2 * txt.get_height())), 20, 2), Vector2f(txt.get_width() * 65 / txt.get_height(), 65), txt, engine, "MAP", "MAP");
    engine.get_game().create_entity(map);
  }

  ~Map_dynamic()
  {
    map->destroy();
  }

  void pre_physics(Engine &engine) override
  {
    if (last_difficulty != game_info.get_difficulty_selected() || last_level != game_info.get_level_selected())
    {
      last_difficulty = game_info.get_difficulty_selected();
      last_level = game_info.get_level_selected();
      map->destroy();

      int level_map_num = game_info.get_ia() ? game_info.conversion_level_selected_ia() : game_info.get_level_selected();
      std::cout << "Nivel seleccionado: " << level_map_num << "  " << game_info.get_level_selected() << " Dificultad: " << game_info.get_difficulty_selected() << "\n";
      if (is_bkg_map)
      {
        txt = engine.load_texture("assets/maps/background_" + std::to_string(Utils::LEVEL_BACKGROUND_TYPE[game_info.get_difficulty_selected()][game_info.get_level_selected()]) + ".png");
        map = std::make_shared<Entity>(position, diagonal, txt, engine, "MAP", "MAP");
        engine.get_game().create_entity(map);
      }
      else
      {
        txt = engine.load_texture("assets/maps/raw/map_" + std::to_string(game_info.get_difficulty_selected()) + "_" + std::to_string(level_map_num) + ".png");
        map = std::make_shared<Entity>(Point3f(10320 - (txt.get_width() * 65 / (2 * txt.get_height())), 20, 2), Vector2f(txt.get_width() * 65 / txt.get_height(), 65), txt, engine, "MAP", "MAP");
        engine.get_game().create_entity(map);
      }
    }
  }
};
