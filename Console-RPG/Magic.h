#ifndef MAGIC_H
#define MAGIC_H

#include "Range.h"


//Spell addSpell(std::string name, int damageLow, int damageHigh, int requiredLevel, int magicPointsRequired);


struct spell
{
	std::string m_name;
	range m_damage_range;
	int m_required_level;
	int m_magic_points_required;
};





#endif // MAGIC_H