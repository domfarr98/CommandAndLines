#include <format>
#include "Game.h"
#include "Terminal.h"
#include "IGamePiece.h"
#include "PlayerGamePiece.h"
#include "ComputerGamePiece.h"
#include "Powerup.h"
#include "BoardRendering.h"

Game::Game()
{
	auto numberOfPlayers = PromptWithResponse<int>("Creating new game.. \nPlease enter the number of players (1-4):");
	while (numberOfPlayers > 4 || numberOfPlayers < 1)
	{
		numberOfPlayers = PromptWithResponse<int>("Invalid number of players. Please enter a valid number (1-4):");
	}

	auto numberOfComputers = PromptWithResponse<int>("Please enter the number of COMP players (1-4):");
	while (numberOfComputers > 4 || numberOfComputers < 1)
	{
		numberOfComputers = PromptWithResponse<int>("Invalid number of COMP players. Please enter a valid number (1-4):");
	}

	auto boardSize = PromptWithResponse<int>(std::format("Please enter the board size (multiple of {}, max 200):", 10));
	while (boardSize < 1 || boardSize > 200 || boardSize % 10 != 0)
	{
		boardSize = PromptWithResponse<int>("Invalid number of board tiles. Please enter a valid size (multiple of 10, max 200):");
	}

	for (auto i = 0; i < numberOfPlayers; i++)
	{
		auto playerName = PromptWithResponse<std::string>(std::format("Please enter a name for player {} (max 10 characters):", i));
		while (playerName.empty() || static_cast<int>(playerName.size()) > 10)
		{
			playerName = PromptWithResponse<std::string>(std::format("Invalid name. Please enter a valid name for player {} (max 10 characters):", i));
		}

		AddPiece(std::make_unique<PlayerGamePiece>(std::move(playerName), std::format("P{}", m_gamePieces.size() + 1), boardSize));
	}

	for (auto i = 0; i < numberOfComputers; i++)
	{
		AddPiece(std::make_unique<ComputerGamePiece>(std::format("COMP{}", i), std::format("C{}", m_gamePieces.size() + 1), boardSize));
	}

	m_gameBoard = Board(boardSize);

	Prompt("Game created!");
}

void Game::StartGame()
{
	Prompt("Game starting now!");

	m_gameInProgress = true;

	while (m_gameInProgress)
	{
		RenderBoard(m_gameBoard, m_gamePieces);

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
					RenderBoard(m_gameBoard, m_gamePieces);
					break;
				case PowerupTypes::Shuffle:
					UseShuffle(m_gameBoard);
					RenderBoard(m_gameBoard, m_gamePieces);
					break;
				case PowerupTypes::Inverse:
					UseInverse(m_gamePieces);
					break;
				}

				piece->SetPowerup(PowerupTypes::None);
			}

			// process piece movement
			piece->PromptPieceMove();

			// check if they have won yet or not
			if (piece->GetPosition() == m_gameBoard.GetBoardSize())
			{
  				FinishGame();
				break;
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
				piece->OffsetPosition(moveTileValue);
			}

		}
	}
}

void Game::FinishGame()
{
	m_gameInProgress = false;

	Prompt("\n\n\n");

	for (auto& piece : m_gamePieces)
	{
		if (piece->GetPosition() == m_gameBoard.GetBoardSize())
		{
			Prompt(std::format("! - {} has won the game - !",  piece->GetName()));
		}
	}

	PromptAndWait("\nPress any key to start a new game..");
}

void Game::AddPiece(std::unique_ptr<IGamePiece> pPiece)
{
	m_gamePieces.emplace_back(std::move(pPiece));
}
