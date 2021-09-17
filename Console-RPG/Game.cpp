// game.cpp

#include "Map.h"
#include "Player.h"
#include "Random.h"
#include "Game.h"
#include "Debug_Mode.h"


#include <cstdlib>
#include <ctime>
#include <iostream>



int main()
{
	srand(time(0));

	

	Map gameMap;

	Player mainPlayer;

	mainPlayer.createClass();

	// Begin adventure.
	bool done = false;

	Monster* monster[2] = { 0, 0 }; // null monster pointer;
	
	while (!done)
	{
		// eash loop cycle we output the player position and a selection menu.

		gameMap.printPlayerPos();

		int selection = 1;
		std::cout << "1) Move, 2) Rest, 3) View Stats, 4) Quit: ";
		std::cin >> selection;

		
		//Monster* monster[2] = {}; // null monster pointer;

		switch (selection)
		{
		case 1:
			// move the player
			gameMap.movePlayer();

			// check for a random encounter. this function returns a null pointer if no monsters are encounterd.
			//monster = gameMap.checkRandomEncounter(mainPlayer);
			gameMap.checkRandomEncounter(mainPlayer, monster);


			// DEBUG MSGS
			if (debugLog.enableDebugMessages && monster[0] != 0)
			{
				std::cout << std::endl;

				for (int i = 0; i < (sizeof(monster) / sizeof(monster[0])); i++)
				{
					std::cout << "monster[" << i << "] = " << monster[i] << std::endl;
				}

				std::cout << std::endl;
			}

			

			// the pointer to a monster returned from checkRandomEncounter was allocated with 'new', so we must delete it to avoid a memory leak.
			//delete[] monster;
			//monster[] = { 0, 0 };

			if (monster[0] != 0)
			{
				RandomEncounterBattle(monster, mainPlayer, done);


				for (int i = 0; i < (sizeof(monster) / sizeof(monster[0])); i++)
				{
					monster[i] = 0;
				}
			}
			

			break;

		case 2:
			// check for a random encounter. this function returns a null pointer if no monsters are encountered.
			if (Random(1, 4) != 1)
			{
				//monster = gameMap.checkRandomEncounter(mainPlayer);
				gameMap.checkRandomEncounter(mainPlayer, monster);


				// DEBUG MSGS
				if (debugLog.enableDebugMessages && monster[0] != 0)
				{
					std::cout << std::endl;

					for (int i = 0; i < (sizeof(monster) / sizeof(monster[0])); i++)
					{
						std::cout << "monster[" << i << "] = " << monster[i] << std::endl;
					}

					std::cout << std::endl;
				}


				if (monster[0] != 0)
				{
					RandomEncounterBattle(monster, mainPlayer, done);

					// the pointer to a monster returned from checkRandomEncounter was allocated with 'new', so we must delete it to avoid a memory leak.
					//delete[] monster;
					//monster[] = { 0, 0 };

					if (monster!= 0)
					{
						for (int i = 0; i < (sizeof(monster) / sizeof(monster[0])); i++)
						{
							monster[i] = 0;
						}
					}
					
				}
			}
			else
			{
				mainPlayer.rest();

			}



			break;

		case 3:
			mainPlayer.viewStates();
			break;
			
		case 4:
			done = true;
			break;

		} // end switch statement


	} // end while sattement
} // end main function

void RandomEncounterBattle(Monster* monster[], Player& mainPlayer, bool& done)
{
	// 'monster' not null, run combat simulation.
	//if (monster != 0)
	if (monster != 0)
	{
		// loop until a 'break' statement

		bool areThereTwoMonsters = ((monster[1] != 0) ? true : false);

		if(monster[0]->getName() == "Baby Dragon")
		{
			if(mainPlayer.getLevel() <= 12)
			{
				monster = nullptr;
				return;
			}
			
			areThereTwoMonsters = false;
		}
		else if(monster[0]->getName() == "Green Dragon")
		{
			if (mainPlayer.getLevel() <= 18)
			{
				monster = nullptr;
				return;
			}
			
			areThereTwoMonsters = false;
		}
		else if(monster[0]->getName() == "Golden Dragon")
		{
			if (mainPlayer.getLevel() <= 25)
			{
				monster = nullptr;
				return;
			}
			
			areThereTwoMonsters = false;
		}
		
		// Debug msg
		if (debugLog.enableDebugMessages)
		{
			std::cout.setf(std::cout.boolalpha); // allows me to display true and false instead of 1 or 0

			std::cout << "Debug MSG" << std::endl;
			std::cout << "areThereTwoMonsters: " << areThereTwoMonsters << std::endl;
			std::cout << "Players level: " << mainPlayer.getLevel() << std::endl;
			std::cout << std::endl;
		}
		

		while (true)
		{


			// display hit points.
			mainPlayer.displayHitPoints();

			// display magic points if (cleric or wizard)
			if (mainPlayer.getClass() == "Wizard" || mainPlayer.getClass() == "Cleric")
				mainPlayer.displayMagicPoints();

			std::cout << std::endl;
			

			if (!monster[0]->isDead())
			{
				monster[0]->displayHitPoints();
			}
			else
			{
				// debug msg
				if (debugLog.enableDebugMessages)
				{
					std::cout.setf(std::cout.boolalpha);

					std::cout << "debug msg" << std::endl;
					std::cout << "monster 0: " << monster[0] << std::endl;
					std::cout << "monster 0 isDead? " << monster[0]->isDead() << std::endl;
				}
			}

			if (areThereTwoMonsters)
			{
				if (!monster[1]->isDead())
				{
					monster[1]->displayHitPoints();
				}
				
			}
			

			std::cout << std::endl;

			// Player's turn to attack first.

			//bool runAway = mainPlayer.attack(*monster);
			
			bool runAway = mainPlayer.attack(monster);

			if (runAway)
			{
				break;
			}

			if ((monster[1] == 0) && (monster[0]->isDead()))
			{
				mainPlayer.victory(monster[0]->getXPReward(), monster[0]->getGoldReward());
				mainPlayer.levelUp();

				break;
			}
			else
			{
				if (monster[0]->isDead() && monster[1] != 0 && !monster[1]->isDead())
				{
					/*mainPlayer.victory(monster[0]->getXPReward(), monster[0]->getGoldReward());
					mainPlayer.levelUp();*/

					//runAway = mainPlayer.attack(monster);



					continue;
				}
				else if (monster[0]->isDead() && monster[0]->isDead())
				{
					mainPlayer.victory(monster[0]->getXPReward(), monster[0]->getGoldReward());
					mainPlayer.victory(monster[1]->getXPReward(), monster[1]->getGoldReward());
					
					mainPlayer.levelUp();

					break;
				}
			}
			

			if (!monster[0]->isDead() )//&& monster[1] == 0)
			{
				monster[0]->attack(mainPlayer, 0);
			}
			else if (monster[0]->isDead() && !monster[1] != 0)
			{
				monster[1]->attack(mainPlayer, 1);
			}


			if (mainPlayer.isDead())
			{
				mainPlayer.gameover();
				done = true;
				break;
			}

		}


	}
}


//void RandomEncounterBattle(Monster* monster[], Player& mainPlayer, bool& done)
//{
//	bool monsterTwoIsTrue = false;
//
//	if (monster[1] != 0)
//	{
//		monsterTwoIsTrue = true;
//	}
//
//	// 'monster' not null, run combat simulation.
//	//if (monster != 0)
//	if (monster[0] != 0 || monster[1] != 0)
//	{
//		// loop until a 'break' statement
//
//		
//
//
//		while (true)
//		{
//			// display hitpoints.
//			mainPlayer.displayHitPoints();
//			monster[0]->displayHitPoints();
//
//			if (monsterTwoIsTrue)
//			{
//				monster[1]->displayHitPoints();
//			}
//			
//			std::cout << std::endl;
//
//			// Player's turn to attack first.
//
//
//			bool runAway = mainPlayer.attack(*monster);
//
//			if (runAway)
//			{
//				break;
//			}
//
//			if (monster[0]->isDead())
//			{
//				mainPlayer.victory(monster->getXPReward(), monster[0]->getGoldReward());
//				mainPlayer.levelUp();
//
//				if (!monsterTwoIsTrue)
//				{
//					break; // no monster 2 or its dead
//				}
//				
//			}
//
//			if (monsterTwoIsTrue)
//			{
//				if (monster[1]->isDead())
//				{
//					mainPlayer.victory(monster[1]->getXPReward(), monster[1]->getGoldReward());
//					mainPlayer.levelUp();
//
//					monsterTwoIsTrue = false;
//
//					if (monster[0]->isDead())
//					{
//						break; // monster 1 is dead
//					}
//				}
//			}
//
//			
//			if (!monster[0]->isDead())
//			{
//				monster[0]->attack(mainPlayer);
//			}
//			
//			if (monsterTwoIsTrue)
//			{
//				if (!monster[1]->isDead())
//				{
//					monster[1]->attack(mainPlayer);
//				}
//			}
//
//			if (mainPlayer.isDead())
//			{
//				mainPlayer.gameover();
//				done = true;
//				break;
//			}
//
//		}
//
//
//	}
//}
