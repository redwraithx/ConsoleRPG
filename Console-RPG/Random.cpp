// Random.cpp

#include "Random.h"
#include <cstdlib>

// returns a random number in range
int Random(Range range)
{
	return range.mLow + rand() % ((range.mHigh + 1) - range.mLow);
}


// returns a random number in [low, high]
int Random(int low, int high)
{
	return low + rand() % ((high + 1) - low);
}