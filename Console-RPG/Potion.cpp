#include "Potion.h"
#include "Range.h"


Potion addPotion(int low, int high, int price)
{
	Potion newPotion;

	newPotion.mPotionValue.mLow = low;
	newPotion.mPotionValue.mHigh = high;
	newPotion.mSellValue = price;

	return newPotion;
}