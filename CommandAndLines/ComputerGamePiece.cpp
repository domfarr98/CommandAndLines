#include "ComputerGamePiece.h"
#include "Powerup.h"
#include "Terminal.h"
#include "Helpers.h"

#include <format>

ComputerGamePiece::ComputerGamePiece(std::string name, std::string pieceNumber, int maxMovement)
	: m_name(std::move(name)), m_position(1), m_currentPowerup(PowerupTypes::None), m_movementInversed(false),
	m_useChance(16), m_pieceNumber(pieceNumber), m_maxMovement(maxMovement)
{

}

void ComputerGamePiece::PromptPieceMove()
{
	auto moveValue = GenerateRandomNumber(1, 12);

	if (m_movementInversed)
	{
		Prompt(std::format("({}) - {} rolled a {}, but it got inversed!", m_pieceNumber, m_name, moveValue));
		moveValue = -moveValue / 2;
		m_movementInversed = false;
	}
	else
	{
		if (moveValue + m_position > m_maxMovement)
		{
			Prompt(std::format("({}) - {} rolled a {}, but it was too high to win!", m_pieceNumber, m_name, moveValue));
			return;
		}
		Prompt(std::format("({}) - {} rolled a {}!", m_pieceNumber, m_name, moveValue));
	}

	m_position += moveValue;
}

PowerupTypes ComputerGamePiece::ShouldUsePowerup()
{
	if (m_currentPowerup != PowerupTypes::None)
	{
		auto const powerupString = GetPowerUpTypeString(m_currentPowerup);

		if (auto generatedNum = GenerateRandomNumber(1, m_useChance); generatedNum == 1)
		{
			Prompt(std::format("({}) - {} used {}!", m_pieceNumber, m_name, powerupString));
			m_useChance = 16;
			return m_currentPowerup;
		}
		
		m_useChance /= 2;
	}
	return PowerupTypes::None;
}