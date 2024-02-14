#pragma once

#include <memory>
#include <vector>
#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "HUD.hpp"
#include "Level_info.hpp"
#include "utils.hpp"

class HUDs
{
private:
  std::vector<std::shared_ptr<Entity>> elements;
  Engine &engine;
  const Vector2f size = Vector2f(0.05833333, 0.1486111);
  Level_info &level_info;

public:
  HUDs(Engine &engine, Level_info &_level_info) : engine(engine), level_info(_level_info)
  {
    setupElements();
  }

  void setupElements()
  {
    auto hudElement = std::make_shared<HUD>(Point3f(-0.0006, 0, 4), Vector2f(1.001, 1), level_info, engine, "assets/hud/hud_", Utils::HUD_BACKGROUND, false, false, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[0], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_VELOCITY, false, false, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.03172222222, 0.8694111111, 1), Vector2f(0.04027777777, 0.05555555555), level_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_PLAY_PAUSE, true, true, true, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.0351, 0.828, 1), Vector2f(0.02638888888, 0.03194444444), level_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_ADD_VELOCITY, true, true, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.033, 0.934, 1), Vector2f(0.03333333333, 0.013888888888), level_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_SUB_VELOCITY, true, true, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[1], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_SPAWN, false, false, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.08733333333, 0.88611111107, 1), Vector2f(0.03888888889, 0.044444444), level_info, engine, "assets/hud/hud_option_1_button_", Utils::HUD_ADD_SPAWN_VELOCITY, true, true, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.08733333333, 0.9402777777, 1), Vector2f(0.03888888889, 0.01666666666), level_info, engine, "assets/hud/hud_option_1_button_", Utils::HUD_SUB_SPAWN_VELOCITY, true, true, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[2], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_CLIMBING);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[3], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_FLOATING);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[4], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_EXPLODE);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[5], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_BLOCKING);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[6], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_BUILDING);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[7], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_DIG_HORIZONTAL);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[8], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_DIG_DIAGONAL);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[9], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_DIG_VERTICAL);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[10], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_ALL_EXPLODE, false, true, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(Utils::positions[level_info.get_option_selected()].x, Utils::positions[level_info.get_option_selected()].y, 2), size, level_info, engine, "assets/hud/hud_option_selected_", Utils::HUD_CURSOR, false, false, false, false, true);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.654, 0.8208333333, 3), Vector2f(0.325, 0.1486111), level_info, engine, "assets/hud/hud_minimap_", Utils::HUD_MINIMAP, false, false, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);
  }
};
