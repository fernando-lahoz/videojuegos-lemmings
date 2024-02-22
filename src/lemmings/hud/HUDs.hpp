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
        auto hudElement = std::make_shared<HUD>(Point3f(320, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_VELOCITY, false, false, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(7, -133, 1), Vector2f(18, 18), game_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_PLAY_PAUSE, true, true, true, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(8, -148, 1), Vector2f(15, 15), game_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_ADD_VELOCITY, true, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(8, -113, 1), Vector2f(15, 5), game_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_SUB_VELOCITY, true, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(32, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_SPAWN, false, false, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(40, -133, 1), Vector2f(15, 15), game_info, engine, "assets/hud/hud_option_1_button_", Utils::HUD_ADD_SPAWN_VELOCITY, true, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(40, -113, 1), Vector2f(15, 5), game_info, engine, "assets/hud/hud_option_1_button_", Utils::HUD_SUB_SPAWN_VELOCITY, true, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(64, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_CLIMBING);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(96, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_FLOATING);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(128, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_EXPLODE);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(160, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_BLOCKING);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(192, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_BUILDING);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(224, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_BASH);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(256, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_MINE);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(288, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_DIG);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(352, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_ALL_EXPLODE, false, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(800, -148, 2), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_selected_", Utils::HUD_CURSOR, false, false, false, false, true);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(384, -148, 3), Vector2f(255, 48), game_info, engine, "assets/hud/hud_minimap_", Utils::HUD_MINIMAP, false, false, false, false);
        engine.get_game().create_entity(hudElement);

        // TEXT

        auto textElement2 = std::make_shared<Dynamic_text_image>(Point3f(0, -178, 3), Vector2f(112, 30), game_info, engine, Utils::STATS_GAME, &Game_info::get_lemming_hovered_type);
        engine.get_game().create_entity(textElement2);

        auto textElement = std::make_shared<Text_image>(Point3f(224, -178, 3), Vector2f(48, 30), game_info, engine, Utils::STATS_GAME, "OUT");
        engine.get_game().create_entity(textElement);

        textElement = std::make_shared<Text_image>(Point3f(368, -178, 3), Vector2f(32, 30), game_info, engine, Utils::STATS_GAME, "IN");
        engine.get_game().create_entity(textElement);

        textElement = std::make_shared<Text_image>(Point3f(448, -178, 3), Vector2f(16, 30), game_info, engine, Utils::STATS_GAME, "%");
        engine.get_game().create_entity(textElement);

        textElement = std::make_shared<Text_image>(Point3f(496, -178, 3), Vector2f(64, 30), game_info, engine, Utils::STATS_GAME, "TIME");
        engine.get_game().create_entity(textElement);

        textElement = std::make_shared<Text_image>(Point3f(592, -178, 3), Vector2f(16, 30), game_info, engine, Utils::STATS_GAME, "-");
        engine.get_game().create_entity(textElement);

        Dynamic_value_display display_lemmings_hovered(
            game_info,                        // Referencia a Game_info
            engine,                           // Instancia de Engine
            Utils::STATS_GAME,                // text_type
            3,                                // maxDigits
            144,                              // startX
            -178,                             // startY
            16,                               // digitWidth
            30,                               // digitHeight
            0,                                // paddingX
            &Game_info::get_lemmings_hovered, // Función miembro de Game_info
            false);

        Dynamic_value_display display_lemming_out(
            game_info,                      // Referencia a Game_info
            engine,                         // Instancia de Engine
            Utils::STATS_GAME,              // text_type
            3,                              // maxDigits
            304,                            // startX
            -178,                           // startY
            16,                             // digitWidth
            30,                             // digitHeight
            0,                              // paddingX
            &Game_info::get_n_lemmings_out, // Función miembro de Game_info
            false);

        Dynamic_value_display display_lemming_in(
            game_info,                          // Referencia a Game_info
            engine,                             // Instancia de Engine
            Utils::STATS_GAME,                  // text_type
            3,                                  // maxDigits
            400,                                // startX
            -178,                               // startY
            16,                                 // digitWidth
            30,                                 // digitHeight
            0,                                  // paddingX
            &Game_info::get_percen_lemmings_in, // Función miembro de Game_info
            false);

        Dynamic_value_display display_minutes_left(
            game_info,                          // Referencia a Game_info
            engine,                             // Instancia de Engine
            Utils::STATS_GAME,                  // text_type
            1,                                  // maxDigits
            576,                                // startX
            -178,                               // startY
            16,                                 // digitWidth
            30,                                 // digitHeight
            0,                                  // paddingX
            &Game_info::get_actual_minutes_left // Función miembro de Game_info
        );

        Dynamic_value_display display_seconds_left(
            game_info,                          // Referencia a Game_info
            engine,                             // Instancia de Engine
            Utils::STATS_GAME,                  // text_type
            2,                                  // maxDigits
            624,                                // startX
            -178,                               // startY
            16,                                 // digitWidth
            30,                                 // digitHeight
            0,                                  // paddingX
            &Game_info::get_actual_seconds_left // Función miembro de Game_info
        );

        Dynamic_value_display display_spawn_velocity(
            game_info,                       // Referencia a Game_info
            engine,                          // Instancia de Engine
            Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
            2,                               // maxDigits
            49,                              // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_spawn_velocity   // Función miembro de Game_info
        );

        Dynamic_value_display display_skill0(
            game_info,                       // Referencia a Game_info
            engine,                          // Instancia de Engine
            Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
            2,                               // maxDigits
            81,                              // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_skill_amount0    // Función miembro de Game_info
        );

        Dynamic_value_display display_skill1(
            game_info,                       // Referencia a Game_info
            engine,                          // Instancia de Engine
            Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
            2,                               // maxDigits
            113,                             // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_skill_amount1    // Función miembro de Game_info
        );

        Dynamic_value_display display_skill2(
            game_info,                       // Referencia a Game_info
            engine,                          // Instancia de Engine
            Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
            2,                               // maxDigits
            145,                             // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_skill_amount2    // Función miembro de Game_info
        );

        Dynamic_value_display display_skill3(
            game_info,                       // Referencia a Game_info
            engine,                          // Instancia de Engine
            Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
            2,                               // maxDigits
            177,                             // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_skill_amount3    // Función miembro de Game_info
        );

        Dynamic_value_display display_skill4(
            game_info,                       // Referencia a Game_info
            engine,                          // Instancia de Engine
            Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
            2,                               // maxDigits
            209,                             // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_skill_amount4    // Función miembro de Game_info
        );

        Dynamic_value_display display_skill5(
            game_info,                       // Referencia a Game_info
            engine,                          // Instancia de Engine
            Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
            2,                               // maxDigits
            241,                             // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_skill_amount5    // Función miembro de Game_info
        );

        Dynamic_value_display display_skill6(
            game_info,                       // Referencia a Game_info
            engine,                          // Instancia de Engine
            Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
            2,                               // maxDigits
            273,                             // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_skill_amount6    // Función miembro de Game_info
        );

        Dynamic_value_display display_skill7(
            game_info,                       // Referencia a Game_info
            engine,                          // Instancia de Engine
            Utils::TEXT_TYPE::SKILL_COUNTER, // text_type
            2,                               // maxDigits
            305,                             // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_skill_amount7    // Función miembro de Game_info
        );
    }
};
