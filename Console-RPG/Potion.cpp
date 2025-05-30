#include "Potion.h"
#include "Range.h"


potion add_potion(const int low, const int high, const int price)
{
	potion new_potion;

	new_potion.m_potion_value.m_low = low;
	new_potion.m_potion_value.m_high = high;
	new_potion.m_sell_value = price;

	return new_potion;
}