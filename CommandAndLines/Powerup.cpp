#include "Powerup.h"

void ReArm(Board& boardState)
{
	boardState.GeneratePowerupTiles();
}

void Shuffle(Board& boardState)
{
	boardState.GenerateMoveTiles();
}

void Inverse(std::list<IGamePiece>& gamePieces)
{
	for (auto& piece : gamePieces)
	{
		piece.InverseMovement();
	}
}
