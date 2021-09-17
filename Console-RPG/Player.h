// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"
#include "Armor.h"
#include "Monster.h"
#include "Magic.h"
#include "Range.h"
#include "Potion.h"

#include <string>
#include <vector>


class Player
{
public:
	// constructor
	Player();

	// methods
	bool isDead();

	std::string getName();
	std::string getClass();
	int getGold();
	void buy(int cost);
	void equipArmor(Armor newArmor);
	void equipWeapon(Weapon newWeapon);
	
	void calculateWeaponDamage();
	void setWeaponBonus(int low, int high);
	int getWeaponBonux(bool getLowDamage);
	void setOriginalWeaponValues(const Range& weaponDamage);
	int getOriginalWeaponValue(bool getLowDamage);

	int getArmor();
	void setArmorBonus(int value);
	void calculateArmor();
	
	void setMagicBonusDamage(int low, int high);
	void setOriginalMagicDamage(const Range magicDamage);
	void increaseSpellManaCost();
	void calculateMagicDamage();

	void takeDamage(int damage);
	void healDamage(int healValue);

	int usePotion(Potion currentPotion);
	bool addNewPotion(Potion newPotion);
	int getPotionCount();

	void createClass();
	void PlayerClassSelection();
	void PlayerRaceSelection();
	//bool attack(Monster& monster);
	bool attack(Monster* monster[]);
	void levelUp();
	int getLevel();
	void rest();
	void viewStates();
	void victory(int xp, int gold);
	void gameover();
	void displayHitPoints();
	void displayMagicPoints();

	// deconstructor
	~Player();

private:
	// data members
	std::string mName;
	std::string mRaceName;
	std::string mClassName;
	int mAccuracy;
	int mHitPoints;
	int mMaxHitPoints;
	int mMagicPoints;
	int mMaxMagicPoints;
	Range mMagicBonusDamage;
	
	int mRewardModifier; // leave at 1 for normal exp and gold, 0 for no exp or gold
	int mExpPoints;
	int mNextLevelExp;
	int mLevel;
	int mArmor;
	Weapon mWeaponHeld;
	Range mOriginalWeaponDamage;
	Range mWeaponBonus;

	Armor mArmorWorn;
	int mArmorBonus;

	int mGold;

	std::vector<Spell> mMagicSpellsKnown;
	std::vector<Range> mOriginalMagicDamage;
	std::vector<Potion> mPotionsOwned; // if we have anything we own it. if we use it we will then pop it. if we buy one we will push it.

};






#endif // PLAYER_H