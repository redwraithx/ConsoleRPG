
#include "Weapon.h"
#include "Range.h"
#include <string>
#include <vector>


Weapon addWeapon(std::string name, int damageLow, int damageHigh, int price)
{
	Weapon newWeapon;

	newWeapon.mName = name;
	newWeapon.mDamageRange.mLow = damageLow;
	newWeapon.mDamageRange.mHigh = damageHigh;
	newWeapon.mSellValue = price;

	return newWeapon;
}

void InitWeapons(std::vector<Weapon>& weaponsContainer, std::string playerClass)
{
	//class type games
	// ---------------
	// fighter weapons
	// ---------------
	// 1) Short Sword
	// 2) Bronze Sword
	// 3) Iron Long Sword
	// 4) Dark Steel Long Sword
	// 5) RuneBlade Bastard Sword
	// 6) Molten RuneBlade Sword of Dragons

	if (playerClass == "Fighter")
	{
		// 1) Short Sword, 
		weaponsContainer.push_back(addWeapon("Short Sword", 1, 8, 0));

		// 2) Bronze Sword
		weaponsContainer.push_back(addWeapon("Bronze Sword", 2, 9, 200));

		// 3) Iron Long Sword
		weaponsContainer.push_back(addWeapon("Iron LongSword", 2, 11, 450));

		// 4) Dark Steel Long Sword
		weaponsContainer.push_back(addWeapon("Dark Steel LongSword", 4, 15, 1000));

		// 5) RuneBlade Bastard Sword
		weaponsContainer.push_back(addWeapon("RuneBlade Bastard Sword", 6, 17, 1500));

		// 6) Molten RuneBlade Sword of Dragons
		weaponsContainer.push_back(addWeapon("Molten RuneBlade sword of Dragons", 8, 20, 2500));

	}
	

	// wizard weapons
	//  -------------
	// 1) worn wooden staff
	// 2) driftwood staff
	// 3) DarkWood rune Staff
	// 4) Staff of the Magi
	// 5) Staff of Ethereal Energy
	// 6) Staff of the Void Dragon

	else if (playerClass == "Wizard")
	{
		
		// 1) worn wooden staff
		weaponsContainer.push_back(addWeapon("Worn Wooden Staff", 1, 4, 0));

		// 2) driftwood staff
		weaponsContainer.push_back(addWeapon("DriftWood Initiate Staff", 2, 4, 200));

		// 3) DarkWood rune Staff
		weaponsContainer.push_back(addWeapon("Darkwood Rune Staff", 2, 5, 450));

		// 4) Staff of the Magi
		weaponsContainer.push_back(addWeapon("Staff of the Magi", 3, 6, 1000));

		// 5) Staff of Ethereal Energy
		weaponsContainer.push_back(addWeapon("Staff of Ethereal Energy", 4, 8, 1500));

		// 6) Staff of the Void Dragon
		weaponsContainer.push_back(addWeapon("Staff of the void Dragon", 5, 10, 2500));

	}

	
	// cleric weapons
	// --------------
	// 1) broken hammer
	// 2) Iron Mace
	// 3) Blackened Mace
	// 4) Firebrand Mace
	// 5) Mace of the Ordained
	// 6) Mace of the Emerald Dragon

	else if (playerClass == "Cleric")
	{
		// 1) broken hammer
		weaponsContainer.push_back(addWeapon("Broken Hammer", 1, 4, 0));

		// 2) Iron Mace
		weaponsContainer.push_back(addWeapon("Iron Mace", 2, 4, 200));

		// 3) Blackened Mace
		weaponsContainer.push_back(addWeapon("Blackened Mace", 2, 5, 450));

		// 4) Firebrand Mace
		weaponsContainer.push_back(addWeapon("Firebrand Blessed Mace", 3, 8, 1000));

		// 5) Mace of the Ordained
		weaponsContainer.push_back(addWeapon("Mace of the Ordained", 4, 12, 1500));

		// 6) Mace of the Emerald Dragon
		weaponsContainer.push_back(addWeapon("Mace of the Emerald Dragon", 5, 15, 2500));

	}


	// thief weapons
	// -------------
	// 1) tarnished dagger
	// 2) iron dagger
	// 3) Twisted Steel Dagger
	// 4) Faded Shadow twin dagger
	// 5) Crystallized Blood Venom Dagger
	// 6) Ancient Dagger of the fallen Hero

	else // thief
	{
		// 1) tarnished dagger
		weaponsContainer.push_back(addWeapon("Tarnished Dagger", 1, 4, 0));

		// 2) iron dagger
		weaponsContainer.push_back(addWeapon("Iron Dagger", 2, 5, 200));

		// 3) Twisted Steel Dagger
		weaponsContainer.push_back(addWeapon("Twisted Steel Dagger", 3, 6, 450));

		// 4) Faded Shadow twin dagger
		weaponsContainer.push_back(addWeapon("Faded Shadow Twin Dagger", 4, 8, 1000));

		// 5) Crystallized Blood Venom Dagger
		weaponsContainer.push_back(addWeapon("Crystallized Blood Venom Dagger", 6, 13, 1500));

		// 6) Ancient Dagger of the fallen Hero
		weaponsContainer.push_back(addWeapon("Ancient Dagger of the fallen Hero", 8, 18, 2500));
	}

}