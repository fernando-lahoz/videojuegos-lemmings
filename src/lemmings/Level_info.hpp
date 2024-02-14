
#pragma once

#include "utils.hpp"
// #include "engine/engine.hpp"
class Level_info
{
private:
  int option_selected = Utils::NO_OPTION_SELECTED;
  Texture txt;
  bool is_cursor_hover = false;
  bool is_action_possible = false;
  int lemmings_hovered = 0;

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
};