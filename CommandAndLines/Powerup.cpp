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

std::string GetPowerUpTypeString(PowerupTypes type)
{
	switch (type)
	{
	case PowerupTypes::ReArm:
		return "ReArm";
	case PowerupTypes::Shuffle:
		return "Shuffle";
	case PowerupTypes::Inverse:
		return "Inverse";
	default:
		return "";
	}
}

std::string GetPowerUpTypeCharacter(PowerupTypes type)
{
	switch (type)
	{
	case PowerupTypes::ReArm:
		return "!";
	case PowerupTypes::Shuffle:
		return "~";
	case PowerupTypes::Inverse:
		return "?";
	default:
		return " ";
	}
}
