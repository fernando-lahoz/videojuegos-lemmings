
#pragma once

#include "utils.hpp"
// #include "engine/engine.hpp"
class Level_info
{
private:
  int option_selected = 11;
  Texture txt;
  bool is_cursor_hover = false;

public:
  void set_option_selected(int option) { option_selected = option; }
  int get_option_selected() { return option_selected; }

  void set_is_cursor_hover(bool _is_cursor_hover) { is_cursor_hover = _is_cursor_hover; }
  bool get_is_cursor_hover() { return is_cursor_hover; }

  void set_txt(std::string path, Engine &engine) { txt = engine.load_texture(path); }
  Texture get_txt() { return txt; }
};