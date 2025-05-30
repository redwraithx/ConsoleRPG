// Monster.h

#ifndef MONSTER_H
#define MONSTER_H

#include "Weapon.h"
#include <string>

class player;

class Monster
{
public:

	Monster(const std::string& name, int min_player_level, int hp, int acc, int xp_reward, int gold_reward, int armor, const std::string& weapon_name, int low_damage, int high_damage);

	bool is_dead() const;

	int get_xp_reward() const;
	int get_gold_reward() const;
	std::string get_name();
	int get_min_player_level() const;
	int get_armor() const;

	void attack(player& player) const;
	void take_damage(int damage);
	void display_hit_points() const;


	~Monster();

private:
	std::string m_name_;
	int m_min_player_level_;
	int m_hit_points_;
	int m_accuracy_;
	int m_exp_reward_;
	int m_gold_reward_;
	int m_armor_;
	weapon m_weapon_;


};

#endif // MONSTER_H

