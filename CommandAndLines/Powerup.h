#pragma once

#include <vector>
#include <memory>
#include "IGamePiece.h"

class Board;

enum class PowerupTypes
{
	ReArm = 3,
	Shuffle = 2,
	Inverse = 1,
	None = 0
};

void UseReArm(Board& boardState);
void UseShuffle(Board& boardState);
void UseInverse(std::vector<std::unique_ptr<IGamePiece>>& gamePieces);
std::string GetPowerUpTypeString(PowerupTypes type);
std::string GetPowerUpTypeCharacter(PowerupTypes type);
