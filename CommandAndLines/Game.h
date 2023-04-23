#pragma once

#include <list>
#include "Board.h"
#include "IGamePiece.h"

class Game
{
public:
	Game();
	void StartGame();
	
	int g_rowSize = 10;

private:
	void FinishGame();

	Board m_gameBoard;

	std::list<IGamePiece> m_gamePieces;

	bool m_gameInProgress = false;
	int m_pieceTurn = 1;

};
