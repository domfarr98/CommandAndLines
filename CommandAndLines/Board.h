#pragma once

#include <vector>
#include "Powerup.h"

class Board
{
public:
	Board();
	Board(int size);

	std::vector<int> getMoveTileAssignments() { return m_moveTileAssignments; }
	void setMoveTileAssignments(std::vector<int> assignments) { m_moveTileAssignments = assignments; }

	std::vector<PowerupTypes> getPowerupTileAssignments() { return m_powerupTileAssignments; }
	void setPowerupTileAssignments(std::vector<PowerupTypes> assignments) { m_powerupTileAssignments = assignments; }

	int GetBoardSize() { return m_boardSize; }

	void GenerateMoveTiles();
	void GeneratePowerupTiles();
	int GenerateRandomNumber(int min, int max);

private:
	int m_boardSize;
	std::vector<int> m_moveTileAssignments;
	std::vector<PowerupTypes> m_powerupTileAssignments;
};
