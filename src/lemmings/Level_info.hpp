
#pragma once

#include "utils.hpp"
class Level_info
{
private:
  int option_selected = Utils::NO_OPTION_SELECTED;
  Texture txt;
  bool is_cursor_hover = false;
  bool is_action_possible = false;
  int lemmings_hovered = 0;

  // Este booleano indica si un lemming es marcado para explotar
  bool dead_marked = false;
  // Este es el tiempo de vida que le queda al lemming si es marcado para explotar
  double time_to_live = 5.0f;

public:
  void set_option_selected(int option)
  {
    option_selected = option;
  }
  int get_option_selected() { return option_selected; }

  void action_done()
  {
    is_action_possible = false;
  }
  void check_action_possible()
  {
    if (option_selected != Utils::NO_OPTION_SELECTED)
    {
      is_action_possible = true;
    }
  }
  bool get_action_possible() { return is_action_possible; }

  void add_lemming_hovered() { lemmings_hovered++; }
  void sub_lemming_hovered() { lemmings_hovered--; }

  void set_is_cursor_hover(bool _is_cursor_hover) { is_cursor_hover = _is_cursor_hover; }
  bool get_is_cursor_hover() { return is_cursor_hover; }

  void set_txt(std::string path, Engine &engine) { txt = engine.load_texture(path); }
  Texture get_txt() { return txt; }

  void set_dead_marked(bool new_value) { dead_marked = new_value; }
  bool get_dead_marked() { return dead_marked; }

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