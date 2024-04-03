#pragma once

#include <memory>

#include "engine/game.hpp"
#include "engine/entity.hpp"
#include "engine/rigid_body.hpp"

#include "lemmings/camera/Dynamic_camera.hpp"
#include "lemmings/camera/Static_camera.hpp"
#include "lemmings/Lemming.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/cursor/Cursor.hpp"
#include "lemmings/cursor/Cursor_menu.hpp"
#include "lemmings/utils.hpp"
#include "lemmings/screen/Screen_manager.hpp"

// ASK: change _collides_up from bool to EntityPtr

// TODO: add movements to the lemming (BUILD, CLIMB, BASH, MINING)
// TODO: add player vs IA mode
// TODO: add sound effects
// TODO: fix lemming animations
// TODO: change assets more similar to original amiga
// TODO: hud more friendly
// TODO: add some structures to levels (CHOF, WALL, ICE, ELECT, TONS WEIGHT)

// TODO: add particles when lemming die

class Lemmings_game : public Game
{
private:
  Game_info game_info;
  Screen_manager screen;

public:
  Lemmings_game()
      : Game("Lemmings"), screen(game_info)
  {
  }

  // Sobrescribe funciones de Game
  std::shared_ptr<Camera2D> get_main_camera() const override
  {
    auto ptr = std::make_shared<Static_camera>(Bound2f(Point2f(10000, 0), Point2f(10640, 400)), Bound2f(Point2f(0, 0), Point2f(640, 400)), 8);

    return std::dynamic_pointer_cast<Camera2D>(ptr);
  }

  void on_game_startup(Engine &engine) override
  {
    engine.set_window_icon("assets/icon.png");

    // Cargamos los efectos de sonido
    game_info.start_sound_assets(engine);

    // HUD CAMERA
    auto ptr = std::make_shared<Static_camera>(Bound2f(Point2f(10000, -500), Point2f(10640, -100)), Bound2f(Point2f(0, 0), Point2f(640, 400)), 8);
    create_camera(std::dynamic_pointer_cast<Camera2D>(ptr));

    // GAME CAMERA
    auto ptr2 = std::make_shared<Dynamic_camera>(game_info, Bound2f(Point2f(1884, 0), Point2f(2524, 320)), Bound2f(Point2f(0, 0), Point2f(640, 320)), 7);
    create_camera(std::dynamic_pointer_cast<Camera2D>(ptr2));
    game_info.set_game_camera_id(ptr2->get_id());

    // MINIMAP CAMERA
    auto minimap_camera = std::make_shared<Static_camera>(Bound2f(Point2f(0, 0), Point2f(3168, 320)), Bound2f(Point2f(416, 356), Point2f(616, 396)), 2);
    create_camera(minimap_camera);
    minimap_camera->set_shader("Lemming", std::move(Shader(engine).filled_box(RGBA{238, 204, 0, 255})));
    minimap_camera->set_shader("BkgMap", std::move(Shader(engine).color_mask(RGBA{0, 136, 0, 255}, Shader::Resolution::AUTO, 22)));
    minimap_camera->set_shader("ALL", std::move(Shader(engine).invisible()));


    game_info.set_cursor_txt("assets/cursor.png", engine);
    engine.hide_cursor();

    auto cursor = std::make_shared<Cursor>(engine, game_info, 25);
    create_entity(cursor);
    auto cursor_menu = std::make_shared<Cursor_menu>(engine, game_info, 24);
    std::cout << cursor_menu << std::endl;
    create_entity(cursor_menu);
    game_info.set_cursor_menu(cursor_menu);
    screen.go_menu(engine, Utils::MENU_TYPE::INTRO, 0, 0);
    // screen.go_level(engine, 7, 0);
  }

  void on_loop_start(Engine &engine) override
  {
    // std::cout << engine.get_delta_time() << std::endl;
    screen.update_game(engine);
  }
};