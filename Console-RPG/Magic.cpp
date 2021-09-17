#include <string>
#include "Magic.h"


Spell addSpell(std::string name, int damageLow, int damageHigh, int requiredLevel, int magicPointsRequired)
{
	Spell newSpell;

	newSpell.mName = name;
	newSpell.mDamageRange.mLow = damageLow;
	newSpell.mDamageRange.mHigh = damageHigh;
	newSpell.mRequiredLevel = requiredLevel;
	newSpell.mMagicPointsRequired = magicPointsRequired;

	return newSpell;
}