#include "Player.h"
#include "Monster.h"
#include "Magic.h"
#include "Random.h"
#include "Potion.h"
// #include "Weapon.h"
// #include "Armor.h"
#include "Debug_Mode.h"

#include <string>
#include <iostream>


// do you want to see debug messages?
//DebugMessages debugLog;





// Prototypes
Spell addSpell(std::string name, int damageLow, int damageHigh, int requiredLevel, int magicPointsRequired);
Potion addPotion(int low, int high, int price);


Player::Player()
{
	mName = "Default";
	mRaceName = "DefaultRace";
	mClassName = "DefaultClass";
	mAccuracy = 0;
	mHitPoints = 0;
	mMaxHitPoints = 0;
	mExpPoints = 0;
	mNextLevelExp = 0;
	mLevel = 0;
	mGold = 0;
	mArmor = 0;
	
	mWeaponHeld.mName = "Default Weapon Name";
	mWeaponHeld.mDamageRange.mLow = 0;
	mWeaponHeld.mDamageRange.mHigh = 0;

	mOriginalWeaponDamage.mLow = 0;
	mOriginalWeaponDamage.mHigh = 0;

	mWeaponBonus.mLow = 0;
	mWeaponBonus.mHigh = 0;

	mArmorWorn.mName = "Default Armor Name";
	mArmorWorn.mArmorValue = 0;
	mArmorWorn.mSellValue = 0;

	mArmorBonus = 0;

	// this should be set to 1 for normal game play
	mRewardModifier = 10;
}

// methods
bool Player::isDead()
{
	return mHitPoints <= 0;
}

std::string Player::getName()
{
	return mName;
}

std::string Player::getClass()
{
	return mClassName;
}

int Player::getGold()
{
	return mGold;
}

void Player::buy(int cost)
{
	mGold -= cost;
}

void Player::equipArmor(Armor newArmor)
{
	// remove old armor value from armor
	mArmor -= mArmorWorn.mArmorValue;

	// wear new armor
	//mArmorWorn.mName = newArmor.mName;
	//mArmorWorn.mArmorValue = newArmor.mArmorValue;
	//mArmorWorn.mSellValue = newArmor.mSellValue;

	if (debugLog.enableDebugMessages)
	{
		std::cout << "debug msg - old armor" << std::endl;
		std::cout << "new armor: " << mArmorWorn.mName << std::endl;
		std::cout << "new armor AC: " << mArmorWorn.mArmorValue << std::endl;
		std::cout << "new armor price: " << mArmorWorn.mSellValue << std::endl;
	}
	
	mArmorWorn = newArmor;

	if (debugLog.enableDebugMessages)
	{
		std::cout << "debug msg - new armor" << std::endl;
		std::cout << "new armor: " << mArmorWorn.mName << std::endl;
		std::cout << "new armor AC: " << mArmorWorn.mArmorValue << std::endl;
		std::cout << "new armor price: " << mArmorWorn.mSellValue << std::endl;
	}
	

	// add new armor value to armor
	mArmor += mArmorWorn.mArmorValue;
}

void Player::equipWeapon(Weapon newWeapon)
{
	// assign new weapon.
	mWeaponHeld = newWeapon;

	// update original damage as for new weapon.
	setOriginalWeaponValues(newWeapon.mDamageRange);
}

int Player::getOriginalWeaponValue(bool getLowDamage)
{
	if (getLowDamage)
		return mOriginalWeaponDamage.mLow;
	else
		return mOriginalWeaponDamage.mHigh;
}

int Player::getArmor()
{
	return mArmor;
}

void Player::setArmorBonus(int value)
{
	mArmorBonus += value;
}

void Player::calculateWeaponDamage()
{
	mWeaponHeld.mDamageRange.mLow = mOriginalWeaponDamage.mLow + mWeaponBonus.mLow;
	mWeaponHeld.mDamageRange.mHigh = mOriginalWeaponDamage.mHigh + mWeaponBonus.mHigh;
}

void Player::setWeaponBonus(int low, int high)
{
	mWeaponBonus.mLow += low;
	mWeaponBonus.mHigh += high;
}

int Player::getWeaponBonux(bool getLowDamage)
{
	if (getLowDamage)
		return mWeaponBonus.mLow;
	else
		return mWeaponBonus.mHigh;
}

void Player::setOriginalWeaponValues(const Range& weaponDamage)
{
	mOriginalWeaponDamage.mLow = weaponDamage.mLow;
	mOriginalWeaponDamage.mHigh = weaponDamage.mHigh;
}

void Player::calculateArmor()
{
	mArmor = mArmorBonus + mArmorWorn.mArmorValue;
}


void Player::setMagicBonusDamage(int low, int high)
{
	mMagicBonusDamage.mLow += low;
	mMagicBonusDamage.mHigh += high;
}

void Player::setOriginalMagicDamage(const Range magicDamage)
{
	//for (int i = 0; i < mOriginalMagicDamage.size(); i++)
	//{
	
	mOriginalMagicDamage.push_back(magicDamage);

	/*	mOriginalMagicDamage[spellNumber].mLow = magicDamage.mLow;
		mOriginalMagicDamage[spellNumber].mHigh = magicDamage.mHigh;*/
	//}
	
}

void Player::increaseSpellManaCost()
{
	for (int i = 0; i < mMagicSpellsKnown.size(); i++)
	{
		mMagicSpellsKnown[i].mMagicPointsRequired++;
	}
}

void Player::calculateMagicDamage()
{
	if (mClassName == "Fighter" || mClassName == "Thief")
		return;

	if (mMagicSpellsKnown.size() < 1)
	{
		std::cout << "It seems you are not a fighter or thief but still have no spells.... log this bug." << std::endl;

		return;
	}
		


	// iterate over all the spells and add the bonus to it
	for (int i = 0; i < mMagicSpellsKnown.size(); i++)
	{
		if (debugLog.enableDebugMessages)
		{
			std::cout << "Debug msgs" << std::endl;
			std::cout << "magic spells known #" << i << ": " << mMagicSpellsKnown[i].mName << std::endl;
			std::cout << "Magic low bonus " << i << ": " << mMagicBonusDamage.mLow << std::endl;
			std::cout << "Magic high bonus " << i << ": " << mMagicBonusDamage.mHigh << std::endl;
			std::cout << "original low damage " << i << ": " << mOriginalMagicDamage[i].mLow << std::endl;
			std::cout << "original high damage " << i << ": " << mOriginalMagicDamage[i].mHigh << std::endl;
		}

		if (mMagicSpellsKnown[i].mRequiredLevel <= mLevel)
		{
			//std::cout << i << ") " << mMagicSpellsKnown[i].mName << " (Low: " << mMagicSpellsKnown[i].mDamageRange.mLow << ", High: " << mMagicSpellsKnown[i].mDamageRange.mHigh << ")" << " <> Spell Cost: " << mMagicSpellsKnown[i].mMagicPointsRequired << std::endl;

			mMagicSpellsKnown[i].mDamageRange.mLow = mMagicBonusDamage.mLow + mOriginalMagicDamage[i].mLow;
			mMagicSpellsKnown[i].mDamageRange.mHigh = mMagicBonusDamage.mHigh + mOriginalMagicDamage[i].mHigh;

		}

	}
}


void Player::takeDamage(int damage)
{
	mHitPoints -= damage;
}

void Player::healDamage(int healValue)
{
	mHitPoints += healValue;

	if (mHitPoints > mMaxHitPoints)
	{
		mHitPoints = mMaxHitPoints;
	}
}

int Player::usePotion(Potion currentPotion)
{
	// heal player
	return (Random(currentPotion.mPotionValue));
}

bool Player::addNewPotion(Potion newPotion)
{
	if (getPotionCount() > 3) // max # of potions you can carry
	{
		return false;
	}


	mPotionsOwned.push_back(newPotion);

	return true;
}

int Player::getPotionCount()
{
	return mPotionsOwned.size();
}

void Player::createClass()
{
	std::cout << "CHARACTER CLASS GENERATION" << std::endl;
	std::cout << "==========================" << std::endl;

	// input character's name
	std::cout << "Enter your character's name: ";
	std::getline(std::cin, mName);

	
	PlayerClassSelection();
	
	std::cout << std::endl;

	PlayerRaceSelection();
	


	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////

	// give the player 1 healing potion to start with
	Potion newPotion = addPotion(3, 8, 30); // low 3, high 8, price 30
	mPotionsOwned.push_back(newPotion);
}

void Player::PlayerClassSelection()
{
	// character selection.
	std::cout << "Please select a character class number..." << std::endl;
	std::cout << "1) Fighter 2) Wizard 3) Cleric 4) Thief: ";
	int characterNum = 1;
	std::cin >> characterNum;


	switch (characterNum)
	{
	case 1:
		// fighter
		mClassName = "Fighter";
		mAccuracy = 10;
		mHitPoints = 20;
		mMaxHitPoints = 20;
		mMagicPoints = 0;
		mMaxMagicPoints = 0;
		mExpPoints = 0;
		mNextLevelExp = 1000;
		mLevel = 1;
		mGold = 0;
		mArmor = 4;

		// weapon
		mWeaponHeld.mName = "Long Sword";
		mWeaponHeld.mDamageRange.mLow = 1;
		mWeaponHeld.mDamageRange.mHigh = 8;

		setOriginalWeaponValues(mWeaponHeld.mDamageRange);

		// armor
		mArmorWorn.mName = "Cloth Rags";
		mArmorWorn.mArmorValue = 0;
		mArmorWorn.mSellValue = 0;

		mArmorBonus = mArmor;

		break;
	case 2:
		// wizard
		mClassName = "Wizard";
		mAccuracy = 5;
		mHitPoints = 10;
		mMaxHitPoints = 10;
		mMagicPoints = 10;
		mMaxMagicPoints = 10;
		mExpPoints = 0;
		mNextLevelExp = 1000;
		mLevel = 1;
		mGold = 0;
		mArmor = 1;

		// weapon
		mWeaponHeld.mName = "Staff";
		mWeaponHeld.mDamageRange.mLow = 1;
		mWeaponHeld.mDamageRange.mHigh = 4;

		setOriginalWeaponValues(mWeaponHeld.mDamageRange);

		// armor
		mArmorWorn.mName = "Cloth Rags";
		mArmorWorn.mArmorValue = 0;
		mArmorWorn.mSellValue = 0;

		mArmorBonus = mArmor;

		// add wizard spells
		mMagicSpellsKnown.push_back(addSpell("Magic Missle", 20, 100, 1, 2));
		mMagicSpellsKnown.push_back(addSpell("Fire Ball", 6, 20, 3, 6));

		for (int i = 0; i < mMagicSpellsKnown.size(); i++)
		{
			setOriginalMagicDamage(mMagicSpellsKnown[i].mDamageRange);
		}

		

		break;
	case 3:
		// cleric
		mClassName = "Cleric";
		mAccuracy = 8;
		mHitPoints = 15;
		mMaxHitPoints = 15;
		mMagicPoints = 6;
		mMaxMagicPoints = 6;
		mExpPoints = 0;
		mNextLevelExp = 1000;
		mLevel = 1;
		mGold = 0;
		mArmor = 3;

		// weapon
		mWeaponHeld.mName = "Flail";
		mWeaponHeld.mDamageRange.mLow = 1;
		mWeaponHeld.mDamageRange.mHigh = 6;

		setOriginalWeaponValues(mWeaponHeld.mDamageRange);

		// armor
		mArmorWorn.mName = "Cloth Rags";
		mArmorWorn.mArmorValue = 0;
		mArmorWorn.mSellValue = 0;

		mArmorBonus = mArmor;

		// add Cleric spells
		mMagicSpellsKnown.push_back(addSpell("Minor Healing", 1, 8, 1, 2));
		mMagicSpellsKnown.push_back(addSpell("Major Healing", 6, 16, 3, 5));

		// could use a for loop to set all spells at once, even if you add more
		for (int i = 0; i < mMagicSpellsKnown.size(); i++)
		{
			setOriginalMagicDamage(mMagicSpellsKnown[i].mDamageRange);
		}

		break;
	default:
		// thief
		mClassName = "Thief";
		mAccuracy = 7;
		mHitPoints = 12;
		mMaxHitPoints = 12;
		mMagicPoints = 0;
		mMaxMagicPoints = 0;
		mExpPoints = 0;
		mNextLevelExp = 1000;
		mLevel = 1;
		mGold = 0;
		mArmor = 2;

		// weapon
		mWeaponHeld.mName = "Tarnished Dagger";
		mWeaponHeld.mDamageRange.mLow = 1;
		mWeaponHeld.mDamageRange.mHigh = 4;

		setOriginalWeaponValues(mWeaponHeld.mDamageRange);

		// armor
		mArmorWorn.mName = "Cloth Rags";
		mArmorWorn.mArmorValue = 0;
		mArmorWorn.mSellValue = 0;

		mArmorBonus = mArmor;

		break;

	}
}

void Player::PlayerRaceSelection()
{
	// race selection
	std::cout << "Race Selection" << std::endl;
	std::cout << "--------------" << std::endl;
	std::cout << "1) Human, 2) Elf, 3) Dwarf, 4) Gnome" << std::endl;
	std::cout << "Select your race number: ";

	int selection = 1;
	std::cin >> selection;


	int tempHp = 0, tempAcc = 0, tempMagicPoints = 0;

	switch (selection) // 
	{
	case 1: // human
		mRaceName = "Human";

		// pro   +(1-3) hps
		tempHp += Random(1, 5);

		// con   -(1-2) acc
		tempAcc -= Random(1, 2);

		if (mClassName == "Wizard" || mClassName == "Cleric")
		{
			tempMagicPoints += Random(0, 3);
		}

		break;

	case 2: // elf
			// pro   +(1-2) acc

		mRaceName = "Elf";
		
		tempAcc += Random(1, 4);

		// con   -(1-2) hps
		tempHp -= Random(1, 2);

		if (mClassName == "Wizard" || mClassName == "Cleric")
		{
			tempMagicPoints += Random(1, 5);
			tempMagicPoints += Random(10, 50);
		}

		break;

	case 3: // dwarf
			// pro   +(2-6) hps

		mRaceName = "Dwarf";

		tempHp += Random(2, 8);

		// con   -(1-2) acc
		tempAcc -= Random(1, 2);

		if (mClassName == "Wizard" || mClassName == "Cleric")
		{
			tempMagicPoints += Random(0, 2);
		}

		break;

	default: // gnome
			 // pro   +(1-4) acc

		mRaceName = "Gnome";

		tempAcc += Random(1, 8);

		// con   -(1-2) hp
		tempHp -= Random(1, 2);

		if (mClassName == "Wizard" || mClassName == "Cleric")
		{
			tempMagicPoints += Random(0, 1);
		}

		break;
	}

	if (debugLog.enableDebugMessages)
	{
		std::cout << "DEBUG MSGS" << std::endl;
		std::cout << "Hp before: " << mMaxHitPoints << std::endl;
		std::cout << "Acc before: " << mAccuracy << std::endl;
		std::cout << "Magic Points before: " << mMagicPoints << std::endl;
	}


	mMaxHitPoints += tempHp;
	mHitPoints = mMaxHitPoints;
	mAccuracy += tempAcc;
	mMaxMagicPoints += tempMagicPoints;

	if (debugLog.enableDebugMessages)
	{
		std::cout << "DEBUG MSGS" << std::endl;
		std::cout << "Hp after: " << mHitPoints << std::endl;
		std::cout << "Acc after: " << mAccuracy << std::endl;
		std::cout << "Magic Points After: " << mMaxMagicPoints << std::endl;
		std::cout << "hpBonus: " << tempHp << std::endl;
		std::cout << "accBonus: " << tempAcc << std::endl;
		std::cout << "Magic points bonus: " << tempMagicPoints << std::endl;
	}


	std::cout << std::endl;
}

bool Player::attack(Monster* monster[])
{
	int selection = 1;
	std::cout << "1) Attack, ";
	
	// check for caster status
	if (mClassName == "Wizard" || mClassName == "Cleric")
	{
		std::cout << "2) use Spells, ";
	}

	// check if user has any potions to use
	if (!mPotionsOwned.empty())
	{
		std::cout << "3) use Potion, ";
	}
	
	std::cout << "4) Run: ";
	std::cin >> selection;

	std::cout << std::endl;



	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (debugLog.enableDebugMessages)
	{
		std::cout << "is monster[1] alive and can it attack, else all momsters are dead and return" << std::endl;
	}

	bool areThereTwoMonsters = (monster[1] != 0 ? true : false);

	int monsterToAttack = 0;

	if (!monster[monsterToAttack]->isDead())
	{
		////////////////////////////////////////////////////////////
		// player attacks first monster debug msg
		if (debugLog.enableDebugMessages)
		{
			std::cout << "Player is attacking monster 1" << std::endl;
			std::cout << "monsterToAttack: " << monsterToAttack << std::endl;
		}
	}
	else if (areThereTwoMonsters && monster[monsterToAttack]->isDead() && !monster[monsterToAttack + 1]->isDead())
	{
		monsterToAttack = 1;

		/////////////////////////////////////////////////////////////
		// player attacks 2nd monster debug msg
		if (debugLog.enableDebugMessages)
		{
			std::cout << "Player is attacking monster 2" << std::endl;
			std::cout << "monsterToAttack: " << monsterToAttack << std::endl;
		}
	}
	else
	{
		/////////////////////////////////////////////////////////////
		// debug msg
		if (debugLog.enableDebugMessages)
		{
			std::cout << "Player isnt attacking at all.... else is returning from battle" << std::endl;
			std::cout << "M1: " << monster[0] << std::endl;
			std::cout << "M2: " << monster[1] << std::endl;
		}

		return false;
	}

	//if (monster[1] != 0 && monster[0]->isDead())
	//{
	//	if (!monster[0]->isDead())
	//	{
	//		monsterToAttack = 1;
	//	}
	//	else
	//	{
	//		// monsters are dead
	//		return true;
	//	}
	//	
	//}

	////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////



	switch (selection)
	{
	case 1:
		// Attack
		std::cout << "You attack an " << monster[monsterToAttack]->getName() << " with a " << mWeaponHeld.mName << std::endl;

		if (Random(0, 20) < mAccuracy)
		{
			int damage = Random(mWeaponHeld.mDamageRange);

			int totalDamage = damage - monster[monsterToAttack]->getArmor();

			if (totalDamage <= 0)
			{
				std::cout << "Your attack failed to penetrate the armor. " << std::endl;
			}
			else
			{
				std::cout << "You attack for " << totalDamage << " damage!" << std::endl;

				// subtract from monster's hitpoints.
				monster[monsterToAttack]->takeDamage(totalDamage);
			}
		}
		else
		{
			std::cout << "You miss!" << std::endl;
		}

		std::cout << std::endl;

		break;

	case 2:
	{
		if (mClassName == "Fighter" || mClassName == "Thief")
		{
			std::cout << "It seems you haven't quite mastered the magical arts... Choose another selection" << std::endl;

			break;
		}

		// else you have magic to use
		std::cout << "Magical spells you currently have." << std::endl;
		std::cout << "----------------------------------" << std::endl;

		// list what spells this player has as choices.
		for (int i = 0; i < mMagicSpellsKnown.size(); i++)
		{
			// do we have the level to use the spell?
			if (mMagicSpellsKnown[i].mRequiredLevel <= mLevel)
			{
				std::cout << "- " << i << ") " << mMagicSpellsKnown[i].mName << " ";
			}

			
		}

		std::cout << std::endl;
		std::cout << "----------------------------------" << std::endl << std::endl;

		std::cout << "Enter the number of the spell you wish to cast: ";

		// get selection from user
		int spellSelection = 1;

		std::cin >> spellSelection;
		


		// take action IF user has enough mana to cast the spell... else loop out and try again
		if (  (spellSelection < 0 || spellSelection > mMagicSpellsKnown.size() ) || mMagicSpellsKnown[spellSelection].mRequiredLevel > mLevel)
		{
			std::cout << "You dont have a spell for [" << spellSelection << "]. Try selecting a spell you can use!" << std::endl;
		}
		else if (mMagicPoints >= mMagicSpellsKnown[spellSelection].mMagicPointsRequired && mMagicSpellsKnown[spellSelection].mRequiredLevel <= mLevel)
		{
			if (mClassName == "Wizard")
			{
				// cast the spell, damages monster
				int spellDamage = Random(mMagicSpellsKnown[spellSelection].mDamageRange);
				monster[monsterToAttack]->takeDamage(spellDamage);

				std::cout << "You hit the " << monster[monsterToAttack]->getName() << ", with the " << mMagicSpellsKnown[spellSelection].mName << " spell. Dealing " << spellDamage << " magical damage to them." << std::endl;

				// update mMagicPoints
				mMagicPoints -= mMagicSpellsKnown[spellSelection].mMagicPointsRequired;
			}
			else // cleric
			{
				// cast the spell, damages monster
				int healingAmount = Random(mMagicSpellsKnown[spellSelection].mDamageRange);
				healDamage(healingAmount);



				std::cout << "Casting the " << mMagicSpellsKnown[spellSelection].mName << " spell. You heal yourself for " << healingAmount << " damage." << std::endl;

				// update mMagicPoints
				mMagicPoints -= mMagicSpellsKnown[spellSelection].mMagicPointsRequired;
			}



		}
		else
		{
			std::cout << "You dont have enough \"Magic Points\" to cast " << mMagicSpellsKnown[spellSelection].mName << std::endl;
			//std::cout << "Make another selection." << std::endl;

		}


		std::cout << std::endl;

		break;
	}
	case 3:
	{
		if (debugLog.enableDebugMessages)
		{
			std::cout << "DEBUG MSG POTION COUNT" << std::endl;
			std::cout << "potions before: " << mPotionsOwned.size() << std::endl;
		}



		if (mPotionsOwned.empty())
		{
			std::cout << "You look for a potion, but you have none it seems." << std::endl << std::endl;

			break; // you have no potions
		}


		if (mHitPoints == mMaxHitPoints)
		{
			std::cout << "You have full hitpoints, you dont need to use that potion right now." << std::endl << std::endl;

			break;
		}
		
		Potion testPotion = mPotionsOwned[0];
		mPotionsOwned.pop_back();

		int healPlayer = usePotion(testPotion);

		mHitPoints += healPlayer;

		if (mHitPoints > mMaxHitPoints)
		{
			mHitPoints = mMaxHitPoints;
		}

		if (debugLog.enableDebugMessages)
		{
			std::cout << "DEBUG MSG POTION COUNT" << std::endl;
			std::cout << "potions after: " << mPotionsOwned.size() << std::endl;
		}
		

		break;
	}
	case 4: // run away
	{
		int roll = Random(1, 4);

		if (mClassName == "Thief")
		{
			// 50% chance of being able to run, if your a sneaky thief
			roll = Random(2, 4);

			if (debugLog.enableDebugMessages)
			{
				std::cout << "DEBUG MSG" << std::endl;
				std::cout << "run roll thief: " << roll << std::endl;
			}
			
		}
		else
		{
			// 25% chance of being able to run.
			roll = Random(1, 4);
		}


		if ((roll == 1 || roll == 2) && mClassName == "Thief")
		{
			std::cout << "You run away!" << std::endl;

			return true; // return out of the function
		}
		else if (roll == 1)
		{
			std::cout << "You run away!" << std::endl;

			return true; // return out of the function
		}
		else
		{
			std::cout << "You could not escape!" << std::endl;
			break;
		}
	} // end case 4
	}// end switch

	return false;
}


//bool Player::attack(Monster& monster)
//{
//	int selection = 1;
//	std::cout << "1) Attack, ";
//
//	// check for caster status
//	if (mClassName == "Wizard" || mClassName == "Cleric")
//	{
//		std::cout << "2) use Spells, ";
//	}
//
//	// check if user has any potions to use
//	if (mPotionsOwned.size() > 0)
//	{
//		std::cout << "3) use Potion, ";
//	}
//
//	std::cout << "4) Run: ";
//	std::cin >> selection;
//
//	std::cout << std::endl;
//
//
//	switch (selection)
//	{
//	case 1:
//		// Attack
//		std::cout << "You attack an " << monster.getName() << " with a " << mWeaponHeld.mName << std::endl;
//
//		if (Random(0, 20) < mAccuracy)
//		{
//			int damage = Random(mWeaponHeld.mDamageRange);
//
//			int totalDamage = damage - monster.getArmor();
//
//			if (totalDamage <= 0)
//			{
//				std::cout << "Your attack failed to penetrate the armor. " << std::endl;
//			}
//			else
//			{
//				std::cout << "You attack for " << totalDamage << " damage!" << std::endl;
//
//				// subtract from monster's hitpoints.
//				monster.takeDamage(totalDamage);
//			}
//		}
//		else
//		{
//			std::cout << "You miss!" << std::endl;
//		}
//
//		std::cout << std::endl;
//
//		break;
//
//	case 2:
//	{
//		if (mClassName == "Fighter" || mClassName == "Thief")
//		{
//			std::cout << "It seems you haven't quite mastered the magical arts... Choose another selection" << std::endl;
//
//			break;
//		}
//
//		// else you have magic to use
//		std::cout << "Magical spells you currently have." << std::endl;
//		std::cout << "----------------------------------" << std::endl;
//
//		// list what spells this player has as choices.
//		for (int i = 0; i < mMagicSpellsKnown.size(); i++)
//		{
//			// do we have the level to use the spell?
//			if (mMagicSpellsKnown[i].mRequiredLevel <= mLevel)
//			{
//				std::cout << "- " << i << ") " << mMagicSpellsKnown[i].mName << " ";
//			}
//
//
//		}
//
//		std::cout << std::endl;
//		std::cout << "----------------------------------" << std::endl << std::endl;
//
//		std::cout << "Enter the number of the spell you wish to cast: ";
//
//		// get selection from user
//		int spellSelection = 1;
//
//		std::cin >> spellSelection;
//
//
//
//		// take action IF user has enough mana to cast the spell... else loop out and try again
//		if ((spellSelection < 0 || spellSelection > mMagicSpellsKnown.size()) || mMagicSpellsKnown[spellSelection].mRequiredLevel > mLevel)
//		{
//			std::cout << "You dont have a spell for [" << spellSelection << "]. Try selecting a spell you can use!" << std::endl;
//		}
//		else if (mMagicPoints >= mMagicSpellsKnown[spellSelection].mMagicPointsRequired && mMagicSpellsKnown[spellSelection].mRequiredLevel <= mLevel)
//		{
//			if (mClassName == "Wizard")
//			{
//				// cast the spell, damages monster
//				int spellDamage = Random(mMagicSpellsKnown[spellSelection].mDamageRange);
//				monster.takeDamage(spellDamage);
//
//				std::cout << "You hit the " << monster.getName() << ", with the " << mMagicSpellsKnown[spellSelection].mName << " spell. Dealing " << spellDamage << " magical damage to them." << std::endl;
//
//				// update mMagicPoints
//				mMagicPoints -= mMagicSpellsKnown[spellSelection].mMagicPointsRequired;
//			}
//			else // cleric
//			{
//				// cast the spell, damages monster
//				int healingAmount = Random(mMagicSpellsKnown[spellSelection].mDamageRange);
//				healDamage(healingAmount);
//
//
//
//				std::cout << "Casting the " << mMagicSpellsKnown[spellSelection].mName << " spell. You heal yourself for " << healingAmount << " damage." << std::endl;
//
//				// update mMagicPoints
//				mMagicPoints -= mMagicSpellsKnown[spellSelection].mMagicPointsRequired;
//			}
//
//
//
//		}
//		else
//		{
//			std::cout << "You dont have enough \"Magic Points\" to cast " << mMagicSpellsKnown[spellSelection].mName << std::endl;
//			//std::cout << "Make another selection." << std::endl;
//
//		}
//
//
//		std::cout << std::endl;
//
//		break;
//	}
//	case 3:
//	{
//		if (debugLog.enableDebugMessages)
//		{
//
//		}
//		std::cout << "DEBUG MSG POTION COUNT" << std::endl;
//		std::cout << "potions before: " << mPotionsOwned.size() << std::endl;
//
//
//		if (mPotionsOwned.size() == 0)
//		{
//			std::cout << "You look for a potion, but you have none it seems." << std::endl << std::endl;
//
//			break; // you have no potions
//		}
//
//
//		if (mHitPoints == mMaxHitPoints)
//		{
//			std::cout << "You have full hitpoints, you dont need to use that potion right now." << std::endl << std::endl;
//
//			break;
//		}
//
//		Potion testPotion = mPotionsOwned[0];
//		mPotionsOwned.pop_back();
//
//		int healPlayer = usePotion(testPotion);
//
//		mHitPoints += healPlayer;
//
//		if (mHitPoints > mMaxHitPoints)
//		{
//			mHitPoints = mMaxHitPoints;
//		}
//
//		if (debugLog.enableDebugMessages)
//		{
//			std::cout << "DEBUG MSG POTION COUNT" << std::endl;
//			std::cout << "potions after: " << mPotionsOwned.size() << std::endl;
//		}
//
//
//		break;
//	}
//	case 4: // run away
//	{
//		int roll = Random(1, 4);
//
//		if (mClassName == "Thief")
//		{
//			// 50% chance of being able to run, if your a sneaky thief
//			roll = Random(2, 4);
//
//			if (debugLog.enableDebugMessages)
//			{
//				std::cout << "DEBUG MSG" << std::endl;
//				std::cout << "run roll thief: " << roll << std::endl;
//			}
//
//		}
//		else
//		{
//			// 25% chance of being able to run.
//			roll = Random(1, 4);
//		}
//
//
//		if ((roll == 1 || roll == 2) && mClassName == "Thief")
//		{
//			std::cout << "You run away!" << std::endl;
//
//			return true; // return out of the function
//		}
//		else if (roll == 1)
//		{
//			std::cout << "You run away!" << std::endl;
//
//			return true; // return out of the function
//		}
//		else
//		{
//			std::cout << "You could not escape!" << std::endl;
//			break;
//		}
//	} // end case 4
//	}// end switch
//
//	return false;
//}


void Player::levelUp()
{
	if (debugLog.enableDebugMessages)
	{
		if (mExpPoints > mNextLevelExp)
			std::cout << "you can level now" << std::endl;
	}
	

	bool test = (mExpPoints > mNextLevelExp);
	{
		if (debugLog.enableDebugMessages)
		{
			std::cout.setf(std::cout.boolalpha);
			std::cout << "test = " << test << ", true means test works, while loop does not." << std::endl;
		}
	}


	while(mExpPoints > mNextLevelExp)
	{
		std::cout << "You gained a level!" << std::endl;

		// increment level
		mLevel++;

		// set experience points required for next level
		mNextLevelExp = mLevel * mLevel * 1000; // need to modify this to use better leveling add later

		// increase stats randomly
		if (mLevel > 20)
		{
			mAccuracy += Random(1, 3);
			mMaxHitPoints += Random(5, 12);
			setArmorBonus(Random(1, 2));
		}
		else if (mLevel > 10)
		{
			mAccuracy += Random(1, 3);
			mMaxHitPoints += Random(2, 9);
			setArmorBonus(Random(1, 2));
		}
		else
		{
			mAccuracy += Random(1, 3);
			mMaxHitPoints += Random(2, 6);
			setArmorBonus(Random(1, 2));
		}

		// class bonus stats
		int tempAc = 0, tempHp = 0, tempAcc = 0, tempDamLow = 0, tempDamHigh = 0, tempMagicLow = 0, tempMagicHigh = 0;


		if (mClassName == "Fighter")
		{
			tempHp = Random(1, 3);
			tempAc = Random(0, 2);
			tempAcc = (mLevel % 4 == 0 ? 1 : 0); // if level divided by 4 is 0, add 1 else add 0

			if (mLevel > 10)
			{
				tempDamLow = Random(0, 2);
				tempDamHigh = Random(1, 4);
			}
			else
			{
				tempDamLow = Random(0, 1);
				tempDamHigh = Random(0, 2);
			}
			
			//tempMagicLow = 0;
			//tempMagicHigh = 0;
		}
		else if (mClassName == "Wizard")
		{
			tempHp = (mLevel % 2 == 0 ? Random(0, 2) : 0); // if level divided by 2 is 0 add 1 to 3 hps else 0
			tempAc = (mLevel % 3 == 0 ? 1 : 0); // if level divided by 3 is 0 add 1 ac point else 0
			tempAcc = 0;
			tempDamLow = Random(0, 1);
			tempDamHigh = Random(0, 2);

			if (mLevel % 3 == 0)
			{
				tempMagicLow += Random(0, 1);
				tempMagicHigh += Random(0, 1);

				if (debugLog.enableDebugMessages)
				{
					std::cout << "DEBUG MSGS" << std::endl;
					std::cout << "magicLow [" << tempMagicLow << "]" << std::endl;
					std::cout << "magicHigh [" << tempMagicHigh << "]" << std::endl;
				}
				

				increaseSpellManaCost();
			}


			// iterate over all spells and update them, if you have any
			for (int i = 0; i < mMagicSpellsKnown.size(); i++)
			{
				// update spell data
				mMagicSpellsKnown[i].mDamageRange.mLow += tempMagicLow;
				mMagicSpellsKnown[i].mDamageRange.mHigh += tempMagicHigh;

				// low damage can't be higher then high damage
				if (mMagicSpellsKnown[i].mDamageRange.mLow > mMagicSpellsKnown[i].mDamageRange.mHigh)
				{
					mMagicSpellsKnown[i].mDamageRange.mLow = mMagicSpellsKnown[i].mDamageRange.mHigh;
				}
			}


		}
		else if (mClassName == "Cleric")
		{
			tempHp = Random(0, 3);
			tempAc = 1;
			tempAcc = Random(0, 1);
			tempDamLow = Random(0, 1);
			tempDamHigh = Random(0, 1);

			if (mLevel % 3 == 0)
			{
				tempMagicLow += Random(0, 1);
				tempMagicHigh += Random(0, 1);

				if (debugLog.enableDebugMessages)
				{
					std::cout << "DEBUG MSGS" << std::endl;
					std::cout << "magicLow [" << tempMagicLow << "]" << std::endl;
					std::cout << "magicHigh [" << tempMagicHigh << "]" << std::endl;
				}

				increaseSpellManaCost();
			}
			
			// iterate over all spells and update them, if you have any
			for (int i = 0; i < mMagicSpellsKnown.size(); i++)
			{
				
				// update spell data
				mMagicSpellsKnown[i].mDamageRange.mLow += tempMagicLow;
				mMagicSpellsKnown[i].mDamageRange.mHigh += tempMagicHigh;

				// low damage can't be higher then high damage
				if (mMagicSpellsKnown[i].mDamageRange.mLow > mMagicSpellsKnown[i].mDamageRange.mHigh)
				{
					mMagicSpellsKnown[i].mDamageRange.mLow = mMagicSpellsKnown[i].mDamageRange.mHigh;
				}
			}
		}
		else // thief
		{
			tempHp = (mLevel % 2 == 0 ? Random(0, 2) : 0); // if level divided by 2 is 0, add 1 to 4 hps, else 0
			tempAc = Random(0, 1);
			tempAcc = Random(0, 1);

			if (mLevel > 10)
			{
				tempDamLow = Random(0, 3);
				tempDamHigh = Random(1, 4);
			}
			else
			{
				tempDamLow = Random(0, 1);
				tempDamHigh = Random(0, 2);
			}

		}

		// debug class bonuses
		if (debugLog.enableDebugMessages)
		{
			std::cout << "DEBUG MSGS" << std::endl;
			std::cout << "Class Bonuses from leveling" << std::endl;
			std::cout << "Max Hit Points: " << tempHp << std::endl;
			std::cout << "Armor: " << tempAc << std::endl;
			std::cout << "Accuracy: " << tempAcc << std::endl;
			std::cout << "Weapon Damage Low: " << tempDamLow << std::endl;
			std::cout << "Weapon Damage High: " << tempDamHigh << std::endl;
			std::cout << "Magic Damage Low: " << tempMagicLow << std::endl;
			std::cout << "Magic Damage High: " << tempMagicHigh << std::endl;
		}
		


		// update stats
		mMaxHitPoints += tempHp;
		setArmorBonus(tempAc);
		
		mAccuracy += tempAcc;
		setWeaponBonus(tempDamLow, tempDamHigh);

		setMagicBonusDamage(tempMagicLow, tempMagicHigh);


		// update armor & weapon damage & magic damage
		calculateArmor();
		calculateWeaponDamage();
		calculateMagicDamage();


		// give player full hitpoints when they level up.
		mHitPoints = mMaxHitPoints;
		mMagicPoints = mMaxMagicPoints;


		if (debugLog.enableDebugMessages)
		{
			std::cout << "current exp: " << mExpPoints << ", exp needed to level: " << mNextLevelExp << std::endl;
		}
		
		if (debugLog.enableDebugMessages)
		{
			std::cout << "test = " << test << ", true = quit, while loop will loop again" << std::endl;
			test = (mExpPoints > mNextLevelExp);
		}
		
	} 
}

int Player::getLevel()
{
	return mLevel;
}

void Player::rest()
{
	std::cout << "Resting... your health and magic have recovered!" << std::endl;

	mHitPoints = mMaxHitPoints;
	mMagicPoints = mMaxMagicPoints;
}

void Player::viewStates()
{
	std::cout << "PLAYER STATS" << std::endl;
	std::cout << "============" << std::endl;
	std::cout << std::endl;

	std::cout << "Name = " << mName << std::endl;
	std::cout << "Race = " << mRaceName << std::endl;
	std::cout << "Class = " << mClassName << std::endl;
	std::cout << "Accuracy = " << mAccuracy << std::endl;
	std::cout << "Hit Points = " << mHitPoints << std::endl;
	std::cout << "Max Hit Points = " << mMaxHitPoints << std::endl;

	if(mClassName == "Wizard" || mClassName == "Cleric")
	{
		std::cout << "Magic Points = " << mMagicPoints << std::endl;
		std::cout << "Max Magic Points = " << mMaxMagicPoints << std::endl;
	}
	
	std::cout << "XP = " << mExpPoints << std::endl;
	std::cout << "XP for Next Lvl = " << mNextLevelExp << std::endl;
	std::cout << "Level = " << mLevel << std::endl;
	std::cout << "Gold = " << mGold << std::endl;
	std::cout << "# of Healing Potions = " << mPotionsOwned.size() << std::endl;
	std::cout << "Armor = " << mArmor << std::endl;
	std::cout << "Armor Name = " << mArmorWorn.mName << std::endl;
	std::cout << "Armor Value = " << mArmorWorn.mArmorValue << std::endl;
	std::cout << "Weapon Name = " << mWeaponHeld.mName << std::endl;
	std::cout << "Weapon Damage = " << mWeaponHeld.mDamageRange.mLow << " - " << mWeaponHeld.mDamageRange.mHigh << std::endl;
	

	std::cout << std::endl;

	if (mClassName == "Wizard" || mClassName == "Cleric")
	{
		std::cout << "----------------------------" << std::endl;
		std::cout << "-    Known Magic Spells    -" << std::endl;
		std::cout << "----------------------------" << std::endl << std::endl;

		if (mMagicSpellsKnown.size() > 0)
		{
			for (int i = 0; i < mMagicSpellsKnown.size(); i++)
			{
				if (mMagicSpellsKnown[i].mRequiredLevel <= mLevel)
				{
					std::cout << i << ") " << mMagicSpellsKnown[i].mName << " (Low: " << mMagicSpellsKnown[i].mDamageRange.mLow << ", High: " << mMagicSpellsKnown[i].mDamageRange.mHigh << ")" << " <> Spell Cost: " << mMagicSpellsKnown[i].mMagicPointsRequired << std::endl;
				}
				
			}

			std::cout << std::endl;
			std::cout << "----------------------------" << std::endl;
		}
		else
		{
			std::cout << "You have no spells." << std::endl << std::endl;
		}


	}
	
	

	std::cout << "END PLAYER STATS" << std::endl;
	std::cout << "===============" << std::endl;
	std::cout << std::endl;
}

void Player::victory(int xp, int gold)
{


	if (debugLog.enableDebugMessages)
	{
		// TESTING CHANGE ONLY
		//xp *= mRewardModifier;
		//gold *= mRewardModifier;
		// ---=-=-=-=-=================================================================================================================================
		// ---=-=-=-=-=================================================================================================================================
		// ---=-=-=-=-=================================================================================================================================
		// ---=-=-=-=-=================================================================================================================================
	}
	
	xp *= mRewardModifier;
	gold *= mRewardModifier;


	std::cout << "You won the battle!" << std::endl;
	std::cout << "You win " << xp << " experience points!" << std::endl;
	std::cout << "You win " << gold << " gold coins!" << std::endl << std::endl;

	//mExpPoints += xp;
	mExpPoints += xp;
	//mGold += gold;
	mGold += gold;
}

void Player::gameover()
{
	std::cout << "You died in battle..." << std::endl;
	std::cout << std::endl;
	std::cout << "======================" << std::endl;
	std::cout << "=     GAME OVER!    =" << std::endl;
	std::cout << "======================" << std::endl;
	std::cout << "Press 'q' to quit: ";
	char q = 'q';
	std::cin >> q;
	std::cout << std::endl;
}

void Player::displayHitPoints()
{
	std::cout << mName << "'s hitpoints = " << mHitPoints;
}

void Player::displayMagicPoints()
{
	std::cout << ", magicpoints = " << mMagicPoints;
}

Player::~Player()
{

}

