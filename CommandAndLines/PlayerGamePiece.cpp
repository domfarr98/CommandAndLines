#include "PlayerGamePiece.h"
#include "Powerup.h"
#include "Terminal.h"
#include "Helpers.h"

#include <format>

PlayerGamePiece::PlayerGamePiece(std::string name, int pieceNumber, int maxMovement)
	: m_name(std::move(name)), m_position(1), m_currentPowerup(PowerupTypes::None), m_movementInversed(false),
	m_pieceNumber(pieceNumber), m_maxMovement(maxMovement)
{

}

void PlayerGamePiece::PromptPieceMove()
{
	PromptAndWait(std::format("(P{}) - It's {}'s turn! Press any key to roll the dice..",m_pieceNumber, m_name));

	auto moveValue = GenerateRandomNumber(1, 12);

	if (m_movementInversed)
	{
		Prompt(std::format("(P{}) - {} rolled a {}, but it got inversed!",m_pieceNumber, m_name, moveValue));
		moveValue =- moveValue / 2;
		m_movementInversed = false;
	}
	else
	{
		if (moveValue + m_position > m_maxMovement)
		{
			Prompt(std::format("C{} rolled a {}, but it was too high to win!", m_name, moveValue));
			return;
		}
		Prompt(std::format("(P{}) - {} rolled a {}!", m_pieceNumber, m_name, moveValue));
	}

	m_position += moveValue;
}

PowerupTypes PlayerGamePiece::ShouldUsePowerup()
{
	if (m_currentPowerup != PowerupTypes::None)
	{
		auto const powerupString = GetPowerUpTypeString(m_currentPowerup);

		auto const response = PromptWithYesNoResponse(std::format("(P{}) - You currently have a {} powerup. Would you like to use it? (y/n)", m_pieceNumber, powerupString));

		if (response)
		{
			Prompt(std::format("(P{}) - {} used {}!", m_pieceNumber, m_name, powerupString));
			return m_currentPowerup;
		}
	}
	return PowerupTypes::None;
}