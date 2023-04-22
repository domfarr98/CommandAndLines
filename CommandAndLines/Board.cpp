#include "Board.h"
#include <random>

Board::Board()
	:m_boardSize(0)
{
}

Board::Board(int size)
	: m_boardSize(size)
{
	GenerateMoveTiles();
	GeneratePowerupTiles();
}

void Board::GenerateMoveTiles()
{
	const auto increment = 5;
	const auto const numberOfMovementTiles = m_boardSize / increment;
	const int maxMoveDistance = floor((m_boardSize / 3) * 2);

	// process all tiles in batches of 5, given there will be 1 move tile to any given 5 tiles
	for (auto movementTile = 1; movementTile < numberOfMovementTiles; movementTile++)
	{
		int desiredPosition = GenerateRandomNumber(1, 5);

		// fill in the blanks before the move tile
		for (auto i = 1; i < desiredPosition - 1; i++)
		{
			m_moveTileAssignments.emplace_back(0);
		}

		// calculate the movement distance value
		int moveDistance = GenerateRandomNumber(1, maxMoveDistance) - maxMoveDistance / 2;

		// ensure movement distance is above 0 or below boardSize-1. If not, half the move distance
		while (m_moveTileAssignments.size() + moveDistance < 0 || m_moveTileAssignments.size() + moveDistance > m_boardSize - 1)
		{
			moveDistance =- moveDistance / 2;
		}

		m_moveTileAssignments.emplace_back(moveDistance);

		// fill in the remaining blank tiles
		for (auto i = desiredPosition; i < increment; i++)
		{
			m_moveTileAssignments.emplace_back(0);
		}
	}
}

void Board::GeneratePowerupTiles()
{
	const auto increment = 10;
	const auto const numberOfPowerupTiles = m_boardSize / increment;

	// process all tiles in batches of 5, given there will be 1 move tile to any given 5 tiles
	for (auto movementTile = 1; movementTile < numberOfPowerupTiles; movementTile++)
	{
		int desiredPosition = GenerateRandomNumber(1, 5);

		// fill in the blanks before the move tile
		for (auto i = 1; i < desiredPosition - 1; i++)
		{
			m_powerupTileAssignments.emplace_back(PowerupTypes::None);
		}

		// decide which powerup to pick
		int powerupPick = GenerateRandomNumber(1, 3);
		PowerupTypes powerup = (PowerupTypes)powerupPick;

		m_powerupTileAssignments.emplace_back(powerup);

		// fill in the remaining blank tiles
		for (auto i = desiredPosition; i < increment; i++)
		{
			m_powerupTileAssignments.emplace_back(PowerupTypes::None);
		}
	}
}

int Board::GenerateRandomNumber(int min, int max)
{
	std::random_device device;
	std::mt19937 random(device);
	std::uniform_int_distribution<std::mt19937::result_type> ranDist(min, max);

	return ranDist(random);
}
