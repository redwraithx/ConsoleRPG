#ifndef MAGIC_H
#define MAGIC_H

#include "Range.h"


//Spell addSpell(std::string name, int damageLow, int damageHigh, int requiredLevel, int magicPointsRequired);


struct Spell
{
	std::string mName;
	Range mDamageRange;
	int mRequiredLevel;
	int mMagicPointsRequired;
};





#endif // MAGIC_H