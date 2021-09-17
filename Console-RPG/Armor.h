#ifndef ARMOR_H
#define ARMOR_H

#include <string>

struct Armor
{
	std::string mName;
	int mArmorValue;
	int mSellValue; // usable in the store only, to set sale price, but can't be sold back.
};


#endif // ARMOR_H