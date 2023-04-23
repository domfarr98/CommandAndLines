#include "ComputerGamePiece.h"
#include "Powerup.h"
#include "Terminal.h"
#include "Helpers.h"

#include <format>

ComputerGamePiece::ComputerGamePiece(std::string name, int pieceNumber)
	: m_name(std::move(name)), m_position(0), m_currentPowerup(PowerupTypes::None), m_movementInversed(false),
	m_useChance(16), m_pieceNumber(pieceNumber)
{

}

void ComputerGamePiece::PromptPieceMove()
{
	auto moveValue = GenerateRandomNumber(1, 12);

	if (m_movementInversed)
	{
		Prompt(std::format("{} rolled a {}, but it got inversed!", m_name, moveValue));
		moveValue = -moveValue / 2;
		m_movementInversed = false;
	}
	else
	{
		Prompt(std::format("{} rolled a {}!", m_name, moveValue));
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
			m_useChance = 16;
			return m_currentPowerup;
		}
		
		m_useChance /= 2;
	}
	return PowerupTypes::None;
}