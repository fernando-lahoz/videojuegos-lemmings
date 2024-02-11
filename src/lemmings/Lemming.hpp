#pragma once

#include "engine/rigid_body.hpp"
#include "engine/render_2D.hpp"

class Lemming : public Rigid_body
{
  bool on_ground = false;
  Texture txt_left, txt_right, txt;

  const int STATE_N_FRAMES[14] = {8, 9, 4, 16, 16, 16, 8, 30, 8, 32, 24, 8, 16, 16};                                               // number of frames of each animation
  const float STATE_ANIMATION_DURATION[14] = {1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}; // duration of each animation in seconds
  float time_frame_sprite = 0.0f;                                                                                                  // time acumulator for sprite animation

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
    return state == FALLING;
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
    return state == FLOATING;
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
  Lemming(Point3f position, Vector2f diagonal, Engine &engine)
      : Rigid_body(position, diagonal,
                   engine.load_texture("assets/lemming/lemming_1_2_0.png"),
                   "Lemming", "Lemming")
  {
    // gravity = 3;
    // enable_gravity();
    go_fall(); // Iniciar callendo
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
  bool add_skill(Skills skill)
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

  void update_state()
  {
    auto speed = get_speed();

    if (is_falling())
    {
      speed.x = 0;
      speed.y = 0.2;
      set_speed(speed);
    }

    if (is_floating())
    {
      speed.x = 0;
      speed.y = 0.1;
      set_speed(speed);
    }

    if (is_walking())
    {
      speed.x = direction * 0.1;
      speed.y = 0.1;
      set_speed(speed);
      on_ground = false;
    }
  }

  void update_position(Engine &engine) override
  {

    time_frame_sprite = (time_frame_sprite + engine.get_delta_time() / STATE_ANIMATION_DURATION[get_state()]);
    if (time_frame_sprite > 1)
    {
      time_frame_sprite = 0;
    }

    update_state(); // Actualiza el estado antes de calcular la nueva posición
    Rigid_body::update_position(engine);
  }
  void on_collision(Engine &engine, EntityPtr other) override
  {
    auto speed = get_speed();

    if (other->get_entity_name() == "MAP" || other->get_entity_name() == "Lemming")
    {
      if (other->get_entity_name() == "Lemming")
      {
        std::shared_ptr<Lemming> lemming_ptr = std::dynamic_pointer_cast<Lemming>(other);
        if (lemming_ptr && lemming_ptr->get_state() != BLOCKING)
          return;
      }

      switch (closest_side(other))
      {
      case 0:
        position.x = other->bound2f().pMax.x;
        if (direction < 0)
          direction *= -1;
        speed.x = 0;
        // std::cout << "Lemming turn right\n";
        break;
      case 1:
        position.x = other->bound2f().pMin.x - diagonal.x;
        if (direction > 0)
          direction *= -1;
        speed.x = 0;
        // std::cout << "Lemming turn left\n";
        break;
      case 2:
        position.y = other->bound2f().pMax.y;
        speed.y = 0;
        break;
      case 3:
        position.y = other->bound2f().pMin.y - diagonal.y;
        on_ground = true;
        if (is_floating() || is_falling())
        {
          go_walk();
        }

        break;
      }
    }

    set_speed(speed);

    Rigid_body::on_collision(engine, other);
  }

  void post_physics(Engine &engine) override
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

    std::string path = "assets/lemming/lemming_" + std::to_string(direction) + "_" + std::to_string(get_state()) + "_" + std::to_string(static_cast<int>((time_frame_sprite)*STATE_N_FRAMES[get_state()])) + ".png";
    txt = engine.load_texture(path.c_str());
    set_active_texture(txt);
  }
};
