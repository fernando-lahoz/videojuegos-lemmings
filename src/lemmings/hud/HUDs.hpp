#pragma once

#include <memory>
#include <vector>

#include "engine/engine.hpp"
#include "engine/entity.hpp"

#include "lemmings/hud/HUD.hpp"
#include "lemmings/hud/Minimap_view.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"
#include "lemmings/display/Text_image.hpp"
#include "lemmings/display/Dynamic_value_display.hpp"
#include "lemmings/display/Dynamic_text_image.hpp"

class HUDs
{
private:
    Game_info &game_info;

public:
    HUDs(Game_info &_game_info) : game_info(_game_info)
    {
    }

    void setupElements(Engine &engine)
    {
        auto hudElement = std::make_shared<HUD>(Point3f(10320, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_PAUSE, false, true, false, false);
        engine.get_game().create_entity(hudElement);

        engine.get_game().create_entity(std::make_shared<Entity>(Point3f(9998, -180, 4), Vector2f(644, 32), engine.load_texture("assets/hud/hud_background.png"), "HUD BACKGROUND"));

        hudElement = std::make_shared<HUD>(Point3f(10000, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_VELOCITY, false, false, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10011, -128, 1), Vector2f(12, 12), game_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_ADD_VELOCITY, true, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10011, -115, 1), Vector2f(12, 12), game_info, engine, "assets/hud/hud_option_0_button_", Utils::HUD_SUB_VELOCITY, true, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10032, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_SPAWN, false, false, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10043, -128, 1), Vector2f(12, 12), game_info, engine, "assets/hud/hud_option_1_button_", Utils::HUD_ADD_SPAWN_VELOCITY, true, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10043, -115, 1), Vector2f(12, 12), game_info, engine, "assets/hud/hud_option_1_button_", Utils::HUD_SUB_SPAWN_VELOCITY, true, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10064, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_CLIMBING);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10096, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_FLOATING);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10128, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_EXPLODE);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10160, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_BLOCKING);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10192, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_BUILDING);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10224, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_BASH);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10256, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_MINE);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10288, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_DIG);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10352, -148, 3), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_", Utils::HUD_ALL_EXPLODE, false, true, false, false);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10800, -148, 2), Vector2f(32, 48), game_info, engine, "assets/hud/hud_option_selected_", Utils::HUD_CURSOR, false, false, false, false, true);
        engine.get_game().create_entity(hudElement);

        hudElement = std::make_shared<HUD>(Point3f(10384, -148, 3), Vector2f(255, 48), game_info, engine, "assets/hud/hud_minimap_", Utils::HUD_MINIMAP, false, false, false, false);
        engine.get_game().create_entity(hudElement);

        engine.get_game().create_entity(std::make_shared<Minimap_view>(Point3f(10412.0f + ((Utils::LEVEL_CAMERA_POS_INI[game_info.get_level()] - 320.0f) / 2528.0f) * 160.0f, -148, 2), Vector2f(48, 48), game_info, engine, 1584));

        // TEXT

        auto textElement2 = std::make_shared<Dynamic_text_image>(Point3f(10000, -178, 3), Vector2f(112, 30), game_info, engine, Utils::STATS_GAME, &Game_info::get_lemming_hovered_type);
        engine.get_game().create_entity(textElement2);

        auto textElement = std::make_shared<Text_image>(Point3f(10224, -178, 3), Vector2f(48, 30), game_info, engine, Utils::STATS_GAME, "OUT");
        engine.get_game().create_entity(textElement);

        textElement = std::make_shared<Text_image>(Point3f(10368, -178, 3), Vector2f(32, 30), game_info, engine, Utils::STATS_GAME, "IN");
        engine.get_game().create_entity(textElement);

        textElement = std::make_shared<Text_image>(Point3f(10448, -178, 3), Vector2f(16, 30), game_info, engine, Utils::STATS_GAME, "%");
        engine.get_game().create_entity(textElement);

        textElement = std::make_shared<Text_image>(Point3f(10496, -178, 3), Vector2f(64, 30), game_info, engine, Utils::STATS_GAME, "TIME");
        engine.get_game().create_entity(textElement);

        textElement = std::make_shared<Text_image>(Point3f(10592, -178, 3), Vector2f(16, 30), game_info, engine, Utils::STATS_GAME, "-");
        engine.get_game().create_entity(textElement);

        Dynamic_value_display display_lemmings_hovered(
            game_info,                        // Referencia a Game_info
            engine,                           // Instancia de Engine
            Utils::STATS_GAME,                // text_type
            3,                                // maxDigits
            10144,                            // startX
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
            10304,                          // startX
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
            10432,                              // startX
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
            10576,                              // startX
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
            10624,                              // startX
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
            10049,                           // startX
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
            10081,                           // startX
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
            10113,                           // startX
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
            10145,                           // startX
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
            10177,                           // startX
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
            10209,                           // startX
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
            10241,                           // startX
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
            10273,                           // startX
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
            10305,                           // startX
            -146,                            // startY
            7,                               // digitWidth
            16,                              // digitHeight
            1,                               // paddingX
            &Game_info::get_skill_amount7    // Función miembro de Game_info
        );
    }
};
