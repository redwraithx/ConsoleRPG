// Map.h

#ifndef MAP_H
#define MAP_H


#include "Weapon.h"
#include "Monster.h"
#include <string>


class Map
{
public:
	// constructor.
	Map();
	
	// Methods
	int getPlayerXPos();
	int getPlayerYPos();
	void movePlayer();
	//Monster* checkRandomEncounter(Player& player);
	void checkRandomEncounter(Player& player, Monster* monster[]);

	void CheckForMonster(Monster* monster[], int monsterNumber);
	
	void printPlayerPos();
	
	
	~Map();

private:
	// data members
	int mPlayerXPos;
	int mPlayerYPos;


};


#endif // MAP_H



