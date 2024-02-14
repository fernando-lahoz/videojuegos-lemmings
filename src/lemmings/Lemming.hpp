#pragma once

#include "engine/rigid_body.hpp"
#include "engine/render_2D.hpp"
#include "utils.hpp"

#include "Chain.hpp"

class Lemming : public Rigid_body
{
  bool on_ground = false;
  Texture txt;
  Level_info &level_info;
  float time_frame_sprite = 0.0f; // Acumulador de tiempo para la animación del sprite
  std::string base_path;          // Base para el path de las texturas de animación
  bool is_loop;                   // Indica si la animación es en bucle
  bool is_playing = true;         // Indica si la animación está actualmente en reproducción
  int current_frame = 0;          // Frame actual de la animación
  int distance_fall = 0;
  bool do_action_in_frame = false;

  int skills = Utils::NO_SKILLS;

  int state = Utils::IDLE;

  // Este booleano indica si un lemming es marcado para explotar
  bool dead_marked = false;
  // Este es el tiempo de vida que le queda al lemming si es marcado para explotar
  double time_to_live = 5.0f;

  int direction = 1; // Comienza moviéndose hacia la derecha

  void go_idle()
  {
    state = Utils::IDLE;
    // std::cout << "GO IDLE\n";
  }

  void go_walk()
  {
    state = Utils::WALKING;
    // std::cout << "GO WALKING\n";
  }

  void go_fall()
  {
    state = Utils::FALLING;
    // std::cout << "GO FALLING\n";
  }

  void go_block()
  {
    state = Utils::BLOCKING;
    // std::cout << "GO BLOCKING\n";
  }

  void go_build()
  {
    state = Utils::BUILDING;
    // std::cout << "GO BUILDING\n";
  }

  void go_climb()
  {
    state = Utils::CLIMBING;
    // std::cout << "GO CLIMBING\n";
  }

  void go_float()
  {
    state = Utils::FLOATING;
    // std::cout << "GO FLOATING\n";
  }

  void go_explode()
  {
    state = Utils::EXPLODING;
    // std::cout << "GO EXPLODING\n";
  }

  void go_dig_vertical()
  {
    state = Utils::DIGGING_VERTICAL;
    // std::cout << "GO DIGGING_VERTICAL\n";
  }

  void go_dig_horizontal()
  {
    state = Utils::DIGGING_HORIZONTAL;
    // std::cout << "GO DIGGING_HORIZONTAL\n";
  }

  void go_dig_diagonal()
  {
    state = Utils::DIGGING_DIAGONAL;
    // std::cout << "GO DIGGING_DIAGONAL\n";
  }

  void go_escape()
  {
    state = Utils::ESCAPING;
    // std::cout << "GO DIGGING_DIAGONAL\n";
  }

  void go_drown()
  {
    state = Utils::DROWNING;
    // std::cout << "GO DIGGING_DIAGONAL\n";
  }

  void go_crash()
  {
    state = Utils::CRASHING;
    // std::cout << "GO DIGGING_DIAGONAL\n";
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

  bool is_digging_vertical()
  {
    return state == Utils::DIGGING_VERTICAL;
  }

  bool is_digging_horizontal()
  {
    return state == Utils::DIGGING_HORIZONTAL;
  }

  bool is_digging_diagonal()
  {
    return state == Utils::DIGGING_DIAGONAL;
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
  Lemming(Point3f position, Vector2f diagonal, Engine &engine, Level_info &_level_info)
      : Rigid_body(position, diagonal,
                   engine.load_texture("assets/lemming/lemming_1_2_0.png"),
                   "Lemming", "Lemming"),
        level_info(_level_info)
  {
    // gravity = 3;
    // enable_gravity();
  }

  int get_state()
  {
    return state;
  }

  /**
   * @brief Adds a skill to the Lemming.
   *
   * @param skill The skill to add.
   * @return True if the skill was successfully added, false otherwise.
   */
  bool add_skill(int skill)
  {
    if (skills & skill) // The new skill cannot be added before
    {
      return false;
    }
    if (((is_floating() || is_falling()) && (skill >= Utils::SKILL_EGOIST)) ||
        (is_escaping() || is_crashing() || is_exploding() || is_drowning()) || (skill >= Utils::SKILL_EGOIST && skills >= Utils::SKILL_EGOIST) || false) // TODO: ADD RESTRICTIONS OF what cases you can't add a skill to the lemming
    {
      return false;
    }
    skills = skills | skill;
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
        if (is_escaping() || is_crashing() || is_exploding() || is_drowning())
        {
          destroy();
          std::cout << "Lemming destruido\n";
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
    level_info.check_action_possible();
    update_animation(engine);
  }

  // Pre: True
  // Post: Actualiza el tiempo de vida del lemming, de estar marcado para morir
  // y lo hace explotar en caso de que se acabe su tiempo de vida
  void update_explode_countdown(Engine &engine)
  {

    // Si el lemming ha sido marcado para morir
    if (dead_marked)
    {

      // Restamos el delta time si el tiempo de vida es mayor a cero
      if (time_to_live > 0.0f)
        time_to_live -= engine.get_delta_time();

      // Si se acaba el tiempo explotamos
      if (time_to_live <= 0.0f)
        go_explode();
    }
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

    if (is_digging_vertical())
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
        if (!(is_digging_vertical() || is_digging_horizontal() || is_digging_diagonal()))
        {
          position.x = other->bound2f().pMax.x;
          if (direction < 0)
            direction *= -1;
          speed.x = 0;
          // std::cout << "Lemming turn right\n";
        }

        break;
      case 1:
        if (!(is_digging_vertical() || is_digging_horizontal() || is_digging_diagonal()))
        {
          position.x = other->bound2f().pMin.x - diagonal.x;
          if (direction > 0)
            direction *= -1;
          speed.x = 0;
          // std::cout << "Lemming turn left\n";
        }
        break;
      case 2:
        if (!(is_digging_vertical() || is_digging_horizontal() || is_digging_diagonal()))
        {
          position.y = other->bound2f().pMax.y;
          direction *= -1;
          speed.y = 0;
        }
        break;
      case 3:
        if (!(is_digging_vertical() || is_digging_horizontal() || is_digging_diagonal()))
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
      destroy();
    }

    if (other->get_entity_name() == "Chain")
    {
      std::shared_ptr<Chain> chain_ptr = std::dynamic_pointer_cast<Chain>(other);
      if (chain_ptr && chain_ptr->get_is_playing())
        return;
      chain_ptr->trigger_event_animation();
      speed.x = 0;
      speed.y = 0;
      destroy();
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
    if (skills & Utils::DIG_VERTICAL)
    {
      go_dig_vertical();
      return;
    }
    if (skills & Utils::DIG_HORIZONTAL)
    {
      go_dig_horizontal();
      return;
    }
    if (skills & Utils::DIG_DIAGONAL)
    {
      go_dig_diagonal();
      return;
    }
    if (skills & Utils::BUILD)
    {
      go_build();
      return;
    }
    if (!on_ground && !(is_floating() || is_falling() || is_digging_vertical() || is_climbing()))
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
      std::cout << "LEMMING PULSADO" << std::endl;
      int skill = Utils::HUD_TO_SKILL[level_info.get_option_selected()];
      if (skill != Utils::NO_SKILLS && level_info.get_action_possible())
      {
        bool res = add_skill(Utils::HUD_TO_SKILL[level_info.get_option_selected()]);
        if (res)
        {
          level_info.action_done();
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
      level_info.add_lemming_hovered();
      if (level_info.get_is_cursor_hover() == false)
      {
        level_info.set_txt("assets/cursor_hover.png", engine);
        level_info.set_is_cursor_hover(true);
      }
    }
  }

  void on_event_up([[maybe_unused]] Engine &engine, EngineIO::InputEvent event) override
  {
    if (event == EngineIO::InputEvent::MOUSE_HOVER && level_info.get_is_cursor_hover() == true)
    {
      level_info.sub_lemming_hovered();

      level_info.set_txt("assets/cursor.png", engine);
      level_info.set_is_cursor_hover(false);
    }
  }
};
