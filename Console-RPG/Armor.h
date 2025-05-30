#ifndef ARMOR_H
#define ARMOR_H

#include <string>

struct armor
{
	std::string m_name;
	int m_armor_value;
	int m_sell_value; // usable in the store only, to set sale price, but can't be sold back.
};


#endif // ARMOR_H