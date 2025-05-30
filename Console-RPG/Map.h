// Map.h

#ifndef MAP_H
#define MAP_H


#include "Weapon.h"
#include "Monster.h"
#include <string>


class map
{
public:
	// constructor.
	map();
	
	// Methods
	int get_player_x_pos() const;
	int get_player_y_pos() const;
	void move_player();
	//Monster* checkRandomEncounter(Player& player);
	void check_random_encounter(player& player, Monster* monster[]) const;

	static auto check_for_monster(Monster* monster[], int monster_number, int players_current_level = 1) -> void;
	
	void print_player_pos() const;
	
	
	~map();

private:
	// data members
	int m_player_x_pos_;
	int m_player_y_pos_;


};


#endif // MAP_H



