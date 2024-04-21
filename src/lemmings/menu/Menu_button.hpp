#pragma once

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"
#include "lemmings/keyboard/Keyboard_manager.hpp"

#include "lemmings/utils.hpp"

class Menu_button : public Rigid_body
{
private:
  int type;
  Texture txt_off;
  Texture txt_on;
  bool is_pressed = false;
  bool is_changeable;
  Game_info &game_info;
  Engine &engine;
  Keyboard_manager &keyboard;

  // Devuelve el nombre del fichero que corresponde a la imagen del tipo de botón
  //  suministrado como entrada
  std::string name_file(int _type)
  {
    return "assets/menu/menu_button_" + std::to_string(_type) + ".png";
  }

public:
  Menu_button(Point3f position, Vector2f size, Engine &_engine, Game_info &_game_info, Keyboard_manager &_keyboard, int _type, bool _is_changeable = false)
      : Rigid_body(position, size, !_game_info.get_sound_effects() && _is_changeable ? _engine.load_texture("assets/menu/menu_button_" + std::to_string(_type + 1) + ".png") : _engine.load_texture(name_file(_type)), engine, "Menu Button"),
        type(_type), game_info(_game_info), engine(_engine), keyboard(_keyboard)
  {
    //std::cout << "Type: " << _type << std::endl;
    txt_on = engine.load_texture(name_file(_type));
    if (_is_changeable)
    {
      txt_off = engine.load_texture("assets/menu/menu_button_" + std::to_string(_type + 1) + ".png");
    }
    is_pressed = !_game_info.get_sound_effects();
    is_changeable = _is_changeable;
    disable_collisions();
  }

  void button_handler(int button_type)
  {
    switch (button_type)
    {
      case Utils::BACK:
        game_info.menu_back();
        break;

      case Utils::PLAY:
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_INTRO, game_info.get_level_selected(), game_info.get_difficulty_selected());
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        break;

      case Utils::PLAYER_SOLO:
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_SELECTOR, 0, 0);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        break;

      case Utils::PLAYER_VS_IA:
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::IA, 0, 0);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        break;

      case Utils::EXIT:
        engine.quit();
        break;

      case Utils::SETTINGS:
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::CONFIG, 0, 0);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);

        // Guardamos en una variable el contenido de fichero de comfiguración
        EngineIO::InputEvent aux[18];
        KeyBindings().readKeyBindingsFile(aux); // Leemos fichero con valores asociados a los botones de partida
        game_info.set_conf_buttons(aux);
        break;

      case Utils::RESET_KEYB:
        game_info.set_default_keys();
        break;

      case Utils::RESET_ALL:
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::RESET_DATA, 0, 0);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        break;

      case Utils::SAVE:
        // Guardar configuración de botones actual
        EngineIO::InputEvent conf_buttons[NUM_KEYBINDINGS];
        game_info.get_conf_buttons(conf_buttons);
        KeyBindings().setKeyBindings(conf_buttons); // Modificamos el fichero
        keyboard.set_key_bindings(); // Actualizamos botones de partida
        // Actualiza teclas de movimiento de mapa en partida
        dynamic_cast<Dynamic_camera *>(game_info.get_dynamic_camera_ptr())->assign_keys();
        game_info.set_volume_aspect(game_info.get_conf_var(0), game_info.get_conf_var(1), game_info.get_conf_var(2));
        game_info.start_sound_assets(engine);
        game_info.set_window_size(engine);
        std::cout << "CONFIGURACION GUARDADA" << std::endl;
        game_info.menu_back();
        break;

      case Utils::BACK_TO_CONFIG:
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::CONFIG, 0, 0);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        break;

      case Utils::RESET_ALL_CONFIRM:
        // Guardar configuración de botones actual
        KeyBindings().setDefaultKeyBindings(conf_buttons);
        keyboard.set_key_bindings();
        dynamic_cast<Dynamic_camera *>(game_info.get_dynamic_camera_ptr())->assign_keys();
        game_info.reset_levels_info();
        game_info.set_volume_aspect(100, 100, 1);
        game_info.start_sound_assets(engine);
        game_info.set_window_size(engine);
        game_info.set_do_transition(true);
        game_info.set_build_menu(Utils::MENU_TYPE::INTRO, 0, 0);
        game_info.set_do_action(Utils::ACTIONS::GO_MENU);
        break;

      default:
        if (button_type >= Utils::PAUSE && button_type <= Utils::MAP_RIGHT) // Gestión de teclas de modificación
        {

          if (button_type != game_info.get_last_button() || !game_info.get_is_button_conf())
          { // Si no concuerda con el ultimo pulsado
            // std::cout << "HABILITADO BOTON  " << button_type-9 << std::endl;
            game_info.set_is_button_conf(true);
            game_info.set_last_button(button_type);
          }
          else
          { // Si pulsamos dos veces seguida el mismo es como dejar de seleccionar el boton
            // std::cout << "DESHABILITADO BOTON  " << button_type-9 << std::endl;
            game_info.set_is_button_conf(false);
          }
        }
        break;
    }
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine))
    {
      button_handler(type);
      if (is_changeable)
      {
        if (is_pressed)
        {
          set_active_texture(txt_on);
          is_pressed = false;
        }
        else
        {
          set_active_texture(txt_off);
          is_pressed = true;
        }
      }
    }
  }
};
