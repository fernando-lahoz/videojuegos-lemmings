#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class HUD : public Rigid_body
{
private:
  bool is_hovereable;
  bool is_clickable;
  bool is_changeable;
  bool is_selectable;
  bool is_cursor;
  std::string path;
  int n;
  bool changed = false;
  Texture txt;
  Game_info &game_info;
  int option_selected = 11;
  float last_position;
  bool multi_pressed = false;
  float timer_multipressed = 0.025f;

public:
  HUD(Point3f position, Vector2f size, Game_info &_game_info, Engine &engine, std::string _path, int _n, bool _is_hovereable = false, bool _is_clickable = true, bool _is_changeable = false, bool _is_selectable = true)
      : Rigid_body(position, size, _n != Utils::HUD::HUD_POPUP ? engine.load_texture(_path + std::to_string(_n) + ".png") : engine.load_texture(_path + ".png"), engine, "HUD"), game_info(_game_info) //, HUDs &_huds
  {
    multi_pressed = false;
    is_hovereable = _is_hovereable;
    is_clickable = _is_clickable;
    is_changeable = _is_changeable;
    is_selectable = _is_selectable;
    is_cursor = false;
    path = _path;
    n = _n;
    if (_n != Utils::HUD::HUD_POPUP)
    {
      txt = engine.load_texture(_path + std::to_string(_n) + ".png");
    }
    else
    {
      txt = engine.load_texture(_path + ".png");
    }
  }

  HUD(Point3f position, Vector2f size, Game_info &_game_info, Engine &engine, std::string _path, int _n, bool _is_hovereable, bool _is_clickable, bool _is_changeable, bool _is_selectable, bool _is_cursor)
      : Rigid_body(position, size, _n != Utils::HUD::HUD_POPUP ? engine.load_texture(_path + std::to_string(_n) + ".png") : engine.load_texture(_path + ".png"), engine, "HUD"), game_info(_game_info) //, HUDs &_huds
  {
    is_hovereable = _is_hovereable;
    is_clickable = _is_clickable;
    is_changeable = _is_changeable;
    is_selectable = _is_selectable;
    is_cursor = _is_cursor;
    path = _path;
    n = _n;
    if (_n != Utils::HUD::HUD_POPUP)
    {
      txt = engine.load_texture(_path + std::to_string(_n) + ".png");
    }
    else
    {
      txt = engine.load_texture(_path + ".png");
    }
    last_position = position.x;
  }

  void pre_physics(Engine &engine) override
  {
    if (is_cursor && option_selected != game_info.get_option_selected())
    {
      option_selected = game_info.get_option_selected();
      Point3f actual_position = get_position3D();
      auto new_position = Utils::positions[option_selected].x + actual_position.x - last_position;
      last_position = Utils::positions[option_selected].x;
      set_position3D(Point3f(new_position, Utils::positions[option_selected].y, 2));
    }
    if (multi_pressed)
    {
      timer_multipressed -= engine.get_delta_time() / engine.get_delta_time_factor();
      if (timer_multipressed < 0)
      {
        timer_multipressed = 0.025f;
        if (n == Utils::HUD_ADD_SPAWN_VELOCITY)
        {
          game_info.add_spawn_velocity();
        }
        else if (n == Utils::HUD_SUB_SPAWN_VELOCITY)
        {
          game_info.sub_spawn_velocity();
        }

        if (!contains_the_mouse(engine))
        {
          multi_pressed = false;
        }
      }
    }
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {

    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine) && n == Utils::HUD_POPUP)
    {
      if (!game_info.get_is_pop_exit_active())
      {
        game_info.set_pop_exit();
      }
      else
      {
        game_info.set_delete_exit();
      }
    }
    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine) && is_clickable && !game_info.get_is_pop_exit_active() /* && !(game_info.get_level_is_paused() && n != Utils::HUD_PAUSE)*/)
    {
      if (is_selectable)
      {
        game_info.set_option_selected(n);

        // Hacemos sonar el sonido de opcion seleccionada si la opcion no es reventar a todos en pedacitos
        if (n != Utils::HUD_ALL_EXPLODE)
        {
          Sound sound;
          switch (n)
          {
          case 2:
            sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND1);
            break;
          case 3:
            sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND2);
            break;
          case 4:
            sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND3);
            break;
          case 5:
            sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND4);
            break;
          case 6:
            sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND5);
            break;
          case 7:
            sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND6);
            break;
          case 8:
            sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND7);
            break;
          case 9:
            sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND8);
            break;
          default:
            sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND);
            break;
          }
          engine.get_sound_mixer().play_sound(sound, game_info.get_effects_volume());
        }
      }

      if (n == Utils::HUD_ALL_EXPLODE)
      {
        game_info.set_spawn_ended();
        game_info.set_all_die(true);
        auto &entities = engine.get_entities();
        int j = 0;

        // FIXME Esto es porque puedes clicar la habilidad mas de una vez, lo suyo seria que no pudieses
        bool isEveryOneDoomed = true;

        for (std::size_t i = 0; i < entities.size(); i++)
        {
          if (entities[i]->get_entity_name() == "Lemming")
          {
            j++;
            std::shared_ptr<Lemming> lemming_ptr = std::dynamic_pointer_cast<Lemming>(entities[i]);
            if (lemming_ptr)
            {
              // Miramos si algun lemming fue marcado para morir y con eso vemos si estan todos condenados
              isEveryOneDoomed &= lemming_ptr->get_dead_marked();
              lemming_ptr->set_dead_marked(true);
            }
          }
        }

        // Si aun no estaban condenados
        if (!isEveryOneDoomed)
        {
          // Hacemos que recen por su vida
          engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::OH_NO_SOUND), game_info.get_effects_volume());
        }

        if (j == 0)
          game_info.set_level_ended();
      }
      else if (n == Utils::HUD_ADD_SPAWN_VELOCITY)
      {
        timer_multipressed = 0.f;
        multi_pressed = true;
      }
      else if (n == Utils::HUD_SUB_SPAWN_VELOCITY)
      {
        timer_multipressed = 0.f;
        multi_pressed = true;
      }
      else if (n == Utils::HUD::HUD_ADD_VELOCITY)
      {
        game_info.add_game_speed();
        engine.set_delta_time_factor(game_info.get_game_speed());
      }
      else if (n == Utils::HUD::HUD_SUB_VELOCITY)
      {
        game_info.sub_game_speed();
        engine.set_delta_time_factor(game_info.get_game_speed());
      }
      else if (n == Utils::HUD_PAUSE)
      {
        // std::cout << (game_info.get_level_is_paused() ? "PAUSE\n" : "PLAY\n");
        game_info.set_level_is_paused(!game_info.get_level_is_paused());
        engine.set_is_game_paused(game_info.get_level_is_paused());
      }

      if (is_changeable)
      {
        if (changed)
        {
          changed = false;
          n--;
          txt = engine.load_texture(path + std::to_string(n) + ".png");
          set_active_texture(txt);
        }
        else
        {
          changed = true;
          n++;
          txt = engine.load_texture(path + std::to_string(n) + ".png");
          set_active_texture(txt);
        }
      }
    }

    if (event == EngineIO::InputEvent::MOUSE_HOVER && is_hovereable && !game_info.get_level_is_paused())
    {
      txt = engine.load_texture(path + std::to_string(n) + "_hover.png");
      set_active_texture(txt);
    }
  }

  void on_event_up([[maybe_unused]] Engine &engine, EngineIO::InputEvent event) override
  {

    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine) && is_clickable /* && !(game_info.get_level_is_paused() && n != Utils::HUD_PAUSE)*/)
    {
      multi_pressed = false;
    }
    if (event == EngineIO::InputEvent::MOUSE_HOVER && !game_info.get_level_is_paused())
    {

      if (n != Utils::HUD::HUD_POPUP)
      {
        txt = engine.load_texture(path + std::to_string(n) + ".png");
      }
      else
      {
        txt = engine.load_texture(path + ".png");
      }
      set_active_texture(txt);
    }
  }

  void on_collision(Engine &, EntityPtr) override
  {
  }
};
