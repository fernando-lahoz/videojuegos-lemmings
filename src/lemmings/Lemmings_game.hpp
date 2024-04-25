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
#include "lemmings/keyboard/Keyboard_manager.hpp"
#include "lemmings/AI_autoplay.cpp"

// ASK: change _collides_up from bool to EntityPtr

// TODO: refine movements of the lemming to be more similar to original
// TODO: add player vs IA mode
// TODO: add sound effects
// TODO: change assets more similar to original amiga
// TODO: hud more friendly
// TODO: add some structures to levels (Rock_crusher, Bear_trap, WALL, TONS WEIGHT)

// TODO: add particles when lemming die

class Lemmings_game : public Game
{
private:
  Game_info game_info;
  Screen_manager screen;
  Keyboard_manager keyboard;

  AI_autoplay ai;
  std::vector<std::shared_ptr<Lemming>> lemmings;
  EntityPtr map;

public:
  Lemmings_game()
      : Game("Lemmings", /*INITIAL WINDOW SIZE*/ Vector2i{1280, 800}), screen(game_info, keyboard), keyboard(game_info)
  {
  }

  // Sobrescribe funciones de Game
  std::shared_ptr<Camera2D> get_main_camera() const override
  {
    auto ptr = std::make_shared<Static_camera>(Bound2f(Point2f(10000, 0), Point2f(10640, 400)), Bound2f(Point2f(0, 0), Point2f(640, 400)), 8);

    return std::dynamic_pointer_cast<Camera2D>(ptr);
  }

  void create_entity(EntityPtr entity) override
  {
    if (entity->get_entity_name() == "Lemming")
    {
      lemmings.push_back(std::dynamic_pointer_cast<Lemming>(entity));
    }
    else if (entity->get_entity_name() == "MAP")
    {
      map = entity;
    }

    Game::create_entity(entity);
  }

  void on_game_startup(Engine &engine) override
  {
    engine.set_window_icon("assets/icon.png");
    game_info.set_window_size(engine);

    // Cargamos los efectos de sonido
    game_info.start_sound_assets(engine);

    // HUD CAMERA
    auto ptr = std::make_shared<Static_camera>(Bound2f(Point2f(10000, -500), Point2f(10640, -100)), Bound2f(Point2f(0, 0), Point2f(640, 400)), 8);
    create_camera(std::dynamic_pointer_cast<Camera2D>(ptr));

    // GAME CAMERA
    auto ptr2 = std::make_shared<Dynamic_camera>(game_info, Bound2f(Point2f(1884, 0), Point2f(2524, 320)), Bound2f(Point2f(0, 0), Point2f(640, 320)), 7);
    create_camera(std::dynamic_pointer_cast<Camera2D>(ptr2));
    game_info.set_game_camera_id(ptr2->get_id());
    game_info.set_dynamic_camera(*ptr2);

    // MINIMAP CAMERA
    auto minimap_camera = std::make_shared<Static_camera>(Bound2f(Point2f(0, 0), Point2f(3168, 320)), Bound2f(Point2f(416, 356), Point2f(616, 396)), 2);
    create_camera(minimap_camera);
    minimap_camera->set_shader("Lemming", std::move(Shader(engine).filled_box(RGBA{238, 204, 0, 255})));
    minimap_camera->set_shader("BkgMap", std::move(Shader(engine).color_mask(RGBA{0, 136, 0, 255}, Shader::Resolution::AUTO, 22)));
    minimap_camera->set_shader("ALL", std::move(Shader(engine).invisible()));

    // KEY BINDINGS
    keyboard.set_key_bindings();

    game_info.set_cursor_txt("assets/cursor.png", engine);
    engine.hide_cursor();

    auto cursor = std::make_shared<Cursor>(engine, game_info, 25);
    create_entity(cursor);
    auto cursor_menu = std::make_shared<Cursor_menu>(engine, game_info, 24);
    std::cout << cursor_menu << std::endl;
    create_entity(cursor_menu);
    game_info.set_cursor_menu(cursor_menu);
    screen.go_menu(engine, Utils::MENU_TYPE::INTRO, 0, 0);
    // screen.go_level(engine, 24, 0); // Con este codigo accedes al nivel sin tener que pasar por los menus
  }

  void on_level_startup(int difficulty_number, int level_id) override
  {
    int executor_id = -1;

    std::cout << "Starting level " << level_id << " of difficulty " << difficulty_number << std::endl;

    if (difficulty_number == 0 && level_id == 1)
      executor_id = 1;
    else if (difficulty_number == 0 && level_id == 3)
      executor_id = 3;
    else if (difficulty_number == 1 && level_id == 1)
      executor_id = 11;

    if (!game_info.get_ia())
    {
      executor_id = -1;
    }
    // -1 if the ai should do nothing
    ai.init_executor(executor_id);
  }

  void on_entity_destruction(Engine &engine, EntityPtr entity) override
  {
    if (entity->get_entity_name() == "Lemming")
    {
      lemmings.erase(std::remove_if(lemmings.begin(), lemmings.end(), [entity](std::shared_ptr<Lemming> lemming)
                                    { return lemming->get_entity_id() == entity->get_entity_id(); }),
                     lemmings.end());
    }
  }

  void on_loop_start(Engine &engine) override
  {
    ai.update_execution(engine, game_info, map, lemmings);
    // std::cout << engine.get_delta_time() << std::endl;
    screen.update_game(engine);
  }

  void on_event_up(Engine &engine, EngineIO::InputEvent event) override
  {
    // Gestionamos el evento si procede del teclado
    if (event < EngineIO::InputEvent::MOUSE_HOVER || event > EngineIO::InputEvent::MOUSE_SCROLL_DOWN)
      keyboard.manage_key_up(engine, event);
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    // Gestionamos el evento si procede del teclado
    if (event < EngineIO::InputEvent::MOUSE_HOVER || event > EngineIO::InputEvent::MOUSE_SCROLL_DOWN)
      keyboard.manage_key_down(engine, event);
  }
};