
#include "Weapon.h"
#include "Range.h"
#include <string>
#include <vector>


static weapon add_weapon(const std::string& name, const int damage_low, const int damage_high, const int price)
{
	weapon new_weapon;

	new_weapon.m_name = name;
	new_weapon.m_damage_range.m_low = damage_low;
	new_weapon.m_damage_range.m_high = damage_high;
	new_weapon.m_sell_value = price;

	return new_weapon;
}

void init_weapons(std::vector<weapon>& weapons_container, const std::string& player_class)
{
	//class type games
	// ---------------
	// fighter weapons
	// ---------------
	// 1) Short Sword
	// 2) Bronze Sword
	// 3) Iron-Long Sword
	// 4) Dark Steel Long Sword
	// 5) RuneBlade Bastard Sword
	// 6) Molten RuneBlade Sword of Dragons

	if (player_class == "Fighter")
	{
		// 1) Short Sword, 
		weapons_container.push_back(add_weapon("Short Sword", 1, 8, 0));

		// 2) Bronze Sword
		weapons_container.push_back(add_weapon("Bronze Sword", 2, 9, 200));

		// 3) Iron-Long Sword
		weapons_container.push_back(add_weapon("Iron LongSword", 2, 11, 450));

		// 4) Dark Steel Long Sword
		weapons_container.push_back(add_weapon("Dark Steel LongSword", 4, 15, 1000));

		// 5) RuneBlade Bastard Sword
		weapons_container.push_back(add_weapon("RuneBlade Bastard Sword", 6, 17, 1500));

		// 6) Molten RuneBlade Sword of Dragons
		weapons_container.push_back(add_weapon("Molten RuneBlade sword of Dragons", 8, 20, 2500));

	}
	

	// wizard weapons
	//  -------------
	// 1) worn wooden staff
	// 2) driftwood staff
	// 3) DarkWood rune Staff
	// 4) Staff of the Magi
	// 5) Staff of Ethereal Energy
	// 6) Staff of the Void Dragon

	else if (player_class == "Wizard")
	{
		
		// 1) worn wooden staff
		weapons_container.push_back(add_weapon("Worn Wooden Staff", 1, 4, 0));

		// 2) driftwood staff
		weapons_container.push_back(add_weapon("DriftWood Initiate Staff", 2, 4, 200));

		// 3) DarkWood rune Staff
		weapons_container.push_back(add_weapon("DarkWood Rune Staff", 2, 5, 450));

		// 4) Staff of the Magi
		weapons_container.push_back(add_weapon("Staff of the Magi", 3, 6, 1000));

		// 5) Staff of Ethereal Energy
		weapons_container.push_back(add_weapon("Staff of Ethereal Energy", 4, 8, 1500));

		// 6) Staff of the Void Dragon
		weapons_container.push_back(add_weapon("Staff of the void Dragon", 5, 10, 2500));

	}

	
	// cleric weapons
	// --------------
	// 1) broken hammer
	// 2) Iron Mace
	// 3) Blackened Mace
	// 4) Firebrand Mace
	// 5) Mace of the Ordained
	// 6) Mace of the Emerald Dragon

	else if (player_class == "Cleric")
	{
		// 1) broken hammer
		weapons_container.push_back(add_weapon("Broken Hammer", 1, 4, 0));

		// 2) Iron Mace
		weapons_container.push_back(add_weapon("Iron Mace", 2, 4, 200));

		// 3) Blackened Mace
		weapons_container.push_back(add_weapon("Blackened Mace", 2, 5, 450));

		// 4) Firebrand Mace
		weapons_container.push_back(add_weapon("Firebrand Blessed Mace", 3, 8, 1000));

		// 5) Mace of the Ordained
		weapons_container.push_back(add_weapon("Mace of the Ordained", 4, 12, 1500));

		// 6) Mace of the Emerald Dragon
		weapons_container.push_back(add_weapon("Mace of the Emerald Dragon", 5, 15, 2500));

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
		weapons_container.push_back(add_weapon("Tarnished Dagger", 1, 4, 0));

		// 2) iron dagger
		weapons_container.push_back(add_weapon("Iron Dagger", 2, 5, 200));

		// 3) Twisted Steel Dagger
		weapons_container.push_back(add_weapon("Twisted Steel Dagger", 3, 6, 450));

		// 4) Faded Shadow twin dagger
		weapons_container.push_back(add_weapon("Faded Shadow Twin Dagger", 4, 8, 1000));

		// 5) Crystallized Blood Venom Dagger
		weapons_container.push_back(add_weapon("Crystallized Blood Venom Dagger", 6, 13, 1500));

		// 6) Ancient Dagger of the fallen Hero
		weapons_container.push_back(add_weapon("Ancient Dagger of the fallen Hero", 8, 18, 2500));
	}

}