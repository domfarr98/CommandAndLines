#include "Powerup.h"
#include "Board.h"

void UseReArm(Board& boardState)
{
	boardState.GeneratePowerupTiles();
}

void UseShuffle(Board& boardState)
{
	boardState.GenerateMoveTiles();
}

void UseInverse(std::vector<std::unique_ptr<IGamePiece>>& gamePieces)
{
	for (auto& piece : gamePieces)
	{
		piece->InverseMovement();
	}
}
