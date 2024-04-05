#ifndef KEYBOARD
#define KEYBOARD

#pragma once

#include <memory>

#include "engine/engine.hpp"
#include "engine/IO.hpp"
#include "lemmings/Game_info.hpp"

#define NUM_ACTIONS 16
#define NUM_CHECKABLE_KEYS 9

class Keyboard_manager
{
private:
	EngineIO::InputEvent actionKey[NUM_ACTIONS];
	bool available[NUM_CHECKABLE_KEYS];
	Game_info &game_info;
	char killAllCounter = 0;

	enum KeyCode
	{
		PAUSE = 0,
		ABILITY_1 = 1,
		ABILITY_2 = 2,
		ABILITY_3 = 3,
		ABILITY_4 = 4,
		ABILITY_5 = 5,
		ABILITY_6 = 6,
		ABILITY_7 = 7,
		ABILITY_8 = 8,
		EXPLODE_ALL = 9,
		ABILITY_UP = 10,
		ABILITY_DOWN = 11,
		SPEED_UP = 12,
		SPEED_DOWN = 13,
		SPAWN_UP = 14,
		SPAWN_DOWN = 15
	};

public:
	Keyboard_manager(Game_info &_game_info)
		: game_info(_game_info)
	{
		// PROVISIONAL: con el sistema de persistencia, se guardarán ahí los controles.
		actionKey[0] = EngineIO::InputEvent::ENTER;			// Pausa
		actionKey[1] = EngineIO::charToInputEvent('1');	// Habilidades
		actionKey[2] = EngineIO::charToInputEvent('2');
		actionKey[3] = EngineIO::charToInputEvent('3');
		actionKey[4] = EngineIO::charToInputEvent('4');
		actionKey[5] = EngineIO::charToInputEvent('5');
		actionKey[6] = EngineIO::charToInputEvent('6');
		actionKey[7] = EngineIO::charToInputEvent('7');
		actionKey[8] = EngineIO::charToInputEvent('8');
		actionKey[9] = EngineIO::charToInputEvent('9');
		actionKey[10] = EngineIO::InputEvent::UP;				// Desplazar entre habilidades
		actionKey[11] = EngineIO::InputEvent::DOWN;
		actionKey[12] = EngineIO::charToInputEvent('Q');// Velocidad de juego
		actionKey[13] = EngineIO::charToInputEvent('A');
		actionKey[14] = EngineIO::charToInputEvent('W');// Velocidad de aparición
		actionKey[15] = EngineIO::charToInputEvent('S');
		for (int i = 0; i < NUM_CHECKABLE_KEYS; i++) available[i] = true;
	}

	void manage_key_down(Engine &engine, EngineIO::InputEvent event)
	{

		// En el caso de que estemos en el menú, el botón de escape cierra el juego.
		if (game_info.get_actual_state() == Utils::STATE::MENU)
		{
			if (event == EngineIO::InputEvent::ESC) engine.quit();
			else return;
		}

		// En el caso de que estemos en el juego, primero se comprueba el botón que se ha pulsado.
		// Si es un botón de habilidad, se selecciona la habilidad correspondiente.
		for (int i = ABILITY_1; i < NUM_CHECKABLE_KEYS; i++)
		{
			if (event == actionKey[i] && available[i])
			{
				game_info.set_option_selected(i+1);
				available[i] = false;
				engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND));
			}
		}

		// Si es un botón de desplazamiento entre habilidades, se cambia la habilidad.
		if (event == actionKey[ABILITY_UP])
		{
			int new_option = (game_info.get_option_selected() - 1) % 8 + 2;
			game_info.set_option_selected(new_option);
			engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND));
		}
		if (event == actionKey[ABILITY_DOWN])
		{
			int new_option = game_info.get_option_selected() - 3;
			new_option = new_option < 0 ? new_option + 10 : new_option + 2;
			game_info.set_option_selected(new_option);
			engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND));
		}

		// Si es el botón de destrucción total, se espera a que se mantenga el botón pulsado
		// durante más o menos un segundo para que se active.
		if (event == actionKey[EXPLODE_ALL]) {
			killAllCounter++;
			if (killAllCounter == 16) {
        game_info.set_spawn_ended();
        game_info.set_all_die(true);
        auto &entities = engine.get_entities();
        int j = 0;
        bool isEveryOneDoomed = true;

        for (std::size_t i = 0; i < entities.size(); i++)
        {
          if (entities[i]->get_entity_name() == "Lemming")
          {
            j++;
            std::shared_ptr<Lemming> lemming_ptr = std::dynamic_pointer_cast<Lemming>(entities[i]);
            if (lemming_ptr)
            {
              //Miramos si algun lemming fue marcado para morir y con eso vemos si estan todos condenados
              isEveryOneDoomed &= lemming_ptr->get_dead_marked();
              lemming_ptr->set_dead_marked(true);
            }
          }
        }

        //Si aun no estaban condenados
        if(!isEveryOneDoomed)
        {
          //Hacemos que recen por su vida
          engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::OH_NO_SOUND));
        }

        if (j == 0)
          game_info.set_level_ended();
			}
		}

		// Si es un botón de velocidad de juego o de aparición, se cambia el valor asociado.
    if (event == actionKey[SPEED_UP]) game_info.add_game_speed();
    if (event == actionKey[SPEED_DOWN]) game_info.sub_game_speed();
    if (event == actionKey[SPAWN_UP]) game_info.add_spawn_velocity();
    if (event == actionKey[SPAWN_DOWN]) game_info.sub_spawn_velocity();

		// Si es el botón de pausa, se pausa o reanuda el juego.
    if (event == actionKey[PAUSE] && available[0])
    {
      available[PAUSE] = false;
      game_info.set_level_is_paused(!game_info.get_level_is_paused());
    }
	}

  void manage_key_up([[maybe_unused]]Engine &engine, EngineIO::InputEvent event)
  {
		// Gestiona que se puedan volver a pulsar los botones de habilidades.
    for (int i = 0; i < NUM_CHECKABLE_KEYS; i++)
        if (event == actionKey[i])
            available[i] = true;
		// Reinicia el contador de tiempo para la destrucción total, si es que se
		// suelta el botón previo a su activación.
		if (event == actionKey[EXPLODE_ALL]) killAllCounter = 0;
  }
};

#endif // KEYBOARD