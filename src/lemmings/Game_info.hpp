
#pragma once

#include <vector>

#include "lemmings/utils.hpp"
#include "engine/entity.hpp"
#include "math/math.hpp"

class Game_info
{
private:
  // global settings
  int do_action = Utils::ACTIONS::NO_ACTION;
  int actual_state = Utils::MENU;
  bool sound_effects = true;
  int build_level = 0;
  int build_difficulty = 0;
  int build_menu = 0;
  bool is_transition_done = false;
  bool do_transition = false;

  // credits
  int credit_frame = 0;

  // level selector
  int level_selected = 1;
  int difficulty_selected = 0;
  bool is_arrow_hovered = false;

  // principal level settings
  int level = 0;
  int difficulty = 0;
  int game_speed = 1;
  bool level_ended = false;
  bool spawn_ended = false;
  bool level_is_paused = false;
  bool all_die = false;

  // camera settings
  bool do_restart_camera = false;
  bool is_camera_stopped = false;
  float pos_camera;
  Camera2D::ID game_camera_id;

  // hud selection
  int option_selected = Utils::NO_OPTION_SELECTED;

  // cursor
  Texture cursor_txt;
  bool is_cursor_hover = false;
  bool is_action_possible = false;
  Entity *cursor_menu = nullptr;

  // lemming count
  int lemmings_hovered = 0;
  std::string lemming_hovered_type = "";

  // level stats
  std::vector<int> skill_amount;
  int n_lemmings_out = 0;
  int n_lemmings_in = 0;
  int spawned_lemmings = 0;
  int percen_lemmings_in = 0;
  double time_left = 0.0f;
  int actual_minutes_left = 0;
  int actual_seconds_left = 0;
  int spawn_velocity = 1;

  // sound effects
  Sound SOUND_EFFECT[19];

public:

  enum SoundAssets{
    CHAIN_SOUND,
    CHANGE_OP_SOUND,
    CHINK_SOUND,
    DIE_SOUND,
    DOOR_SOUND,
    ELECTRIC_SOUND,
    EXPLODE_SOUND,
    FIRE_SOUND,
    GLUG_SOUND,
    LETS_GO_SOUND,
    MOUSE_PRESS_SOUND,
    OH_NO_SOUND,
    SPLASH_SOUND,
    SPLAT_SOUND,
    TENTON_SOUND,
    THUD_SOUND,
    THUNK_SOUND,
    TING_SOUND,
    YIPEE_SOUND
  };

  // Inicializa los efectos de sonido
  void start_sound_assets(Engine& engine){
    SOUND_EFFECT[CHAIN_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/chain.wav");
    SOUND_EFFECT[CHANGE_OP_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/changeop.wav");
    SOUND_EFFECT[CHINK_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/chink.wav");
    SOUND_EFFECT[DIE_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/die.wav");
    SOUND_EFFECT[DOOR_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/door.wav");
    SOUND_EFFECT[ELECTRIC_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/electric.wav");
    SOUND_EFFECT[EXPLODE_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/explode.wav");
    SOUND_EFFECT[FIRE_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/fire.wav");
    SOUND_EFFECT[GLUG_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/glug.wav");
    SOUND_EFFECT[LETS_GO_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/letsgo.wav");
    SOUND_EFFECT[MOUSE_PRESS_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/mousepre.wav");
    SOUND_EFFECT[OH_NO_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/ohno.wav");
    SOUND_EFFECT[SPLASH_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/splash.wav");
    SOUND_EFFECT[SPLAT_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/splat.wav");
    SOUND_EFFECT[TENTON_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/tenton.wav");
    SOUND_EFFECT[THUD_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/thud.wav");
    SOUND_EFFECT[THUNK_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/thunk.wav");
    SOUND_EFFECT[TING_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/ting.wav");
    SOUND_EFFECT[YIPEE_SOUND] = engine.get_sound_mixer().load_sound("assets/sounds/yipee.wav");
  }

  // Devuelve el sonido asociado al asset correspondiente
  Sound get_sound_asset(SoundAssets asset){
    return SOUND_EFFECT[asset];
  }

  void start_game_info(int _level, int _difficulty)
  {
    credit_frame = 0;
    game_speed = 1;
    level_is_paused = false;
    do_restart_camera = true;
    is_camera_stopped = false;
    level_ended = false;
    all_die = false;
    level = _level;
    difficulty = _difficulty;
    option_selected = Utils::NO_OPTION_SELECTED;
    is_action_possible = false;
    is_cursor_hover = false;
    n_lemmings_out = 0;
    n_lemmings_in = 0;
    lemmings_hovered = 0;
    lemming_hovered_type = "";
    spawned_lemmings = 0;
    percen_lemmings_in = 0;
    time_left = Utils::LEVEL_TIME_LIMIT[_difficulty][_level];
    spawn_velocity = Utils::LEVEL_SPAWN_VELOCITY[_difficulty][_level];
    skill_amount.clear();
    skill_amount = Utils::LEVEL_SKILLS_AMOUNT[_difficulty][_level];
    actual_minutes_left = 0;
    actual_seconds_left = 0;
    spawn_ended = false;
  }
  int get_level() const { return level; }
  int get_difficulty() const { return difficulty; }

  void set_do_action(int action) { do_action = action; }
  int get_do_action() const { return do_action; }

  void set_is_transition_done(bool new_value) { is_transition_done = new_value; }
  bool get_is_transition_done() const { return is_transition_done; }

  void set_do_transition(bool new_value) { do_transition = new_value; }
  bool get_do_transition() const { return do_transition; }

  void add_level_selected() { level_selected = math::min(level_selected + 1, 30); }
  void sub_level_selected() { level_selected = math::max(level_selected - 1, 1); }
  int get_level_selected() const { return level_selected; }
  void set_level_selected(int new_level) { level_selected = new_level; }

  void add_difficulty_selected()
  {
    int aux = math::min(difficulty_selected + 1, 3);
    if (aux != difficulty_selected)
    {
      difficulty_selected = aux;
      set_level_selected(1);
    }
  }
  void sub_difficulty_selected()
  {
    int aux = math::max(difficulty_selected - 1, 0);
    if (aux != difficulty_selected)
    {
      difficulty_selected = aux;
      set_level_selected(1);
    }
  }
  int get_difficulty_selected() const { return difficulty_selected; }

  void add_game_speed() { game_speed = math::min(game_speed + 1, 4); }
  void sub_game_speed() { game_speed = math::max(game_speed - 1, 1); }
  int get_game_speed() const { return game_speed; }

  void add_spawned_lemmings() { spawned_lemmings++; }
  void set_spawned_lemmings(int new_value) { spawned_lemmings = new_value; }
  int get_spawned_lemmings() const { return spawned_lemmings; }

  void set_is_arrow_hovered(bool new_value) { is_arrow_hovered = new_value; }
  bool get_is_arrow_hovered() const { return is_arrow_hovered; }

  void set_credit_frame(int new_value) { credit_frame = new_value; }
  int get_credit_frame() const { return credit_frame; }

  void set_do_restart_camera(bool new_value) { do_restart_camera = new_value; }
  bool get_do_restart_camera() const { return do_restart_camera; }

  void set_level_is_paused(bool new_value) { level_is_paused = new_value; }
  bool get_level_is_paused() const { return level_is_paused; }

  void set_all_die(bool new_value) { all_die = new_value; }
  bool get_all_die() const { return all_die; }

  void set_pos_camera(float new_value) { pos_camera = new_value; }
  float get_pos_camera() const { return pos_camera; }

  void set_is_camera_stopped(bool new_value) { is_camera_stopped = new_value; }
  bool get_is_camera_stopped() const { return is_camera_stopped; }

  void set_actual_state(int state) { actual_state = state; }
  int get_actual_state() const { return actual_state; }

  void set_sound_effects(bool new_value) { sound_effects = new_value; }
  bool get_sound_effects() const { return sound_effects; }

  void set_build_level(int _level) { build_level = _level; }
  int get_build_level() const { return build_level; }

  void set_build_difficulty(int _difficulty) { build_difficulty = _difficulty; }
  int get_build_difficulty() const { return build_difficulty; }

  void set_build_menu(int _menu, int _level = -1, int _difficulty = -1)
  {
    build_menu = _menu;
    if (_level != -1 && _difficulty != -1)
    {
      level = _level;
      difficulty = _difficulty;
    }
  }
  int get_build_menu() const { return build_menu; }

  void set_spawn_ended() { spawn_ended = true; }

  void set_option_selected(int option) { option_selected = option; }
  int get_option_selected() const { return option_selected; }

  void sub_skill_amount(int i) { skill_amount[i]--; }
  int get_skill_amount(int i) const { return skill_amount[i]; }
  int get_skill_amount0() const { return skill_amount[0]; }
  int get_skill_amount1() const { return skill_amount[1]; }
  int get_skill_amount2() const { return skill_amount[2]; }
  int get_skill_amount3() const { return skill_amount[3]; }
  int get_skill_amount4() const { return skill_amount[4]; }
  int get_skill_amount5() const { return skill_amount[5]; }
  int get_skill_amount6() const { return skill_amount[6]; }
  int get_skill_amount7() const { return skill_amount[7]; }

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
  void set_level_ended() { level_ended = true; }

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
    percen_lemmings_in = math::min(n_lemmings_in * 100 / Utils::LEVEL_N_LEMMINGS[difficulty][level], 100);
  }
  void sub_n_lemmings_in()
  {
    n_lemmings_in--;
    percen_lemmings_in = math::min(n_lemmings_in * 100 / Utils::LEVEL_N_LEMMINGS[difficulty][level], 100);
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

  void set_lemming_hovered_type(std::string new_value) { lemming_hovered_type = new_value; }
  std::string get_lemming_hovered_type() const { return lemming_hovered_type; }

  void set_cursor_menu_visible()
  {
    auto [cursorX, cursorY] = cursor_menu->get_position2D();
    cursor_menu->set_position3D(Point3f{cursorX, cursorY, -INFINITY});
  }

  void set_cursor_menu(EntityPtr cursor) { cursor_menu = cursor.get(); }

  void set_game_camera_id(Camera2D::ID id) { game_camera_id = id; }
  Camera2D::ID get_game_camera_id() { return game_camera_id; }
};