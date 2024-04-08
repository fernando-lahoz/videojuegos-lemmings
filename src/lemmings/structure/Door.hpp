#pragma once

#include "lemmings/structure/Structure.hpp"
#include "lemmings/Lemming.hpp"
#include "lemmings/utils.hpp"

class Door : public Structure
{
private:
  float spawn_timer = 0.0f;
  int level, difficulty;
  Vector2f lemming_size;
  bool is_debug;
  bool change = false;

  //Esto es para que solo suene una vez tanto el sonido de apertura de puertas como el lets go
  bool play_open_sound = true;
  bool play_letsgo_sound = true;
  bool play_music = true;


public:
  Door(Point3f position, Engine &engine, int structure_type, float animation_duration, int level, Game_info &game_info, bool is_debug = false)
      : Structure(position, Vector2f(82, 50), engine, "assets/door/door", structure_type, 10, animation_duration, "Door", false, false, game_info, is_debug),
        level(level),
        difficulty(0),
        lemming_size(Vector2f(40, 40))
  {
  }

  Door(Point3f position, Engine &engine, int structure_type, float animation_duration, int level, Game_info &game_info, int difficulty, bool is_debug = false)
      : Structure(position, Vector2f(82, 50), engine, "assets/door/door", structure_type, 10, animation_duration, "Door", false, false, game_info, is_debug),
        level(level),
        difficulty(difficulty),
        lemming_size(Vector2f(40, 40))
  {
  }

  void pre_physics(Engine &engine) override
  {
    if (game_info.get_level_is_paused())
      return;
    Structure::update_animation(engine); // Actualiza la animación

    //Hacemos sonar una puerta que chirria
    if(play_open_sound){
        engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::DOOR_SOUND));
        play_open_sound = false;
    }

    if (!is_playing)
    { // Espera a que la animación termine para comenzar a invocar
      
      //Hacemos sonar el letsgo
      if(play_letsgo_sound)
      {
        engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::LETS_GO_SOUND));
        
        //FIXME: Necesito una función para saber cuando no esta sonando nigun sonido, aunque parece no ser necesaria
        //UPDATE: Usa esta: SoundMixer::is_playing_any_sound()
        //while(engine.get_sound_mixer().is_playing_music()); //Esperamos a que termine el let's go
        play_letsgo_sound = false;
      }
      else if (play_music && !engine.get_sound_mixer().is_playing_any_sound())
      {
        play_music = false;

        // Setup music
        auto& mixer = engine.get_sound_mixer();
        int difficulty = game_info.get_difficulty();
        int level = game_info.get_level();
        std::string music_file = [&]() {
          using namespace Utils;
          if (difficulty == DIFFICULTY_LEVEL::FUN && level == 22)
          {
              return MUSIC_DIRECTORY + SPECIAL_MUSIC[0];
          }
          else if (difficulty == DIFFICULTY_LEVEL::TRICKY && level == 14)
          {
              return MUSIC_DIRECTORY + SPECIAL_MUSIC[1];
          }
          else if (difficulty == DIFFICULTY_LEVEL::TAXING && level == 15)
          {
              return MUSIC_DIRECTORY + SPECIAL_MUSIC[2];
          }
          else if (difficulty == DIFFICULTY_LEVEL::MAYHEM && level == 22)
          {
              return MUSIC_DIRECTORY + SPECIAL_MUSIC[3];
          }
          else
          {
              return MUSIC_DIRECTORY + LEVEL_MUSIC[((30 * difficulty + level - 1) % 17)];
          }
        }();
        
        mixer.play_music(mixer.load_music(music_file), true /*play on loop*/);
      }

      spawn_timer += engine.get_delta_time() * game_info.get_game_speed();
      if (spawn_timer >= 0.1 + (game_info.get_spawn_velocity() / 50.0f) && game_info.get_spawned_lemmings() < Utils::LEVEL_N_LEMMINGS[difficulty][level] && !game_info.get_all_die())
      {
        // Lógica para invocar Lemmings
        spawn_timer = 0.0f;
        game_info.add_spawned_lemmings();
        game_info.add_n_lemmings_out();
        // Asume que hay una función para crear e inicializar un Lemming
        auto lemming = std::make_shared<Lemming>(calculate_spawn_position(lemming_size), lemming_size, engine, game_info);
        engine.get_game().create_entity(lemming);
        if (game_info.get_spawned_lemmings() == Utils::LEVEL_N_LEMMINGS[difficulty][level])
        {
          game_info.set_spawn_ended();
        }
      }
    }
  }

  Point3f calculate_spawn_position(Vector2f lemming_size) const
  {
    Point3f pos = get_position3D();
    // Calcula la posición central en el eje X de la estructura y ajusta en Y para que el Lemming aparezca encima
    float spawn_x = pos.x + (diagonal.x / 2) - (lemming_size.x / 2);
    float spawn_y = pos.y + (diagonal.y / 2) - (lemming_size.y / 2);
    return Point3f(int(spawn_x), int(spawn_y), game_info.get_spawned_lemmings());
  }
};
