#pragma once

#include "engine/engine.hpp"
#include "Level_info.hpp"
#include "Level.hpp"

class Screen_manager
{
private:
  Level level;

  Level_info &level_info;

  int last_lemmings_hovered = 0;

public:
  Screen_manager(Level_info &_level_info) : level(_level_info), level_info(_level_info)
  {
  }

  void go_level(Engine &engine, int _level)
  {
    level.setup_level(engine, _level);
  }

  void update_game(Engine &engine)
  {
    int actual_lemmings_hovered = level_info.get_lemmings_hovered();

    if (actual_lemmings_hovered != last_lemmings_hovered)
    {
      std::cout << "Lemmings hovered: " << actual_lemmings_hovered << std::endl;
      last_lemmings_hovered = actual_lemmings_hovered;
    }

    if (level_info.get_time_left() > 0.0f && !level_info.get_level_ended())
    {
      level_info.set_time_left(level_info.get_time_left() - engine.get_delta_time());
    }

    if (level_info.update_explode_countdown(engine))
    {
      auto &entities = engine.get_entities();
      for (std::size_t i = 0; i < entities.size(); i++)
      {
        if (entities[i]->get_entity_name() == "Lemming")
        {
          std::shared_ptr<Lemming> lemming_ptr = std::dynamic_pointer_cast<Lemming>(entities[i]);
          if (lemming_ptr)
          {
            lemming_ptr->add_skill(Utils::EXPLODE);
          }
        }
      }
    }
  }
};