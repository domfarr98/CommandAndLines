#pragma once

#include <list>

enum class PowerupTypes
{
	ReArm = 3,
	Shuffle = 2,
	Inverse = 1,
	None = 0
};

std::list<int> Shuffle(std::list<int>);
void Inverse();
