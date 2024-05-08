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
#include "lemmings/AI_autoplay.hpp"
#include "lemmings/menu/Menu_slider.hpp"

class Lemmings_game : public Game
{
private:
  Game_info game_info;
  Screen_manager screen;
  Keyboard_manager keyboard;

  AI_autoplay ai;
  std::vector<std::shared_ptr<Lemming>> lemmings;
  EntityPtr map;

  static Point2i lemmings_font_map(char c)
  {
    if (c >= 'A' && c <= 'M')
      return {(c - 'A'), 0};
    else if (c >= 'N' && c <= 'Z')
      return {(c - 'N'), 1};
    else if (c >= 'a' && c <= 'm')
      return {(c - 'a'), 2};
    else if (c >= 'n' && c <= 'z')
      return {(c - 'n'), 3};
    else if (c >= '0' && c <= '9')
      return {(c - '0'), 4};
    else
    {
      switch (c)
      {
      case '.':
        return {0, 5};
      case '(':
        return {1, 5};
      case ')':
        return {2, 5};
      case '\'':
        return {3, 5};
      case '!':
        return {4, 5};
      case '%':
        return {5, 5};
      case '-':
        return {6, 5};
      default:
        return {12, 5}; // white space
      }
    }
  }

  void delete_exit(Engine &engine)
  {

    auto entities = engine.get_entities();
    for (auto &entity : entities)
    {
      if (entity->get_class() == "POP")
      {
        entity->destroy();
      }
    }
  }

  void pop_up_menu_in_game(Engine &engine)
  {
    auto background = std::make_shared<Entity>(Point3f(10000, 0, 3), Vector2f(640, 400), engine.load_texture("assets/menu/ingame_popup.png"), engine, "Background", "Background");
    background->set_class("POP");

    engine.get_game().create_entity(background);

    auto x_b = 10320 - 100;
    auto y_b = 220;

    auto b_sonido = std::make_shared<Entity>(Point3f(x_b, y_b, 2), Vector2f(200, 80), engine.load_texture("assets/menu/menu_wide_volume.png"), engine, "Background", "Background");
    b_sonido->set_class("POP");
    engine.get_game().create_entity(b_sonido);

    auto s_musica = std::make_shared<Menu_slider>(Point3f(x_b + 90, y_b + 39, 1), 86, Vector2f(12, 12), 0, engine, game_info);
    s_musica->set_class("POP");
    engine.get_game().create_entity(s_musica);
    auto s_efectos = std::make_shared<Menu_slider>(Point3f(x_b + 90, y_b + 55, 1), 86, Vector2f(12, 12), 1, engine, game_info);
    s_efectos->set_class("POP");
    engine.get_game().create_entity(s_efectos);
    auto text = std::make_shared<Text_displayer>(Point3f(x_b + 85, y_b + 45, 0), Vector2f(5, 10), game_info, "right",
                                                 engine.load_texture("assets/font/font-cyan.png"),
                                                 Vector2i(16, 30), lemmings_font_map, "Music", engine,
                                                 "POP");
    engine.get_game().create_entity(text);
    text = std::make_shared<Text_displayer>(Point3f(x_b + 85, y_b + 61, 0), Vector2f(5, 10), game_info, "right",
                                            engine.load_texture("assets/font/font-cyan.png"),
                                            Vector2i(16, 30), lemmings_font_map, "Effects", engine,
                                            "POP");
    engine.get_game().create_entity(text);

    // Botón volver a menú
    auto b_home = std::make_shared<Menu_button>(Point3f(10220, 120, 2), Vector2f(80, 80), engine, game_info, keyboard, Utils::BUTTON_TYPE::GO_HOME);
    b_home->set_class("POP");
    engine.get_game().create_entity(b_home);

    // Botón de salir juego
    auto b_exit = std::make_shared<Menu_button>(Point3f(10340, 120, 2), Vector2f(80, 80), engine, game_info, keyboard, Utils::BUTTON_TYPE::YES_EXIT);
    b_exit->set_class("POP");
    engine.get_game().create_entity(b_exit);

    // Botón de vuelta al menu
    auto b_back = std::make_shared<Menu_button>(Point3f(10175, 326, 2), Vector2f(35, 18.5), engine, game_info, keyboard, Utils::BUTTON_TYPE::NO_EXIT_GAME);
    b_back->set_class("POP");
    engine.get_game().create_entity(b_back);
  }

  void create_pop_up_exit(Engine &engine)
  {
    if (game_info.get_pop_exit())
    {
      // crear pop
      game_info.set_level_is_paused(true);
      engine.set_is_game_paused(true);
      pop_up_menu_in_game(engine);
      std::cout << "Creando pop exit\n";
      game_info.pop_exit_creado();
    }
    if (game_info.get_delete_exit())
    {
      // eliminar pop
      delete_exit(engine);
      std::cout << "Eliminando pop exit\n";
      game_info.pop_exit_eliminado();
      game_info.set_level_is_paused(false);
      engine.set_is_game_paused(false);
    }
  }

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
    engine.set_window_icon("assets/icon.ico");
    game_info.set_window_size(engine);
    engine.show_window();

    // Cargamos los efectos de sonido
    game_info.start_sound_assets(engine);

    // HUD CAMERA
    auto ptr = std::make_shared<Static_camera>(Bound2f(Point2f(10000, -500), Point2f(10640, -100)), Bound2f(Point2f(0, 0), Point2f(640, 400)), 8);
    create_camera(ptr);

    // GAME CAMERA
    auto ptr2 = std::make_shared<Dynamic_camera>(game_info, Bound2f(Point2f(1884, 0), Point2f(2524, 320)), Bound2f(Point2f(0, 0), Point2f(640, 320)), 7);
    create_camera(ptr2);
    game_info.set_game_camera_id(ptr2->get_id());
    game_info.set_dynamic_camera(*ptr2);
    // MINIMAP CAMERA
    auto minimap_camera = std::make_shared<Static_camera>(Bound2f(Point2f(0, 0), Point2f(3168, 320)), Bound2f(Point2f(416, 356), Point2f(616, 396)), 2);
    create_camera(minimap_camera);
    minimap_camera->set_shader("Lemming", Shader(engine).filled_box(Utils::colors::minimap_lemming, 50, 50));
    minimap_camera->set_shader("BkgMap", Shader(engine).color_mask(RGBA{0, 136, 0, 255}, 264, 40));
    minimap_camera->set_shader("ALL", Shader(engine).invisible());

    // KEY BINDINGS
    keyboard.set_key_bindings();

    game_info.set_cursor_txt("assets/cursor.png", engine);
    engine.hide_cursor();

    auto cursor = std::make_shared<Cursor>(engine, game_info, 25);
    create_entity(cursor);
    auto cursor_menu = std::make_shared<Cursor_menu>(engine, game_info);
    std::cout << cursor_menu << std::endl;
    create_entity(cursor_menu);
    game_info.set_cursor_menu(cursor_menu);
    screen.go_menu(engine, Utils::MENU_TYPE::INTRO, 0, 0);
    // screen.go_level(engine, 4, 2); // Con este codigo accedes al nivel sin tener que pasar por los menus
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

  void on_entity_destruction(Engine &, EntityPtr entity) override
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
    create_pop_up_exit(engine);
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