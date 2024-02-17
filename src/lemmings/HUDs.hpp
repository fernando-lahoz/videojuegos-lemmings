#pragma once

#include <memory>
#include <vector>
#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "HUD.hpp"
#include "Level_info.hpp"
#include "utils.hpp"
#include "Text_image.hpp"
#include "Dynamic_value_display.hpp"
#include "Dynamic_text_image.hpp"

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

    // BUTTONS

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

    hudElement = std::make_shared<HUD>(Utils::positions[7], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_BASH);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[8], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_MINE);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[9], size, level_info, engine, "assets/hud/hud_option_", Utils::HUD_DIG);
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

    // TEXT
    double size = 0.045;
    double size_width = 0.5333333333 * size;

    auto textElement2 = std::make_shared<Dynamic_text_image>(Point3f(0.022, 0.775 - size / 2, 3), Vector2f(7 * size_width, size), level_info, engine, Utils::STATS_GAME, &Level_info::get_lemming_hovered_type);
    engine.get_game()->create_entity(textElement2);
    elements.push_back(textElement2);

    // textElement = std::make_shared<Text_image>(Point3f(0.022, 0.775 - size / 2, 3), Vector2f(7 * size_width, size), level_info, engine, Utils::STATS_GAME, "WALKER");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.022 + size_width * 8, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "3");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.022 + size_width * 9, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "3");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.022 + size_width * 10, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "3");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    auto textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 26.5, 0.775 - size / 2, 3), Vector2f(3 * size_width, size), level_info, engine, Utils::STATS_GAME, "OUT");
    engine.get_game()->create_entity(textElement);
    elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 23, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "3");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 22, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "3");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 21, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "3");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 17.5, 0.775 - size / 2, 3), Vector2f(2 * size_width, size), level_info, engine, Utils::STATS_GAME, "IN");
    engine.get_game()->create_entity(textElement);
    elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 15, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "1");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 14, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "0");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 13, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "0");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 12, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "%");
    engine.get_game()->create_entity(textElement);
    elements.push_back(textElement);

    textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 9, 0.775 - size / 2, 3), Vector2f(4 * size_width, size), level_info, engine, Utils::STATS_GAME, "TIME");
    engine.get_game()->create_entity(textElement);
    elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 4.5, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "4");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 3.25, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "-");
    engine.get_game()->create_entity(textElement);
    elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 2, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "5");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    // textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width, 0.775 - size / 2, 3), Vector2f(size_width, size), level_info, engine, Utils::STATS_GAME, "9");
    // engine.get_game()->create_entity(textElement);
    // elements.push_back(textElement);

    Dynamic_value_display display_lemmings_hovered(
        level_info,                        // Referencia a Level_info
        engine,                            // Instancia de Engine
        Utils::STATS_GAME,                 // text_type
        3,                                 // maxDigits
        0.022 + size_width * 9,            // startX
        0.775 - size / 2,                  // startY
        size_width,                        // digitWidth
        size,                              // digitHeight
        &Level_info::get_lemmings_hovered, // Función miembro de Level_info
        false);
    display_lemmings_hovered.add_to_game(); // Agrega los dígitos al juego

    Dynamic_value_display display_lemming_out(
        level_info,                      // Referencia a Level_info
        engine,                          // Instancia de Engine
        Utils::STATS_GAME,               // text_type
        3,                               // maxDigits
        0.98 - size_width * 21,          // startX
        0.775 - size / 2,                // startY
        size_width,                      // digitWidth
        size,                            // digitHeight
        &Level_info::get_n_lemmings_out, // Función miembro de Level_info
        false);
    display_lemming_out.add_to_game();

    Dynamic_value_display display_lemming_in(
        level_info,                          // Referencia a Level_info
        engine,                              // Instancia de Engine
        Utils::STATS_GAME,                   // text_type
        3,                                   // maxDigits
        0.98 - size_width * 13,              // startX
        0.775 - size / 2,                    // startY
        size_width,                          // digitWidth
        size,                                // digitHeight
        &Level_info::get_percen_lemmings_in, // Función miembro de Level_info
        false);
    display_lemming_in.add_to_game();

    Dynamic_value_display display_minutes_left(
        level_info,                          // Referencia a Level_info
        engine,                              // Instancia de Engine
        Utils::STATS_GAME,                   // text_type
        1,                                   // maxDigits
        0.98 - size_width * 4.5,             // startX
        0.775 - size / 2,                    // startY
        size_width,                          // digitWidth
        size,                                // digitHeight
        &Level_info::get_actual_minutes_left // Función miembro de Level_info
    );
    display_minutes_left.add_to_game();

    Dynamic_value_display display_seconds_left(
        level_info,                          // Referencia a Level_info
        engine,                              // Instancia de Engine
        Utils::STATS_GAME,                   // text_type
        2,                                   // maxDigits
        0.98 - size_width,                   // startX
        0.775 - size / 2,                    // startY
        size_width,                          // digitWidth
        size,                                // digitHeight
        &Level_info::get_actual_seconds_left // Función miembro de Level_info
    );
    display_seconds_left.add_to_game();
  }
};
