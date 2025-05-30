#include "Monster.h"
#include "Player.h"
#include "Random.h"
#include <string>
#include <iostream>


Monster::Monster(const std::string& name, const int min_player_level, const int hp, const int acc, const int xp_reward, const int gold_reward, const int armor, const std::string& weapon_name, const int low_damage, const int high_damage)
{
	m_name_ = name;
	m_min_player_level_ = min_player_level;
	m_hit_points_ = hp;
	m_accuracy_ = acc;
	m_exp_reward_ = xp_reward;
	m_gold_reward_ = gold_reward;
	m_armor_ = armor;
	m_weapon_.m_name = weapon_name;
	m_weapon_.m_damage_range.m_low = low_damage;
	m_weapon_.m_damage_range.m_high = high_damage;

}

bool Monster::is_dead() const
{
	return m_hit_points_ <= 0;
}

int Monster::get_xp_reward() const
{
	return m_exp_reward_;
}

int Monster::get_gold_reward() const
{
	return m_gold_reward_;
}

std::string Monster::get_name()
{
	return m_name_;
}

int Monster::get_min_player_level() const
{
	return m_min_player_level_;
}

int Monster::get_armor() const
{
	return m_armor_;
}

void Monster::attack(player& player) const
{
	std::cout << "A " << m_name_ << " attacks you with a " << m_weapon_.m_name << '\n';

	if (random(0, 20) < m_accuracy_)
	{
		const int damage = random(m_weapon_.m_damage_range);

		const int total_damage = damage - player.get_armor();

		if (total_damage <= 0)
		{
			std::cout << "The monster's attack failed to penetrate your armor." << '\n';
		}
		else
		{
			std::cout << "You are hit for " << total_damage << " damage!" << '\n';

			player.take_damage(total_damage);
		}

	}
	else
	{
		std::cout << "The " << m_name_ << " missed!" << '\n';
	}

	std::cout << '\n';
}

void Monster::take_damage(const int damage)
{
	m_hit_points_ -= damage;
}

void Monster::display_hit_points() const
{
	std::cout << m_name_ << "'s hit points = " << m_hit_points_ << '\n';
}

Monster::~Monster() = default;
