#pragma once

#include <vector>

#include "lemmings/utils.hpp"
#include "engine/rigid_body.hpp"
#include "engine/entity.hpp"
#include "math/math.hpp"
#include "memory/keyBindings.hpp"
#include "memory/levelsInfo.hpp"
#include "memory/volumeAndAspect.hpp"

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
  bool can_do_transition = true;

  // credits
  int credit_frame = 0;

  // ia
  bool ia = false;

  // level selector
  int level_selected = 1;
  int difficulty_selected = 0;
  int level_selected_ia = 1;
  int difficulty_selected_ia = 0;
  bool is_arrow_hovered = false;

  // principal level settings
  std::shared_ptr<Rigid_body> map_ptr;
  int level = 0;
  int difficulty = 0;
  float game_speed = 1;
  bool level_ended = false;
  bool spawn_ended = false;
  bool level_is_paused = false;
  bool all_die = false;
  int level_ia = 0;
  int difficulty_ia = 0;

  // level info
  LevelsInfo levelsInfo;

  // camera settings
  bool do_restart_camera = false;
  bool is_camera_stopped = false;
  float pos_camera;
  Camera2D::ID game_camera_id;
  Camera2D *dynamic_camera = nullptr;

  // hud selection
  int option_selected = Utils::NO_OPTION_SELECTED;

  // Variables de configuración
  bool is_button_conf = false;                        // indica si está pulsado un botón del menu de configuración
  int last_button = -1;                               // indica el ultimo boton pulsado en el menu de configuración
  EngineIO::InputEvent conf_buttons[NUM_KEYBINDINGS]; // Guarda la configuración de teclas del fichero para modificarlo
  uint8_t conf_values[3];

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
  bool let_lemmings_spawn = false;

  // key bindings

  // ia

  // sound effects
  Sound SOUND_EFFECT[19];

  bool play_open_sound = false;
  bool play_letsgo_sound = false;
  bool play_music = false;
  bool is_door_open = false;

  // volume
  VolumeAndAspect volumeAndAspect;

public:
  enum SoundAssets
  {
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
  void start_sound_assets(Engine &engine)
  {
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
  Sound get_sound_asset(SoundAssets asset)
  {
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

    let_lemmings_spawn = false;
    play_open_sound = true;
    play_letsgo_sound = true;
    play_music = true;
    is_door_open = false;
  }

  int conversion_level_selected_ia()
  {
    if (ia)
    {
      if (difficulty_selected_ia == 0)
      {
        if (level_selected_ia == 2)
        {
          return 3;
        }
        return level_selected_ia;
      }
      else
      {
        return level_selected_ia;
      }
    }
    else
    {
      return level_selected;
    }
  }

  std::shared_ptr<Rigid_body> get_map_ptr()
  {
    return map_ptr;
  }

  void set_map_ptr(std::shared_ptr<Rigid_body> new_ptr)
  {
    map_ptr = new_ptr;
  }

  int conversion_level_ia()
  {
    if (ia)
    {
      if (difficulty_ia == 0)
      {
        if (level_ia == 2)
        {
          return 3;
        }
        return level_ia;
      }
      else
      {
        return level_ia;
      }
    }
    else
    {
      return level;
    }
  }

  int get_level()
  {
    if (ia)
    {
      return level_ia;
    }
    else
    {
      return level;
    }
  }
  int get_difficulty()
  {
    if (ia)
      return difficulty_ia;
    else
    {
      return difficulty;
    }
  }

  void set_ia(bool ia_) { ia = ia_; }
  int get_ia() const { return ia; }

  void set_do_action(int action) { do_action = action; }
  int get_do_action() const { return do_action; }

  void set_is_transition_done(bool new_value) { is_transition_done = new_value; }
  bool get_is_transition_done() const { return is_transition_done; }

  void set_do_transition(bool new_value) { do_transition = new_value; }
  bool get_do_transition() const { return do_transition; }

  void set_can_do_transition(bool new_value) { can_do_transition = new_value; }
  bool get_can_do_transition() const { return can_do_transition; }

  void add_level_selected()
  {
    if (ia)
    {
      level_selected_ia = math::min(level_selected_ia + 1, Utils::LEVEL_MAX_IA_DIFFICULTY[difficulty_selected_ia]);
    }
    else
    {
      level_selected = math::min(level_selected + 1, 30);
    }
  }
  void sub_level_selected()
  {
    if (ia)
      level_selected_ia = math::max(level_selected_ia - 1, 1);
    else
      level_selected = math::max(level_selected - 1, 1);
  }
  int get_level_selected() const
  {
    if (ia)
    {
      return level_selected_ia;
    }
    else
    {
      return level_selected;
    }
  }
  void set_level_selected(int new_level)
  {
    if (ia)
      level_selected_ia = new_level;
    else
      level_selected = new_level;
  }

  void add_difficulty_selected()
  {
    if (ia)
    {
      int aux = math::min(difficulty_selected_ia + 1, 1);
      if (aux != difficulty_selected_ia)
      {
        difficulty_selected_ia = aux;
        set_level_selected(1);
      }
    }
    else
    {
      int aux = math::min(difficulty_selected + 1, 3);
      if (aux != difficulty_selected)
      {
        difficulty_selected = aux;
        set_level_selected(1);
      }
    }
  }
  void sub_difficulty_selected()
  {
    if (ia)
    {
      int aux = math::max(difficulty_selected_ia - 1, 0);
      if (aux != difficulty_selected_ia)
      {
        difficulty_selected_ia = aux;
        set_level_selected(1);
      }
    }
    else
    {
      int aux = math::max(difficulty_selected - 1, 0);
      if (aux != difficulty_selected)
      {
        difficulty_selected = aux;
        set_level_selected(1);
      }
    }
  }
  int get_difficulty_selected() const
  {
    if (ia)
      return difficulty_selected_ia;
    else
      return difficulty_selected;
  }

  void add_game_speed() { game_speed = math::min(game_speed + 0.5, 2); }
  void sub_game_speed() { game_speed = math::max(game_speed - 0.5, 0.5); }
  float get_game_speed() const { return game_speed; }
  int get_game_speed_hud() const { return game_speed * 2; }

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
    if (ia)
    {
      if (_level != -1 && _difficulty != -1)
      {
        std::cout << "Level " << difficulty_ia << " : " << _difficulty << std::endl;
        level_ia = _level;
        difficulty_ia = _difficulty;
      }
    }
    else
    {
      if (_level != -1 && _difficulty != -1)
      {
        // std::cout << "Level " << level << " : " << _level << std::endl;
        level = _level;
        difficulty = _difficulty;
      }
    }
  }
  int get_build_menu() const { return build_menu; }

  void set_spawn_ended() { spawn_ended = true; }

  void set_option_selected(int option)
  {
    if (ia)
      option_selected = Utils::NO_OPTION_SELECTED;
    else
      option_selected = option;
  }
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
    if (spawn_velocity < 99)
    {
      std::cout << "spawn_velocity: " << spawn_velocity << std::endl;
      spawn_velocity = spawn_velocity + 1;
    }
  }
  void sub_spawn_velocity()
  {
    auto min_spawn_velocity = (ia ? Utils::LEVEL_SPAWN_VELOCITY_IA[difficulty_ia][level_ia] : Utils::LEVEL_SPAWN_VELOCITY[difficulty][level]);
    std::cout << "min_spawn_velocity: " << min_spawn_velocity << std::endl;
    if (spawn_velocity > min_spawn_velocity)
    {
      std::cout << "spawn_velocity: " << spawn_velocity << std::endl;
      spawn_velocity = spawn_velocity - 1;
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
    if (ia)
    {
      percen_lemmings_in = math::min(n_lemmings_in * 100 / Utils::LEVEL_N_LEMMINGS_IA[difficulty_ia][level_ia], 100);
    }
    else
    {
      percen_lemmings_in = math::min(n_lemmings_in * 100 / Utils::LEVEL_N_LEMMINGS[difficulty][level], 100);
    }
  }
  void sub_n_lemmings_in()
  {
    n_lemmings_in--;
    if (ia)
      percen_lemmings_in = math::min(n_lemmings_in * 100 / Utils::LEVEL_N_LEMMINGS_IA[difficulty_ia][level_ia], 100);
    else
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

  void set_dynamic_camera(Camera2D &cam) { dynamic_camera = &cam; }
  Camera2D &get_dynamic_camera() { return *dynamic_camera; }
  Camera2D *get_dynamic_camera_ptr() { return dynamic_camera; }

  void set_is_button_conf(bool _is_button_conf) { is_button_conf = _is_button_conf; }
  bool get_is_button_conf() { return is_button_conf; }

  void set_last_button(int _last_button) { last_button = _last_button; }
  int get_last_button() { return last_button; }

  void set_default_keys()
  {
    KeyBindings().setDefaultKeyBindings(conf_buttons);
  }

  void set_conf_buttons(EngineIO::InputEvent _conf_buttons[])
  {
    for (int i = 0; i < NUM_KEYBINDINGS; i++)
    {
      conf_buttons[i] = _conf_buttons[i];
    }
  }

  void set_conf_buttons(EngineIO::InputEvent _conf_button, int idx)
  {
    if (idx >= 0 && idx <= NUM_KEYBINDINGS)
    {
      for (int i = 0; i < NUM_KEYBINDINGS; i++)
        if (conf_buttons[i] == _conf_button)
          conf_buttons[i] = conf_buttons[idx];
      conf_buttons[idx] = _conf_button;
    }
    set_is_button_conf(false);
  }

  void get_conf_buttons(EngineIO::InputEvent _conf_buttons[])
  {
    for (int i = 0; i < NUM_KEYBINDINGS; i++)
      _conf_buttons[i] = conf_buttons[i];
  }

  EngineIO::InputEvent get_conf_buttons(int idx) { return conf_buttons[idx]; }

  uint8_t &get_conf_var(uint8_t idx) { return conf_values[idx]; }
  void set_conf_var(uint8_t idx, uint8_t value) { conf_values[idx] = value; }

  bool get_let_lemmings_spawn()
  {
    return let_lemmings_spawn;
  }

  void set_let_lemmings_spawn(bool value)
  {
    let_lemmings_spawn = value;
  }

  bool get_play_open_sound()
  {
    return play_open_sound;
  }

  void set_play_open_sound(bool value)
  {
    play_open_sound = value;
  }
  bool get_play_letsgo_sound()
  {
    return play_letsgo_sound;
  }

  void set_play_letsgo_sound(bool value)
  {
    play_letsgo_sound = value;
  }
  bool get_play_music()
  {
    return play_music;
  }

  void set_play_music(bool value)
  {
    play_music = value;
  }

  bool get_is_door_opening()
  {
    return is_door_open;
  }

  void set_is_door_opening(bool value)
  {
    is_door_open = value;
  }

  void menu_back()
  {
    set_build_menu(Utils::MENU_TYPE::TITLE);
    set_do_action(Utils::ACTIONS::GO_MENU);
    set_do_transition(true);
    if (build_menu == Utils::MENU_TYPE::CONFIG)
    {
      set_is_button_conf(false);
    }
  }

  bool is_selected_level_won()
  {
    if (ia)
      return levelsInfo.isAiLevelWon(difficulty_selected_ia, level_selected_ia);
    else
      return levelsInfo.isLevelWon(difficulty_selected, level_selected);
  }

  std::string get_selected_level_best_time()
  {
    if (ia)
    {
      int m = levelsInfo.getMin_Ai(difficulty_selected_ia, level_selected_ia);
      int s = levelsInfo.getSec_Ai(difficulty_selected_ia, level_selected_ia);
      return std::to_string(m) + (s < 10 ? "-0" : "-") + std::to_string(s);
    }
    else
    {
      int m = levelsInfo.getMin(difficulty_selected, level_selected);
      int s = levelsInfo.getSec(difficulty_selected, level_selected);
      return std::to_string(m) + (s < 10 ? "-0" : "-") + std::to_string(s);
    }
  }

  std::string get_selected_level_best_perc()
  {
    if (ia)
      return std::to_string(levelsInfo.getPerc_Ai(difficulty_selected_ia, level_selected_ia)) + "%";
    else
      return std::to_string(levelsInfo.getPerc(difficulty_selected, level_selected)) + "%";
  }

  void manage_level_results()
  {
    if (ia)
    {
      int needed = Utils::LEVEL_SAVE_LEMMINGS_IA[difficulty_ia][level_ia] * 100 / Utils::LEVEL_N_LEMMINGS_IA[difficulty_ia][level_ia];
      int rescued = get_percen_lemmings_in();
      int limit_time = Utils::LEVEL_TIME_LIMIT_IA[difficulty_ia][level_ia];
      int left_time = get_actual_minutes_left() * 60 + get_actual_seconds_left();
      if (rescued >= needed && left_time > 0)
      {
        int game_time = limit_time - left_time;
        LevelInfo wonLevel(true, game_time / 60, game_time % 60, rescued);
        levelsInfo.setNewAiLevelInfo(difficulty_ia, level_ia, wonLevel);
      }
    }
    else
    {
      int needed = Utils::LEVEL_SAVE_LEMMINGS[difficulty][level] * 100 / Utils::LEVEL_N_LEMMINGS[difficulty][level];
      int rescued = get_percen_lemmings_in();
      int limit_time = Utils::LEVEL_TIME_LIMIT[difficulty][level];
      int left_time = get_actual_minutes_left() * 60 + get_actual_seconds_left();
      if (rescued >= needed && left_time > 0)
      {
        int game_time = limit_time - left_time;
        LevelInfo wonLevel(true, game_time / 60, game_time % 60, rescued);
        levelsInfo.setNewLevelInfo(difficulty, level, wonLevel);
      }
    }
  }

  void set_config_screen()
  {
    conf_values[0] = volumeAndAspect.getMusicVol();
    conf_values[1] = volumeAndAspect.getEffectsVol();
    conf_values[2] = volumeAndAspect.getAspect();
  }

  void set_volume_aspect(uint8_t _music, uint8_t _effects, uint8_t _aspect)
  {
    volumeAndAspect.setMusicVol(_music);
    volumeAndAspect.setEffectsVol(_effects);
    volumeAndAspect.setAspect(_aspect);
    volumeAndAspect.writeVolAspFile();
  }

  uint8_t get_music_volume() { return volumeAndAspect.getMusicVol(); }
  uint8_t get_effects_volume() { return volumeAndAspect.getEffectsVol(); }
  uint8_t get_aspect_ratio() { return volumeAndAspect.getAspect(); }

  void set_window_size(Engine &engine)
  {
    uint8_t aspect = volumeAndAspect.getAspect();
    if (aspect == 3)
    {
      engine.set_fullscreen();
    }
    else
    {
      engine.set_windowmode();
      switch (aspect)
      {
      case 0:
        engine.set_window_size(Vector2i{640, 400});
        break;
      case 1:
        engine.set_window_size(Vector2i{960, 600});
        break;
      case 2:
        engine.set_window_size(Vector2i{1280, 800});
        break;
      }
    }
  }

  void reset_levels_info()
  {
    levelsInfo.setDefaultLevelsInfo();
  }

  void reset_volume_aspect_info()
  {
    volumeAndAspect.setDefaultVolAsp();
  }
};