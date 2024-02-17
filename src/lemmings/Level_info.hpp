
#pragma once

#include "utils.hpp"
class Level_info
{
private:
  // principal settings
  int level = 0;
  bool is_playing = false;
  bool level_ended = false;
  bool spawn_ended = false;

  // hud selection
  int option_selected = Utils::NO_OPTION_SELECTED;

  // cursor
  Texture cursor_txt;
  bool is_cursor_hover = false;
  bool is_action_possible = false;

  // lemming count
  int lemmings_hovered = 0;
  std::string lemming_hovered_type = "";

  // level stats
  int n_lemmings_out = 0;
  int n_lemmings_in = 0;
  int percen_lemmings_in = 0;
  double time_left = 0.0f;
  int actual_minutes_left = 0;
  int actual_seconds_left = 0;
  int spawn_velocity = 1;

  // Este booleano indica si un lemming es marcado para explotar
  bool dead_marked = false;
  // Este es el tiempo de vida que le queda al lemming si es marcado para explotar
  double time_to_live = 5.0f;

public:
  void start_level_info(int _level)
  {
    level_ended = false;
    is_playing = true;
    level = _level;
    option_selected = Utils::NO_OPTION_SELECTED;
    is_action_possible = false;
    is_cursor_hover = false;
    n_lemmings_out = 0;
    n_lemmings_in = 0;
    lemming_hovered_type = "";
    time_to_live = 5.0f;
    percen_lemmings_in = 0;
    time_left = Utils::LEVEL_TIME_LIMIT[_level];
    spawn_velocity = Utils::LEVEL_SPAWN_VELOCITY[_level];
    actual_minutes_left = 0;
    actual_seconds_left = 0;
    spawn_ended = false;
  }
  void set_spawn_ended() { spawn_ended = true; }

  void set_option_selected(int option) { option_selected = option; }
  int get_option_selected() const { return option_selected; }

  void action_done() { is_action_possible = false; }
  void check_action_possible()
  {
    if (option_selected != Utils::NO_OPTION_SELECTED)
    {
      is_action_possible = true;
    }
  }
  bool get_action_possible() const { return is_action_possible; }

  bool get_level_ended() const { return level_ended; }

  void add_lemmings_hovered() { lemmings_hovered++; }
  void sub_lemmings_hovered() { lemmings_hovered--; }
  int get_lemmings_hovered() const { return lemmings_hovered; }

  void add_spawn_velocity()
  {
    if (spawn_velocity < 97)
    {
      spawn_velocity = spawn_velocity + 3;
    }
  }
  void sub_spawn_velocity()
  {
    if (spawn_velocity > 3)
    {
      spawn_velocity = spawn_velocity - 3;
    }
  }
  int get_spawn_velocity() const { return spawn_velocity; }

  void add_n_lemmings_out() { n_lemmings_out++; }
  void sub_n_lemmings_out()
  {
    n_lemmings_out--;
    if (n_lemmings_out == 0 && spawn_ended)
    {
      level_ended = true;
    }
  }
  int get_n_lemmings_out() const { return n_lemmings_out; }

  void set_time_left(double new_value)
  {
    actual_minutes_left = int(new_value) / 60;
    actual_seconds_left = int(new_value) % 60;
    time_left = new_value;
    if (new_value == 0)
    {
      level_ended = true;
    }
  }

  double get_time_left() const { return time_left; }

  int get_actual_minutes_left() const { return actual_minutes_left; }
  int get_actual_seconds_left() const { return actual_seconds_left; }

  void add_n_lemmings_in()
  {
    n_lemmings_in++;
    percen_lemmings_in = n_lemmings_in * 100 / Utils::LEVEL_N_LEMMINGS[level];
  }
  void sub_n_lemmings_in()
  {
    n_lemmings_in--;
    percen_lemmings_in = n_lemmings_in / Utils::LEVEL_N_LEMMINGS[level];
  }

  int get_n_lemmings_in() const { return n_lemmings_in; }
  int get_percen_lemmings_in() const { return percen_lemmings_in; }

  void set_is_cursor_hover(bool _is_cursor_hover)
  {
    if (_is_cursor_hover == false)
    {
      if (lemmings_hovered == 0)
      {
        is_cursor_hover = _is_cursor_hover;
      }
    }
    else
    {
      is_cursor_hover = _is_cursor_hover;
    }
  }
  bool get_is_cursor_hover() { return is_cursor_hover; }

  void set_cursor_txt(std::string path, Engine &engine) { cursor_txt = engine.load_texture(path); }
  Texture get_cursor_txt() { return cursor_txt; }

  void set_dead_marked(bool new_value) { dead_marked = new_value; }
  bool get_dead_marked() { return dead_marked; }

  void set_lemming_hovered_type(std::string new_value) { lemming_hovered_type = new_value; }
  std::string get_lemming_hovered_type() const { return lemming_hovered_type; }

  // Pre: True
  // Post: Actualiza el tiempo de vida del lemming, de estar marcado para morir
  // y lo hace explotar en caso de que se acabe su tiempo de vida
  bool update_explode_countdown(Engine &engine)
  {
    // Si el lemming ha sido marcado para morir
    if (dead_marked)
    {
      // Restamos el delta time si el tiempo de vida es mayor a cero
      if (time_to_live > 0.0f)
        time_to_live -= engine.get_delta_time();

      // Si se acaba el tiempo explotamos
      if (time_to_live <= 0.0f)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    return false;
  }
};