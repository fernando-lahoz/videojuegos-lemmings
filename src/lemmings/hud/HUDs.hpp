#pragma once

#include <memory>
#include <vector>

#include "engine/engine.hpp"
#include "engine/entity.hpp"

#include "lemmings/hud/HUD.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"
#include "lemmings/display/Text_image.hpp"
#include "lemmings/display/Dynamic_value_display.hpp"
#include "lemmings/display/Dynamic_text_image.hpp"

class HUDs
{
private:
  const Vector2f size = Vector2f(0.05833333, 0.1486111);
  Game_info &game_info;

public:
  HUDs(Game_info &_game_info) : game_info(_game_info)
  {
  }

  void setupElements(Engine &engine)
  {
    auto hudElement = std::make_shared<HUD>(Point3f(-0.0006, 0, 4), Vector2f(1.001, 1), game_info, engine, "assets/hud/hud_", Utils::HUD_BACKGROUND, false, false, false, false);
    engine.get_game()->create_entity(hudElement);

    // BUTTONS

    hudElement = std::make_shared<HUD>(Utils::positions[0], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_VELOCITY, false, false, false, false);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.03172222222, 0.8694111111, 1), Vector2f(0.04027777777, 0.05555555555), game_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_PLAY_PAUSE, true, true, true, false);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.0351, 0.828, 1), Vector2f(0.02638888888, 0.03194444444), game_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_ADD_VELOCITY, true, true, false, false);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.033, 0.934, 1), Vector2f(0.03333333333, 0.013888888888), game_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_SUB_VELOCITY, true, true, false, false);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[1], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_SPAWN, false, false, false, false);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.08733333333, 0.88611111107, 1), Vector2f(0.03888888889, 0.044444444), game_info, engine, "assets/hud/hud_option_1_button_", Utils::HUD_ADD_SPAWN_VELOCITY, true, true, false, false);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.08733333333, 0.9402777777, 1), Vector2f(0.03888888889, 0.01666666666), game_info, engine, "assets/hud/hud_option_1_button_", Utils::HUD_SUB_SPAWN_VELOCITY, true, true, false, false);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[2], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_CLIMBING);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[3], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_FLOATING);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[4], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_EXPLODE);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[5], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_BLOCKING);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[6], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_BUILDING);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[7], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_BASH);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[8], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_MINE);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[9], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_DIG);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Utils::positions[10], size, game_info, engine, "assets/hud/hud_option_", Utils::HUD_ALL_EXPLODE, false, true, false, false);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(Utils::positions[game_info.get_option_selected()].x, Utils::positions[game_info.get_option_selected()].y, 2), size, game_info, engine, "assets/hud/hud_option_selected_", Utils::HUD_CURSOR, false, false, false, false, true);
    engine.get_game()->create_entity(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.654, 0.8208333333, 3), Vector2f(0.325, 0.1486111), game_info, engine, "assets/hud/hud_minimap_", Utils::HUD_MINIMAP, false, false, false, false);
    engine.get_game()->create_entity(hudElement);

    // TEXT
    double size = 0.045;
    double size_width = 0.5333333333 * size;

    auto textElement2 = std::make_shared<Dynamic_text_image>(Point3f(0.022, 0.775 - size / 2, 3), Vector2f(7 * size_width, size), game_info, engine, Utils::STATS_GAME, &Game_info::get_lemming_hovered_type);
    engine.get_game()->create_entity(textElement2);

    auto textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 26.5, 0.775 - size / 2, 3), Vector2f(3 * size_width, size), game_info, engine, Utils::STATS_GAME, "OUT");
    engine.get_game()->create_entity(textElement);

    textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 17.5, 0.775 - size / 2, 3), Vector2f(2 * size_width, size), game_info, engine, Utils::STATS_GAME, "IN");
    engine.get_game()->create_entity(textElement);

    textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 12, 0.775 - size / 2, 3), Vector2f(size_width, size), game_info, engine, Utils::STATS_GAME, "%");
    engine.get_game()->create_entity(textElement);

    textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 9, 0.775 - size / 2, 3), Vector2f(4 * size_width, size), game_info, engine, Utils::STATS_GAME, "TIME");
    engine.get_game()->create_entity(textElement);

    textElement = std::make_shared<Text_image>(Point3f(0.98 - size_width * 3.25, 0.775 - size / 2, 3), Vector2f(size_width, size), game_info, engine, Utils::STATS_GAME, "-");
    engine.get_game()->create_entity(textElement);

    Dynamic_value_display display_lemmings_hovered(
        game_info,                        // Referencia a Game_info
        engine,                           // Instancia de Engine
        Utils::STATS_GAME,                // text_type
        3,                                // maxDigits
        0.022 + size_width * 9,           // startX
        0.775 - size / 2,                 // startY
        size_width,                       // digitWidth
        size,                             // digitHeight
        0.00001,                          // paddingX
        &Game_info::get_lemmings_hovered, // Función miembro de Game_info
        false);

    Dynamic_value_display display_lemming_out(
        game_info,                      // Referencia a Game_info
        engine,                         // Instancia de Engine
        Utils::STATS_GAME,              // text_type
        3,                              // maxDigits
        0.98 - size_width * 21,         // startX
        0.775 - size / 2,               // startY
        size_width,                     // digitWidth
        size,                           // digitHeight
        0.00001,                        // paddingX
        &Game_info::get_n_lemmings_out, // Función miembro de Game_info
        false);

    Dynamic_value_display display_lemming_in(
        game_info,                          // Referencia a Game_info
        engine,                             // Instancia de Engine
        Utils::STATS_GAME,                  // text_type
        3,                                  // maxDigits
        0.98 - size_width * 13,             // startX
        0.775 - size / 2,                   // startY
        size_width,                         // digitWidth
        size,                               // digitHeight
        0.00001,                            // paddingX
        &Game_info::get_percen_lemmings_in, // Función miembro de Game_info
        false);

    Dynamic_value_display display_minutes_left(
        game_info,                          // Referencia a Game_info
        engine,                             // Instancia de Engine
        Utils::STATS_GAME,                  // text_type
        1,                                  // maxDigits
        0.98 - size_width * 4.5,            // startX
        0.775 - size / 2,                   // startY
        size_width,                         // digitWidth
        size,                               // digitHeight
        0.00001,                            // paddingX
        &Game_info::get_actual_minutes_left // Función miembro de Game_info
    );

    Dynamic_value_display display_seconds_left(
        game_info,                          // Referencia a Game_info
        engine,                             // Instancia de Engine
        Utils::STATS_GAME,                  // text_type
        2,                                  // maxDigits
        0.98 - size_width,                  // startX
        0.775 - size / 2,                   // startY
        size_width,                         // digitWidth
        size,                               // digitHeight
        0.00001,                            // paddingX
        &Game_info::get_actual_seconds_left // Función miembro de Game_info
    );

    Dynamic_value_display display_spawn_velocity(
        game_info,                       // Referencia a Game_info
        engine,                          // Instancia de Engine
        Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
        2,                               // maxDigits
        0.11,                            // startX
        0.836,                           // startY
        0.014,                           // digitWidth
        0.0373333,                       // digitHeight
        0.003,                           // paddingX
        &Game_info::get_spawn_velocity   // Función miembro de Game_info
    );

    Dynamic_value_display display_skill0(
        game_info,                       // Referencia a Game_info
        engine,                          // Instancia de Engine
        Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
        2,                               // maxDigits
        0.167 + 0.0575 * 0,              // startX
        0.836,                           // startY
        0.014,                           // digitWidth
        0.0373333,                       // digitHeight
        0.003,                           // paddingX
        &Game_info::get_skill_amount0    // Función miembro de Game_info
    );

    Dynamic_value_display display_skill1(
        game_info,                       // Referencia a Game_info
        engine,                          // Instancia de Engine
        Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
        2,                               // maxDigits
        0.167 + 0.0575 * 1,              // startX
        0.836,                           // startY
        0.014,                           // digitWidth
        0.0373333,                       // digitHeight
        0.003,                           // paddingX
        &Game_info::get_skill_amount1    // Función miembro de Game_info
    );

    Dynamic_value_display display_skill2(
        game_info,                       // Referencia a Game_info
        engine,                          // Instancia de Engine
        Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
        2,                               // maxDigits
        0.167 + 0.0575 * 2,              // startX
        0.836,                           // startY
        0.014,                           // digitWidth
        0.0373333,                       // digitHeight
        0.003,                           // paddingX
        &Game_info::get_skill_amount2    // Función miembro de Game_info
    );

    Dynamic_value_display display_skill3(
        game_info,                       // Referencia a Game_info
        engine,                          // Instancia de Engine
        Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
        2,                               // maxDigits
        0.167 + 0.0575 * 3,              // startX
        0.836,                           // startY
        0.014,                           // digitWidth
        0.0373333,                       // digitHeight
        0.003,                           // paddingX
        &Game_info::get_skill_amount3    // Función miembro de Game_info
    );

    Dynamic_value_display display_skill4(
        game_info,                       // Referencia a Game_info
        engine,                          // Instancia de Engine
        Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
        2,                               // maxDigits
        0.167 + 0.0575 * 4,              // startX
        0.836,                           // startY
        0.014,                           // digitWidth
        0.0373333,                       // digitHeight
        0.003,                           // paddingX
        &Game_info::get_skill_amount4    // Función miembro de Game_info
    );

    Dynamic_value_display display_skill5(
        game_info,                       // Referencia a Game_info
        engine,                          // Instancia de Engine
        Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
        2,                               // maxDigits
        0.167 + 0.0575 * 5,              // startX
        0.836,                           // startY
        0.014,                           // digitWidth
        0.0373333,                       // digitHeight
        0.003,                           // paddingX
        &Game_info::get_skill_amount5    // Función miembro de Game_info
    );

    Dynamic_value_display display_skill6(
        game_info,                       // Referencia a Game_info
        engine,                          // Instancia de Engine
        Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
        2,                               // maxDigits
        0.167 + 0.0575 * 6,              // startX
        0.836,                           // startY
        0.014,                           // digitWidth
        0.0373333,                       // digitHeight
        0.003,                           // paddingX
        &Game_info::get_skill_amount6    // Función miembro de Game_info
    );

    Dynamic_value_display display_skill7(
        game_info,                       // Referencia a Game_info
        engine,                          // Instancia de Engine
        Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
        2,                               // maxDigits
        0.167 + 0.0575 * 7,              // startX
        0.836,                           // startY
        0.014,                           // digitWidth
        0.0373333,                       // digitHeight
        0.003,                           // paddingX
        &Game_info::get_skill_amount7    // Función miembro de Game_info
    );
  }
};
