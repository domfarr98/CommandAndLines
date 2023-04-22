#pragma once

#include <list>
#include "Powerup.h"

class Board
{
public:
	Board();
	Board(int size);

	std::list<int> getMoveTileAssignments() { return m_moveTileAssignments; }
	void setMoveTileAssignments(std::list<int> assignments) { m_moveTileAssignments = assignments; }

	std::list<PowerupTypes> getPowerupTileAssignments() { return m_powerupTileAssignments; }
	void setPowerupTileAssignments(std::list<PowerupTypes> assignments) { m_powerupTileAssignments = assignments; }

private:
	void GenerateMoveTiles();
	void GeneratePowerupTiles();
	int GenerateRandomNumber(int min, int max);

	int m_boardSize;
	std::list<int> m_moveTileAssignments;
	std::list<PowerupTypes> m_powerupTileAssignments;
};
