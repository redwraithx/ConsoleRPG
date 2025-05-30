#include "Armor.h"
#include <vector>
#include <string>


static armor add_armor(const std::string& name, int armor_selection, const int price)
{
	armor new_armor;

	new_armor.m_name = name;
	new_armor.m_armor_value = armor_selection;
	new_armor.m_sell_value = price;

	return new_armor;
}

void init_armors(std::vector<armor>& armors_container, const std::string& player_class)
{
	// limiting armors to 4 each for now
	if (player_class == "Fighter")
	{
		// 1) Banded Armor
		armors_container.push_back(add_armor("Banded Armor", 3, 200));

		// 2) PlateMail Armor
		armors_container.push_back(add_armor("PlateMail Armor", 6, 500));

		// 3) Champions Full Plate Armor
		armors_container.push_back(add_armor("Champions Full Plate Armor", 10, 1500));

		// 4) Dragon Warlord PlateMail
		armors_container.push_back(add_armor("Dragon Warlord PlateMail", 12, 2500));
	}
	else if (player_class == "Wizard")
	{
		// 1) Cloth Robe
		armors_container.push_back(add_armor("Cloth Robe", 2, 200));

		// 2) Initiate Robe
		armors_container.push_back(add_armor("Initiate Robe", 4, 500));

		// 3) Rune inlaid Robe
		armors_container.push_back(add_armor("Rune Inlaid Robe", 6, 1500));

		// 4) Magi Robe of Knowledge
		armors_container.push_back(add_armor("Magi Robe of Knowledge", 8, 2500));
	}
	else if (player_class == "Cleric")
	{
		// 1) ChainMail Armor
		armors_container.push_back(add_armor("ChainMail Armor", 2, 200));

		// 2) Mithril Armor
		armors_container.push_back(add_armor("Mithril Armor", 5, 500));

		// 3) Enchanted Elven ChainMail
		armors_container.push_back(add_armor("Enchanted Elven ChainMail", 9, 1500));

		// 4) Dragon ScaleMail Armor
		armors_container.push_back(add_armor("Dragon ScaleMail Armor", 11, 2500));
	}
	else // thief
	{
		// 1) Hide Leather Armor
		armors_container.push_back(add_armor("Hide Leather Armor", 3, 200));

		// 2) Shadow Hide Armor
		armors_container.push_back(add_armor("Shadow Hide Armor", 5, 500));

		// 3) Blackened Leather of Shadows
		armors_container.push_back(add_armor("Blackened Leather of Shadows", 8, 1500));

		// 4) Phantom Leather of the Shadow
		armors_container.push_back(add_armor("Phantom Leather of the Shadow", 10, 2500));
	}
}