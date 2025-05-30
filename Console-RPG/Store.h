#ifndef STORE_H
#define STORE_H

#include "Player.h"
#include "Armor.h"
#include "Weapon.h"
//#include <string>
#include <vector>


class store
{
public:
	store();

	// disable copy constructor and assignment operator
	store(const store& other) = delete;
	store& operator=(const store& other) = delete;
	store(store&& other) noexcept = delete;
	store& operator=(store&& other) noexcept = delete;

	
	void enter(player& player);


	~store();


private:
	std::vector<armor> m_armor_objects_;
	std::vector<weapon> m_weapon_objects_;


};





#endif // STORE_H