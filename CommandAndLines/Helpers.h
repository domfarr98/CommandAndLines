#pragma once

#include <random>

static int GenerateRandomNumber(int min, int max)
{
	std::random_device device;
	std::mt19937 random(device());
	std::uniform_int_distribution<std::mt19937::result_type> ranDist(min, max);

	return ranDist(random);
}