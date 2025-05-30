#include <string>
#include "Magic.h"


spell add_spell(const std::string& name, const int damage_low, const int damage_high, const int required_level, const int magic_points_required)
{
	spell new_spell;

	new_spell.m_name = name;
	new_spell.m_damage_range.m_low = damage_low;
	new_spell.m_damage_range.m_high = damage_high;
	new_spell.m_required_level = required_level;
	new_spell.m_magic_points_required = magic_points_required;

	return new_spell;
}