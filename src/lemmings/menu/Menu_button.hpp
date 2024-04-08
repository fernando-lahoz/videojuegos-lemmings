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

  //Devuelve el nombre del fichero que corresponde a la imagen del tipo de botón
  // suministrado como entrada
  std::string name_file(int _type)
  {
    std::string n_file;

    if(_type < 6)
    {
      n_file = "assets/menu/menu_button_" + std::to_string(_type) + ".png";
    }
    else 
    {//Botones de modificar teclas
      if(_type == Utils::PAUSE)
      {
        n_file = "assets/menu/config_pause.png";
      }
      else if(_type >= Utils::ABILITY_1 && _type <= Utils::ABILITY_8){
        n_file = "assets/menu/config_skill_" + std::to_string(_type - 5) + ".png";
      }
      else if(_type == Utils::EXPLODE_ALL)
      {
        n_file = "assets/menu/config_explode_all.png";	
      }
      else if(_type == Utils::ABILITY_UP)
      {
        n_file = "assets/menu/config_skill_left.png";	
      }
      else if(_type == Utils::ABILITY_DOWN)
      {
        n_file = "assets/menu/config_skill_right.png";	
      }
      else if(_type == Utils::SPEED_UP)
      {
        n_file = "assets/menu/config_speed_plus.png";	
      }
      else if(_type == Utils::SPEED_DOWN)
      {
        n_file = "assets/menu/config_speed_minus.png";	
      }
      else if(_type == Utils::SPAWN_UP)
      {
        n_file = "assets/menu/config_spawn_plus.png";	
      }
      else if(_type == Utils::SPAWN_DOWN)
      {
        n_file = "assets/menu/config_spawn_minus.png";	
      }
      else if(_type == Utils::MAP_LEFT)
      {
        n_file = "assets/menu/config_map_left.png";	
      }
      else if(_type == Utils::MAP_RIGHT)
      {
        n_file = "assets/menu/config_map_right.png";	
      }
      else if(_type == Utils::SAVE)
      {
        n_file = "assets/menu/menu_conf_save.png";	
      }

    }
    return n_file;
  }

public:
  Menu_button(Point3f position, Vector2f size, Engine &_engine, Game_info &_game_info, Keyboard_manager &_keyboard, int _type, bool _is_changeable = false)
      : Rigid_body(position, size, !_game_info.get_sound_effects() && _is_changeable ? _engine.load_texture("assets/menu/menu_button_" + std::to_string(_type + 1) + ".png") : _engine.load_texture(name_file(_type)), engine, "Menu Button"),
        type(_type), game_info(_game_info), engine(_engine), keyboard(_keyboard)
  {
    std::cout << "Type: " << _type << std::endl;
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
    if (button_type == Utils::PLAYER_SOLO)
    {
      game_info.set_do_transition(true);
      game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_SELECTOR, 0, 0);
      game_info.set_do_action(Utils::ACTIONS::GO_MENU);
    }
    else if (button_type == Utils::PLAYER_VS_IA)
    {
      game_info.set_do_transition(true);
      game_info.set_build_menu(Utils::MENU_TYPE::LEVEL_INTRO, 0, 0);
      game_info.set_do_action(Utils::ACTIONS::GO_MENU);
    }
    else if (button_type == Utils::SOUND_EFFECTS)
    {
      game_info.set_sound_effects(!game_info.get_sound_effects());
    }
    else if (button_type == Utils::EXIT)
    {
      engine.quit();
    }
    else if (button_type == Utils::CONFIGURACION)
    {
      game_info.set_do_transition(true);
      game_info.set_build_menu(Utils::MENU_TYPE::CONFIG, 0, 0);
      game_info.set_do_action(Utils::ACTIONS::GO_MENU);

      //Guardamos en una variable el contenido de fichero de comfiguración
      EngineIO::InputEvent aux[18];
      KeyBindings().readKeyBindingsFile(aux);//Leemos fichero con valores asociados a los botones de partida
      game_info.set_conf_buttons(aux);

    }
    else if (button_type >= Utils::PAUSE && button_type <= Utils::MAP_RIGHT)//Gestión de teclas de modificación
    {

      if(button_type != game_info.get_last_button() || !game_info.get_is_button_conf())
      {//Si no concuerda con el ultimo pulsado
        //std::cout << "HABILITADO BOTON  " << button_type-6 << std::endl;
        game_info.set_is_button_conf(true);
        game_info.set_last_button(button_type);
      }
      else
      {//Si pulsamos dos veces seguida el mismo es como dejar de seleccionar el boton
        //std::cout << "DESHABILITADO BOTON  " << button_type-6 << std::endl;
        game_info.set_is_button_conf(false);
      }
    }
    else if(button_type >= Utils::SAVE)
    {
      //Guardar configuración de botones actual
      EngineIO::InputEvent conf_buttons[NUM_KEYBINDINGS];
      game_info.get_conf_buttons(conf_buttons);
      KeyBindings().setKeyBindings(conf_buttons);//Modificamos el fichero

      keyboard.set_key_bindings();//Actualizamos botones de partida
      
      //Actualiza teclas de movimiento de mapa en partida
      dynamic_cast<Dynamic_camera *>(game_info.get_dynamic_camera_ptr())->assign_keys();
      std::cout << "CONFIGURACION GUARDADA"<< std::endl;
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
