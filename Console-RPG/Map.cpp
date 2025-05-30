#include "Map.h"
#include "Random.h"
#include "Store.h"

#include <iostream>



map::map()
{
	// player starts at origin (0, 0)
	m_player_x_pos_ = 0;
	m_player_y_pos_ = 0;
}


int map::get_player_x_pos() const
{
	return m_player_x_pos_;
}

int map::get_player_y_pos() const
{
	return m_player_y_pos_;
}

void map::move_player()
{
	int selection = 1;
	std::cout << "1) North, 2) East, 3) South, 4) West: ";
	std::cin >> selection;

	// update coordinates based on selection.
	switch (selection)
	{
	case 1: // north
		m_player_y_pos_++;
		break;
	case 2: // East
		m_player_x_pos_++;
		break;
	case 3: // south
		m_player_y_pos_--;
		break;
	default: // west
		m_player_x_pos_--;
		break;
	}

	std::cout << '\n';

}

// this code could easily be refactored to use a switch statement and only type out the msg's once for all statments.
void map::check_random_encounter(player& player, Monster* monster[]) const
{
	monster[0] = nullptr; // null monster 1 pointer
	monster[1] = nullptr; // null monster 2 pointer

	// check if player is at a store
	const int find_store = random(0, 100);
	if (get_player_x_pos() % 2 == 0 && get_player_y_pos() % 4 == 0 && find_store <= 5)
	{
		store store;
		store.enter(player);

		//return monster;

		return;
	}

	check_for_monster(monster, 0, player.get_level());
	
	if (monster[0] != nullptr && player.get_level() >= 6)
	{
		check_for_monster(monster, 1, player.get_level());
	}


	//return monster;
}

void map::check_for_monster(Monster* monster[], const int monster_number, const int players_current_level)
{
	monster[monster_number] = nullptr; // clear the pointer to a monster

	// generate a potential random encounter.
	const int roll = random(0, 23);
	
	if (roll <= 5)
	{
		// no encounter, return a null pointer.
		//monster[0] = 0; // null monster 1 pointer
		//monster[1] = 0; // null monster 2 pointer

		//return 0;
	}
	else if (roll >= 6 && roll <= 10)
	{
		constexpr int monsters_spawn_level = 1;
		
		if (players_current_level >= monsters_spawn_level)
		{
			monster[monster_number] = new Monster("Orc", monsters_spawn_level, 10, 8, 200, 50, 1, "Short Sword", 2, 7);

			/*std::cout << "You encountered an Orc!" << '\n';
			std::cout << "Prepare for battle!" << '\n';
			std::cout << '\n';*/
		}
	}
	else if (roll >= 11 && roll <= 15)
	{
		constexpr int monsters_spawn_level = 1;
		
		if (players_current_level >= monsters_spawn_level)
		{
			monster[monster_number] = new Monster("Goblin", monsters_spawn_level, 6, 6, 100, 75, 0, "Dagger", 1, 5);

			/*std::cout << "You encountered a Goblin!" << '\n';
			std::cout << "Prepare for battle!" << '\n';
			std::cout << '\n';*/
		}
	}
	else if (roll >= 16 && roll <= 19)
	{
		constexpr int monsters_spawn_level = 2;
		
		if (players_current_level >= monsters_spawn_level)
		{
			monster[monster_number] = new Monster("Ogre", monsters_spawn_level, 20, 12, 500, 150, 2, "Club", 3, 8);

			/*std::cout << "You encountered an Ogre!" << '\n';
			std::cout << "Prepare for battle!" << '\n';
			std::cout << '\n';*/
		}
	}
	else if (roll == 20)
	{
		constexpr int monsters_spawn_level = 5;
		
		if (players_current_level >= monsters_spawn_level)
		{
			monster[monster_number] = new Monster("Orc Lord", monsters_spawn_level, 25, 15, 2000, 500, 5, "Two Handed Sword", 5, 20);

			/*std::cout << "You encountered an Orc Lord!!!" << '\n';
			std::cout << "Prepare for battle!" << '\n';
			std::cout << '\n';*/
		}
	}
	else if (roll == 21)
	{
		constexpr int monsters_spawn_level = 12;
		
		if (players_current_level >= monsters_spawn_level)
		{
			monster[monster_number] = new Monster("Baby Dragon", monsters_spawn_level, 75, 35, 4000, 1500, 10, "Tail Swipe", 30, 75);

			/*std::cout << "You encountered an Baby Dragon!!!" << '\n';
			std::cout << "Prepare for battle!" << '\n';
			std::cout << '\n';*/
		}
	}
	else if (roll == 22)
	{
		constexpr int monsters_spawn_level = 18;
		
		if (players_current_level >= monsters_spawn_level)
		{
			monster[monster_number] = new Monster("Green Dragon", monsters_spawn_level, 175, 35, 6000, 4000, 15, "Corrosive Breath", 50, 100);

			/*std::cout << "You encountered an Green Dragon!!!" << '\n';
			std::cout << "Prepare for battle!" << '\n';
			std::cout << '\n';*/
		}
	}
	else if (roll == 23)
	{
		constexpr int monsters_spawn_level = 25;
		
		if (players_current_level >= monsters_spawn_level)
		{
			monster[monster_number] = new Monster("Gold Dragon", monsters_spawn_level, 250, 55, 10000, 10000, 20, "Molten Lava Breath", 40, 125);

			/*std::cout << "You encountered an Golden Dragon!!!" << '\n';
			std::cout << "Prepare for battle!" << '\n';
			std::cout << '\n';*/
		}
	}
	
	if (monster[monster_number] != nullptr)
	{
		std::cout << "You encountered an " << monster[monster_number]->get_name();

		
		if (monster[monster_number]->get_name() == "Green Dragon" || 
			monster[monster_number]->get_name() == "Gold Dragon")
		{
			std::cout << "!!!";
		}
		else if (monster[monster_number]->get_name() == "Baby Dragon")
		{
			std::cout << "!!";
		}
		else
		{
			std::cout << "!";
		}
		
			
		std::cout << "\nPrepare for battle!\n\n";
	}

	
}


void map::print_player_pos() const
{
	std::cout << "\nMap Position = (" << m_player_x_pos_ << ", " << m_player_y_pos_ << ")" << "\n\n";
}


map::~map() = default;
