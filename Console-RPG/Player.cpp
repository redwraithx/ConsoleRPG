#include "Player.h"
#include "Monster.h"
#include "Magic.h"
#include "Random.h"
#include "Potion.h"
// #include "Weapon.h"
// #include "Armor.h"
#include "Debug_Mode.h"

#include <algorithm>
#include <string>
#include <iostream>


// do you want to see debug messages?
//DebugMessages debugLog;





// Prototypes
spell add_spell(const std::string& name, int damage_low, int damage_high, int required_level, int magic_points_required);
potion add_potion(int low, int high, int price);


player::player(): m_magic_points_(0), m_max_magic_points_(0), m_magic_bonus_damage_()
{
	m_name_ = "Default";
	m_race_name_ = "DefaultRace";
	m_class_name_ = "DefaultClass";
	m_accuracy_ = 0;
	m_hit_points_ = 0;
	m_max_hit_points_ = 0;
	m_exp_points_ = 0;
	m_next_level_exp_ = 0;
	m_level_ = 0;
	m_gold_ = 0;
	m_armor_ = 0;

	m_weapon_held_.m_name = "Default Weapon Name";
	m_weapon_held_.m_damage_range.m_low = 0;
	m_weapon_held_.m_damage_range.m_high = 0;

	m_original_weapon_damage_.m_low = 0;
	m_original_weapon_damage_.m_high = 0;

	m_weapon_bonus_.m_low = 0;
	m_weapon_bonus_.m_high = 0;

	m_armor_worn_.m_name = "Default Armor Name";
	m_armor_worn_.m_armor_value = 0;
	m_armor_worn_.m_sell_value = 0;

	m_armor_bonus_ = 0;

	// this should be set to 1 for normal game play
	m_reward_modifier_ = 1;
}

// methods
bool player::is_dead() const
{
	return m_hit_points_ <= 0;
}

std::string player::get_name()
{
	return m_name_;
}

std::string player::get_class()
{
	return m_class_name_;
}

int player::get_gold() const
{
	return m_gold_;
}

void player::buy(const int cost)
{
	m_gold_ -= cost;
}

void player::equip_armor(const armor& new_armor)
{
	// remove old armor value from armor
	m_armor_ -= m_armor_worn_.m_armor_value;

	// wear new armor
	//mArmorWorn.mName = newArmor.mName;
	//mArmorWorn.mArmorValue = newArmor.mArmorValue;
	//mArmorWorn.mSellValue = newArmor.mSellValue;

	if (debug_log.enable_debug_messages)
	{
		std::cout << "debug msg - old armor" << "\n";
		std::cout << "new armor: " << m_armor_worn_.m_name << "\n";
		std::cout << "new armor AC: " << m_armor_worn_.m_armor_value << "\n";
		std::cout << "new armor price: " << m_armor_worn_.m_sell_value << "\n";
	}
	
	m_armor_worn_ = new_armor;

	if (debug_log.enable_debug_messages)
	{
		std::cout << "debug msg - new armor" << "\n";
		std::cout << "new armor: " << m_armor_worn_.m_name << "\n";
		std::cout << "new armor AC: " << m_armor_worn_.m_armor_value << "\n";
		std::cout << "new armor price: " << m_armor_worn_.m_sell_value << "\n";
	}
	

	// add new armor value to armor
	m_armor_ += m_armor_worn_.m_armor_value;
}

void player::equip_weapon(const weapon& new_weapon)
{
	// assign a new weapon.
	m_weapon_held_ = new_weapon;

	// update original damage as for a new weapon.
	set_original_weapon_values(new_weapon.m_damage_range);
}

int player::get_original_weapon_value(const bool get_low_damage) const
{
	if (get_low_damage)
		return m_original_weapon_damage_.m_low;
	else
		return m_original_weapon_damage_.m_high;
}

int player::get_armor() const
{
	return m_armor_;
}

void player::set_armor_bonus(const int value)
{
	m_armor_bonus_ += value;
}

void player::calculate_weapon_damage()
{
	const int value1 = m_original_weapon_damage_.m_low + m_weapon_bonus_.m_low;
	const int value2 = m_original_weapon_damage_.m_high + m_weapon_bonus_.m_high;

	if (value1 > value2)
	{
		m_weapon_held_.m_damage_range.m_low = value2;
		m_weapon_held_.m_damage_range.m_high = value1;
	}
	else
	{
		m_weapon_held_.m_damage_range.m_low = value1;
		m_weapon_held_.m_damage_range.m_high = value2;
	}
	
}

void player::set_weapon_bonus(const int low, const int high)
{
	m_weapon_bonus_.m_low += low;
	m_weapon_bonus_.m_high += high;
}

int player::get_weapon_bonus(const bool get_low_damage) const
{
	if (get_low_damage)
		return m_weapon_bonus_.m_low;
	
	return m_weapon_bonus_.m_high;
}

void player::set_original_weapon_values(const range& weapon_damage)
{
	m_original_weapon_damage_.m_low = weapon_damage.m_low;
	m_original_weapon_damage_.m_high = weapon_damage.m_high;
}

void player::calculate_armor()
{
	m_armor_ = m_armor_bonus_ + m_armor_worn_.m_armor_value;
}


void player::set_magic_bonus_damage(const int low, const int high)
{
	m_magic_bonus_damage_.m_low += low;
	m_magic_bonus_damage_.m_high += high;
}

void player::set_original_magic_damage(const range magic_damage)
{
	//for (int i = 0; i < mOriginalMagicDamage.size(); i++)
	//{
	
	m_original_magic_damage_.push_back(magic_damage);

	/*	mOriginalMagicDamage[spellNumber].mLow = magicDamage.mLow;
		mOriginalMagicDamage[spellNumber].mHigh = magicDamage.mHigh;*/
	//}
	
}

void player::increase_spell_mana_cost()
{
	//for (int i = 0; i < m_magic_spells_known_.size(); i++)
	for (auto& i : m_magic_spells_known_)
	{
		if (get_level() % 2 == 0)
		{
			i.m_magic_points_required++;
		}
	}
}

void player::calculate_magic_damage()
{
	if (m_class_name_ == "Fighter" || m_class_name_ == "Thief")
		return;

	//if (m_magic_spells_known_.size() < 1)
	if (m_magic_spells_known_.empty())
	{
		std::cout << "It seems you are not a fighter or thief but still have no spells.... log this bug." << "\n";

		return;
	}
		


	// iterate over all the spells and add the bonus to it
	for (size_t i = 0; i < m_magic_spells_known_.size(); i++)
	{
		if (debug_log.enable_debug_messages)
		{
			std::cout << "Debug messages" << "\n";
			std::cout << "magic spells known #" << i << ": " << m_magic_spells_known_[i].m_name << "\n";
			std::cout << "Magic low bonus " << i << ": " << m_magic_bonus_damage_.m_low << "\n";
			std::cout << "Magic high bonus " << i << ": " << m_magic_bonus_damage_.m_high << "\n";
			std::cout << "original low damage " << i << ": " << m_original_magic_damage_[i].m_low << "\n";
			std::cout << "original high damage " << i << ": " << m_original_magic_damage_[i].m_high << "\n";
		}

		if (m_magic_spells_known_[i].m_required_level <= m_level_)
		{
			//std::cout << i << ") " << mMagicSpellsKnown[i].mName << " (Low: " << mMagicSpellsKnown[i].mDamageRange.mLow << ", High: " << mMagicSpellsKnown[i].mDamageRange.mHigh << ")" << " <> Spell Cost: " << mMagicSpellsKnown[i].mMagicPointsRequired << "\n";

			m_magic_spells_known_[i].m_damage_range.m_low = m_magic_bonus_damage_.m_low + m_original_magic_damage_[i].m_low;
			m_magic_spells_known_[i].m_damage_range.m_high = m_magic_bonus_damage_.m_high + m_original_magic_damage_[i].m_high;

		}

	}
}


void player::take_damage(const int damage)
{
	m_hit_points_ -= damage;
}

void player::heal_damage(const int heal_value)
{
	m_hit_points_ += heal_value;

	/*if(m_hit_points_ > m_max_hit_points_)
	{
		m_hit_points_ = m_max_hit_points_;
	}*/
	
	m_hit_points_ = std::min(m_hit_points_, m_max_hit_points_);
}

int player::use_potion(const potion current_potion)
{
	// heal player
	return (random(current_potion.m_potion_value));
}

bool player::add_new_potion(const potion new_potion)
{
	if (get_potion_count() > 3) // max # of potions you can carry
	{
		return false;
	}


	m_potions_owned_.push_back(new_potion);

	return true;
}

size_t player::get_potion_count() const
{
	return m_potions_owned_.size();
}

void player::create_class()
{
	std::cout << "CHARACTER CLASS GENERATION" << "\n";
	std::cout << "==========================" << "\n";

	// input character's name
	std::cout << "Enter your character's name: ";
	std::getline(std::cin, m_name_);

	
	player_class_selection();
	
	std::cout << "\n";

	player_race_selection();
	


	/////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////

	// give the player 1 healing potion to start with
	const potion new_potion = add_potion(3, 8, 30); // low 3, high 8, price 30
	m_potions_owned_.push_back(new_potion);
}

void player::player_class_selection()
{
	// character selection.
	std::cout << "Please select a character class number..." << "\n";
	std::cout << "1) Fighter 2) Wizard 3) Cleric 4) Thief 5) Random Class: ";
	int character_num = 1;
	std::cin >> character_num;

	if(character_num == 5)
	{
		character_num = random(1, 4);
	}

	switch (character_num)
	{
	case 1:
		// fighter
		m_class_name_ = "Fighter";
		m_accuracy_ = 10;
		m_hit_points_ = 20;
		m_max_hit_points_ = 20;
		m_magic_points_ = 0;
		m_max_magic_points_ = 0;
		m_exp_points_ = 0;
		m_next_level_exp_ = 1000;
		m_level_ = 1;
		m_gold_ = 0;
		m_armor_ = 4;

		// weapon
		m_weapon_held_.m_name = "Long Sword";
		m_weapon_held_.m_damage_range.m_low = 1;
		m_weapon_held_.m_damage_range.m_high = 8;

		set_original_weapon_values(m_weapon_held_.m_damage_range);

		// armor
		m_armor_worn_.m_name = "Cloth Rags";
		m_armor_worn_.m_armor_value = 0;
		m_armor_worn_.m_sell_value = 0;

		m_armor_bonus_ = m_armor_;

		break;
	case 2:
		// wizard
		m_class_name_ = "Wizard";
		m_accuracy_ = 5;
		m_hit_points_ = 10;
		m_max_hit_points_ = 10;
		m_magic_points_ = 10;
		m_max_magic_points_ = 10;
		m_exp_points_ = 0;
		m_next_level_exp_ = 1000;
		m_level_ = 1;
		m_gold_ = 0;
		m_armor_ = 1;

		// weapon
		m_weapon_held_.m_name = "Staff";
		m_weapon_held_.m_damage_range.m_low = 1;
		m_weapon_held_.m_damage_range.m_high = 4;

		set_original_weapon_values(m_weapon_held_.m_damage_range);

		// armor
		m_armor_worn_.m_name = "Cloth Rags";
		m_armor_worn_.m_armor_value = 0;
		m_armor_worn_.m_sell_value = 0;

		m_armor_bonus_ = m_armor_;

		// add wizard spells
		m_magic_spells_known_.push_back(add_spell("Magic Missile", 20, 100, 1, 2));
		m_magic_spells_known_.push_back(add_spell("Ice Blast", 4, 14, 3, 4));
		m_magic_spells_known_.push_back(add_spell("Fire Blast", 6, 20, 5, 6));
		m_magic_spells_known_.push_back(add_spell("Fire Ball", 1, 34, 8, 8));
		m_magic_spells_known_.push_back(add_spell("Lightning Flash", 10, 40, 12, 10));
		m_magic_spells_known_.push_back(add_spell("Lightning Blast", 20, 60, 20, 12));

		//for (int i = 0; i < m_magic_spells_known_.size(); i++)
		for (const auto& i : m_magic_spells_known_)
		{
			set_original_magic_damage(i.m_damage_range);
		}

		

		break;
	case 3:
		// cleric
		m_class_name_ = "Cleric";
		m_accuracy_ = 8;
		m_hit_points_ = 15;
		m_max_hit_points_ = 15;
		m_magic_points_ = 6;
		m_max_magic_points_ = 6;
		m_exp_points_ = 0;
		m_next_level_exp_ = 1000;
		m_level_ = 1;
		m_gold_ = 0;
		m_armor_ = 3;

		// weapon
		m_weapon_held_.m_name = "Flail";
		m_weapon_held_.m_damage_range.m_low = 1;
		m_weapon_held_.m_damage_range.m_high = 6;

		set_original_weapon_values(m_weapon_held_.m_damage_range);

		// armor
		m_armor_worn_.m_name = "Cloth Rags";
		m_armor_worn_.m_armor_value = 0;
		m_armor_worn_.m_sell_value = 0;

		m_armor_bonus_ = m_armor_;

		// add Cleric spells
		m_magic_spells_known_.push_back(add_spell("Minor Healing", 1, 8, 1, 2));
		m_magic_spells_known_.push_back(add_spell("Healing", 6, 16, 6, 5));
		m_magic_spells_known_.push_back(add_spell("Major Healing", 12, 26, 10, 8));
		m_magic_spells_known_.push_back(add_spell("Massive Healing", 22, 46, 16, 14));
		m_magic_spells_known_.push_back(add_spell("Full Healing", 80, 100, 22, 25));

		// could use a for loop to set all spells at once, even if you add more
		//for (int i = 0; i < m_magic_spells_known_.size(); i++)
		for (const auto& i : m_magic_spells_known_)
		{
			set_original_magic_damage(i.m_damage_range);
		}

		break;
	default:
		// thief
		m_class_name_ = "Thief";
		m_accuracy_ = 7;
		m_hit_points_ = 12;
		m_max_hit_points_ = 12;
		m_magic_points_ = 0;
		m_max_magic_points_ = 0;
		m_exp_points_ = 0;
		m_next_level_exp_ = 1000;
		m_level_ = 1;
		m_gold_ = 0;
		m_armor_ = 2;

		// weapon
		m_weapon_held_.m_name = "Tarnished Dagger";
		m_weapon_held_.m_damage_range.m_low = 1;
		m_weapon_held_.m_damage_range.m_high = 4;

		set_original_weapon_values(m_weapon_held_.m_damage_range);

		// armor
		m_armor_worn_.m_name = "Cloth Rags";
		m_armor_worn_.m_armor_value = 0;
		m_armor_worn_.m_sell_value = 0;

		m_armor_bonus_ = m_armor_;

		break;

	}
}

void player::player_race_selection()
{
	// race selection
	std::cout << "Race Selection" << "\n";
	std::cout << "--------------" << "\n";
	std::cout << "1) Human, 2) Elf, 3) Dwarf, 4) Gnome 5) Random Race" << "\n";
	std::cout << "Select your race number: ";

	int selection = 1;
	std::cin >> selection;

	if(selection == 5)
	{
		selection = random(1, 4);
	}


	int temp_hp = 0, temp_acc = 0, temp_magic_points = 0;

	switch (selection) // 
	{
	case 1: // human
		m_race_name_ = "Human";

		// pro   +(1-3) hps
		temp_hp += random(1, 5);

		// con   -(1-2) acc
		temp_acc -= random(1, 2);

		if (m_class_name_ == "Wizard" || m_class_name_ == "Cleric")
		{
			temp_magic_points += random(0, 3);
		}

		break;

	case 2: // elf
			// pro   +(1-2) acc

		m_race_name_ = "Elf";
		
		temp_acc += random(1, 4);

		// con   -(1-2) hps
		temp_hp -= random(1, 2);

		if (m_class_name_ == "Wizard" || m_class_name_ == "Cleric")
		{
			temp_magic_points += random(1, 15);
		}

		break;

	case 3: // dwarf
			// pro   +(2-6) hps

		m_race_name_ = "Dwarf";

		temp_hp += random(2, 8);

		// con   -(1-2) acc
		temp_acc -= random(1, 2);

		if (m_class_name_ == "Wizard" || m_class_name_ == "Cleric")
		{
			temp_magic_points += random(0, 6);
		}

		break;

	default: // gnome
			 // pro   +(1-4) acc

		m_race_name_ = "Gnome";

		temp_acc += random(1, 8);

		// con   -(1-2) hp
		temp_hp -= random(1, 2);

		if (m_class_name_ == "Wizard" || m_class_name_ == "Cleric")
		{
			temp_magic_points += random(0, 4);
		}

		break;
	}

	if (debug_log.enable_debug_messages)
	{
		std::cout << "DEBUG messages" << "\n";
		std::cout << "Hp before: " << m_max_hit_points_ << "\n";
		std::cout << "Acc before: " << m_accuracy_ << "\n";
		std::cout << "Magic Points before: " << m_magic_points_ << "\n";
	}


	m_max_hit_points_ += temp_hp;
	m_hit_points_ = m_max_hit_points_;
	m_accuracy_ += temp_acc;
	m_max_magic_points_ += temp_magic_points;

	if (debug_log.enable_debug_messages)
	{
		std::cout << "DEBUG messages" << "\n";
		std::cout << "Hp after: " << m_hit_points_ << "\n";
		std::cout << "Acc after: " << m_accuracy_ << "\n";
		std::cout << "Magic Points After: " << m_max_magic_points_ << "\n";
		std::cout << "hpBonus: " << temp_hp << "\n";
		std::cout << "accBonus: " << temp_acc << "\n";
		std::cout << "Magic points bonus: " << temp_magic_points << "\n";
	}


	std::cout << "\n";
}

bool player::attack(Monster* monster[])
{
	int selection = 1;
	std::cout << "1) Attack, ";
	
	// check for caster status
	if (m_class_name_ == "Wizard" || m_class_name_ == "Cleric")
	{
		std::cout << "2) use Spells, ";
	}

	// check if user has any potions to use
	if (!m_potions_owned_.empty())
	{
		std::cout << "3) use Potion, ";
	}
	
	std::cout << "4) Run: ";
	std::cin >> selection;

	std::cout << "\n";



	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (debug_log.enable_debug_messages)
	{
		std::cout << "is monster[1] alive and can it attack, else all monsters are dead and return" << "\n";
	}

	const bool are_there_two_monsters = (monster[1] != nullptr ? true : false);

	int monster_to_attack = 0;

	if (!monster[monster_to_attack]->is_dead())
	{
		////////////////////////////////////////////////////////////
		// player attacks first monster debug msg
		if (debug_log.enable_debug_messages)
		{
			std::cout << "Player is attacking monster 1" << "\n";
			std::cout << "monsterToAttack: " << monster_to_attack << "\n";
		}
	}
	else if (are_there_two_monsters && monster[monster_to_attack]->is_dead() && !monster[monster_to_attack + 1]->is_dead())
	{
		monster_to_attack = 1;

		/////////////////////////////////////////////////////////////
		// player attacks 2nd monster debug msg
		if (debug_log.enable_debug_messages)
		{
			std::cout << "Player is attacking monster 2" << "\n";
			std::cout << "monsterToAttack: " << monster_to_attack << "\n";
		}
	}
	else
	{
		/////////////////////////////////////////////////////////////
		// debug msg
		if (debug_log.enable_debug_messages)
		{
			std::cout << "Player isn't attacking at all.... else is returning from battle" << "\n";
			std::cout << "M1: " << monster[0] << "\n";
			std::cout << "M2: " << monster[1] << "\n";
		}

		return false;
	}

	//if (monster[1] != 0 && monster[0]->isDead())
	//{
	//	if (!monster[0]->isDead())
	//	{
	//		monsterToAttack = 1;
	//	}
	//	else
	//	{
	//		// monsters are dead
	//		return true;
	//	}
	//	
	//}

	////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////



	switch (selection)
	{
	case 1:
		// Attack
		std::cout << "You attack an " << monster[monster_to_attack]->get_name() << " with a " << m_weapon_held_.m_name << "\n";

		if (random(0, 20) < m_accuracy_)
		{
			const int damage = random(m_weapon_held_.m_damage_range);

			const int total_damage = damage - monster[monster_to_attack]->get_armor();

			if (total_damage <= 0)
			{
				std::cout << "Your attack failed to penetrate the armor. " << "\n";
			}
			else
			{
				std::cout << "You attack for " << total_damage << " damage!" << "\n";

				// subtract from monster's hit points.
				monster[monster_to_attack]->take_damage(total_damage);
			}
		}
		else
		{
			std::cout << "You miss!" << "\n";
		}

		std::cout << "\n";

		break;

	case 2:
	{
		if (m_class_name_ == "Fighter" || m_class_name_ == "Thief")
		{
			std::cout << "It seems you haven't quite mastered the magical arts... Choose another selection" << "\n";

			break;
		}

		// else you have magic to use
		std::cout << "Magical spells you currently have." << "\n";
		std::cout << "----------------------------------" << "\n";

		// list what spells this player has as choices.
		size_t counter = 0;
		for (size_t i = 0; i < m_magic_spells_known_.size(); i++)
		{
			// do we have the level to use the spell?
			if (m_magic_spells_known_[counter].m_required_level <= m_level_)
			{
				std::cout << "- " << counter + 1 << ") " << m_magic_spells_known_[counter].m_name << " - cost: " << m_magic_spells_known_[counter].m_magic_points_required << "\n";
				
				counter++;
			}

			
		}
			
		std::cout << "- " << (counter + 1) << ") Cancel Casting Spell\n";
		std::cout << "----------------------------------" << "\n" << "\n";

		std::cout << "Enter the number of the spell you wish to cast: ";

		// get selection from user
		size_t spell_selection = 1;

		std::cin >> spell_selection;
		
		spell_selection -= 1; // adjust for 0 based index
			
		// take action IF user has enough mana to cast the spell... else loop out and try again
		if (!m_magic_spells_known_.empty() && spell_selection == (get_number_of_owned_spells())) // cancel spell casting	
		{
			std::cout << "You cancel casting a spell." << "\n";
		}
		else if (  (spell_selection < 0 || spell_selection > m_magic_spells_known_.size() ) || m_magic_spells_known_[spell_selection].m_required_level > m_level_)
		{
			std::cout << "You dont have a spell for [" << spell_selection << "]. Try selecting a spell you can use!" << "\n";
		}
		else if (m_magic_points_ >= m_magic_spells_known_[spell_selection].m_magic_points_required && m_magic_spells_known_[spell_selection].m_required_level <= m_level_)
		{
			if (m_class_name_ == "Wizard")
			{
				// cast the spell, damages monster
				const int spell_damage = random(m_magic_spells_known_[spell_selection].m_damage_range);
				monster[monster_to_attack]->take_damage(spell_damage);

				std::cout << "You hit the " << monster[monster_to_attack]->get_name() << ", with the " << m_magic_spells_known_[spell_selection].m_name << " spell. Dealing " << spell_damage << " magical damage to them." << "\n";

				// update mMagicPoints
				m_magic_points_ -= m_magic_spells_known_[spell_selection].m_magic_points_required;
			}
			else // cleric
			{
				// cast the spell, damages monster
				const int healing_amount = random(m_magic_spells_known_[spell_selection].m_damage_range);
				heal_damage(healing_amount);



				std::cout << "Casting the " << m_magic_spells_known_[spell_selection].m_name << " spell. You heal yourself for " << healing_amount << " hit point(s)." << "\n";

				// update mMagicPoints
				m_magic_points_ -= m_magic_spells_known_[spell_selection].m_magic_points_required;
			}



		}
		else
		{
			std::cout << "You dont have enough \"Magic Points\" to cast " << m_magic_spells_known_[spell_selection].m_name << "\n";
			//std::cout << "Make another selection." << "\n";

		}


		std::cout << "\n";

		break;
	}
	case 3:
	{
		if (debug_log.enable_debug_messages)
		{
			std::cout << "DEBUG MSG POTION COUNT" << "\n";
			std::cout << "potions before: " << m_potions_owned_.size() << "\n";
		}



		if (m_potions_owned_.empty())
		{
			std::cout << "You look for a potion, but you have none it seems." << "\n" << "\n";

			break; // you have no potions
		}


		if (m_hit_points_ == m_max_hit_points_)
		{
			std::cout << "You have full hit points, you dont need to use that potion right now." << "\n" << "\n";

			break;
		}
		
		potion testPotion = m_potions_owned_[0];
		m_potions_owned_.pop_back();

		int healPlayer = use_potion(testPotion);

		m_hit_points_ += healPlayer;

		/*if (m_hit_points_ > m_max_hit_points_)
		{
			m_hit_points_ = m_max_hit_points_;
		}*/
		m_hit_points_ = std::min(m_hit_points_, m_max_hit_points_);

		if (debug_log.enable_debug_messages)
		{
			std::cout << "DEBUG MSG POTION COUNT" << "\n";
			std::cout << "potions after: " << m_potions_owned_.size() << "\n";
		}
		

		break;
	}
	case 4: // run away
	{
		int roll; // = random(1, 4);

		if (m_class_name_ == "Thief")
		{
			// 50% chance of being able to run if you're a sneaky thief
			roll = random(2, 4);

			if (debug_log.enable_debug_messages)
			{
				std::cout << "DEBUG MSG" << "\n";
				std::cout << "run roll thief: " << roll << "\n";
			}

			if (roll == 1 || roll == 2)
			{
				std::cout << "You run away!" << "\n";

				return true; // return out of the function
			}
			
		}
		else
		{
			// 25% chance of being able to run.
			roll = random(1, 4);

			if (roll == 1)
			{
				std::cout << "You run away!" << "\n";

				return true; // return out of the function
			}
		}


		std::cout << "You could not escape!" << "\n";
		break;
			
	} // end case 4
	default:
		break;
	}// end switch

	return false;
}


//bool Player::attack(Monster& monster)
//{
//	int selection = 1;
//	std::cout << "1) Attack, ";
//
//	// check for caster status
//	if (mClassName == "Wizard" || mClassName == "Cleric")
//	{
//		std::cout << "2) use Spells, ";
//	}
//
//	// check if user has any potions to use
//	if (mPotionsOwned.size() > 0)
//	{
//		std::cout << "3) use Potion, ";
//	}
//
//	std::cout << "4) Run: ";
//	std::cin >> selection;
//
//	std::cout << "\n";
//
//
//	switch (selection)
//	{
//	case 1:
//		// Attack
//		std::cout << "You attack an " << monster.getName() << " with a " << mWeaponHeld.mName << "\n";
//
//		if (Random(0, 20) < mAccuracy)
//		{
//			int damage = Random(mWeaponHeld.mDamageRange);
//
//			int totalDamage = damage - monster.getArmor();
//
//			if (totalDamage <= 0)
//			{
//				std::cout << "Your attack failed to penetrate the armor. " << "\n";
//			}
//			else
//			{
//				std::cout << "You attack for " << totalDamage << " damage!" << "\n";
//
//				// subtract from monster's hit points.
//				monster.takeDamage(totalDamage);
//			}
//		}
//		else
//		{
//			std::cout << "You miss!" << "\n";
//		}
//
//		std::cout << "\n";
//
//		break;
//
//	case 2:
//	{
//		if (mClassName == "Fighter" || mClassName == "Thief")
//		{
//			std::cout << "It seems you haven't quite mastered the magical arts... choose another selection" << "\n";
//
//			break;
//		}
//
//		// else you have magic to use
//		std::cout << "Magical spells you currently have." << "\n";
//		std::cout << "----------------------------------" << "\n";
//
//		// list what spells this player has as choices.
//		for (int i = 0; i < mMagicSpellsKnown.size(); i++)
//		{
//			// do we have the level to use the spell?
//			if (mMagicSpellsKnown[i].mRequiredLevel <= mLevel)
//			{
//				std::cout << "- " << i << ") " << mMagicSpellsKnown[i].mName << " ";
//			}
//
//
//		}
//
//		std::cout << "\n";
//		std::cout << "----------------------------------" << "\n" << "\n";
//
//		std::cout << "Enter the number of the spell you wish to cast: ";
//
//		// get selection from user
//		int spellSelection = 1;
//
//		std::cin >> spellSelection;
//
//
//
//		// take action IF user has enough mana to cast the spell... else loop out and try again
//		if ((spellSelection < 0 || spellSelection > mMagicSpellsKnown.size()) || mMagicSpellsKnown[spellSelection].mRequiredLevel > mLevel)
//		{
//			std::cout << "You don't have a spell for [" << spellSelection << "]. Try selecting a spell you can use!" << "\n";
//		}
//		else if (mMagicPoints >= mMagicSpellsKnown[spellSelection].mMagicPointsRequired && mMagicSpellsKnown[spellSelection].mRequiredLevel <= mLevel)
//		{
//			if (mClassName == "Wizard")
//			{
//				// cast the spell, damages monster
//				int spellDamage = Random(mMagicSpellsKnown[spellSelection].mDamageRange);
//				monster.takeDamage(spellDamage);
//
//				std::cout << "You hit the " << monster.getName() << ", with the " << mMagicSpellsKnown[spellSelection].mName << " spell. Dealing " << spellDamage << " magical damage to them." << "\n";
//
//				// update mMagicPoints
//				mMagicPoints -= mMagicSpellsKnown[spellSelection].mMagicPointsRequired;
//			}
//			else // cleric
//			{
//				// cast the spell, damages monster
//				int healingAmount = Random(mMagicSpellsKnown[spellSelection].mDamageRange);
//				healDamage(healingAmount);
//
//
//
//				std::cout << "Casting the " << mMagicSpellsKnown[spellSelection].mName << " spell. You heal yourself for " << healingAmount << " damage." << "\n";
//
//				// update mMagicPoints
//				mMagicPoints -= mMagicSpellsKnown[spellSelection].mMagicPointsRequired;
//			}
//
//
//
//		}
//		else
//		{
//			std::cout << "You don't have enough \"Magic Points\" to cast " << mMagicSpellsKnown[spellSelection].mName << "\n";
//			//std::cout << "Make another selection." << "\n";
//
//		}
//
//
//		std::cout << "\n";
//
//		break;
//	}
//	case 3:
//	{
//		if (debugLog.enableDebugMessages)
//		{
//
//		}
//		std::cout << "DEBUG MSG POTION COUNT" << "\n";
//		std::cout << "potions before: " << mPotionsOwned.size() << "\n";
//
//
//		if (mPotionsOwned.size() == 0)
//		{
//			std::cout << "You look for a potion, but you have none it seems." << "\n" << "\n";
//
//			break; // you have no potions
//		}
//
//
//		if (mHitPoints == mMaxHitPoints)
//		{
//			std::cout << "You have full hit points, you don't need to use that potion right now." << "\n" << "\n";
//
//			break;
//		}
//
//		Potion testPotion = mPotionsOwned[0];
//		mPotionsOwned.pop_back();
//
//		int healPlayer = usePotion(testPotion);
//
//		mHitPoints += healPlayer;
//
//		if (mHitPoints > mMaxHitPoints)
//		{
//			mHitPoints = mMaxHitPoints;
//		}
//
//		if (debugLog.enableDebugMessages)
//		{
//			std::cout << "DEBUG MSG POTION COUNT" << "\n";
//			std::cout << "potions after: " << mPotionsOwned.size() << "\n";
//		}
//
//
//		break;
//	}
//	case 4: // run away
//	{
//		int roll = Random(1, 4);
//
//		if (mClassName == "Thief")
//		{
//			// 50% chance of being able to run, if you're a sneaky thief
//			roll = Random(2, 4);
//
//			if (debugLog.enableDebugMessages)
//			{
//				std::cout << "DEBUG MSG" << "\n";
//				std::cout << "run roll thief: " << roll << "\n";
//			}
//
//		}
//		else
//		{
//			// 25% chance of being able to run.
//			roll = Random(1, 4);
//		}
//
//
//		if ((roll == 1 || roll == 2) && mClassName == "Thief")
//		{
//			std::cout << "You run away!" << "\n";
//
//			return true; // return out of the function
//		}
//		else if (roll == 1)
//		{
//			std::cout << "You run away!" << "\n";
//
//			return true; // return out of the function
//		}
//		else
//		{
//			std::cout << "You could not escape!" << "\n";
//			break;
//		}
//	} // end case 4
//	}// end switch
//
//	return false;
//}


void player::level_up()
{
	if (debug_log.enable_debug_messages)
	{
		if (m_exp_points_ > m_next_level_exp_)
			std::cout << "you can level now" << "\n";
	}
	

	bool test = (m_exp_points_ > m_next_level_exp_);
	{
		if (debug_log.enable_debug_messages)
		{
			///std::cout.setf(std::cout.boolalpha);
			std::cout.setf(std::ostream::boolalpha);
			std::cout << "test = " << test << ", true means test works, while loop does not." << "\n";
		}
	}


	while(m_exp_points_ > m_next_level_exp_)
	{
		std::cout << "You gained a level!" << "\n";

		// increment level
		m_level_++;

		// set experience points required for the next level
		m_next_level_exp_ = m_level_ * m_level_ * 1000; // need to modify this to use better leveling add later

		// increase stats randomly
		if (m_level_ > 20)
		{
			m_accuracy_ += random(1, 3);
			m_max_hit_points_ += random(5, 12);
			set_armor_bonus(random(1, 2));
		}
		else if (m_level_ > 10)
		{
			m_accuracy_ += random(1, 3);
			m_max_hit_points_ += random(2, 9);
			set_armor_bonus(random(1, 2));
		}
		else
		{
			m_accuracy_ += random(1, 3);
			m_max_hit_points_ += random(2, 6);
			set_armor_bonus(random(1, 2));
		}

		// class bonus stats
		int temp_ac, temp_hp, temp_acc, temp_dam_low, temp_dam_high, temp_magic_low = 0, temp_magic_high = 0;


		if (m_class_name_ == "Fighter")
		{
			temp_hp = random(1, 3);
			temp_ac = random(0, 4);
			temp_acc = (m_level_ % 4 == 0 ? random(1, 3) : 0); // if the level divided by 4 is 0, add 1 else adding 0

			if (m_level_ > 10)
			{
				temp_dam_low = random(0, 2);
				temp_dam_high = random(1, 4);
			}
			else
			{
				temp_dam_low = random(0, 1);
				temp_dam_high = random(0, 2);
			}
			
			//tempMagicLow = 0;
			//tempMagicHigh = 0;
		}
		else if (m_class_name_ == "Wizard")
		{
			temp_hp = (m_level_ % 2 == 0 ? random(0, 2) : 0); // if the level divided by 2 is 0, add 1 to 3 hps else 0
			temp_ac = (m_level_ % 3 == 0 ? random(1, 2) : 0); // if the level divided by 3 is 0, add 1 ac point else 0
			temp_acc = random(0, 3);
			temp_dam_low = random(0, 2);
			temp_dam_high = random(0, 3);

			m_max_magic_points_ += random(3, 8);
			m_magic_points_ = m_max_magic_points_; // reset magic points to max

			if (m_level_ % 3 == 0)
			{
				temp_magic_low += random(0, 3);
				temp_magic_high += random(1, 4);

				if (debug_log.enable_debug_messages)
				{
					std::cout << "DEBUG messages" << "\n";
					std::cout << "magic damage Low [" << temp_magic_low << "]" << "\n";
					std::cout << "magic damage High [" << temp_magic_high << "]" << "\n";
				}
				

				increase_spell_mana_cost();
			}


			// iterate over all spells and update them if you have any
			for (auto& i : m_magic_spells_known_)
			{
				// update spell data
				i.m_damage_range.m_low += temp_magic_low;
				i.m_damage_range.m_high += temp_magic_high;

				// low damage can't be higher than high damage
				/*if (m_magic_spells_known_[i].m_damage_range.m_low > m_magic_spells_known_[i].m_damage_range.m_high)
				{
					m_magic_spells_known_[i].m_damage_range.m_low = m_magic_spells_known_[i].m_damage_range.m_high;
				}*/
				i.m_damage_range.m_low = std::min(i.m_damage_range.m_low, i.m_damage_range.m_high);
			}


		}
		else if (m_class_name_ == "Cleric")
		{
			temp_hp = random(0, 3);
			temp_ac = random(1, 3);
			temp_acc = random(0, 1);
			temp_dam_low = random(0, 1);
			temp_dam_high = random(0, 3);

			m_max_magic_points_ += random(1, 6);
			m_magic_points_ = m_max_magic_points_; // reset magic points to max

			if (m_level_ % 3 == 0)
			{
				temp_magic_low += random(0, 2);
				temp_magic_high += random(0, 4);

				if (debug_log.enable_debug_messages)
				{
					std::cout << "DEBUG messages" << "\n";
					std::cout << "magicLow [" << temp_magic_low << "]" << "\n";
					std::cout << "magicHigh [" << temp_magic_high << "]" << "\n";
				}

				increase_spell_mana_cost();
			}
			
			// iterate over all spells and update them if you have any
			//for (int i = 0; i < m_magic_spells_known_.size(); i++)
			for (auto& i : m_magic_spells_known_)
			{
				
				// update spell data
				i.m_damage_range.m_low += temp_magic_low;
				i.m_damage_range.m_high += temp_magic_high;

				// low damage can't be higher than high damage
				/*if (m_magic_spells_known_[i].m_damage_range.m_low > m_magic_spells_known_[i].m_damage_range.m_high)
				{
					m_magic_spells_known_[i].m_damage_range.m_low = m_magic_spells_known_[i].m_damage_range.m_high;
				}*/
				i.m_damage_range.m_low = std::min(i.m_damage_range.m_low, i.m_damage_range.m_high);
			}
		}
		else // thief
		{
			temp_hp = (m_level_ % 2 == 0 ? random(0, 2) : 0); // if the level divided by 2 is 0, add 1 to 4 hps, else 0
			temp_ac = random(0, 1);
			temp_acc = random(0, 1);

			if (m_level_ > 10)
			{
				temp_dam_low = random(0, 3);
				temp_dam_high = random(1, 4);
			}
			else
			{
				temp_dam_low = random(0, 1);
				temp_dam_high = random(0, 2);
			}

		}

		// debug class bonuses
		if (debug_log.enable_debug_messages)
		{
			std::cout << "DEBUG messages" << "\n";
			std::cout << "Class Bonuses from leveling" << "\n";
			std::cout << "Max Hit Points: " << temp_hp << "\n";
			std::cout << "Armor: " << temp_ac << "\n";
			std::cout << "Accuracy: " << temp_acc << "\n";
			std::cout << "Weapon Damage Low: " << temp_dam_low << "\n";
			std::cout << "Weapon Damage High: " << temp_dam_high << "\n";
			std::cout << "Magic Damage Low: " << temp_magic_low << "\n";
			std::cout << "Magic Damage High: " << temp_magic_high << "\n";
		}
		


		// update stats
		m_max_hit_points_ += temp_hp;
		set_armor_bonus(temp_ac);
		
		m_accuracy_ += temp_acc;

		if (temp_dam_low > temp_dam_high)
		{
			const int temp = temp_dam_low;
			temp_dam_low = temp_dam_high;
			temp_dam_high = temp;
		}
		set_weapon_bonus(temp_dam_low, temp_dam_high);

		
		if (temp_magic_low > temp_magic_high)
		{
			const int temp = temp_magic_low;
			temp_magic_low = temp_magic_high;
			temp_magic_high = temp;
		}
		set_magic_bonus_damage(temp_magic_low, temp_magic_high);


		// update armor & weapon damage & magic damage
		calculate_armor();
		calculate_weapon_damage();
		calculate_magic_damage();


		// give player full hit points when they level up.
		m_hit_points_ = m_max_hit_points_;
		m_magic_points_ = m_max_magic_points_;


		if (debug_log.enable_debug_messages)
		{
			std::cout << "current exp: " << m_exp_points_ << ", exp needed to level: " << m_next_level_exp_ << "\n";
		}
		
		if (debug_log.enable_debug_messages)
		{
			std::cout << "test = " << test << ", true = quit, while loop will loop again" << "\n";
			test = (m_exp_points_ > m_next_level_exp_);
		}
		
	} 
}

int player::get_level() const
{
	return m_level_;
}

void player::rest()
{
	std::cout << "Your health and magic have recovered!" << "\n";

	m_hit_points_ = m_max_hit_points_;
	m_magic_points_ = m_max_magic_points_;
}

void player::view_states() const
{
	std::cout << "PLAYER STATS" << "\n";
	std::cout << "============" << "\n";
	std::cout << "\n";

	std::cout << "Name = " << m_name_ << "\n";
	std::cout << "Race = " << m_race_name_ << "\n";
	std::cout << "Class = " << m_class_name_ << "\n";
	std::cout << "Accuracy = " << m_accuracy_ << "\n";
	std::cout << "Hit Points = " << m_hit_points_ << "\n";
	std::cout << "Max Hit Points = " << m_max_hit_points_ << "\n";

	if(m_class_name_ == "Wizard" || m_class_name_ == "Cleric")
	{
		std::cout << "Magic Points = " << m_magic_points_ << "\n";
		std::cout << "Max Magic Points = " << m_max_magic_points_ << "\n";
	}
	
	std::cout << "XP = " << m_exp_points_ << "\n";
	std::cout << "XP for Next Lvl = " << m_next_level_exp_ << "\n";
	std::cout << "Level = " << m_level_ << "\n";
	std::cout << "Gold = " << m_gold_ << "\n";
	std::cout << "# of Healing Potions = " << m_potions_owned_.size() << "\n";
	std::cout << "Armor = " << m_armor_ << "\n";
	std::cout << "Armor Name = " << m_armor_worn_.m_name << "\n";
	std::cout << "Armor Value = " << m_armor_worn_.m_armor_value << "\n";
	std::cout << "Weapon Name = " << m_weapon_held_.m_name << "\n";
	std::cout << "Weapon Damage = " << m_weapon_held_.m_damage_range.m_low << " - " << m_weapon_held_.m_damage_range.m_high << "\n";
	

	std::cout << "\n";

	if (m_class_name_ == "Wizard" || m_class_name_ == "Cleric")
	{
		std::cout << "----------------------------" << "\n";
		std::cout << "-    Known Magic Spells    -" << "\n";
		std::cout << "----------------------------" << "\n" << "\n";

		//if (m_magic_spells_known_.size() > 0)
		if (!m_magic_spells_known_.empty())
		{
			for (size_t i = 0; i < m_magic_spells_known_.size(); i++)
			{
				if (m_magic_spells_known_[i].m_required_level <= m_level_)
				{
					std::cout << i << ") " << m_magic_spells_known_[i].m_name << " (Low: " << m_magic_spells_known_[i].m_damage_range.m_low << ", High: " << m_magic_spells_known_[i].m_damage_range.m_high << ")" << " <> Spell Cost: " << m_magic_spells_known_[i].m_magic_points_required << "\n";

					if (i < m_magic_spells_known_.size() - 1)
					{
						std::cout << "\n";
					}
				}
				
			}

			

			std::cout << "\n";
			std::cout << "----------------------------" << "\n";
		}
		else
		{
			std::cout << "You have no spells." << "\n" << "\n";
		}


	}
	
	

	std::cout << "END PLAYER STATS" << "\n";
	std::cout << "===============" << "\n";
	std::cout << "\n";
}

void player::victory(int xp, int gold)
{


	if (debug_log.enable_debug_messages)
	{
		// TESTING CHANGE ONLY
		//xp *= mRewardModifier;
		//gold *= mRewardModifier;
		// ---=-=-=-=-=================================================================================================================================
		// ---=-=-=-=-=================================================================================================================================
		// ---=-=-=-=-=================================================================================================================================
		// ---=-=-=-=-=================================================================================================================================
	}
	
	xp *= m_reward_modifier_;
	gold *= m_reward_modifier_;


	std::cout << "You won the battle!" << "\n";
	std::cout << "You win " << xp << " experience points!" << "\n";
	std::cout << "You win " << gold << " gold coins!" << "\n" << "\n";

	//mExpPoints += xp;
	m_exp_points_ += xp;
	//mGold += gold;
	m_gold_ += gold;
}

void player::gameOver()
{
	std::cout << "You died in battle..." << "\n";
	std::cout << "\n";
	std::cout << "======================" << "\n";
	std::cout << "=     GAME OVER!    =" << "\n";
	std::cout << "======================" << "\n";
	std::cout << "Press 'q' to quit: ";
	char q = 'q';
	std::cin >> q;
	std::cout << "\n";
}

void player::display_hit_points() const
{
	std::cout << m_name_ << "'s hit points = " << m_hit_points_;
}

void player::display_magic_points() const
{
	std::cout << ", magic points = " << m_magic_points_;
}

size_t player::get_number_of_owned_spells() const
{
	size_t spell_count = 0;

	for (const auto& i : m_magic_spells_known_)
	{
		if (i.m_required_level <= m_level_)
		{
			spell_count++;
		}
	}

	return spell_count;
	
}

player::~player() = default;

