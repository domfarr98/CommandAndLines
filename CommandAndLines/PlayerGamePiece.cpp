#include "PlayerGamePiece.h"
#include "Powerup.h"
#include "Terminal.h"
#include "Helpers.h"

#include <format>

PlayerGamePiece::PlayerGamePiece(std::string name, int pieceNumber)
	: m_name(std::move(name)), m_position(0), m_currentPowerup(PowerupTypes::None), m_movementInversed(false),
	m_pieceNumber(pieceNumber)
{

}

void PlayerGamePiece::PromptPieceMove()
{
	PromptAndWait(std::format("({}) - It's {}'s turn! Press any key to roll the dice..",m_pieceNumber, m_name));

	auto moveValue = GenerateRandomNumber(1, 12);

	if (m_movementInversed)
	{
		Prompt(std::format("({}) - {} rolled a {}, but it got inversed!",m_pieceNumber, m_name, moveValue));
		moveValue =- moveValue / 2;
		m_movementInversed = false;
	}
	else
	{
		Prompt(std::format("({}) - {} rolled a {}!", m_pieceNumber, m_name, moveValue));
	}

	m_position += moveValue;
}

PowerupTypes PlayerGamePiece::ShouldUsePowerup()
{
	if (m_currentPowerup != PowerupTypes::None)
	{
		auto const powerupString = GetPowerUpTypeString(m_currentPowerup);

		auto const response = PromptWithYesNoResponse(std::format("({}) - You currently have a {} powerup. Would you like to use it? (y/n)", m_pieceNumber, powerupString));

		if (response)
		{
			Prompt(std::format("({}) - {} used {}!", m_pieceNumber, m_name, powerupString));
			return m_currentPowerup;
		}
	}
	return PowerupTypes::None;
}