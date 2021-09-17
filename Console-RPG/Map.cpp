#include "Map.h"
#include "Random.h"
#include "Store.h"

#include <iostream>



Map::Map()
{
	// player starts at origin (0, 0)
	mPlayerXPos = 0;
	mPlayerYPos = 0;
}


int Map::getPlayerXPos()
{
	return mPlayerXPos;
}

int Map::getPlayerYPos()
{
	return mPlayerYPos;
}

void Map::movePlayer()
{
	int selection = 1;
	std::cout << "1) North, 2) East, 3) South, 4) West: ";
	std::cin >> selection;

	// update coordinates based on selection.
	switch (selection)
	{
	case 1: // north
		mPlayerYPos++;
		break;
	case 2: // East
		mPlayerXPos++;
		break;
	case 3: // south
		mPlayerYPos--;
		break;
	default: // west
		mPlayerXPos--;
		break;
	}

	std::cout << std::endl;

}

void Map::checkRandomEncounter(Player& player, Monster* monster[]) // this code could easily be refactored to use a switch statement and only type out the msg's once for all statments.
{
	monster[0] = 0; // null monster 1 pointer
	monster[1] = 0; // null monster 2 pointer

	if (getPlayerXPos() == 0 && getPlayerYPos() == 4)
	{
		Store store;
		store.enter(player);

		//return monster;

		return;
	}

	CheckForMonster(monster, 0);

	if (monster[0] != 0 && player.getLevel() >= 6)
	{
		CheckForMonster(monster, 1);
	}


	//return monster;
}

void Map::CheckForMonster(Monster* monster[], int monsterNumber)
{
	int roll = Random(0, 23);


	//monster = 0; // null monsters pointer


	//int monsterCounter = 0;

	if (roll <= 5)
	{
		// no encounter, return a null pointer.
		//monster[0] = 0; // null monster 1 pointer
		//monster[1] = 0; // null monster 2 pointer

		//return 0;
	}
	else if (roll >= 6 && roll <= 10)
	{
		monster[monsterNumber] = new Monster("Orc", 10, 8, 200, 50, 1, "Short Sword", 2, 7);

		std::cout << "You encountered an Orc!" << std::endl;
		std::cout << "Prepare for battle!" << std::endl;
		std::cout << std::endl;
	}
	else if (roll >= 11 && roll <= 15)
	{
		monster[monsterNumber] = new Monster("Goblin", 6, 6, 100, 75, 0, "Dagger", 1, 5);

		std::cout << "You encountered a Goblin!" << std::endl;
		std::cout << "Prepare for battle!" << std::endl;
		std::cout << std::endl;
	}
	else if (roll >= 16 && roll <= 19)
	{
		monster[monsterNumber] = new Monster("Ogre", 20, 12, 500, 150, 2, "Club", 3, 8);

		std::cout << "You encountered an Ogre!" << std::endl;
		std::cout << "Prepare for battle!" << std::endl;
		std::cout << std::endl;
	}
	else if (roll == 20)
	{
		monster[monsterNumber] = new Monster("Orc Lord", 25, 15, 2000, 500, 5, "Two Handed Sword", 5, 20);

		std::cout << "You encounted an Orc Lord!!!" << std::endl;
		std::cout << "Prepare for battle!" << std::endl;
		std::cout << std::endl;
	}
	else if (roll == 21)
	{
		monster[monsterNumber] = new Monster("Baby Dragon", 75, 35, 4000, 1500, 10, "Tail Swipe", 30, 75);

		std::cout << "You encounted an Baby Dragon!!!" << std::endl;
		std::cout << "Prepare for battle!" << std::endl;
		std::cout << std::endl;
	}
	else if (roll == 22)
	{
		monster[monsterNumber] = new Monster("Green Dragon", 175, 35, 6000, 4000, 15, "Corrosive Breath", 50, 100);

		std::cout << "You encounted an Green Dragon!!!" << std::endl;
		std::cout << "Prepare for battle!" << std::endl;
		std::cout << std::endl;
	}
	else if (roll == 23)
	{
		monster[monsterNumber] = new Monster("Gold Dragon", 250, 55, 10000, 10000, 20, "Molten Lava Breath", 40, 125);

		std::cout << "You encounted an Golden Dragon!!!" << std::endl;
		std::cout << "Prepare for battle!" << std::endl;
		std::cout << std::endl;
	}
	
	
}


//Monster* Map::checkRandomEncounter(Player& player) // this code could easily be refactored to use a switch statement and only type out the msg's once for all statments.
//{
//	if (getPlayerXPos() == 0 && getPlayerYPos() == 4)
//	{
//		Store store;
//		store.enter(player);
//
//		Monster* monster = 0;
//
//		return monster;
//
//	}
//
//	int roll = Random(0, 20);
//
//	Monster* monster = 0; // null monster pointer
//	monster = 0; // null monsters pointer
//
//
//	int monsterCounter = 0;
//
//	if (roll <= 5)
//	{
//		// no encounter, return a null pointer.
//		monster = 0;
//
//		//return 0;
//	}
//	else if (roll >= 6 && roll <= 10)
//	{
//		monster = new Monster("Orc", 10, 8, 200, 50, 1, "Short Sword", 2, 7);
//
//		std::cout << "You encountered an Orc!" << std::endl;
//		std::cout << "Prepare for battle!" << std::endl;
//		std::cout << std::endl;
//	}
//	else if (roll >= 11 && roll <= 15)
//	{
//		monster = new Monster("Goblin", 6, 6, 100, 75, 0, "Dagger", 1, 5);
//
//		std::cout << "You encountered a Goblin!" << std::endl;
//		std::cout << "Prepare for battle!" << std::endl;
//		std::cout << std::endl;
//	}
//	else if (roll >= 16 && roll <= 19)
//	{
//		monster = new Monster("Ogre", 20, 12, 500, 150, 2, "Club", 3, 8);
//
//		std::cout << "You encountered an Ogre!" << std::endl;
//		std::cout << "Prepare for battle!" << std::endl;
//		std::cout << std::endl;
//	}
//	else if (roll == 20)
//	{
//		monster = new Monster("Orc Lord", 25, 15, 2000, 500, 5, "Two Handed Sword", 5, 20);
//
//		std::cout << "You encounted an Orc Lord!!!" << std::endl;
//		std::cout << "Prepare for battle!" << std::endl;
//		std::cout << std::endl;
//	}
//
//	return monster;
//}


//void Map::checkRandomEncounter(Player& player, Monster* monster[])
//{
//	if (getPlayerXPos() == 0 && getPlayerYPos() == 4)
//	{
//		Store store;
//		store.enter(player);
//
//		Monster* monster = 0;
//
//		//return monster;
//
//	}
//
//	int roll = Random(0, 20);
//
//	//Monster* monster = 0; // null monster pointer
//	monster[2] = nullptr; // null monsters pointer
//
//
//	int monsterCounter = 0;
//
//	if (roll <= 5)
//	{
//		// no encounter, return a null pointer.
//		monster[monsterCounter] = 0;
//
//		//return 0;
//	}
//	else if (roll >= 6 && roll <= 10) 
//	{
//		monster[monsterCounter] = new Monster("Orc", 10, 8, 200, 50, 1, "Short Sword", 2, 7);
//
//		std::cout << "You encountered an Orc!" << std::endl;
//		std::cout << "Prepare for battle!" << std::endl;
//		std::cout << std::endl;
//	}
//	else if (roll >= 11 && roll <= 15)
//	{
//		monster[monsterCounter] = new Monster("Goblin", 6, 6, 100, 75, 0, "Dagger", 1, 5);
//
//		std::cout << "You encountered a Goblin!" << std::endl;
//		std::cout << "Prepare for battle!" << std::endl;
//		std::cout << std::endl;
//	}
//	else if (roll >= 16 && roll <= 19)
//	{
//		monster[monsterCounter] = new Monster("Ogre", 20, 12, 500, 150, 2, "Club", 3, 8);
//
//		std::cout << "You encountered an Ogre!" << std::endl;
//		std::cout << "Prepare for battle!" << std::endl;
//		std::cout << std::endl;
//	}
//	else if (roll == 20)
//	{
//		monster[monsterCounter] = new Monster("Orc Lord", 25, 15, 2000, 500, 5, "Two Handed Sword", 5, 20);
//
//		std::cout << "You encounted an Orc Lord!!!" << std::endl;
//		std::cout << "Prepare for battle!" << std::endl;
//		std::cout << std::endl;
//	}
//
//	if (player.getLevel() > 10 && monster[1] == 0)
//	{
//		if (Random(1, 10) >8 )
//		{
//			// get another monster.
//			monsterCounter == 1;
//
//			//monster[monsterCounter] = checkRandomEncounter(player, monster);
//
//			checkRandomEncounter(player, monster);
//		}
//	}
//	
//
//	//return &monster;
//}

void Map::printPlayerPos()
{
	std::cout << "Player Position = (" << mPlayerXPos << ", " << mPlayerYPos << ")" << std::endl << std::endl;
}


Map::~Map()
{
}