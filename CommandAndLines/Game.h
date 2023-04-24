#pragma once

#include <vector>
#include "Board.h"

class IGamePiece;

class Game
{
public:
	Game();
	void StartGame();

private:
	void FinishGame();
	void AddPiece(std::unique_ptr<IGamePiece> pPiece);

	Board m_gameBoard;

	std::vector<std::unique_ptr<IGamePiece>> m_gamePieces;

	bool m_gameInProgress = false;
	int m_pieceTurn = 1;
};
