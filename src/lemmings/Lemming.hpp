#pragma once

#include "engine/rigid_body.hpp"
#include "engine/render_2D.hpp"
#include "engine/engine.hpp"
#include "geometry/point.hpp"

#include "lemmings/structure/Chain.hpp"
#include "lemmings/structure/Directional_wall.hpp"
#include "lemmings/structure/Brick.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/display/Dynamic_counter_image.hpp"
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
  bool is_loop; // Indica si la animación es en bucle

  bool is_playing = true; // Indica si la animación está actualmente en reproducción
  int current_frame = 0;  // Frame actual de la animación
  bool climb_now = false;
  float distance_fall = 0.0f;
  float last_y = 0.0f;
  bool do_action_in_frame = false;
  bool is_hovered = false;
  float velocity = 50;

  int skills = Utils::NO_SKILLS;

  int state = Utils::FALLING;

  int direction = 1; // Comienza moviéndose hacia la derecha

  // Este booleano es para que solo se ejecute una vez el sonido de muerte
  bool play_death_sound = true;

  // Este booleano indica si un lemming es marcado para explotar
  bool dead_marked = false;
  // Este es el tiempo de vida que le queda al lemming si es marcado para explotar
  double time_to_live = 5.0f;
  int last_time_to_live = 6;
  std::shared_ptr<Dynamic_counter_image> counter;

  std::shared_ptr<Brick> brick_ptr;

  std::string get_type()
  {
    return type;
  }

  void restart_animation()
  {
    is_playing = true;
    current_frame = 0;
    time_frame_sprite = 0.0f;
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

    // Hacemos que suene el yipee
    if (play_death_sound)
    {
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::YIPEE_SOUND));
      play_death_sound = false;
    }

    state = Utils::ESCAPING;
    type = Utils::LEMMING_TYPE[Utils::ESCAPING];
    // std::cout << "GO MINING\n";
  }

  void go_drown()
  {
    state = Utils::DROWNING;
    type = Utils::LEMMING_TYPE[Utils::DROWNING];

    // Hacemos que suene el chapuzon que se dan
    if (play_death_sound)
    {
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SPLASH_SOUND));
      play_death_sound = false;
    }

    // std::cout << "GO MINING\n";
  }

  void go_crash()
  {
    state = Utils::CRASHING;
    type = Utils::LEMMING_TYPE[Utils::CRASHING];

    // Hacemos que suene como se estrellan contra el suelo
    engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SPLAT_SOUND));

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
                   engine, "Lemming", "Lemming"),
        game_info(_game_info), engine(_engine)
  {
    constructor_set_collision_type(Collision_type::CHARACTER);

    // gravity = 3;
    // enable_gravity();
    override_down_point(Point2f(0.5, 0.75));
    override_up_point(Point2f(0.5, 0.3));
    override_left_point(Point2f(0.5, 0.45));
    override_right_point(Point2f(0.5, 0.45));
    disable_alpha_mouse();
  }
  ~Lemming()
  {
    if (counter)
      counter->destroy();
  }

  void set_dead_marked(bool new_value) { dead_marked = new_value; }
  bool get_dead_marked() { return dead_marked; }

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

    // std::cout << "skill_amount_index = " << ind << std::endl;
    // std::cout << "skill_amount = " << a << std::endl;
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
    if (skill == Utils::Lemming_Skills::EXPLODE)
    {
      set_dead_marked(true);
    }
    else
    {
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
    }
    game_info.sub_skill_amount(Utils::SKILL_TO_SKILLS_AMOUNT[skill_to_index(skill)]);
    return true;
  }

  void remove_skill(int skill)
  {
    skills = skills & ~skill;
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
        time_to_live -= engine.get_delta_time() * game_info.get_game_speed();

      // Si se acaba el tiempo explotamos
      if (time_to_live <= 0.0f)
        return true;
    }
    return false;
  }

  void update_counter(Engine &engine)
  {
    if (dead_marked)
    {
      if (!counter)
      {
        counter = std::make_shared<Dynamic_counter_image>(Point3f(position.x + (diagonal.x / 2), position.y - 2, position.z - 1), Vector2f(10, 10), game_info, engine, Utils::TEXT_TYPE::LEMMING_COUNTDOWN, 0, 1, last_time_to_live, true);
        engine.get_game().create_entity(counter);
      }
      if (last_time_to_live != (int)(time_to_live + 0.999))
      {
        last_time_to_live = (int)(time_to_live + 0.999);
      }
    }
  }

  void update_animation(Engine &engine)
  {
    if (!is_playing)
      return;

    time_frame_sprite += engine.get_delta_time() * game_info.get_game_speed();
    if (time_frame_sprite >= Utils::STATE_ANIMATION_DURATION[get_state()] / Utils::STATE_N_FRAMES[get_state()])
    {
      // int times = time_frame_sprite / (Utils::STATE_ANIMATION_DURATION[get_state()] / Utils::STATE_N_FRAMES[get_state()]);
      // time_frame_sprite = time_frame_sprite - (Utils::STATE_ANIMATION_DURATION[get_state()] / Utils::STATE_N_FRAMES[get_state()]) * times;
      // current_frame = (current_frame + times) % Utils::STATE_N_FRAMES[get_state()];

      time_frame_sprite = 0.0f;
      current_frame = (current_frame + 1) % Utils::STATE_N_FRAMES[get_state()];

      if (counter)
      {
        counter->set_position2D(Point2f(position.x + (diagonal.x / 2) - (counter->get_diagonal().x / 2), position.y - 2));
      }

      if (is_falling())
      {
        position.y += 2;
      }

      if (is_floating())
      {
        position.y += 1;
      }

      if (is_walking())
      {
        position.x += 2 * direction;
        Ray ray_down = Ray(local_to_world(Point2f(0.45, 0.5)), Vector2f(0, 1));
        Float hit_offset_down;
        EntityPtr hit_entity_down;

        std::vector<std::string> force_entity_names = {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"};

        engine.intersect_ray(ray_down, get_entity_id(),
                             force_entity_names, hit_offset_down, hit_entity_down);
        // bool cond = true;
        // if (hit_entity_down && hit_entity_down->get_entity_name() == "BRICKS")
        // {
        //   std::shared_ptr<Brick> bricks_ptr = std::dynamic_pointer_cast<Brick>(hit_entity_down);
        //   cond = bricks_ptr->get_direction() == direction;
        // }
        // if (true)
        // {

        // }
        if (hit_offset_down < diagonal.y / 2 && hit_offset_down > 0)
        {
          if (std::abs(hit_offset_down - diagonal.y / 4) > diagonal.y / 80)
          {
            // std::cout << "sube baja altura\n";
            position.y += (hit_offset_down - diagonal.y / 4);
          }
        }
        else if (hit_offset_down > diagonal.y / 2)
        {
          on_ground = false;
        }
      }

      if (!Utils::STATE_IS_LOOP_ANIMATION[get_state()] && current_frame == 0)
      {
        is_playing = false; // Detiene la animación si no es en bucle
        if (is_escaping())
        {
          game_info.add_n_lemmings_in();
          destroy_lemming(engine);
          return;
        }
        if (is_exploding())
        {
          Bound2f box;
          box.pMin = Point2f(local_to_world(Point2f(0.35, 0)));
          box.pMax = Point2f(local_to_world(Point2f(0.65, 1)));
          Bound2f box2;
          box2.pMin = Point2f(local_to_world(Point2f(0.65, 0)));
          box2.pMax = Point2f(local_to_world(Point2f(0.35, 1)));
          Bound2f box3;
          box3.pMin = Point2f(local_to_world(Point2f(0.2, 0.05)));
          box3.pMax = Point2f(local_to_world(Point2f(0.8, 0.95)));
          Bound2f box4;
          box4.pMin = Point2f(local_to_world(Point2f(0.05, 0.2)));
          box4.pMax = Point2f(local_to_world(Point2f(0.95, 0.8)));
          Bound2f box5;
          box5.pMin = Point2f(local_to_world(Point2f(0.15, 0.15)));
          box5.pMax = Point2f(local_to_world(Point2f(0.85, 0.85)));

          bool destroyed = false;
          auto &entities = engine.get_entities();
          for (auto &entity : entities)
          {
            if (entity->get_entity_name() == "MAP")
            {
              if (entity->destroy_box_alpha(engine, box))
                destroyed = true;
              if (entity->destroy_box_alpha(engine, box2))
                destroyed = true;
              if (entity->destroy_box_alpha(engine, box3))
                destroyed = true;
              if (entity->destroy_box_alpha(engine, box4))
                destroyed = true;
              if (entity->destroy_box_alpha(engine, box5))
                destroyed = true;
            }
            else if (entity->get_entity_name() == "DIRECTIONAL WALL")
            {
              std::shared_ptr<Directional_wall> dir_wall_ptr = std::dynamic_pointer_cast<Directional_wall>(entity);

              if (dir_wall_ptr->destroy_box_alpha(engine, box, 0))
                destroyed = true;
              if (dir_wall_ptr->destroy_box_alpha(engine, box2, 0))
                destroyed = true;
              if (dir_wall_ptr->destroy_box_alpha(engine, box3, 0))
                destroyed = true;
              if (dir_wall_ptr->destroy_box_alpha(engine, box4, 0))
                destroyed = true;
              if (dir_wall_ptr->destroy_box_alpha(engine, box5, 0))
                destroyed = true;
            }
            else if (entity->get_entity_name() == "BRICKS")
            {
              std::shared_ptr<Brick> bricks_ptr = std::dynamic_pointer_cast<Brick>(entity);
              if (bricks_ptr->destroy_box_alpha(engine, box, 0))
                destroyed = true;
              if (bricks_ptr->destroy_box_alpha(engine, box2, 0))
                destroyed = true;
              if (bricks_ptr->destroy_box_alpha(engine, box3, 0))
                destroyed = true;
              if (bricks_ptr->destroy_box_alpha(engine, box4, 0))
                destroyed = true;
              if (bricks_ptr->destroy_box_alpha(engine, box5, 0))
                destroyed = true;
            }
          }
          if (!destroyed)
          {
            // std::cout << "NO EXPLOTE EN NADA" << std::endl;
          }

          destroy_lemming(engine);

          // Hacemos que suene el pop al petar el lemming
          engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::EXPLODE_SOUND));
          return;
        }
        if (is_crashing())
        {
          destroy_lemming(engine);
          return;
        }
        if (is_drowning())
        {
          // Hacemos que suene como se ahogan
          engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::GLUG_SOUND));

          destroy_lemming(engine);
          return;
        }
        if (is_idle())
        {
          is_playing = true;
          go_walk();
          return;
        }
        return;
      }

      if (is_building())
      {
        if (current_frame == 9)
        {
          if (!brick_ptr)
          {
            auto point = direction == -1 ? local_to_world(Point2f(-0.85, 0.15)) : local_to_world(Point2f(0.45, 0.15));
            brick_ptr = std::make_shared<Brick>(Point3f(int(point.x), int(point.y), 250), engine, game_info, direction);
            engine.get_game().create_entity(brick_ptr);
          }
          else
          {
            brick_ptr->add_brick();
          }
        }
        else if (current_frame == 0)
        {
          position.y -= 2;
          position.x += 4 * direction;
          Ray ray_up = Ray(local_to_world(Point2f(0.5, 0.5)), Vector2f(0, -1));
          Ray ray_dir = Ray(local_to_world(Point2f(0.5, 0.5)), Vector2f(direction, 0));
          Float hit_offset;
          EntityPtr hit_entity;
          std::vector<std::string> force_entity_names = {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"};
          if (!brick_ptr->check_bricks())
          {
            brick_ptr = NULL;
            remove_skill(Utils::Lemming_Skills::BUILD);
            go_idle();
          }
          else if (engine.intersect_ray(ray_up, get_entity_id(),
                                        force_entity_names, hit_offset, hit_entity))
          {
            if (hit_offset < diagonal.y / 4)
            {
              brick_ptr = NULL;
              remove_skill(Utils::Lemming_Skills::BUILD);
              go_idle();
            }
          }
          else if (engine.intersect_ray(ray_dir, get_entity_id(),
                                        force_entity_names, hit_offset, hit_entity))
          {
            if (hit_offset < diagonal.y / 4)
            {
              brick_ptr = NULL;
              remove_skill(Utils::Lemming_Skills::BUILD);
              go_idle();
            }
          }
        }
      }

      std::string frame_path;

      if (state == Utils::Lemming_State::BUILDING)
        frame_path = "assets/lemming/lemming_" + std::to_string(direction) + "_" + std::to_string(get_state()) + "_" + std::to_string(Utils::LEVEL_BRICKS_TYPE[game_info.get_difficulty_selected()][game_info.get_level_selected()]) + "_" + std::to_string(current_frame) + ".png";
      else
        frame_path = "assets/lemming/lemming_" + std::to_string(direction) + "_" + std::to_string(get_state()) + "_" + std::to_string(current_frame) + ".png";

      Texture txt = engine.load_texture(frame_path.c_str());
      set_active_texture(txt);
    }
  }

  void pre_physics(Engine &engine) override
  {
    if (game_info.get_level_is_paused())
      return;
    Entity::pre_physics(engine);
    last_y = position.y;
    game_info.check_action_possible();
    update_animation(engine);
    update_counter(engine);
  }

  void update_state(Engine &engine) override
  {
    if (game_info.get_level_is_paused())
      return;

    Rigid_body::update_state(engine);

    // EXPLODING LOGIC
    if (update_explode_countdown(engine))
      add_skill_explode_all();

    // STATES LOGIC
    auto speed = get_speed();

    if (is_walking())
      return;

    if (is_falling())
      return;

    if (is_floating())
      return;

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
      return;

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

          Bound2f box;
          box.pMin = local_to_world(Point2f(0.25, 0.65));
          box.pMax = box.pMin + Vector2f(18, 8);

          bool destroyed = false;
          auto &entities = engine.get_entities();
          for (auto &entity : entities)
          {
            if (entity->get_entity_name() == "MAP")
            {

              if (entity->destroy_box_alpha(engine, box))
              {
                // std::cout << "HE CAVADO" << std::endl;
                destroyed = true;
              }
            }
            else if (entity->get_entity_name() == "DIRECTIONAL WALL")
            {
              std::shared_ptr<Directional_wall> dir_wall_ptr = std::dynamic_pointer_cast<Directional_wall>(entity);
              if (dir_wall_ptr->destroy_box_alpha(engine, box, 0))
                destroyed = true;
            }
            else if (entity->get_entity_name() == "BRICKS")
            {
              std::shared_ptr<Brick> bricks_ptr = std::dynamic_pointer_cast<Brick>(entity);
              if (bricks_ptr->destroy_box_alpha(engine, box, 0))
                destroyed = true;
            }
          }
          if (!destroyed)
          {
            remove_skill(Utils::Lemming_Skills::DIG);
            on_ground = false;
          }

          do_action_in_frame = true;
          speed.x = 0;
          speed.y = velocity;
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
    if (is_bashing())
    {
      if (current_frame == 3 || current_frame == 19)
      {
        if (!do_action_in_frame)
        {
          std::cout << current_frame << " " << do_action_in_frame << std::endl;
          Bound2f box, box1, box2;
          if (direction > 0)
          {
            box.pMin = local_to_world(Point2f(0.50, 0.30));
            box.pMax = box.pMin + Vector2f(9, 4);
            box2.pMin = local_to_world(Point2f(0.50, 0.35));
            box2.pMax = box2.pMin + Vector2f(11, 4);
            box1.pMin = local_to_world(Point2f(0.50, 0.40));
            box1.pMax = box1.pMin + Vector2f(13, 4);
            if (current_frame == 3)
            {
              box.pMax = box.pMin + Vector2f(7, 4);
              box2.pMax = box2.pMin + Vector2f(9, 4);
              box1.pMax = box1.pMin + Vector2f(11, 4);
            }
          }
          else
          {
            box.pMin = local_to_world(Point2f(0.25, 0.30));
            box.pMax = box.pMin + Vector2f(9, 4);
            box2.pMin = local_to_world(Point2f(0.20, 0.35));
            box2.pMax = box2.pMin + Vector2f(11, 4);
            box1.pMin = local_to_world(Point2f(0.15, 0.40));
            box1.pMax = box1.pMin + Vector2f(13, 4);
          }
          std::cout << current_frame << " " << box << box1 << std::endl;
          bool destroyed = false;
          auto &entities = engine.get_entities();
          for (auto &entity : entities)
          {
            if (entity->get_entity_name() == "MAP")
            {
              if (entity->destroy_box_alpha(engine, box))
              {
                destroyed = true;
              }
              if (entity->destroy_box_alpha(engine, box1))
              {
                destroyed = true;
              }
              if (entity->destroy_box_alpha(engine, box2))
              {
                destroyed = true;
              }
            }
          }
          if (!destroyed)
          {
            remove_skill(Utils::Lemming_Skills::BASH);
            go_walk();
            std::cout << "Termina de cavar...: " << destroyed << std::endl;
          }
          do_action_in_frame = true;
        }
      }
      else if (current_frame == 5 || current_frame == 21)
      {
        if (!do_action_in_frame)
        {
          std::cout << current_frame << " " << do_action_in_frame << std::endl;
          Bound2f box, box1, box2, box3;
          if (direction > 0)
          {
            box3.pMin = local_to_world(Point2f(0.45, 0.45));
            box3.pMax = box3.pMin + Vector2f(14, 3);
            box.pMin = local_to_world(Point2f(0.50, 0.50));
            box.pMax = box.pMin + Vector2f(13, 4);
            box2.pMin = local_to_world(Point2f(0.50, 0.55));
            box2.pMax = box2.pMin + Vector2f(11, 4);
            box1.pMin = local_to_world(Point2f(0.50, 0.60));
            box1.pMax = box1.pMin + Vector2f(9, 5);
            if (current_frame == 5)
            {
              box3.pMax = box3.pMin + Vector2f(12, 3);
              box.pMax = box.pMin + Vector2f(11, 4);
              box2.pMax = box2.pMin + Vector2f(9, 4);
              box1.pMax = box1.pMin + Vector2f(7, 4);
            }
          }
          else
          {
            box3.pMin = local_to_world(Point2f(0.15, 0.45));
            box3.pMax = box3.pMin + Vector2f(14, 3);
            box.pMin = local_to_world(Point2f(0.10, 0.50));
            box.pMax = box.pMin + Vector2f(13, 4);
            box2.pMin = local_to_world(Point2f(0.15, 0.55));
            box2.pMax = box2.pMin + Vector2f(11, 4);
            box1.pMin = local_to_world(Point2f(0.20, 0.60));
            box1.pMax = box1.pMin + Vector2f(9, 4);
          }
          std::cout << current_frame << " " << box << box1 << std::endl;
          bool destroyed = false;
          auto &entities = engine.get_entities();
          for (auto &entity : entities)
          {
            if (entity->get_entity_name() == "MAP")
            {
              if (entity->destroy_box_alpha(engine, box))
              {
                destroyed = true;
              }
              if (entity->destroy_box_alpha(engine, box1))
              {
                destroyed = true;
              }
              if (entity->destroy_box_alpha(engine, box2))
              {
                destroyed = true;
              }
              if (entity->destroy_box_alpha(engine, box3))
              {
                destroyed = true;
              }
            }
          }
          if (!destroyed)
          {
            remove_skill(Utils::Lemming_Skills::BASH);
            go_walk();
            std::cout << "Termina de cavar...: " << destroyed << std::endl;
          }
          do_action_in_frame = true;
        }
      }
      else if (current_frame == 9 || current_frame == 25)
      {
        if (!do_action_in_frame)
        {
          std::cout << current_frame << " " << do_action_in_frame << std::endl;
          do_action_in_frame = true;
          position.x += 2 * direction;
        }
      }
      else if (current_frame == 31)
      {
        if (!do_action_in_frame)
        {
          do_action_in_frame = true;
          position.x += 5 * direction;
        }
      }
      else
      {
        do_action_in_frame = false;
      }
      return;
    }

    if (is_climbing())
    {
      if (current_frame == 7)
      {
        if (!do_action_in_frame && !climb_now)
        {
          // position.y -= 0;
          current_frame = -1;
          on_ground = false;
        }
      }
      else if (current_frame == 0)
      {
        if (!do_action_in_frame && !climb_now)
        {
          position.y -= 3;
        }
      }
      else
      {
        do_action_in_frame = false;
      }
      return;
    }

    if (is_mining())
    {
      if (current_frame == 0)
      {
        if (!do_action_in_frame)
        { // Hay que mover la posición 0 a la altura de la 23 para que no se teletransporte

          do_action_in_frame = true;
          // Actualizamos la posivion del Lemming
          position.x += direction * 8.0; // Dirección indica el sentido de avance del Lemming
          position.y += 5.0;
        }
      }
      else if (current_frame == 1)
      {
        if (do_action_in_frame)
        { // Destruimos el cubo de mapa

          Bound2f box;
          auto minC = 0.65;
          box.pMin = local_to_world(Point2f(direction > 0 ? minC : 1 - minC, 0.75));
          box.pMax = box.pMin + Vector2f(13 * direction, -14); // Extremo del vector para señalar tamaño de caja

          Bound2f box2;
          box2.pMin = local_to_world(Point2f(direction > 0 ? minC : 1 - minC, 0.80));
          box2.pMax = box2.pMin + Vector2f(10 * direction, -17); // Extremo del vector para señalar tamaño de caja

          Bound2f box3; // Destruimos un cubo más a medio camino del movimineto de excabación
          position.x -= direction * 4.0;
          position.y -= 2.5;

          box3.pMin = local_to_world(Point2f(direction > 0 ? minC : 1 - minC, 0.80));
          box3.pMax = box3.pMin + Vector2f(14 * direction, -17);

          position.x += direction * 4.0; // Volvemos a poner el Lemming donde estaba
          position.y += 2.5;

          auto &entities = engine.get_entities();

          for (auto &entity : entities)
          {
            if (entity->get_entity_name() == "MAP")
            {

              entity->destroy_box_alpha(engine, box);
              entity->destroy_box_alpha(engine, box2);
              entity->destroy_box_alpha(engine, box3);
            }
            else if (entity->get_entity_name() == "DIRECTIONAL WALL")
            {
              std::shared_ptr<Directional_wall> dir_wall_ptr = std::dynamic_pointer_cast<Directional_wall>(entity);
              dir_wall_ptr->destroy_box_alpha(engine, box, 0);
              dir_wall_ptr->destroy_box_alpha(engine, box2, 0);
              dir_wall_ptr->destroy_box_alpha(engine, box3, 0);
            }
          }
          do_action_in_frame = false;
        }
      }
      else
      {
        do_action_in_frame = false;
        speed.x = 0;
        speed.y = 0;
        set_speed(speed);
      }
      // Comprobamos que haya suelo
      Ray ray_down = Ray(local_to_world(Point2f(direction > 0 ? 0.65 : 1 - 0.65, 0.5)), Vector2f(0, 1));
      Float hit_offset_down;
      EntityPtr hit_entity_down;

      std::vector<std::string> force_entity_names = {"MAP", "METAL", "DIRECTIONAL WALL"};

      engine.intersect_ray(ray_down, get_entity_id(),
                           force_entity_names, hit_offset_down, hit_entity_down);

      if (hit_offset_down > (diagonal.y / 2)) // Detectamos que no hay suelo
      {
        remove_skill(Utils::Lemming_Skills::MINE);
        on_ground = false;
      }

      return;
    }
  }

  void on_collision(Engine &, EntityPtr other) override
  {
    if (game_info.get_level_is_paused())
      return;
    Entity::on_collision(engine, other);
    auto speed = get_speed();

    if (other->get_entity_name() == "MAP" || other->get_entity_name() == "DIRECTIONAL WALL" || other->get_entity_name() == "METAL" || other->get_entity_name() == "Lemming")
    {
      // if (other->get_entity_name() == "Lemming")
      // {
      //   std::shared_ptr<Lemming> lemming_ptr = std::dynamic_pointer_cast<Lemming>(other);
      //   if (lemming_ptr && lemming_ptr->get_state() != Utils::BLOCKING)
      //     return;
      // }

      if (is_walking())
      {
        if ((check_collision_left(other) && direction == -1) || (check_collision_right(other) && direction == 1))
        {

          if (skills & Utils::CLIMB)
          {
            go_climb();
          }
          else
          {
            position.x -= 3 * direction;
            direction *= -1;
          }
          // std::cout << "Lemming turn left\n";
        }
      }
      if (is_climbing())
      {
        // Se aleja virtualmente el Lemming de la pared para que no interfiera
        // con la comprobación de si hay techo. Luego se revierte.
        position.x -= 2 * direction;
        if (check_collision_up(other))
        {
          std::cout << "Techo\n";
          go_fall();
          // position.x += 2 * direction;
          direction *= -1;
        }
        else
        {
          position.x += 2 * direction;
          if ((!check_collision_left(other) && direction == -1) || (!check_collision_right(other) && direction == 1))
          {
            std::cout << "No hay pared\n";
            if (!climb_now)
            {
              climb_now = true;
            }
            else if (current_frame == 15)
            {
              climb_now = false;
              go_walk();
            }
          }
        }
      }

      if ((is_falling() || is_floating()) && !(other->get_entity_name() == "Lemming"))
      {
        if (check_collision_down(other))
        {
          // std::cout << "detect down\n";
          // std::cout << on_ground << std::endl;

          on_ground = true;
          // std::cout << "Distance falling: " << distance_fall << std::endl;

          speed.y = 0;
          if (distance_fall >= Utils::MAX_DISTANCE_FALL && !is_floating())
          {
            go_crash();
          }
          else
          {
            position.y -= 1;
            distance_fall = 0.0f;
            go_walk();
          }
        }
      }
    }

    if (other->get_entity_name() == "Gate hitbox")
    {
      on_ground = true;
      go_escape();
      speed.x = 0;
      speed.y = 0;
    }

    if (other->get_entity_name() == "LIQUID TRIGGER")
    {
      on_ground = true;
      go_drown();
      speed.x = 0;
      speed.y = 0;
    }

    if (other->get_entity_name() == "Fire")
    {
      on_ground = true;
      go_crash();
      speed.x = 0;
      speed.y = 0;
    }

    if (other->get_entity_name() == "Spinner" || other->get_entity_name() == "Flamethrower")
    {
      on_ground = true;
      speed.x = 0;
      speed.y = 0;
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::FIRE_SOUND));
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "Chain")
    {
      on_ground = true;
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
    if (game_info.get_level_is_paused())
      return;
    if (is_falling() || is_floating())
    {
      distance_fall = distance_fall + (position.y - last_y);
      //std::cout << "Posicion de Lemming: " << position.y << std::endl;

      //Si se salen fuera del mapa
      if(position.y > 320.0f){

        //Obten el sonido de un Lemming gritando por su vida
        engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::DIE_SOUND));

        //Destruye el lemming
        destroy_lemming(engine);
      }
    }
    else
    {
      distance_fall = 0.0f;
    }

    if (skills & Utils::EXPLODE)
    {
      go_explode();
      return;
    }
    if (skills & Utils::BLOCK)
    {
      go_block();
      change_collision_type(engine, Entity::Collision_type::STRUCTURE);
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
    if (is_falling() && distance_fall > Utils::MAX_DISTANCE_FALL / 4 && skills & Utils::FLOAT)
    {
      go_float();
    }
    if (!(is_floating() || is_falling() || is_climbing()))
    {
      if (!on_ground)
      {
        go_fall();
      }
    }
    else
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
    }
  }

  void on_event_down(Engine &engine, EngineIO::InputEvent event) override
  {
    // Evita que se puedan seleccionar desde el minimapa
    if (engine.get_camera_in_which_hovered(*this) != game_info.get_game_camera_id())
      return;

    if (event == EngineIO::InputEvent::MOUSE_LEFT && contains_the_mouse(engine) && !game_info.get_level_is_paused())
    {
      // std::cout << "LEMMING PULSADO" << std::endl;
      int skill = Utils::HUD_TO_SKILL[game_info.get_option_selected()];
      std::cout << skill << std::endl;
      if (skill != Utils::NO_SKILLS && game_info.get_action_possible())
      {
        bool res = add_skill(Utils::HUD_TO_SKILL[game_info.get_option_selected()]);
        if (res)
        {
          // Realizamos el sonido de presion sobre el lemming
          engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::MOUSE_PRESS_SOUND));

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
      if (!is_hovered && !((is_escaping() || is_crashing() || is_exploding() || is_drowning())))
      {
        game_info.set_lemming_hovered_type(type);
        game_info.add_lemmings_hovered();
        is_hovered = true;
      }

      if (game_info.get_is_cursor_hover() == false && !((is_escaping() || is_crashing() || is_exploding() || is_drowning())))
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

  void on_creation(Engine &engine) override
  {
    Rigid_body::on_creation(engine);

    // Change type after rigid body creation
    //  (sets by default it to STRUCTURE)
    change_collision_type(engine, Collision_type::CHARACTER);
  }
};
