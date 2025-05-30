// Random.cpp

#include "Random.h"
///#include <cstdlib>
#include <random>

// returns a random number in range
int random(const range range)
{
	//return range.m_low + rand() % ((range.m_high + 1) - range.m_low);

	std::random_device rd;
	std::mt19937 rng(rd());

	const std::uniform_int_distribution<int> dist(range.m_low, range.m_high);
	return dist(rng);
}


// returns a random number in [low, high]
int random(const int low, const int high)
{
	//return low + rand() % ((high + 1) - low);

	const range rng{low, high};
	return random(rng);
}