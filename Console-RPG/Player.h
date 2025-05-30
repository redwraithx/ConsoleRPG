// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"
#include "Armor.h"
#include "Monster.h"
#include "Magic.h"
#include "Range.h"
#include "Potion.h"

#include <string>
#include <vector>


/**
 * 
 */
class player
{
public:
	// constructor
	player();

	// copy constructor
	player(const player& other) = default;
	// assignment operator
	player& operator=(const player& other) = default;
	// move constructor
	player(player&& other) noexcept = default;
	// move assignment operator
	player& operator=(player&& other) noexcept = default;
	

	// methods
	bool is_dead() const;

	std::string get_name();
	std::string get_class();
	int get_gold() const;
	void buy(int cost);
	void equip_armor(const armor& new_armor);
	void equip_weapon(const weapon& new_weapon);
	
	void calculate_weapon_damage();
	void set_weapon_bonus(int low, int high);
	int get_weapon_bonus(bool get_low_damage) const;
	void set_original_weapon_values(const range& weapon_damage);
	int get_original_weapon_value(bool get_low_damage) const;

	int get_armor() const;
	void set_armor_bonus(int value);
	void calculate_armor();
	
	void set_magic_bonus_damage(int low, int high);
	void set_original_magic_damage(const range magic_damage);
	void increase_spell_mana_cost();
	void calculate_magic_damage();

	void take_damage(int damage);
	void heal_damage(int heal_value);

	static int use_potion(potion current_potion);
	bool add_new_potion(potion new_potion);
	size_t get_potion_count() const;

	void create_class();
	void player_class_selection();
	void player_race_selection();
	//bool attack(Monster& monster);
	bool attack(Monster* monster[]);
	void level_up();
	int get_level() const;
	void rest();
	void view_states() const;
	void victory(int xp, int gold);
	static void gameOver();
	void display_hit_points() const;
	void display_magic_points() const;
	size_t get_number_of_owned_spells() const;

	// deconstructor
	~player();

private:
	// data members
	std::string m_name_;
	std::string m_race_name_;
	std::string m_class_name_;
	int m_accuracy_;
	int m_hit_points_;
	int m_max_hit_points_;
	int m_magic_points_;
	int m_max_magic_points_;
	range m_magic_bonus_damage_;

	
	int m_reward_modifier_; // leave at 1 for normal exp and gold, 0 for no exp or gold
	int m_exp_points_;
	int m_next_level_exp_;
	int m_level_;
	int m_armor_;
	weapon m_weapon_held_;
	range m_original_weapon_damage_;
	range m_weapon_bonus_;

	armor m_armor_worn_;
	int m_armor_bonus_;

	int m_gold_;

	std::vector<spell> m_magic_spells_known_;
	std::vector<range> m_original_magic_damage_;
	std::vector<potion> m_potions_owned_; // if we have anything, we own it. if we use it, we will then pop it. if we buy one, we will push it.

};






#endif // PLAYER_H