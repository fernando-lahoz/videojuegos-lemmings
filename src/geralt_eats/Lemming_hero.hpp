#pragma once

#include "engine/rigid_body.hpp"
#include "engine/render_2D.hpp"
#include "geometry/point.hpp"

class Lemming_hero : public Rigid_body
{
  bool on_ground = false;
  Texture txt_left, txt_right, txt;

  float time_frame_sprite = 0.0f; // Acumulador de tiempo para la animación del sprite
  std::string base_path;          // Base para el path de las texturas de animación
  bool is_loop;                   // Indica si la animación es en bucle
  bool is_playing = true;         // Indica si la animación está actualmente en reproducción
  int current_frame = 0;          // Frame actual de la animación

  const int STATE_IS_LOOP_ANIMATION[14] = {false, true, true, true, true, true, true, false, true, true, true, false, false, false}; // indicates if the animation is loop
  const int STATE_N_FRAMES[14] = {8, 9, 4, 16, 16, 16, 8, 30, 16, 32, 24, 8, 16, 16};                                                // number of frames of each animation
  const float STATE_ANIMATION_DURATION[14] = {1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};   // duration of each animation in seconds

  enum Skills
  {
    NO_SKILLS = 0,
    BLOCK = 1,
    BUILD = 2,
    CLIMB = 4,
    FLOAT = 8,
    DIG_VERTICAL = 16,
    DIG_HORIZONTAL = 32,
    DIG_DIAGONAL = 64,
    EXPLODE = 128,
  };

  int skills = NO_SKILLS;

  enum State
  {
    IDLE = 0,
    WALKING = 1,
    FALLING = 2,
    BLOCKING = 3,
    BUILDING = 4,
    CLIMBING = 5,
    FLOATING = 6,
    EXPLODING = 7,
    DIGGING_VERTICAL = 8,
    DIGGING_HORIZONTAL = 9,
    DIGGING_DIAGONAL = 10,
    ESCAPING = 11,
    DROWNING = 12,
    CRASHING = 13,
  };

  int state = IDLE;

  int direction = 1; // Comienza moviéndose hacia la derecha

  void go_idle()
  {
    state = IDLE;
    // std::cout << "GO IDLE\n";
  }

  void go_walk()
  {
    state = WALKING;
    // std::cout << "GO WALKING\n";
  }

  void go_fall()
  {
    state = FALLING;
    // std::cout << "GO FALLING\n";
  }

  void go_block()
  {
    state = BLOCKING;
    // std::cout << "GO BLOCKING\n";
  }

  void go_build()
  {
    state = BUILDING;
    // std::cout << "GO BUILDING\n";
  }

  void go_climb()
  {
    state = CLIMBING;
    // std::cout << "GO CLIMBING\n";
  }

  void go_float()
  {
    state = FLOATING;
    // std::cout << "GO FLOATING\n";
  }

  void go_explode()
  {
    state = EXPLODING;
    // std::cout << "GO EXPLODING\n";
  }

  void go_dig_vertical()
  {
    state = DIGGING_VERTICAL;
    // std::cout << "GO DIGGING_VERTICAL\n";
  }

  void go_dig_horizontal()
  {
    state = DIGGING_HORIZONTAL;
    // std::cout << "GO DIGGING_HORIZONTAL\n";
  }

  void go_dig_diagonal()
  {
    state = DIGGING_DIAGONAL;
    // std::cout << "GO DIGGING_DIAGONAL\n";
  }

  void go_escape()
  {
    state = ESCAPING;
    // std::cout << "GO DIGGING_DIAGONAL\n";
  }

  void go_drown()
  {
    state = DROWNING;
    // std::cout << "GO DIGGING_DIAGONAL\n";
  }

  void go_crash()
  {
    state = CRASHING;
    // std::cout << "GO DIGGING_DIAGONAL\n";
  }

  bool is_idle()
  {
    return state == IDLE;
  }

  bool is_falling()
  {
    return state == FALLING && !on_ground;
  }

  bool is_walking()
  {
    return state == WALKING;
  }

  bool is_blocking()
  {
    return state == BLOCKING;
  }

  bool is_building()
  {
    return state == BUILDING;
  }

  bool is_climbing()
  {
    return state == CLIMBING;
  }

  bool is_floating()
  {
    return state == FLOATING && !on_ground;
  }

  bool is_exploding()
  {
    return state == EXPLODING;
  }

  bool is_digging_vertical()
  {
    return state == DIGGING_VERTICAL;
  }

  bool is_digging_horizontal()
  {
    return state == DIGGING_HORIZONTAL;
  }

  bool is_digging_diagonal()
  {
    return state == DIGGING_DIAGONAL;
  }

  bool is_escaping()
  {
    return state == ESCAPING;
  }

  bool is_drowning()
  {
    return state == DROWNING;
  }

  bool is_crashing()
  {
    return state == CRASHING;
  }

public:
  Lemming_hero(Point3f position, Vector2f diagonal, Engine &engine)
      : Rigid_body(position, diagonal,
                   engine.load_texture("assets/lemming/lemming_1_2_0.png"),
                   "Lemming", "Lemming")
  {
    override_down_point(Point2f(0.5, 0.75));
    override_up_point(Point2f(0.5, 0.3));
    override_left_point(Point2f(0.5, 0.45));
    override_right_point(Point2f(0.5, 0.55));

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
    if ((is_blocking() && skill & ~EXPLODE) || false) // TODO: ADD RESTRICTIONS OF what cases you can't add a skill to the lemming
    {
      return false;
    }
    skills = skills | skill;
  }

  void update_animation(Engine &engine)
  {
    if (!is_playing)
      return;

    time_frame_sprite += engine.get_delta_time();
    if (time_frame_sprite >= STATE_ANIMATION_DURATION[get_state()] / STATE_N_FRAMES[get_state()])
    {
      time_frame_sprite = 0.0f;
      current_frame = (current_frame + 1) % STATE_N_FRAMES[get_state()];

      if (!STATE_IS_LOOP_ANIMATION[get_state()] && current_frame == 0)
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
    Rigid_body::pre_physics(engine);
    update_animation(engine);
  }

  void update_state(Engine &engine)
  {
    auto speed = get_speed();

    if (engine.is_up_arrow_down())
    {
      if (on_ground)
      {
        speed.y = -1;
        set_speed(speed);
        // on_ground = false;
      }
    }

    if (engine.is_down_arrow_down())
    {
      // direction = 1;
    }

    if (engine.is_left_arrow_down())
    {
      direction = -1;
    }

    if (engine.is_right_arrow_down())
    {
      direction = 1;
    }

    if (engine.is_right_arrow_down() && engine.is_left_arrow_down())
    {
      // direction = 0;
    }

    if (!engine.is_right_arrow_down() && !engine.is_left_arrow_down())
    {
      // direction = 0;
    }

    if (is_walking())
    {
      speed.x = direction * 0.1;
      Ray ray_down = Ray(local_to_world(Point2f(0.5, 0.5)), Vector2f(0, 1));
      Float hit_offset_down;
      EntityPtr hit_entity_down;

      engine.intersect_ray(ray_down, get_entity_id(),
                           RIGID_BODY_ID, hit_offset_down, hit_entity_down);

      // std::cout << "Hit offset down: " << hit_offset_down << "\n";

      if (hit_offset_down < diagonal.y / 2 && hit_offset_down > 0)
      {
        if (std::abs(hit_offset_down - diagonal.y / 4) > diagonal.y / 20)
        {
          // std::cout << "sube baja altura\n";
          speed.y = 0;
          position.y += (hit_offset_down - diagonal.y / 4);
        }
      }
      else if (hit_offset_down > diagonal.y / 2)
      {
        speed.y = 0;
        speed.x = 0;
        on_ground = false;
      }
      set_speed(speed);
      return;
    }

    if (is_falling())
    {
      speed.x = 0;
      speed.y = 0.2;
      if (colliding_down())
      {
        // std::cout << "detect down\n";
        // std::cout << on_ground << std::endl;

        on_ground = true;
        speed.y = 0;
        go_walk();
      }
      set_speed(speed);
      return;
    }

    if (is_floating())
    {
      speed.x = 0;
      speed.y = 0.1;
      if (colliding_down())
      {
        // std::cout << "detect down\n";
        // std::cout << on_ground << std::endl;

        on_ground = true;
        speed.y = 0;
        go_walk();
      }
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
        if (false) //! do_action_in_frame)
        {
          // do_action_in_frame = true;
          speed.x = 0;
          speed.y = 0.05;
          set_speed(speed);
        }
      }
      else
      {
        // do_action_in_frame = false;
        speed.x = 0;
        speed.y = 0;
        set_speed(speed);
      }
      return;
    }
  }

  void update_position(Engine &engine) override
  {
    Rigid_body::update_position(engine);
    update_state(engine); // Actualiza el estado antes de calcular la nueva posición
  }

  void on_collision(Engine &engine, EntityPtr other) override
  {
    Entity::on_collision(engine, other);

    auto speed = get_speed();

    if (other->get_entity_name() == "MAP" || other->get_entity_name() == "Lemming")
    {
      if (other->get_entity_name() == "Lemming")
      {
        std::shared_ptr<Lemming_hero> lemming_ptr = std::dynamic_pointer_cast<Lemming_hero>(other);
        if (lemming_ptr && lemming_ptr->get_state() != BLOCKING)
          return;
      }
      if (is_falling() || is_floating())
      {
        if (colliding_down())
        {
          // std::cout << "detect down\n";
          // std::cout << on_ground << std::endl;

          on_ground = true;
          speed.y = 0;
          go_walk();
        }
      }

      if (is_walking())
      {
        if ((colliding_left() || colliding_right()))
        {

          position.x -= diagonal.x * 0.05 * direction;
          direction *= -1;

          // std::cout << "Lemming turn left\n";
        }
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
    set_speed(speed);
  }

  void post_physics(Engine &) override
  {
    if (!on_ground && !(is_floating() || is_falling()))
    {
      if (skills & FLOAT)
      {
        go_float();
      }
      else
      {
        go_fall();
      }
    }
  }
};
