#include "Monster.h"
#include "Player.h"
#include "Random.h"
#include <string>
#include <iostream>


Monster::Monster(const std::string& name, int hp, int acc, int xpReward, int goldReward, int armor, const std::string& weaponName, int lowDamage, int highDamage)
{
	mName = name;
	mHitPoints = hp;
	mAccuracy = acc;
	mExpReward = xpReward;
	mGoldReward = goldReward;
	mArmor = armor;
	mWeapon.mName = weaponName;
	mWeapon.mDamageRange.mLow = lowDamage;
	mWeapon.mDamageRange.mHigh = highDamage;

}

bool Monster::isDead()
{
	return mHitPoints <= 0;
}

int Monster::getXPReward()
{
	return mExpReward;
}

int Monster::getGoldReward()
{
	return mGoldReward;
}

std::string Monster::getName()
{
	return mName;
}

int Monster::getArmor()
{
	return mArmor;
}

void Monster::attack(Player& player, int monsterToAttack)
{
	std::cout << "A " << mName << " attacks you with a " << mWeapon.mName << std::endl;

	if (Random(0, 20) < mAccuracy)
	{
		int damage = Random(mWeapon.mDamageRange);

		int totalDamage = damage - player.getArmor();

		if (totalDamage <= 0)
		{
			std::cout << "The monster's attack failed to penetrate your armor." << std::endl;
		}
		else
		{
			std::cout << "You are hit for " << totalDamage << " damage!" << std::endl;

			player.takeDamage(totalDamage);
		}

	}
	else
	{
		std::cout << "The " << mName << " missed!" << std::endl;
	}

	std::cout << std::endl;
}

void Monster::takeDamage(int damage)
{
	mHitPoints -= damage;
}

void Monster::displayHitPoints()
{
	std::cout << mName << "'s hitpoints = " << mHitPoints << std::endl;
}

Monster::~Monster()
{
}