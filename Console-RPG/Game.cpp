// game.cpp

#include "Map.h"
#include "Player.h"
#include "Random.h"
#include "Game.h"
#include "Debug_Mode.h"
#include <iostream>
#include <random>

int main()
{
	// should update this someday to a more standard way of seeding the random number generator.
	///srand(time(nullptr));
	//std::random_device rd; // moved to random.cpp/.h
	//std::mt19937 rng(rd()); // Initialize random number generator with a random seed.
	
	map game_map;

	player main_player;

	std::cout << "Welcome to the Console RPG!\n\n";

	main_player.create_class();

	// Begin adventure.
	bool done = false;

	Monster* monster[2] = { nullptr, nullptr }; // null monster pointer;
	
	while (!done)
	{
		// each loop cycle we output the player position and a selection menu.

		game_map.print_player_pos();

		int selection = 1;
		std::cout << "1) Move, 2) Rest, 3) View Stats, 4) Quit: ";
		std::cin >> selection;

		
		//Monster* monster[2] = {}; // null monster pointer;
		
		switch (selection)
		{
		case 1:
			// move the player
			game_map.move_player();

			// check for a random encounter. this function returns a null pointer if no monsters are encountered.
			//monster = gameMap.checkRandomEncounter(mainPlayer);
			game_map.check_random_encounter(main_player, monster);


			/// DEBUG MSGS
			if (debug_log.enable_debug_messages && monster[0] != nullptr)
			{
				std::cout << '\n';

				//for (int i = 0; i < (sizeof(monster) / sizeof(monster[0])); i++)
				for (size_t i = 0; i < std::size(monster); i++)
				{
					std::cout << "monster[" << i << "] = " << monster[i] << '\n';
				}

				std::cout << '\n';
			}

			

			// the pointer to a monster returned from checkRandomEncounter was allocated with 'new', so we must delete it to avoid a memory leak.
			//delete[] monster;
			//monster[] = { 0, 0 };

			if (*monster != nullptr)
			{
				if (monster[0] != nullptr)
				{
					random_encounter_battle(monster, main_player, done);


					//for (int i = 0; i < (sizeof(monster) / sizeof(monster[0])); i++)
					for (auto& i : monster)
					{
						delete i;
						i = nullptr;
					}
				}
			}

			break;

		case 2:
			// check for a random encounter. this function returns a null pointer if no monsters are encountered.
			if (random(1, 4) > 2)
			{
				//monster = gameMap.checkRandomEncounter(mainPlayer);
				game_map.check_random_encounter(main_player, monster);


				/// DEBUG MSGS
				if (debug_log.enable_debug_messages && monster[0] != nullptr)
				{
					std::cout << '\n';

					//for (int i = 0; i < (sizeof(monster) / sizeof(monster[0])); i++)
					for (size_t i = 0; i < std::size(monster); i++)
					{
						std::cout << "monster[" << i << "] = " << monster[i] << '\n';
					}

					std::cout << '\n';
				}


				if (monster[0] != nullptr)
				{
					std::cout << "You were ambushed by a " << monster[0]->get_name();
					
					if (monster[1] != nullptr)
					{
						std::cout << " and a " << monster[1]->get_name();
					}
					
					std::cout << "!\n\n";
					
					random_encounter_battle(monster, main_player, done);

					// the pointer to a monster returned from checkRandomEncounter was allocated with 'new', so we must delete it to avoid a memory leak.
					//delete[] monster;
					//monster[] = { 0, 0 };

					if (*monster != nullptr)
					{
						//for (int i = 0; i < (sizeof(monster) / sizeof(monster[0])); i++)
						for (auto& i : monster)
						{
							i = nullptr;
						}
					}
					
				}
				else
				{
					std::cout << "\nYou find yourself unable to rest, perhaps next time.\n";
				}
			}
			else
			{
				std::cout << "\nYou rest peacefully.\n";
				main_player.rest();
			}



			break;

		case 3:
			main_player.view_states();
			break;
			
		case 4:
		default:
			done = true;
			break;

		} // end switch statement


	} // end while statement
} // end the main function

void random_encounter_battle(Monster* monster[], player& main_player, bool& done)
{
	if (debug_log.enable_debug_messages)
	{
		std::cout << "Test: monsters[0] = " << (monster[0] != nullptr ? monster[0]->get_name() : "Monster[0] = nullptr") << '\n';
		std::cout << "Test: monsters[1] = " << (monster[1] != nullptr ? monster[1]->get_name() : "monster[1] = nullptr") << '\n';
	}
	
	// 'monster' not null, run combat simulation.
	//if (monster != 0)
	if (monster != nullptr)
	{
		// loop until a 'break' statement

		// monster[0]
		if(monster[0]->get_name() == "Baby Dragon" || monster[0]->get_name() == "Green Dragon" || monster[0]->get_name() == "Gold Dragon")
		{
			if (main_player.get_level() <= monster[0]->get_min_player_level())
			{
				monster = nullptr;
				return;
			}
		}

		// monster[1]
		if (monster[1] != nullptr)
		{
			if(monster[1]->get_name() == "Baby Dragon" || monster[1]->get_name() == "Green Dragon" || monster[1]->get_name() == "Gold Dragon")
			{
				// 6
				if(main_player.get_level() <= monster[1]->get_min_player_level())
				{
					monster = nullptr;
					return;
				}
			}
		}

		const bool are_there_two_monsters = (monster[0] != nullptr) && (monster[1] != nullptr);
		
		// Debug msg
		if (debug_log.enable_debug_messages)
		{
			///std::cout.setf(std::cout.boolalpha); // allows me to display true and false instead of 1 or 0
			std::cout.setf(std::ostream::boolalpha); // allows me to display true and false instead of 1 or 0

			std::cout << "Debug MSG" << '\n';
			std::cout << "areThereTwoMonsters: " << are_there_two_monsters << '\n';
			std::cout << "Players level: " << main_player.get_level() << '\n';
			std::cout << '\n';
		}
		

		// game loop
		while (true)
		{
			// Display hit points.
			main_player.display_hit_points();

			// display magic points if (cleric or wizard)
			if (main_player.get_class() == "Wizard" || main_player.get_class() == "Cleric")
				main_player.display_magic_points();

			std::cout << '\n';
			

			if (!monster[0]->is_dead())
			{
				monster[0]->display_hit_points();
			}
			else
			{
				// debug msg
				if (debug_log.enable_debug_messages)
				{
					std::cout.setf(std::ostream::boolalpha);

					std::cout << "debug msg" << "\n";
					std::cout << "monster 0: " << monster[0] << "\n";
					std::cout << "monster 0 isDead? " << monster[0]->is_dead() << "\n";
				}
			}

			if (are_there_two_monsters)
			{
				if (!monster[1]->is_dead())
				{
					monster[1]->display_hit_points();
				}
				else
				{
					//std::cout << "Testing Message - monster[1] is dead." << '\n';
					
				}
				
			}
			

			std::cout << '\n';

			// Player's turn to attack first.
			
			const bool run_away = main_player.attack(monster);

			if (run_away)
			{
				break;
			}

			if (monster[1] == nullptr && monster[0]->is_dead())
			{
				if (monster[0]->get_name() == "Gold Dragon") 
				{
					std::cout << "You have defeated a Gold Dragon!" << '\n';
					std::cout << "What a victorious feat!\n\n";
				}
				else
				{
					std::cout << "You have defeated a " << monster[0]->get_name() << "\n\n";
				}
				
				
				main_player.victory(monster[0]->get_xp_reward(), monster[0]->get_gold_reward());
				main_player.level_up();

				break;
			}
			else
			{
				if (monster[0]->is_dead() && monster[1]->is_dead())
				{
					if (monster[0]->get_name() == "Gold Dragon")
					{
						std::cout << "You have defeated the Gold Dragon!" << '\n';
						std::cout << "You are victorious!" << '\n';
					}
					else
					{
						std::cout << "You have defeated a " << monster[0]->get_name() << '\n';
					}
					
					if (monster[1]->get_name() == "Gold Dragon")
					{
						std::cout << "You have defeated the Gold Dragon!" << '\n';
						std::cout << "You are victorious!" << '\n';
					}
					else
					{
						std::cout << "You have defeated a " << monster[1]->get_name() << '\n';
					}
					
					main_player.victory(monster[0]->get_xp_reward(), monster[0]->get_gold_reward());
					main_player.victory(monster[1]->get_xp_reward(), monster[1]->get_gold_reward());
					
					main_player.level_up();

					break;
				}
			}
			

			if (!monster[0]->is_dead() )//&& monster[1] == 0)
			{
				monster[0]->attack(main_player);
			}
			else if (monster[0]->is_dead() && monster[1] != nullptr)
			{
				monster[1]->attack(main_player);
			}


			if (main_player.is_dead())
			{
				player::gameOver();
				done = true;
				break;
			}

		}


	}
}



