#include <format>
#include "Game.h"
#include "Terminal.h"
#include "IGamePiece.h"
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

		AddPiece(std::make_unique<PlayerGamePiece>(std::move(playerName), boardSize));
	}

	for (auto i = 1; i < numberOfComptuers; i++)
	{
		AddPiece(std::make_unique<ComputerGamePiece>(std::format("Computer {}", i), boardSize));
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
			if (auto powerup = piece->ShouldUsePowerup(); powerup != PowerupTypes::None)
			{
				// use powerup
				switch (powerup)
				{
				case PowerupTypes::ReArm:
					UseReArm(m_gameBoard);
					// render board
					break;
				case PowerupTypes::Shuffle:
					UseShuffle(m_gameBoard);
					// render board
					break;
				case PowerupTypes::Inverse:
					UseInverse(m_gamePieces);
					break;
				}
			}

			// process piece movement
			piece->PromptPieceMove();

			// check if they have won yet or not
			if (piece->GetPosition() == m_gameBoard.GetBoardSize())
			{
				FinishGame();
				continue;
			}

			// check if powerups need to be picked up
			if (auto const powerupTileValue = m_gameBoard.getPowerupTileAssignments().at(piece->GetPosition()); powerupTileValue != PowerupTypes::None)
			{
				piece->SetPowerup(powerupTileValue);

				m_gameBoard.RemovePowerupFromBoardTile(piece->GetPosition());
			}

			// process piece tile movement
			if (auto const moveTileValue = m_gameBoard.getMoveTileAssignments().at(piece->GetPosition()); moveTileValue != 0)
			{
				piece->OffsetPoition(moveTileValue);
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

void Game::AddPiece(std::unique_ptr<IGamePiece> pPiece)
{
	m_gamePieces.emplace_back(std::move(pPiece));
}
