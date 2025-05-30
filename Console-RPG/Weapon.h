// Weapon.h

#ifndef WEAPON_H
#define WEAPON_H

#include "Range.h"
#include <string>

struct weapon
{
	std::string m_name;
	range m_damage_range;
	int m_sell_value;

	//Weapon()
	//{}

	//Weapon(std::string name, Range damage, int price) : mName(name), mDamageRange(damage), mSellValue(price)
	//{
	//	/*mName = name;
	//	mDamageRange.mLow = low;
	//	mDamageRange.mHigh = high;
	//	mSellValue = price;*/
	//}
};


#endif // WEAPON_H