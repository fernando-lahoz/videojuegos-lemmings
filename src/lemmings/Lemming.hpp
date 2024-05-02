#pragma once

#include "engine/rigid_body.hpp"
#include "engine/render_2D.hpp"
#include "engine/engine.hpp"
#include "geometry/point.hpp"

#include "lemmings/structure/Chain.hpp"
#include "lemmings/structure/Ball_zapper.hpp"
#include "lemmings/structure/Tons_trigger.hpp"
#include "lemmings/structure/Rock_crusher_trigger.hpp"
#include "lemmings/structure/Bear_trap_trigger.hpp"
#include "lemmings/structure/Antimatter_beam_trigger.hpp"
#include "lemmings/structure/Pin_trigger.hpp"
#include "lemmings/structure/Thumper.hpp"
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
  float distance_fall = 0.0f;
  float last_y = 0.0f;
  bool do_action_in_frame = false;
  bool is_hovered = false;
  float velocity = 50;

  int skills = Utils::NO_SKILLS;
  bool change_state_mine = false;
  bool explosion_in_liquid = false;

  bool bashing_destroyed_map = false; // Indica si en un loop de la animacion se ha roto algo

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

  std::chrono::time_point<std::chrono::steady_clock> last_falling = std::chrono::steady_clock::now();

  std::shared_ptr<Brick> brick_ptr;
  int brick_num = 0;

  std::string get_type() { return type; }

  void restart_animation()
  {
    is_playing = true;
    current_frame = 0;
    time_frame_sprite = 0.0f;
  }

  void go_idle()
  {
    if (!is_idle())
      restart_animation();
    state = Utils::IDLE;
    type = Utils::LEMMING_TYPE[Utils::IDLE];
  }

  void go_walk()
  {
    if (!is_walking())
      restart_animation();
    state = Utils::WALKING;
    if (skills & Utils::FLOAT && skills & Utils::CLIMB)
      type = Utils::LEMMING_TYPE[14]; // ATHLETE
    else if (skills & Utils::FLOAT)
      type = Utils::LEMMING_TYPE[Utils::FLOATING];
    else if (skills & Utils::CLIMB)
      type = Utils::LEMMING_TYPE[Utils::CLIMBING];
    else
      type = Utils::LEMMING_TYPE[Utils::WALKING];
  }

  void go_fall()
  {
    if (!is_falling())
      restart_animation();
    state = Utils::FALLING;
    if (skills & Utils::FLOAT && skills & Utils::CLIMB)
      type = Utils::LEMMING_TYPE[14]; // ATHLETE
    else if (skills & Utils::FLOAT)
      type = Utils::LEMMING_TYPE[Utils::FLOATING];
    else if (skills & Utils::CLIMB)
      type = Utils::LEMMING_TYPE[Utils::CLIMBING];
    else
      type = Utils::LEMMING_TYPE[Utils::FALLING];
  }

  void go_block()
  {
    if (!is_blocking())
      restart_animation();
    state = Utils::BLOCKING;
    type = Utils::LEMMING_TYPE[Utils::BLOCKING];
  }

  void go_build()
  {
    if (!is_building())
    {
      brick_num = 0;
      restart_animation();
    }
    state = Utils::BUILDING;
    type = Utils::LEMMING_TYPE[Utils::BUILDING];
  }

  void go_climb()
  {
    if (!is_climbing())
      restart_animation();
    state = Utils::CLIMBING;
    if (skills & Utils::FLOAT && skills & Utils::CLIMB)
      type = Utils::LEMMING_TYPE[14]; // ATHLETE
    else if (skills & Utils::FLOAT)
      type = "ERROR NO HAVE CLIMB SKILL BUT FLOAT SKILL HAS";
    else
      type = Utils::LEMMING_TYPE[Utils::CLIMBING];
  }

  void go_float()
  {
    if (!is_floating())
      restart_animation();
    current_frame = 0;
    state = Utils::FLOATING;
    if (skills & Utils::FLOAT && skills & Utils::CLIMB)
      type = Utils::LEMMING_TYPE[14]; // ATHLETE
    else if (skills & Utils::CLIMB)
      type = "ERROR NO HAVE FLOAT SKILL BUT CLIMB SKILL HAS";
    else
      type = Utils::LEMMING_TYPE[Utils::FLOATING];
  }

  void go_explode()
  {
    if (!is_exploding())
      restart_animation();
    state = Utils::EXPLODING;
    type = Utils::LEMMING_TYPE[Utils::EXPLODING];
  }

  void go_dig()
  {
    if (!is_digging())
      restart_animation();
    state = Utils::DIGGING;
    type = Utils::LEMMING_TYPE[Utils::DIGGING];
  }

  void go_bash()
  {
    if (!is_bashing())
      restart_animation();
    state = Utils::BASHING;
    type = Utils::LEMMING_TYPE[Utils::BASHING];
  }

  void go_mine()
  {
    if (!is_mining())
      restart_animation();
    state = Utils::MINING;
    type = Utils::LEMMING_TYPE[Utils::MINING];
  }

  void go_escape()
  {
    if (!is_escaping())
      restart_animation();
    if (play_death_sound) // Hacemos que suene el yipee
    {
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::YIPEE_SOUND), game_info.get_effects_volume());
      play_death_sound = false;
    }
    state = Utils::ESCAPING;
    type = Utils::LEMMING_TYPE[Utils::ESCAPING];
  }

  void go_drown()
  {
    if (!is_drowning())
      restart_animation();
    state = Utils::DROWNING;
    type = Utils::LEMMING_TYPE[Utils::DROWNING];
    if (play_death_sound) // Hacemos que suene el chapuzon que se dan
    {
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SPLASH_SOUND), game_info.get_effects_volume());
      play_death_sound = false;
    }
  }

  void go_crash()
  {
    if (!is_crashing())
      restart_animation();
    state = Utils::CRASHING;
    type = Utils::LEMMING_TYPE[Utils::CRASHING];
    // Hacemos que suene como se estrellan contra el suelo
    engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SPLAT_SOUND), game_info.get_effects_volume());
  }

  bool is_idle() { return state == Utils::IDLE; }

  bool is_falling() { return state == Utils::FALLING; }

  bool is_walking() { return state == Utils::WALKING; }

  bool is_blocking() { return state == Utils::BLOCKING; }

  bool is_building() { return state == Utils::BUILDING; }

  bool is_climbing() { return state == Utils::CLIMBING; }

  bool is_floating() { return state == Utils::FLOATING; }

  bool is_exploding() { return state == Utils::EXPLODING; }

  bool is_digging() { return state == Utils::DIGGING; }

  bool is_bashing() { return state == Utils::BASHING; }

  bool is_mining() { return state == Utils::MINING; }

  bool is_escaping() { return state == Utils::ESCAPING; }

  bool is_drowning() { return state == Utils::DROWNING; }

  bool is_crashing() { return state == Utils::CRASHING; }

public:
  Lemming(Point3f position, Vector2f diagonal, Engine &_engine, Game_info &_game_info)
      : Rigid_body(position, diagonal,
                   _engine.load_texture("assets/lemming/lemming_1_2_0.png"),
                   engine, "Lemming", "Lemming"),
        game_info(_game_info), engine(_engine)
  {
    constructor_set_collision_type(Collision_type::CHARACTER);
    override_down_point(Bound2f(Point2f(0.45, 0.65), Point2f(0.55, 0.85)));
    override_up_point(Bound2f(Point2f(0.4, 0.2), Point2f(0.6, 0.4)));
    override_left_point(Bound2f(Point2f(0.4, 0.45), Point2f(0.5, 0.55)));
    override_right_point(Bound2f(Point2f(0.5, 0.45), Point2f(0.6, 0.55)));

    disable_alpha_mouse();
    // disable_alpha_collision();
  }
  ~Lemming()
  {
  }

  void set_dead_marked(bool new_value) { dead_marked = new_value; }
  bool get_dead_marked() { return dead_marked; }

  int get_state() { return state; }

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

  void add_skill_explode_all() { skills = skills | Utils::EXPLODE; }

  void remove_skill(int skill) { skills = skills & ~skill; }

  bool is_skill(int skill) { return skills & skill; }

  bool add_skill(int skill)
  {
    int ind = skill_to_index(skill);
    int a = game_info.get_skill_amount(Utils::SKILL_TO_SKILLS_AMOUNT[ind]);
    if (a <= 0)
      return false;

    if (skills & skill) // The new skill cannot be added before
      return false;
    // RESTRICTIONS
    if (((is_floating() || is_falling()) && (skill >= Utils::SKILL_EGOIST)) || ((skill == Utils::CLIMB || skill == Utils::FLOAT) && (skills >= Utils::SKILL_EGOIST)) ||
        (is_escaping() || is_crashing() || is_exploding() || is_drowning()) || (skill >= Utils::SKILL_EGOIST && skills >= Utils::SKILL_EGOIST) || false)
      return false;
    if (skill == Utils::Lemming_Skills::EXPLODE)
      set_dead_marked(true);
    else
    {
      skills = skills | skill;
      if (skills < Utils::SKILL_EGOIST) // change name type of the lemming depending on the skill
      {
        if (skills & Utils::FLOAT && skills & Utils::CLIMB)
          type = Utils::LEMMING_TYPE[14]; // ATHLETE
        else if (skills & Utils::FLOAT)
          type = Utils::LEMMING_TYPE[Utils::FLOATING];
        else if (skills & Utils::CLIMB)
          type = Utils::LEMMING_TYPE[Utils::CLIMBING];
        else
          type = Utils::LEMMING_TYPE[Utils::FALLING];
      }
    }
    game_info.sub_skill_amount(Utils::SKILL_TO_SKILLS_AMOUNT[skill_to_index(skill)]);
    return true;
  }

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
        last_time_to_live = (int)(time_to_live + 0.999);
    }
  }

  void update_animation(Engine &engine)
  {
    if (!is_playing)
      return;

    time_frame_sprite += engine.get_delta_time() * game_info.get_game_speed();
    if (time_frame_sprite >= Utils::STATE_ANIMATION_DURATION[get_state()] / Utils::STATE_N_FRAMES[get_state()])
    {
      time_frame_sprite = 0.0f;
      current_frame = (current_frame + 1) % Utils::STATE_N_FRAMES[get_state()];
      if (counter)
      {
        if (is_drowning())
          counter->set_position2D(Point2f(position.x + ((int)(current_frame / 4)) * 4 + (diagonal.x / 2) - (counter->get_diagonal().x / 2), position.y - 2));
        else
          counter->set_position2D(Point2f(position.x + (diagonal.x / 2) - (counter->get_diagonal().x / 2), position.y - 2));
        if (is_crashing()) // Eliminamos el contador de la cuenta regresiba cuando se muere por caida
          counter->destroy();
      }
      if (is_falling())
        position.y += 4;
      if (is_floating())
        position.y += 2;
      if (is_climbing())
      {
        if (current_frame == 8)
        {
          Ray ray_down = Ray(local_to_world(Point2f(0.5 + (0.15 * direction), 0.15)), Vector2f(0, 1));
          Ray ray_up = Ray(local_to_world(Point2f(0.5 - (0.15 * direction), 0.5)), Vector2f(0, -1));
          float hit_offset;
          EntityPtr hit_entity;
          engine.intersect_ray(ray_up, get_entity_id(),
                               {"MAP", "METAL", "DIRECTIONAL WALL"}, hit_offset, hit_entity);
          if (hit_offset < diagonal.y * (10. / 20.))
          {
            std::cout << "Lemming choco con techo\n";
            position.y -= 6;
            go_fall();
            direction *= -1;
            return;
          }
          engine.intersect_ray(ray_down, get_entity_id(),
                               {"MAP", "METAL", "DIRECTIONAL WALL"}, hit_offset, hit_entity);
          // if (hit_offset < diagonal.y * (1. / 20.))
          // {
          //   current_frame = 0;
          //   position.y -= 6;
          //   on_ground = false;
          // }
          if (hit_offset == 0)
          {
            current_frame = 0;
            position.y -= 6;
            on_ground = false;
          }
          else
          {
            position.y += round(hit_offset) - 2;
          }
        }
        else if (current_frame == 9)
        {
          position.y -= 8;
        }
        else if (current_frame == 0)
        {
          position.y -= 10;
          position.x += 4 * direction;
          go_walk();
        }

        // Los lemmings se pueden colar por encima del mapa en el original
        // if (position.y < -8)
        // {
        //   std::cout << "Lemming escalador llegó al límite de altura del mapa\n";
        //   go_fall();
        //   direction *= -1;
        // }
      }
      if (is_bashing())
      {
        Bound2f box;
        bool is_frame_destroy_alpha = false;
        if (current_frame == 2)
        {
          position.x += 2 * direction;
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.5, 0.3))), Point2f(local_to_world(Point2f(0.7, 0.4)))) : Bound2f(Point2f(local_to_world(Point2f(0.3, 0.3))), Point2f(local_to_world(Point2f(0.5, 0.4))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 18)
        {
          position.x += 2 * direction;
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.5, 0.3))), Point2f(local_to_world(Point2f(0.9, 0.4)))) : Bound2f(Point2f(local_to_world(Point2f(0.1, 0.3))), Point2f(local_to_world(Point2f(0.5, 0.4))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 3)
        {
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.5, 0.35))), Point2f(local_to_world(Point2f(0.75, 0.55)))) : Bound2f(Point2f(local_to_world(Point2f(0.25, 0.35))), Point2f(local_to_world(Point2f(0.5, 0.55))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 19)
        {
          position.x += 2 * direction;
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.5, 0.35))), Point2f(local_to_world(Point2f(0.95, 0.55)))) : Bound2f(Point2f(local_to_world(Point2f(0.05, 0.35))), Point2f(local_to_world(Point2f(0.5, 0.55))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 4)
        {
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.5, 0.5))), Point2f(local_to_world(Point2f(0.75, 0.6)))) : Bound2f(Point2f(local_to_world(Point2f(0.25, 0.5))), Point2f(local_to_world(Point2f(0.5, 0.6))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 20)
        {
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.5, 0.5))), Point2f(local_to_world(Point2f(0.95, 0.6)))) : Bound2f(Point2f(local_to_world(Point2f(0.05, 0.5))), Point2f(local_to_world(Point2f(0.5, 0.6))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 5)
        {
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.5, 0.55))), Point2f(local_to_world(Point2f(0.75, 0.7)))) : Bound2f(Point2f(local_to_world(Point2f(0.25, 0.55))), Point2f(local_to_world(Point2f(0.5, 0.7))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 21)
        {
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.5, 0.55))), Point2f(local_to_world(Point2f(0.95, 0.7)))) : Bound2f(Point2f(local_to_world(Point2f(0.05, 0.55))), Point2f(local_to_world(Point2f(0.5, 0.7))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 6)
        {
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.4, 0.65))), Point2f(local_to_world(Point2f(0.7, 0.75)))) : Bound2f(Point2f(local_to_world(Point2f(0.3, 0.65))), Point2f(local_to_world(Point2f(0.6, 0.75))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 22)
        {
          position.x += 4 * direction;
          box = direction > 0 ? Bound2f(Point2f(local_to_world(Point2f(0.4, 0.65))), Point2f(local_to_world(Point2f(0.7, 0.75)))) : Bound2f(Point2f(local_to_world(Point2f(0.2, 0.65))), Point2f(local_to_world(Point2f(0.6, 0.75))));
          is_frame_destroy_alpha = true;
        }
        else if (current_frame == 10 || current_frame == 4 || current_frame == 15 || current_frame == 26)
          position.x += 2 * direction;
        else if (current_frame == 0)
          position.x += 6 * direction;
        else if (current_frame == 22)
          position.x += 4 * direction;
        if (is_frame_destroy_alpha)
        {
          auto &entities = engine.get_entities();
          for (auto &entity : entities)
          {
            if (entity->get_entity_name() == "MAP")
            {
              if (entity->destroy_box_alpha(engine, box))
                bashing_destroyed_map = true;
            }
            else if (entity->get_entity_name() == "DIRECTIONAL WALL")
            {
              std::shared_ptr<Directional_wall> dir_wall_ptr = std::dynamic_pointer_cast<Directional_wall>(entity);
              if (dir_wall_ptr->destroy_box_alpha(engine, box, direction))
                bashing_destroyed_map = true;
            }
            else if (entity->get_entity_name() == "BRICKS")
            {
              std::shared_ptr<Brick> bricks_ptr = std::dynamic_pointer_cast<Brick>(entity);
              if (bricks_ptr->destroy_box_alpha(engine, box, 0))
                bashing_destroyed_map = true;
            }
          }
        }
        if (current_frame == 3 || current_frame == 4 || current_frame == 5 || current_frame == 19 || current_frame == 20 || current_frame == 21)
        {
          if (!bashing_destroyed_map)
          {
            remove_skill(Utils::Lemming_Skills::BASH);
            go_walk();
            std::cout << "Termina de cavar...: " << bashing_destroyed_map << std::endl;
          }
          else
          {
            bashing_destroyed_map = false;
            float hit_offset_down;
            EntityPtr hit_entity_down;
            Ray ray_down = Ray(local_to_world(Point2f(0.5, 0.4)), Vector2f(0, 1));
            engine.intersect_ray(ray_down, get_entity_id(),
                                 {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset_down, hit_entity_down);
            if (hit_offset_down > diagonal.y * 0.5)
            {
              remove_skill(Utils::Lemming_Skills::BASH);
              go_walk();
            }
          }
        }
        if (current_frame == 31 || current_frame == 14)
        {
          if (!bashing_destroyed_map)
          {
            remove_skill(Utils::Lemming_Skills::BASH);
            go_walk();
            std::cout << "Termina de cavar...: " << bashing_destroyed_map << std::endl;
          }
          else
          {
            bashing_destroyed_map = false;
            float hit_offset_down;
            EntityPtr hit_entity_down;
            Ray ray_down = Ray(local_to_world(Point2f(0.5, 0.4)), Vector2f(0, 1));
            engine.intersect_ray(ray_down, get_entity_id(),
                                 {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset_down, hit_entity_down);
            if (hit_offset_down > diagonal.y * 0.5)
            {
              remove_skill(Utils::Lemming_Skills::BASH);
              go_walk();
            }
          }
        }
      }
      if (is_walking())
      {
        position.x += 2 * direction;

        bool cond = false;
        Point2f collision_pixel_up, collision_pixel_down;
        EntityPtr hit_entity;
        Bound2f collision_point_up = direction == -1 ? Bound2f(Point2f(0.45, 0.4), Point2f(0.5, 0.75)) : Bound2f(Point2f(0.5, 0.4), Point2f(0.55, 0.75));
        Bound2f collision_point_down = direction == -1 ? Bound2f(Point2f(0.5, 0.75), Point2f(0.55, 1.05)) : Bound2f(Point2f(0.45, 0.75), Point2f(0.5, 1.05));
 
        bool is_valid_up = false;
        bool collides = engine.alpha_box_collision_if_all_Y_force_entity_names(Entity::local_to_world(collision_point_up),
                                                                               get_entity_id(), {"MAP", "METAL", "DIRECTIONAL WALL"}, is_valid_up,
                                                                               collision_pixel_up, Physics_engine::GET_LAST, Physics_engine::GET_LAST,
                                                                               hit_entity);

        bool is_down_valid = false;
        engine.alpha_box_collision_if_all_Y_force_entity_names(Entity::local_to_world(collision_point_down),
                                                               get_entity_id(), {"MAP", "METAL", "DIRECTIONAL WALL"}, is_down_valid,
                                                               collision_pixel_down, Physics_engine::GET_FIRST, Physics_engine::GET_FIRST,
                                                               hit_entity);

        if (collides)
        {
          float distance_y = collision_pixel_up.y - (Entity::get_position2D().y + 30);
          //std::cout << "COLLIDES: " << distance_y << '\n';
          
          cond = true;
        }

        if (!cond && is_valid_up)
        {
          float distance_y = collision_pixel_up.y - (Entity::get_position2D().y + 30);
          //std::cout << "collision_pixel.y: " << collision_pixel_up.y << ' ' << distance_y << " \n";
          position.y = (static_cast<int>((position.y + (static_cast<int>(distance_y) / 2) * 2)) / 2) * 2;
          if (distance_y < 0)
          {
            // std::cout << "El lemming sube - dist: " << distance_y << " \n";
            cond = true;
          }
        }
        if (!cond)
        {

          if (is_down_valid)
          {
            float distance_y = collision_pixel_down.y - (Entity::get_position2D().y + 30);
            position.y = (static_cast<int>((position.y + (std::round(distance_y) / 2) * 2)) / 2) * 2;
            cond = true;
            if (distance_y > 0)
            {
              // std::cout << "El lemming baja - dist: " << distance_y << " \n";
            }
          }
        }
        if (!cond)
        {
          //std::cout << "El lemming cae \n";
          on_ground = false;
        }

        /*
        Ray ray_down = Ray(local_to_world(Point2f((direction > 0) ? 0.45 : 1 - 0.45, 0.4)), Vector2f(0, 1));
        Ray ray_mid_down = Ray(local_to_world(Point2f(0.5, 0.75)), Vector2f(0, 1));
        float hit_offset_down = diagonal.y / 2;
        float offset_fall = 0.7;
        float offset_adjust = 0.35;
        EntityPtr hit_entity_down;

        Ray ray_up = Ray(local_to_world(Point2f(direction > 0 ? 0.65 : 1 - 0.65, 0)), Vector2f(0, -1));
        Float hit_offset_up;
        EntityPtr hit_entity_up;
        engine.intersect_ray(ray_up, get_entity_id(),
                             {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset_up, hit_entity_up);

        engine.intersect_ray(ray_down, get_entity_id(),
                             {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset_down, hit_entity_down);

        if (hit_entity_down && hit_entity_down->get_entity_name() == "BRICKS")
        {
          std::shared_ptr<Brick> ptr = std::dynamic_pointer_cast<Brick>(hit_entity_down);
          if (direction != ptr->get_direction())
            engine.intersect_ray(ray_mid_down, get_entity_id(),
                                 {"MAP", "METAL", "DIRECTIONAL WALL"}, hit_offset_down, hit_entity_down);
        }
        if (hit_offset_down == 0)
        {
          offset_fall = 0.35;
          offset_adjust = 0;
          engine.intersect_ray(ray_mid_down, get_entity_id(),
                               {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset_down, hit_entity_down);
        }
        if (hit_offset_down < diagonal.y * offset_fall)
        {
          if (hit_offset_down > 0 && (hit_offset_down > diagonal.y * (8. / 20.) || hit_offset_down < diagonal.y * (6. / 20.)))
          { // std::cout << "sube baja altura " << diagonal.y * (14. / 20.) << " - " << hit_offset_down << " - " << static_cast<int>(round(hit_offset_down / 2.) * 2) << "\n";
            hit_offset_down = (static_cast<int>(round(hit_offset_down / 2.) * 2));

            if ((abs(hit_offset_down - diagonal.y * offset_adjust) > 0) || hit_offset_up > 0)
            { // En caso de que el Lemming ya toque el techo, no puede subir más su posición
              position.y += (hit_offset_down - diagonal.y * offset_adjust);
              // position.y = (static_cast<int>(position.y) / 2) * 2;
              // position.y = static_cast<int>(position.y);
            }
          }
        }
        else
        {
          // std::cout << "cae " << diagonal.y * (14. / 20.) << " - " << hit_offset_down << "\n";
          // std::cout << "lemming nº" << get_entity_id() << " se cayó pq detecto dist: " << hit_offset_down << "\n";
          on_ground = false;
        }
        */
      }

      if (is_blocking() && current_frame == 0)
      {
        Ray ray_down = Ray(local_to_world(Point2f(0.45, 0.5)), Vector2f(0, 1));
        Float hit_offset_down;
        EntityPtr hit_entity_down;
        engine.intersect_ray(ray_down, get_entity_id(),
                             {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset_down, hit_entity_down);
        if (hit_offset_down > diagonal.y / 2)
        {
          remove_skill(Utils::Lemming_Skills::BLOCK);
          change_collision_type(engine, Entity::Collision_type::CHARACTER);
          enable_alpha_collision();
          on_ground = false;
        }
      }

      if (is_mining())
      {
        // Comprobamos que haya suelo
        Ray ray_down = Ray(local_to_world(Point2f(direction > 0 ? 0.65 : 1 - 0.65, 0.5)), Vector2f(0, 1));
        Float hit_offset_down;
        EntityPtr hit_entity_down;
        engine.intersect_ray(ray_down, get_entity_id(),
                             {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset_down, hit_entity_down);

        if (hit_offset_down > (diagonal.y / 2)) // Detectamos que no hay suelo
        {
          remove_skill(Utils::Lemming_Skills::MINE);
          on_ground = false;
          return;
        }

        engine.intersect_ray(ray_down, get_entity_id(),
                             "METAL", hit_offset_down, hit_entity_down);
        if (hit_entity_down && hit_offset_down < (diagonal.y / 2))
        {
          remove_skill(Utils::Lemming_Skills::MINE);
          go_walk();
          return;
        }
        // Comprobamos si hay suelo en diagonal
        Ray ray_dia = Ray(local_to_world(Point2f(direction > 0 ? 0.65 : 1 - 0.65, 0.5)), Vector2f(direction * 1, 1));

        engine.intersect_ray(ray_dia, get_entity_id(),
                             {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset_down, hit_entity_down);

        if (hit_offset_down > (diagonal.y / 1.8)) // Detectamos que no hay suelo
        {
          remove_skill(Utils::Lemming_Skills::MINE);
          go_walk();
        }

        if (current_frame == 0)
        {                                // Hay que mover la posición 0 a la altura de la 23 para que no se teletransporte
                                         // Actualizamos la posivion del Lemming
          position.x += direction * 8.0; // Dirección indica el sentido de avance del Lemming
          position.y += 5.0;
        }
        else if (current_frame == 1)
        {
          // Destruimos el cubo de mapa
          Bound2f box;
          auto minC = 0.65;
          box.pMin = local_to_world(Point2f(direction > 0 ? minC : 1 - minC, 0.50));
          box.pMax = box.pMin + Vector2f(7 * direction, -9.0); // Extremo del vector para señalar tamaño de caja

          auto &entities = engine.get_entities();
          for (auto &entity : entities)
          {
            if (entity->get_entity_name() == "MAP")
              entity->destroy_box_alpha(engine, box);
            else if (entity->get_entity_name() == "DIRECTIONAL WALL")
            {
              std::shared_ptr<Directional_wall> dir_wall_ptr = std::dynamic_pointer_cast<Directional_wall>(entity);
              dir_wall_ptr->destroy_box_alpha(engine, box, direction);
            }
            else if (entity->get_entity_name() == "BRICKS")
            {
              std::shared_ptr<Brick> bricks_ptr = std::dynamic_pointer_cast<Brick>(entity);
              bricks_ptr->destroy_box_alpha(engine, box, 0);
            }
          }
        }
        else if (current_frame == 2)
        {
          std::cout << "MINING 2\n";
          Bound2f box; // Cubo de arriba a la derecha
          auto minC = 0.65;
          box.pMin = local_to_world(Point2f(direction > 0 ? minC : 1 - minC, 0.75));
          box.pMax = box.pMin + Vector2f(11 * direction, -15); // Extremo del vector para señalar tamaño de caja

          Bound2f box2; // Cubo de abajo a la derecha
          box2.pMin = local_to_world(Point2f(direction > 0 ? minC : 1 - minC, 0.80));
          box2.pMax = box2.pMin + Vector2f(8 * direction, -10); // Extremo del vector para señalar tamaño de caja

          Bound2f box3; // Cubo central a la derecha
          box3.pMin = local_to_world(Point2f(direction > 0 ? minC : 1 - minC, 0.65));
          box3.pMax = box3.pMin + Vector2f(13 * direction, -7); // Extremo del vector para señalar tamaño de caja

          Bound2f box4; // Destruimos un cubo en la posición del lemming
          position.x -= direction * 9.0;
          position.y -= 5.6;

          box4.pMin = local_to_world(Point2f(direction > 0 ? minC : 1 - minC, 0.80));
          box4.pMax = box4.pMin + Vector2f(12 * direction, -17);

          position.x += direction * 9.0; // Volvemos a poner el Lemming donde estaba
          position.y += 5.6;

          Bound2f box5; // Destruimos un cubo más a medio camino del movimineto de excabación
          position.x -= direction * 4.0;
          position.y -= 2.5;

          minC = 0.6;
          box5.pMin = local_to_world(Point2f(direction > 0 ? minC : 1 - minC, 0.80));
          box5.pMax = box5.pMin + Vector2f(14 * direction, -17);

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
              entity->destroy_box_alpha(engine, box4);
              entity->destroy_box_alpha(engine, box5);
            }
            else if (entity->get_entity_name() == "DIRECTIONAL WALL")
            {
              std::shared_ptr<Directional_wall> dir_wall_ptr = std::dynamic_pointer_cast<Directional_wall>(entity);
              dir_wall_ptr->destroy_box_alpha(engine, box, direction);
              dir_wall_ptr->destroy_box_alpha(engine, box2, direction);
              dir_wall_ptr->destroy_box_alpha(engine, box3, direction);
              dir_wall_ptr->destroy_box_alpha(engine, box4, direction);
              dir_wall_ptr->destroy_box_alpha(engine, box5, direction);
            }
            else if (entity->get_entity_name() == "BRICKS")
            {
              std::shared_ptr<Brick> bricks_ptr = std::dynamic_pointer_cast<Brick>(entity);
              bricks_ptr->destroy_box_alpha(engine, box, 0);
              bricks_ptr->destroy_box_alpha(engine, box2, 0);
              bricks_ptr->destroy_box_alpha(engine, box3, 0);
              bricks_ptr->destroy_box_alpha(engine, box4, 0);
              bricks_ptr->destroy_box_alpha(engine, box5, 0);
            }
          }
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
          Bound2f box = Bound2f(Point2f(local_to_world(Point2f(0.35, 0))), Point2f(local_to_world(Point2f(0.65, 1))));
          Bound2f box2 = Bound2f(Point2f(local_to_world(Point2f(0.65, 0))), Point2f(local_to_world(Point2f(0.35, 1))));
          Bound2f box3 = Bound2f(Point2f(local_to_world(Point2f(0.2, 0.05))), Point2f(local_to_world(Point2f(0.8, 0.95))));
          Bound2f box4 = Bound2f(Point2f(local_to_world(Point2f(0.05, 0.2))), Point2f(local_to_world(Point2f(0.95, 0.8))));
          Bound2f box5 = Bound2f(Point2f(local_to_world(Point2f(0.15, 0.15))), Point2f(local_to_world(Point2f(0.85, 0.85))));

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
          engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::EXPLODE_SOUND), game_info.get_effects_volume());
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
          engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::GLUG_SOUND), game_info.get_effects_volume());
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
            // TODO: remove Brick references...

            // brick_ptr = std::make_shared<Brick>(Point3f((static_cast<int>(point.x) / 2) * 2, (static_cast<int>(point.y) / 2) * 2, 250), engine, game_info, direction);
            // engine.get_game().create_entity(brick_ptr);
            brick_num++;
            auto bound = direction == -1 ? Bound2f(Point2f(0.25, 0.7), Point2f(0.55, 0.75)) : Bound2f(Point2f(0.45, 0.7), Point2f(0.75, 0.75));
            game_info.get_map_ptr()->fill_box_with_color(engine, local_to_world(bound), Utils::BRICKS_COLOR_FOR_TYPE[Utils::LEVEL_BRICKS_TYPE[game_info.get_difficulty()][game_info.get_level()]]);
          }
          else
          {
            // brick_ptr->add_brick(engine);
          }
        }
        else if (current_frame == 0)
        {
          position.y -= 2;
          position.x += 4 * direction;
        }
        else if (current_frame == 1)
        {
          Ray ray_up = Ray(local_to_world(Point2f(0.5, 0.5)), Vector2f(0, -1));
          Ray ray_dir = Ray(local_to_world(Point2f(0.5, 0.5)), Vector2f(direction, 0));
          Float hit_offset;
          EntityPtr hit_entity;
          if (/*brick_ptr && !brick_ptr->check_bricks()*/ brick_num >= 12)
          {
            brick_ptr = NULL;
            remove_skill(Utils::Lemming_Skills::BUILD);
            go_idle();
          }
          else if (engine.intersect_ray(ray_up, get_entity_id(),
                                        {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset, hit_entity))
          {
            if (hit_offset < diagonal.y * 1.1 / 4)
            {
              brick_ptr = NULL;
              remove_skill(Utils::Lemming_Skills::BUILD);
              restart_animation();
              go_idle();
            }
          }
          else if (engine.intersect_ray(ray_dir, get_entity_id(),
                                        {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset, hit_entity))
          {
            if (hit_offset < diagonal.y / 4)
            {
              brick_ptr = NULL;
              remove_skill(Utils::Lemming_Skills::BUILD);
              restart_animation();
              go_idle();
            }
          }
          // Los lemmings se pueden llegar a salir del mapa sin problemas
          // if (position.y < -10)
          // {
          //   brick_ptr = NULL;
          //   remove_skill(Utils::Lemming_Skills::BUILD);
          //   restart_animation();
          //   go_idle();
          // }
        }
      }

      std::string frame_path;

      if (state == Utils::Lemming_State::BUILDING)
        if (game_info.get_ia())
          frame_path = "assets/levvil/levvil_" + std::to_string(direction) + "_" + std::to_string(get_state()) + "_" + std::to_string(Utils::LEVEL_BRICKS_TYPE[game_info.get_difficulty()][game_info.get_level()]) + "_" + std::to_string(current_frame) + ".png";
        else
          frame_path = "assets/lemming/lemming_" + std::to_string(direction) + "_" + std::to_string(get_state()) + "_" + std::to_string(Utils::LEVEL_BRICKS_TYPE[game_info.get_difficulty()][game_info.get_level()]) + "_" + std::to_string(current_frame) + ".png";
      else if (game_info.get_ia())
        frame_path = "assets/levvil/levvil_" + std::to_string(direction) + "_" + std::to_string(get_state()) + "_" + std::to_string(current_frame) + ".png";
      else
        frame_path = "assets/lemming/lemming_" + std::to_string(direction) + "_" + std::to_string(get_state()) + "_" + std::to_string(current_frame) + ".png";

      Texture txt = engine.load_texture(frame_path.c_str());
      set_active_texture(txt);
    }
  }

  int get_direction() const { return direction; }

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

  std::chrono::time_point<std::chrono::steady_clock> get_last_falling() { return last_falling; }

  void update_state(Engine &engine) override
  {
    // If falling
    if (is_falling())
      last_falling = std::chrono::steady_clock::now();

    if (game_info.get_level_is_paused())
      return;

    Rigid_body::update_state(engine);

    // EXPLODING LOGIC
    if (update_explode_countdown(engine))
    {
      if (!(is_crashing()))
      { // Si no se está muriendo ya el Lemming de caida
        if (is_drowning() && !explosion_in_liquid)
        { // Posicionamos el Lemming explosivo donde se esta ahogando, una vez
          position.x += ((int)(current_frame / 4) * 5);
          position.y += 10;
          explosion_in_liquid = true;
        }
        add_skill_explode_all();
      }
    }
    if (is_digging())
    {
      if (current_frame == 4 || current_frame == 12)
      {
        if (!do_action_in_frame)
        {
          Bound2f box;
          box.pMin = local_to_world(Point2f(0.25, 0.65));
          box.pMax = box.pMin + Vector2f(18, 6);

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
          }
          if (!destroyed)
          {
            remove_skill(Utils::Lemming_Skills::DIG);
            on_ground = false;
          }
          do_action_in_frame = true;
          position.y += 2; // Desplazamos el Lemming hacia abajo
        }
      }
      else
        do_action_in_frame = false;
      return;
    }
  }

  void on_collision(Engine &, EntityPtr other) override
  {
    if (game_info.get_level_is_paused())
      return;
    Entity::on_collision(engine, other);
    if (other->get_entity_name() == "MAP" || other->get_entity_name() == "DIRECTIONAL WALL" || other->get_entity_name() == "METAL" || other->get_entity_name() == "BRICKS" || other->get_entity_name() == "Lemming")
    {
      if (is_walking())
      {
        if ((check_collision_left(other) && direction == -1) || (check_collision_right(other) && direction == 1))
        {
          if (other->get_entity_name() == "Lemming")
          {
            std::shared_ptr<Entity> lemming_ptr = std::dynamic_pointer_cast<Entity>(other);
            float distance = lemming_ptr->get_position2D().x - position.x;
            if ((direction == 1 && 12 > distance && distance > 8) || (direction == -1 && -12 < distance && distance < -8))
            {
              position.x -= 2 * direction;
              direction *= -1;
            }
          }
          else if (skills & Utils::CLIMB)
            go_climb();
          else // if (other->get_entity_name() != "BRICKS")
          {
            // Comprobamos si todos lo pixeles desde la nariz a los pies son opacos
            bool valid_pixel = false;
            Point2f collision_pixel;
            Bound2f collision_point = direction == -1 ? Bound2f(Point2f(0.4, 0.4), Point2f(0.45, 0.75)) : Bound2f(Point2f(0.55, 0.4), Point2f(0.6, 0.75));
            bool collides = Physics_engine::alpha_box_collision_if_all(
                *other, Entity::local_to_world(collision_point),
                Physics_engine::GET_FIRST, Physics_engine::GET_FIRST,
                valid_pixel, collision_pixel);

            //float distance_y = collision_pixel.y - (Entity::get_position2D().y + 30);

            // Si todos lo son colisiona y cambia de sentido
            if (collides)
            {

              // std::cout << "COLISIONA:  " << collision_pixel << " " << Entity::world_to_local(collision_pixel) << "  ; d = " << distance_y << "\n";
              position.x -= 3 * direction;
              direction *= -1;
            }
            else if (valid_pixel)
            {
              // std::cout << "NO COLISIONA:  d = " << distance_y << "\n";
            }
            else
            {
              // std::cout << "NO COLISIONA:  d = NULL \n";
            }
          }
        }
      }

      if ((is_falling() || is_floating()) && !(other->get_entity_name() == "Lemming"))
      {
        position.x = (static_cast<int>(position.x) / 2) * 2;
        std::cout << "position.x :"  << position.x << "\n";
        if (check_collision_down(other))
        {
          //std::cout << "COLLISION DOWN !\n";
          on_ground = true;
          if (distance_fall >= Utils::MAX_DISTANCE_FALL && !is_floating())
            go_crash();
          else
          {
            // Lanzamos un rayo hacia abajo con el fin de saber cuanto se a metido en el suelo
            //  Comprobamos que haya suelo
            Ray ray_down = Ray(local_to_world(Point2f(0.5, 0)), Vector2f(0, 1));
            Float hit_offset_down;
            EntityPtr hit_entity_down;
            engine.intersect_ray(ray_down, get_entity_id(),
                                 {"MAP", "METAL", "DIRECTIONAL WALL", "BRICKS"}, hit_offset_down, hit_entity_down);

            if (hit_offset_down < 34)
            { // El impacto con el suelo ocurre cuando el offset es menor a 34 que es lo que mide el Lemming
              // std::cout << "Offset down: " << hit_offset_down << std::endl;
              if (hit_offset_down >= 30)
              {
                if (current_frame == 2)
                {
                  position.y += hit_offset_down - 31; // El offset que deberían tener los Lemmmings es 32
                  if (hit_offset_down - 31 > 0)
                  {
                    position.y = (static_cast<int>(position.y) / 2) * 2 - (((float)position.y > (int)position.y) ? 1 : 0);
                  }
                  else
                  {
                    position.y = (static_cast<int>(position.y) / 2) * 2 + (((float)position.y > (int)position.y) ? 1 : 0);
                  }
                }
                else
                {
                  position.y += hit_offset_down - 30; // El offset que deberían tener los Lemmmings es 32
                  position.y = (static_cast<int>(position.y) / 2) * 2 + (((float)position.y > (int)position.y) ? 1 : 0);
                }
              }
              distance_fall = 0.0f;
              go_walk();
            }
          }
        }
      }
    }

    if (other->get_entity_name() == "GATE TRIGGER" && is_walking())
    {
      on_ground = true;
      go_escape();
    }

    if (other->get_entity_name() == "LIQUID TRIGGER" && !is_exploding()) // No puede ahogarse si explota
    {
      on_ground = true;
      go_drown();
    }

    if (other->get_entity_name() == "Fire")
    {
      on_ground = true;
      go_crash();
    }

    if (other->get_entity_name() == "Spinner" || other->get_entity_name() == "Flamethrower")
    {
      on_ground = true;
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "Chain")
    {
      other->get_entity_id();
      auto entities = engine.get_entities();
      std::shared_ptr<Chain> chain_ptr;
      for (auto &entity : entities)
      {
        if (other->get_entity_name() == entity->get_entity_name() && other->get_entity_id() == entity->get_entity_id())
        {
          chain_ptr = std::dynamic_pointer_cast<Chain>(entity);
          break;
        }
      }
      on_ground = true;
      if (chain_ptr && chain_ptr->get_is_playing())
        return;
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::CHAIN_SOUND), game_info.get_effects_volume());
      chain_ptr->trigger_event_animation();
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "Thumper")
    {
      other->get_entity_id();
      auto entities = engine.get_entities();
      std::shared_ptr<Thumper> ptr;
      for (auto &entity : entities)
      {
        if (other->get_entity_name() == entity->get_entity_name() && other->get_entity_id() == entity->get_entity_id())
        {
          ptr = std::dynamic_pointer_cast<Thumper>(entity);
          break;
        }
      }
      on_ground = true;
      if (ptr && ptr->get_is_playing())
        return;
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::TENTON_SOUND), game_info.get_effects_volume());
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::DIE_SOUND), game_info.get_effects_volume());
      ptr->trigger_event_animation();
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "Ball_zapper")
    {
      other->get_entity_id();
      auto entities = engine.get_entities();
      std::shared_ptr<Ball_zapper> ptr;
      for (auto &entity : entities)
      {
        if (other->get_entity_name() == entity->get_entity_name() && other->get_entity_id() == entity->get_entity_id())
        {
          ptr = std::dynamic_pointer_cast<Ball_zapper>(entity);
          break;
        }
      }
      on_ground = true;
      if (ptr && ptr->get_is_playing())
        return;
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::ELECTRIC_SOUND), game_info.get_effects_volume());
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::DIE_SOUND), game_info.get_effects_volume());
      ptr->trigger_event_animation();
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "TONS TRIGGER")
    {
      other->get_entity_id();
      auto entities = engine.get_entities();
      std::shared_ptr<Tons_trigger> ptr;
      for (auto &entity : entities)
      {
        if (other->get_entity_name() == entity->get_entity_name() && other->get_entity_id() == entity->get_entity_id())
        {
          ptr = std::dynamic_pointer_cast<Tons_trigger>(entity);
          break;
        }
      }
      on_ground = true;
      if (ptr && ptr->trap.get_is_playing())
        return;
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::TENTON_SOUND), game_info.get_effects_volume());
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::DIE_SOUND), game_info.get_effects_volume());
      ptr->trap.trigger_event_animation();
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "ROCK CRUSHER TRIGGER")
    {
      other->get_entity_id();
      auto entities = engine.get_entities();
      std::shared_ptr<Rock_crusher_trigger> ptr;
      for (auto &entity : entities)
      {
        if (other->get_entity_name() == entity->get_entity_name() && other->get_entity_id() == entity->get_entity_id())
        {
          ptr = std::dynamic_pointer_cast<Rock_crusher_trigger>(entity);
          break;
        }
      }
      on_ground = true;
      if (ptr && ptr->trap.get_is_playing())
        return;
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::THUD_SOUND), game_info.get_effects_volume());
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::DIE_SOUND), game_info.get_effects_volume());
      ptr->trap.trigger_event_animation();
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "BEAR TRAP TRIGGER")
    {
      other->get_entity_id();
      auto entities = engine.get_entities();
      std::shared_ptr<Bear_trap_trigger> ptr;
      for (auto &entity : entities)
      {
        if (other->get_entity_name() == entity->get_entity_name() && other->get_entity_id() == entity->get_entity_id())
        {
          ptr = std::dynamic_pointer_cast<Bear_trap_trigger>(entity);
          break;
        }
      }
      on_ground = true;
      if (ptr && ptr->trap.get_is_playing())
        return;
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::THUNK_SOUND), game_info.get_effects_volume());
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::DIE_SOUND), game_info.get_effects_volume());
      ptr->trap.trigger_event_animation();
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "ANTIMATTER BEAM TRIGGER")
    {
      other->get_entity_id();
      auto entities = engine.get_entities();
      std::shared_ptr<Antimatter_beam_trigger> ptr;
      for (auto &entity : entities)
      {
        if (other->get_entity_name() == entity->get_entity_name() && other->get_entity_id() == entity->get_entity_id())
        {
          ptr = std::dynamic_pointer_cast<Antimatter_beam_trigger>(entity);
          break;
        }
      }
      on_ground = true;
      if (ptr && ptr->trap.get_is_playing())
        return;
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::ELECTRIC_SOUND), game_info.get_effects_volume());
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::DIE_SOUND), game_info.get_effects_volume());
      ptr->trap.trigger_event_animation();
      destroy_lemming(engine);
    }

    if (other->get_entity_name() == "PIN TRIGGER")
    {
      other->get_entity_id();
      auto entities = engine.get_entities();
      std::shared_ptr<Pin_trigger> ptr;
      for (auto &entity : entities)
      {
        if (other->get_entity_name() == entity->get_entity_name() && other->get_entity_id() == entity->get_entity_id())
        {
          ptr = std::dynamic_pointer_cast<Pin_trigger>(entity);
          break;
        }
      }
      on_ground = true;
      if (ptr && ptr->trap.get_is_playing())
        return;
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::THUNK_SOUND), game_info.get_effects_volume());
      engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::SoundAssets::DIE_SOUND), game_info.get_effects_volume());
      ptr->trap.trigger_event_animation();
      destroy_lemming(engine);
    }
  }

  void post_physics(Engine &) override
  {
    if (game_info.get_level_is_paused())
      return;
    if (is_exploding())
      return;
    // Los lemmings se pueden salir del mapa sin problema
    // if (is_walking() && position.y < -8)
    // {
    //   position.y = -8;
    //   position.x -= 2 * direction;
    //   direction *= -1;
    // }
    if (is_falling() || is_floating())
    {
      distance_fall = distance_fall + (position.y - last_y);
      if (is_floating())
        if (current_frame == 10)
          current_frame = 4;
      if (position.y > 320.0f) // Si se salen fuera del mapa
      {
        // Obten el sonido de un Lemming gritando por su vida
        engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::DIE_SOUND), game_info.get_effects_volume());
        destroy_lemming(engine); // Destruye el lemming
        return;
      }
    }
    else
      distance_fall = 0.0f;

    if (skills & Utils::EXPLODE)
      go_explode();
    else if (skills & Utils::BLOCK)
    {
      go_block();
      change_collision_type(engine, Entity::Collision_type::STRUCTURE);
      disable_alpha_collision();
    }
    else if (skills & Utils::DIG)
      go_dig();
    else if (skills & Utils::BASH)
      go_bash();
    else if (skills & Utils::MINE)
      go_mine();
    else if (skills & Utils::BUILD)
      go_build();
    else if (is_falling() && distance_fall > Utils::MAX_DISTANCE_FALL / 4 && skills & Utils::FLOAT)
      go_float();
    if (!(is_floating() || is_falling() || is_climbing()))
    {
      if (!on_ground && !is_exploding())
      {
        go_fall();
      }
      else if (is_hovered)
      {
        game_info.sub_lemmings_hovered();
        is_hovered = false;
        if (game_info.get_lemmings_hovered() == 0)
          game_info.set_lemming_hovered_type("");
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
      int skill = Utils::HUD_TO_SKILL[game_info.get_option_selected()];
      if (skill != Utils::NO_SKILLS && game_info.get_action_possible() && !game_info.get_ia())
      {
        bool res = add_skill(Utils::HUD_TO_SKILL[game_info.get_option_selected()]);
        if (res)
        {
          // Realizamos el sonido de presion sobre el lemming
          engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::MOUSE_PRESS_SOUND), game_info.get_effects_volume());
          game_info.action_done();
          // std::cout << "HABILIDAD AÑADIDA" << std::endl;
        }
        else
        {
          // std::cout << "HABILIDAD NO AÑADIDA" << std::endl;
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
        if (!game_info.get_ia())
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
          game_info.set_lemming_hovered_type("");
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
        game_info.set_lemming_hovered_type("");
    }
    game_info.set_cursor_txt("assets/cursor.png", engine);
    game_info.set_is_cursor_hover(false);
    game_info.sub_n_lemmings_out();
    destroy();
    if (counter)
      counter->destroy();
  }

  void on_creation(Engine &engine) override
  {
    Rigid_body::on_creation(engine);
    // Change type after rigid body creation
    //  (sets by default it to STRUCTURE)
    change_collision_type(engine, Collision_type::CHARACTER);
  }
};
