#ifndef STORE_H
#define STORE_H

#include "Player.h"
#include "Armor.h"
#include "Weapon.h"
#include <string>
#include <vector>


class Store
{
public:
	Store();
	void enter(Player& player);


	~Store();


private:
	std::vector<Armor> mArmorObjects;
	std::vector<Weapon> mWeaponObjects;


};





#endif // STORE_H