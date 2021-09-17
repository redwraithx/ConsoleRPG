#include "Armor.h"
#include <vector>
#include <string>


Armor addArmor(std::string name, int armor, int price)
{
	Armor newArmor;

	newArmor.mName = name;
	newArmor.mArmorValue = armor;
	newArmor.mSellValue = price;

	return newArmor;
}

void InitArmors(std::vector<Armor>& armorsContainer, std::string playerClass)
{
	// limiting armors to 4 each for now
	if (playerClass == "Fighter")
	{
		// 1) Banded Armor
		armorsContainer.push_back(addArmor("Banded Armor", 3, 200));

		// 2) PlateMail Armor
		armorsContainer.push_back(addArmor("PlateMail Armor", 6, 500));

		// 3) Champions Full Plate Armor
		armorsContainer.push_back(addArmor("Champions Full Plate Armor", 10, 1500));

		// 4) Dragon Warlord PlateMail
		armorsContainer.push_back(addArmor("Dragon Warlord PlateMail", 12, 2500));
	}
	else if (playerClass == "Wizard")
	{
		// 1) Cloth Robe
		armorsContainer.push_back(addArmor("Cloth Robe", 2, 200));

		// 2) Initiate Robe
		armorsContainer.push_back(addArmor("Initiate Robe", 4, 500));

		// 3) Rune inlaid Robe
		armorsContainer.push_back(addArmor("Rune Inlaid Robe", 6, 1500));

		// 4) Magi Robe of Knowledge
		armorsContainer.push_back(addArmor("Magi Robe of Knowledge", 8, 2500));
	}
	else if (playerClass == "Cleric")
	{
		// 1) ChainMail Armor
		armorsContainer.push_back(addArmor("ChainMail Armor", 2, 200));

		// 2) Mithril Armor
		armorsContainer.push_back(addArmor("Mithril Armor", 5, 500));

		// 3) Enchanted Elven ChainMail
		armorsContainer.push_back(addArmor("Enchanted Elven ChainMail", 9, 1500));

		// 4) Dragon ScaleMail Armor
		armorsContainer.push_back(addArmor("Dragon ScaleMail Armor", 11, 2500));
	}
	else // thief
	{
		// 1) Hide Leather Armor
		armorsContainer.push_back(addArmor("Hide Leather Armor", 3, 200));

		// 2) Shadow Hide Armor
		armorsContainer.push_back(addArmor("Shadow Hide Armor", 5, 500));

		// 3) Blackened Leather of Shadows
		armorsContainer.push_back(addArmor("Blackened Leather of Shadows", 8, 1500));

		// 4) Phantom Leather of the Shadow
		armorsContainer.push_back(addArmor("Phantom Leather of the Shadow", 10, 2500));
	}
}