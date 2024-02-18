#pragma once

#include "engine/rigid_body.hpp"
#include "engine/render_2D.hpp"

#include "lemmings/structure/Chain.hpp"
#include "lemmings/utils.hpp"

class Lemming : public Rigid_body
{
  bool on_ground = false;
  Texture txt;
  Game_info &game_info;
  Engine &engine;
  float time_frame_sprite = 0.0f; // Acumulador de tiempo para la animación del sprite
  std::string base_path;          // Base para el path de las texturas de animación
  std::string type = "WALKER";
  bool is_loop;           // Indica si la animación es en bucle
  bool is_playing = true; // Indica si la animación está actualmente en reproducción
  int current_frame = 0;  // Frame actual de la animación
  int distance_fall = 0;
  bool do_action_in_frame = false;
  bool is_hovered = false;

  int skills = Utils::NO_SKILLS;

  int state = Utils::IDLE;

  int direction = 1; // Comienza moviéndose hacia la derecha

  std::string get_type()
  {
    return type;
  }

  void go_idle()
  {
    state = Utils::IDLE;
    type = Utils::LEMMING_TYPE[Utils::IDLE];
    // std::cout << "GO IDLE\n";
  }

  void go_walk()
  {
    state = Utils::WALKING;
    if (skills & Utils::FLOAT && skills & Utils::CLIMB)
    {
      type = Utils::LEMMING_TYPE[14]; // ATHLETE
    }
    else if (skills & Utils::FLOAT)
    {
      type = Utils::LEMMING_TYPE[Utils::FLOATING];
    }
    else if (skills & Utils::CLIMB)
    {
      type = Utils::LEMMING_TYPE[Utils::CLIMBING];
    }
    else
    {
      type = Utils::LEMMING_TYPE[Utils::WALKING];
    }
    // std::cout << "GO WALKING\n";
  }

  void go_fall()
  {
    state = Utils::FALLING;
    if (skills & Utils::FLOAT && skills & Utils::CLIMB)
    {
      type = Utils::LEMMING_TYPE[14]; // ATHLETE
    }
    else if (skills & Utils::FLOAT)
    {
      type = Utils::LEMMING_TYPE[Utils::FLOATING];
    }
    else if (skills & Utils::CLIMB)
    {
      type = Utils::LEMMING_TYPE[Utils::CLIMBING];
    }
    else
    {
      type = Utils::LEMMING_TYPE[Utils::FALLING];
    }
    // std::cout << "GO FALLING\n";
  }

  void go_block()
  {
    state = Utils::BLOCKING;
    type = Utils::LEMMING_TYPE[Utils::BLOCKING];
    // std::cout << "GO BLOCKING\n";
  }

  void go_build()
  {
    state = Utils::BUILDING;
    // std::cout << "GO BUILDING\n";
    type = Utils::LEMMING_TYPE[Utils::BUILDING];
  }

  void go_climb()
  {
    state = Utils::CLIMBING;
    if (skills & Utils::FLOAT && skills & Utils::CLIMB)
    {
      type = Utils::LEMMING_TYPE[14]; // ATHLETE
    }
    else if (skills & Utils::FLOAT)
    {
      type = "ERROR NO HAVE CLIMB SKILL BUT FLOAT SKILL HAS";
    }
    else
    {
      type = Utils::LEMMING_TYPE[Utils::CLIMBING];
    }
    // std::cout << "GO CLIMBING\n";
  }

  void go_float()
  {
    state = Utils::FLOATING;
    if (skills & Utils::FLOAT && skills & Utils::CLIMB)
    {
      type = Utils::LEMMING_TYPE[14]; // ATHLETE
    }
    else if (skills & Utils::CLIMB)
    {
      type = "ERROR NO HAVE FLOAT SKILL BUT CLIMB SKILL HAS";
    }
    else
    {
      type = Utils::LEMMING_TYPE[Utils::FLOATING];
    }
    // std::cout << "GO FLOATING\n";
  }

  void go_explode()
  {
    state = Utils::EXPLODING;
    type = Utils::LEMMING_TYPE[Utils::EXPLODING];
    // std::cout << "GO EXPLODING\n";
  }

  void go_dig()
  {
    state = Utils::DIGGING;
    type = Utils::LEMMING_TYPE[Utils::DIGGING];
    // std::cout << "GO DIGGING\n";
  }

  void go_bash()
  {
    state = Utils::BASHING;
    type = Utils::LEMMING_TYPE[Utils::BASHING];
    // std::cout << "GO BASHING\n";
  }

  void go_mine()
  {
    state = Utils::MINING;
    type = Utils::LEMMING_TYPE[Utils::MINING];
    // std::cout << "GO MINING\n";
  }

  void go_escape()
  {
    state = Utils::ESCAPING;
    type = Utils::LEMMING_TYPE[Utils::ESCAPING];
    // std::cout << "GO MINING\n";
  }

  void go_drown()
  {
    state = Utils::DROWNING;
    type = Utils::LEMMING_TYPE[Utils::DROWNING];
    // std::cout << "GO MINING\n";
  }

  void go_crash()
  {
    state = Utils::CRASHING;
    type = Utils::LEMMING_TYPE[Utils::CRASHING];
    // std::cout << "GO MINING\n";
  }

  bool is_idle()
  {
    return state == Utils::IDLE;
  }

  bool is_falling()
  {
    return state == Utils::FALLING;
  }

  bool is_walking()
  {
    return state == Utils::WALKING;
  }

  bool is_blocking()
  {
    return state == Utils::BLOCKING;
  }

  bool is_building()
  {
    return state == Utils::BUILDING;
  }

  bool is_climbing()
  {
    return state == Utils::CLIMBING;
  }

  bool is_floating()
  {
    return state == Utils::FLOATING;
  }

  bool is_exploding()
  {
    return state == Utils::EXPLODING;
  }

  bool is_digging()
  {
    return state == Utils::DIGGING;
  }

  bool is_bashing()
  {
    return state == Utils::BASHING;
  }

  bool is_mining()
  {
    return state == Utils::MINING;
  }

  bool is_escaping()
  {
    return state == Utils::ESCAPING;
  }

  bool is_drowning()
  {
    return state == Utils::DROWNING;
  }

  bool is_crashing()
  {
    return state == Utils::CRASHING;
  }

public:
  Lemming(Point3f position, Vector2f diagonal, Engine &_engine, Game_info &_game_info)
      : Rigid_body(position, diagonal,
                   _engine.load_texture("assets/lemming/lemming_1_2_0.png"),
                   "Lemming", "Lemming"),
        game_info(_game_info), engine(_engine)
  {
    // gravity = 3;
    // enable_gravity();
  }

  int get_state()
  {
    return state;
  }

  int skill_to_index(int skill)
  {
    int index = 0;
    while (skill > 1)
    {
      skill = static_cast<Utils::Lemming_Skills>(skill >> 1);
      ++index;
    }
    return index;
  }

  void add_skill_explode_all()
  {
    skills = skills | Utils::EXPLODE;
  }

  /**
   * @brief Adds a skill to the Lemming.
   *
   * @param skill The skill to add.
   * @return True if the skill was successfully added, false otherwise.
   */
  bool add_skill(int skill)
  {
    int ind = skill_to_index(skill);
    int a = game_info.get_skill_amount(Utils::SKILL_TO_SKILLS_AMOUNT[ind]);

    std::cout << "skill_amount_index = " << ind << std::endl;
    std::cout << "skill_amount = " << a << std::endl;
    if (a <= 0)
    {
      return false;
    }

    if (skills & skill) // The new skill cannot be added before
    {
      return false;
    }
    // RESTRICTIONS
    if (((is_floating() || is_falling()) && (skill >= Utils::SKILL_EGOIST)) || ((skill == Utils::CLIMB || skill == Utils::FLOAT) && (skills >= Utils::SKILL_EGOIST)) ||
        (is_escaping() || is_crashing() || is_exploding() || is_drowning()) || (skill >= Utils::SKILL_EGOIST && skills >= Utils::SKILL_EGOIST) || false)
    {
      return false;
    }
    skills = skills | skill;
    if (skills < Utils::SKILL_EGOIST) // change name type of the lemming depending on the skill
    {
      if (skills & Utils::FLOAT && skills & Utils::CLIMB)
      {
        type = Utils::LEMMING_TYPE[14]; // ATHLETE
      }
      else if (skills & Utils::FLOAT)
      {
        type = Utils::LEMMING_TYPE[Utils::FLOATING];
      }
      else if (skills & Utils::CLIMB)
      {
        type = Utils::LEMMING_TYPE[Utils::CLIMBING];
      }
      else
      {
        type = Utils::LEMMING_TYPE[Utils::FALLING];
      }
    }
    game_info.sub_skill_amount(Utils::SKILL_TO_SKILLS_AMOUNT[skill_to_index(skill)]);
    return true;
  }

  /**
   * @brief Checks if the Lemming have a skill.
   *
   * @param skill The skill to check.
   * @return True if the Lemming have the skill, false otherwise.
   */
  bool is_skill(int skill)
  {
    return skills & skill;
  }

  void update_animation(Engine &engine)
  {
    if (!is_playing)
      return;

    time_frame_sprite += engine.get_delta_time();
    if (time_frame_sprite >= Utils::STATE_ANIMATION_DURATION[get_state()] / Utils::STATE_N_FRAMES[get_state()])
    {
      time_frame_sprite = 0.0f;
      current_frame = (current_frame + 1) % Utils::STATE_N_FRAMES[get_state()];

      if (!Utils::STATE_IS_LOOP_ANIMATION[get_state()] && current_frame == 0)
      {
        is_playing = false; // Detiene la animación si no es en bucle
        if (is_escaping())
        {
          game_info.add_n_lemmings_in();
          destroy_lemming(engine);
        }
        if (is_crashing() || is_exploding() || is_drowning())
        {
          destroy_lemming(engine);
        }
        return;
      }

      std::string frame_path = "assets/lemming/lemming_" + std::to_string(direction) + "_" + std::to_string(get_state()) + "_" + std::to_string(current_frame) + ".png";

      Texture txt = engine.load_texture(frame_path.c_str());
      set_active_texture(txt);
    }
  }

  void pre_physics(Engine &engine) override
  {
    game_info.check_action_possible();
    update_animation(engine);
  }

  void update_state()
  {
    auto speed = get_speed();

    if (is_walking())
    {
      speed.x = direction * 0.1;
      speed.y = 0.1;
      set_speed(speed);
      on_ground = false;
      return;
    }

    if (is_falling())
    {
      speed.x = 0;
      speed.y = 0.2;
      set_speed(speed);
      return;
    }

    if (is_floating())
    {
      speed.x = 0;
      speed.y = 0.1;
      set_speed(speed);
      return;
    }

    if (is_exploding())
    {
      speed.x = 0;
      speed.y = 0;
      set_speed(speed);
      return;
    }

    if (is_idle())
    {
      speed.x = 0;
      speed.y = 0;
      set_speed(speed);
      return;
    }

    if (is_escaping())
    {
      return;
    }

    if (is_blocking())
    {
      speed.x = 0;
      speed.y = 0;
      set_speed(speed);
      return;
    }

    if (is_digging())
    {
      if (current_frame == 4 || current_frame == 12)
      {
        if (!do_action_in_frame)
        {
          do_action_in_frame = true;
          speed.x = 0;
          speed.y = 0.05;
          set_speed(speed);
        }
      }
      else
      {
        do_action_in_frame = false;
        speed.x = 0;
        speed.y = 0;
        set_speed(speed);
      }
      return;
    }
  }

  void update_position(Engine &engine) override
  {
    update_state(); // Actualiza el estado antes de calcular la nueva posición
    Rigid_body::update_position(engine);
  }

  void on_collision(Engine &, EntityPtr other) override
  {
    auto speed = get_speed();

    if (other->get_entity_name() == "MAP" || other->get_entity_name() == "Lemming")
    {
      if (other->get_entity_name() == "Lemming")
      {
        std::shared_ptr<Lemming> lemming_ptr = std::dynamic_pointer_cast<Lemming>(other);
        if (lemming_ptr && lemming_ptr->get_state() != Utils::BLOCKING)
          return;
      }

      switch (closest_side(other))
      {
      case 0:
        if (!(is_digging() || is_bashing() || is_mining()))
        {
          position.x = other->bound2f().pMax.x;
          if (direction < 0)
            direction *= -1;
          speed.x = 0;
          // std::cout << "Lemming turn right\n";
        }

        break;
      case 1:
        if (!(is_digging() || is_bashing() || is_mining()))
        {
          position.x = other->bound2f().pMin.x - diagonal.x;
          if (direction > 0)
            direction *= -1;
          speed.x = 0;
          // std::cout << "Lemming turn left\n";
        }
        break;
      case 2:
        if (!(is_digging() || is_bashing() || is_mining()))
        {
          position.y = other->bound2f().pMax.y;
          direction *= -1;
          speed.y = 0;
        }
        break;
      case 3:
        if (!(is_digging() || is_bashing() || is_mining()))
        {
          position.y = other->bound2f().pMin.y - diagonal.y;
          on_ground = true;
          if (is_floating() || is_falling())
          {
            go_walk();
          }
        }

        break;
      }
    }

    if (other->get_entity_name() == "Gate")
    {
      go_escape();
      speed.x = 0;
      speed.y = 0;
    }

    if (other->get_entity_name() == "Liquid")
    {
      go_drown();
      speed.x = 0;
      speed.y = 0;
    }

    if (other->get_entity_name() == "Fire")
    {
      go_escape();
      speed.x = 0;
      speed.y = 0;
    }

    if (other->get_entity_name() == "Spinner" || other->get_entity_name() == "Flamethrower")
    {
      speed.x = 0;
      speed.y = 0;
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "Chain")
    {
      std::shared_ptr<Chain> chain_ptr = std::dynamic_pointer_cast<Chain>(other);
      if (chain_ptr && chain_ptr->get_is_playing())
        return;
      chain_ptr->trigger_event_animation();
      speed.x = 0;
      speed.y = 0;
      destroy_lemming(engine);
    }
    set_speed(speed);
  }

  void post_physics(Engine &) override
  {
    if (skills & Utils::EXPLODE)
    {
      go_explode();
      return;
    }
    if (skills & Utils::BLOCK)
    {
      go_block();
      return;
    }
    if (skills & Utils::DIG)
    {
      go_dig();
      return;
    }
    if (skills & Utils::BASH)
    {
      go_bash();
      return;
    }
    if (skills & Utils::MINE)
    {
      go_mine();
      return;
    }
    if (skills & Utils::BUILD)
    {
      go_build();
      return;
    }
    if (!on_ground && !(is_floating() || is_falling() || is_digging() || is_climbing()))
    {
      if (skills & Utils::FLOAT)
      {
        go_float();
      }
      else
      {
        go_fall();
      }
    }
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine))
    {
      // std::cout << "LEMMING PULSADO" << std::endl;
      int skill = Utils::HUD_TO_SKILL[game_info.get_option_selected()];
      if (skill != Utils::NO_SKILLS && game_info.get_action_possible())
      {
        bool res = add_skill(Utils::HUD_TO_SKILL[game_info.get_option_selected()]);
        if (res)
        {
          game_info.action_done();
          std::cout << "HABILIDAD AÑADIDA" << std::endl;
        }
        else
        {
          std::cout << "HABILIDAD NO AÑADIDA" << std::endl;
        }
      }
    }

    if (event == EngineIO::InputEvent::MOUSE_HOVER)
    {
      if (!is_hovered)
      {
        game_info.set_lemming_hovered_type(type);
        game_info.add_lemmings_hovered();
        is_hovered = true;
      }

      if (game_info.get_is_cursor_hover() == false)
      {
        game_info.set_cursor_txt("assets/cursor_hover.png", engine);
        game_info.set_is_cursor_hover(true);
      }
    }
  }

  void on_event_up([[maybe_unused]] Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_HOVER && game_info.get_is_cursor_hover() == true)
    {
      if (is_hovered)
      {
        game_info.sub_lemmings_hovered();
        is_hovered = false;
        if (game_info.get_lemmings_hovered() == 0)
        {

          game_info.set_lemming_hovered_type("");
        }
      }

      game_info.set_cursor_txt("assets/cursor.png", engine);
      game_info.set_is_cursor_hover(false);
    }
  }

  void destroy_lemming(Engine &engine)
  {
    if (is_hovered)
    {
      game_info.sub_lemmings_hovered();
      if (game_info.get_lemmings_hovered() == 0)
      {
        game_info.set_lemming_hovered_type("");
      }
    }
    game_info.set_cursor_txt("assets/cursor.png", engine);
    game_info.set_is_cursor_hover(false);

    game_info.sub_n_lemmings_out();
    destroy();
  }
};
