#ifndef LEMMINGS_KEYBOARD
#define LEMMINGS_KEYBOARD

#pragma once

#include <memory>

#include "engine/engine.hpp"
#include "engine/IO.hpp"
#include "lemmings/Game_info.hpp"
#include "lemmings/memory/keyBindings.hpp"

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
		for (int i = 0; i < NUM_CHECKABLE_KEYS; i++)
			available[i] = true;
	}

	void set_key_bindings()
	{
		EngineIO::InputEvent aux[18];
		KeyBindings().readKeyBindingsFile(aux);
		for (int i = 0; i < NUM_ACTIONS; i++)
			actionKey[i] = aux[i];
	}

	void manage_key_down(Engine &engine, EngineIO::InputEvent event)
	{
		// En el caso de que estemos en el menú, el botón de escape cierra el juego.
		if (game_info.get_actual_state() == Utils::STATE::MENU && !game_info.get_is_pop_exit_active())
		{
			if (event == EngineIO::InputEvent::ESC)
			{
				std::cout << "Se ha pulsado ESC \n"
									<< std::endl;
				// engine.quit();
			}
			else
			{
				if (game_info.get_is_button_conf())
				{																																			// Si hay un boton de configuración seleccionado
					game_info.set_conf_buttons(event, game_info.get_last_button() - 9); // Guardamos la tecla pulsada
				}
				return;
			}
		}

		if (game_info.get_actual_state() == Utils::STATE::GAME)
		{
			if (event == EngineIO::InputEvent::ESC)
			{
				std::cout << "Se ha pulsado ESC en GAME\n"
									<< std::endl;
				if (!game_info.get_is_pop_exit_active()){
					game_info.set_pop_exit();
				}
				else{
					game_info.set_delete_exit();
				}
				// engine.quit();
			}
		}
		if (game_info.get_ia()){
			return;
		}
		// En el caso de que estemos en el juego, primero se comprueba el botón que se ha pulsado.
		// Si es un botón de habilidad, se selecciona la habilidad correspondiente.
		for (int i = ABILITY_1; i < NUM_CHECKABLE_KEYS; i++)
		{
			if (event == actionKey[i] && available[i])
			{
				game_info.set_option_selected(i + 1);
				available[i] = false;
				Sound sound;
				switch (i)
				{
				case 1:
					sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND1);
					break;
				case 2:
					sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND2);
					break;
				case 3:
					sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND3);
					break;
				case 4:
					sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND4);
					break;
				case 5:
					sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND5);
					break;
				case 6:
					sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND6);
					break;
				case 7:
					sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND7);
					break;
				case 8:
					sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND8);
					break;
				default:
					sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND);
					break;
				}
				engine.get_sound_mixer().play_sound(sound, game_info.get_effects_volume());
			}
		}

		// Si es un botón de desplazamiento entre habilidades, se cambia la habilidad.
		if (event == actionKey[ABILITY_UP])
		{
			int new_option = (game_info.get_option_selected() - 1) % 8 + 2;
			game_info.set_option_selected(new_option);
			Sound sound;
			switch (new_option - 1)
			{
			case 1:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND1);
				break;
			case 2:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND2);
				break;
			case 3:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND3);
				break;
			case 4:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND4);
				break;
			case 5:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND5);
				break;
			case 6:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND6);
				break;
			case 7:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND7);
				break;
			case 8:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND8);
				break;
			default:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND);
				break;
			}
			engine.get_sound_mixer().play_sound(sound, game_info.get_effects_volume());
		}
		if (event == actionKey[ABILITY_DOWN])
		{
			int new_option = game_info.get_option_selected() - 3;
			new_option = new_option < 0 ? new_option + 10 : new_option + 2;
			game_info.set_option_selected(new_option);
			Sound sound;
			switch (new_option - 1)
			{
			case 1:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND1);
				break;
			case 2:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND2);
				break;
			case 3:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND3);
				break;
			case 4:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND4);
				break;
			case 5:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND5);
				break;
			case 6:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND6);
				break;
			case 7:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND7);
				break;
			case 8:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND8);
				break;
			default:
				sound = game_info.get_sound_asset(Game_info::CHANGE_OP_SOUND);
				break;
			}
			engine.get_sound_mixer().play_sound(sound, game_info.get_effects_volume());
		}

		// Si es el botón de destrucción total, se espera a que se mantenga el botón pulsado
		// durante más o menos un segundo para que se active.
		if (event == actionKey[EXPLODE_ALL])
		{
			killAllCounter++;
			if (killAllCounter == 16)
			{
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
							// Miramos si algun lemming fue marcado para morir y con eso vemos si estan todos condenados
							isEveryOneDoomed &= lemming_ptr->get_dead_marked();
							lemming_ptr->set_dead_marked(true);
						}
					}
				}

				// Si aun no estaban condenados
				if (!isEveryOneDoomed)
				{
					// Hacemos que recen por su vida
					engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::OH_NO_SOUND), game_info.get_effects_volume());
				}

				if (j == 0)
					game_info.set_level_ended();
			}
		}

		// Si es un botón de velocidad de juego o de aparición, se cambia el valor asociado.
		if (event == actionKey[SPEED_UP])
		{
			game_info.add_game_speed();
			engine.set_delta_time_factor(game_info.get_game_speed());
		}
		if (event == actionKey[SPEED_DOWN])
		{
			game_info.sub_game_speed();
			engine.set_delta_time_factor(game_info.get_game_speed());
		}
		if (event == actionKey[SPAWN_UP])
			game_info.add_spawn_velocity();
		if (event == actionKey[SPAWN_DOWN])
			game_info.sub_spawn_velocity();

		// Si es el botón de pausa, se pausa o reanuda el juego.
		if (event == actionKey[PAUSE] && available[0] && !game_info.get_is_pop_exit_active())
		{
			available[PAUSE] = false;
			game_info.set_level_is_paused(!game_info.get_level_is_paused());
			engine.set_is_game_paused(game_info.get_level_is_paused());
		}
	}

	void manage_key_up([[maybe_unused]] Engine &engine, EngineIO::InputEvent event)
	{
		// Gestiona que se puedan volver a pulsar los botones de habilidades.
		if (!game_info.get_ia() && !game_info.get_is_pop_exit_active())
		{
			for (int i = 0; i < NUM_CHECKABLE_KEYS; i++)
				if (event == actionKey[i])
					available[i] = true;
			// Reinicia el contador de tiempo para la destrucción total, si es que se
			// suelta el botón previo a su activación.
			if (event == actionKey[EXPLODE_ALL])
				killAllCounter = 0;
		}
	}
};

#endif // LEMMINGS_KEYBOARD