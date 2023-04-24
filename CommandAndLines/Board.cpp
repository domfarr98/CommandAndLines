#include "Board.h"
#include "Helpers.h"

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
	m_moveTileAssignments.clear();

	const auto increment = 5;
	const auto numberOfMovementTiles = m_boardSize / increment - 1;
	const int maxMoveDistance = static_cast<int>(floor((m_boardSize / 3) * 2));

	// fill the vector with blanks to start with
	for (auto i = 0; i <= m_boardSize - 1; i++)
	{
		m_moveTileAssignments.emplace_back(0);
	}

	// process all tiles in batches of 5, given there will be 1 move tile to any given 5 tiles
	for (auto movementTile = 0; movementTile < numberOfMovementTiles; movementTile++)
	{
		int const desiredPosition = GenerateRandomNumber(0, increment - 1);
		
		int moveDistance = GenerateRandomNumber(1, maxMoveDistance) - maxMoveDistance / 2;

		// ensure movement distance is above 0 or below boardSize-1. If not, half the move distance
		auto currentPosition = movementTile * increment + desiredPosition;
		while (currentPosition + moveDistance < 0 || currentPosition + moveDistance > m_boardSize - 1)
		{
			moveDistance =- moveDistance / 2;
		}

		if (currentPosition == 0)
		{
			currentPosition++;
		}
		if (currentPosition != m_boardSize - 1)
		{
			m_moveTileAssignments.at(currentPosition) = moveDistance;
		}
	}
}

void Board::GeneratePowerupTiles()
{
	m_powerupTileAssignments.clear();

	const auto increment = 10;
	const auto numberOfPowerupTiles = m_boardSize / increment;

	// fill the vector with blanks to start with
	for (auto i = 0; i <= m_boardSize - 1; i++)
	{
		m_powerupTileAssignments.emplace_back(PowerupTypes::None);
	}

	// process all tiles in batches of 5, given there will be 1 move tile to any given 5 tiles
	for (auto movementTile = 0; movementTile < numberOfPowerupTiles; movementTile++)
	{
		int desiredPosition = GenerateRandomNumber(0, increment - 1);

		// decide which powerup to pick
		int powerupPick = GenerateRandomNumber(1, 3);
		PowerupTypes powerup = (PowerupTypes)powerupPick;

		auto currentPosition = movementTile * increment + desiredPosition;

		if (currentPosition == 0)
		{
			currentPosition++;
		}
		if (currentPosition != m_boardSize - 1)
		{
			m_powerupTileAssignments.at(currentPosition) = powerup;
		}
	}
}
