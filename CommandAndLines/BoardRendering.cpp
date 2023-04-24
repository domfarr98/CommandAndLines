#include <iostream>
#include <format>
#include "BoardRendering.h"
#include "Terminal.h"

namespace
{
	std::string BuildUpperTile(int tileNumber, Board& boardState)
	{
		std::string topTile = "|";
		topTile.append(std::format("{}", tileNumber));

		std::string moveTileString;
		if (auto const moveTileValue = boardState.getMoveTileAssignments().at(tileNumber - 1); moveTileValue != 0)
		{
			moveTileString = std::format("{}{}", moveTileValue > 0 ? "+" : "", moveTileValue);
		}

		for (auto i = 8 - (static_cast<int>(topTile.size()) + static_cast<int>(moveTileString.size())); i != 0; i--)
		{
			topTile.append(" ");
		}

		topTile.append(std::move(moveTileString));

		return std::move(topTile);
	}

	std::string BuildLowerTile(int tileNumber, std::vector<std::unique_ptr<IGamePiece>>& piecesList, Board& boardState)
	{
		std::string bottomTile = "|";

		std::string pieceNameTile = "";
		auto piecesCount = 0;
		for (auto& piece : piecesList)
		{
			if (piece->GetPosition() == tileNumber)
			{
				piecesCount++;
				if (piecesCount > 1)
				{
					pieceNameTile = "P*";
					break;
				}
				pieceNameTile = std::format("{}", piece->GetPieceNumber());
			}
		}
		bottomTile.append(pieceNameTile);

		bottomTile.append(pieceNameTile.empty() ? "      " : "    ");

		auto const powerupTileValue = boardState.getPowerupTileAssignments().at(tileNumber - 1);
		bottomTile.append(GetPowerUpTypeCharacter(powerupTileValue));

		return std::move(bottomTile);
	}
}

void RenderBoard(Board& boardState, std::vector<std::unique_ptr<IGamePiece>>& piecesList)
{
	auto boardRows = boardState.GetBoardSize() / 10;

	for (auto row = 0; row < boardRows; row++)
	{
		std::string topRow = "";
		std::string bottomRow = "";
		for (auto i = 0; i < 10; i++)
		{
			auto const tileNumber = (i + 1) + row * 10;
			topRow.append(BuildUpperTile(tileNumber, boardState));
			bottomRow.append(BuildLowerTile(tileNumber, piecesList, boardState));
		}

		topRow.append("|");
		bottomRow.append("|");

		Prompt("---------------------------------------------------------------------------------");
		Prompt(topRow);
		Prompt(bottomRow);
	}
	Prompt("----------------------------------------------------------------------------------");
}