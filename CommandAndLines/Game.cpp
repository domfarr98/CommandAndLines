#include <format>
#include "Game.h"
#include "Terminal.h"
#include "PlayerGamePiece.h"
#include "ComputerGamePiece.h"
#include "Powerup.h"

Game::Game()
{
	auto numberOfPlayers = PromptWithResponse<int>("Creating new game.. \n Please enter the number of players (1-4):");
	while (numberOfPlayers > 4 && numberOfPlayers < 1)
	{
		numberOfPlayers = PromptWithResponse<int>("Invalid number of players. Please enter a valid number (1-4):");
	}

	auto numberOfComptuers = PromptWithResponse<int>("Please enter the number of COMP players (1-4):");
	while (numberOfComptuers > 4 && numberOfComptuers < 1)
	{
		numberOfComptuers = PromptWithResponse<int>("Invalid number of COMP players. Please enter a valid number (1-4):");
	}

	auto boardSize = PromptWithResponse<int>(std::format("Please enter the board size (multiple of {}, max 200):", g_rowSize));
	while (boardSize < 1 || boardSize > 200 || boardSize % 10 != 0)
	{
		boardSize = PromptWithResponse<int>("Invalid number of board tiles. Please enter a valid size (multiple of 10, max 200):");
	}

	for (auto i = 0; i < numberOfPlayers; i++)
	{
		auto playerName = PromptWithResponse<std::string>(std::format("Please enter a name for player {} (max 10 characters):", i));
		while (playerName.empty() || playerName.size() > 10)
		{
			playerName = PromptWithResponse<std::string>(std::format("Invalid name. Please enter a valid name for player {} (max 10 characters):", i));
		}

		m_gamePieces.emplace_back(PlayerGamePiece(std::move(playerName), boardSize));
	}

	for (auto i = 1; i < numberOfComptuers; i++)
	{
		m_gamePieces.emplace_back(ComputerGamePiece(std::format("Computer {}", i), boardSize));
	}

	m_gameBoard = Board(boardSize);

	Prompt("Game created!");
}

void Game::StartGame()
{
	Prompt("Game starting now!");

	while (m_gameInProgress)
	{
		// render board

		// process peices one by one
		for (auto& piece : m_gamePieces)
		{
			// process powerup use
			if (auto powerup = piece.ShouldUsePowerup(); powerup != PowerupTypes::None)
			{
				// use powerup
				switch (powerup)
				{
				case PowerupTypes::ReArm:
					// do rearm
					// render board
					break;
				case PowerupTypes::Shuffle:
					// do shuffle
					// render board
					break;
				case PowerupTypes::Inverse:
					// do rearm
					break;
				}
			}

			// process piece movement
			piece.MovePiece();

			// check if they have won yet or not
			if (piece.GetPosition() == m_gameBoard.GetBoardSize())
			{
				FinishGame();
			}

		}
	}
}

void Game::FinishGame()
{
	m_gameInProgress = false;

	// wrap up game

	// output leaderboard information

	// etc
}
