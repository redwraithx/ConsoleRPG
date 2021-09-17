// Monster.h

#ifndef MONSTER_H
#define MONSTER_H

#include "Weapon.h"
#include <string>

class Player;

class Monster
{
public:

	Monster(const std::string& name, int hp, int acc, int xpReward, int goldReward, int armor, const std::string& weaponName, int lowDamage, int highDamage);

	bool isDead();

	int getXPReward();
	int getGoldReward();
	std::string getName();
	int getArmor();

	void attack(Player& player, int monsterToAttack);
	void takeDamage(int damage);
	void displayHitPoints();


	~Monster();

private:
	std::string mName;
	int mHitPoints;
	int mAccuracy;
	int mExpReward;
	int mGoldReward;
	int mArmor;
	Weapon mWeapon;


};

#endif // MONSTER_H

