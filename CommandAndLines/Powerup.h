#pragma once

#include <list>
#include "IGamePiece.h"
#include "Board.h"

enum class PowerupTypes
{
	ReArm = 3,
	Shuffle = 2,
	Inverse = 1,
	None = 0
};

void ReArm(Board& boardState);
void Shuffle(Board& boardState);
void Inverse(std::list<IGamePiece>& gamePieces);
