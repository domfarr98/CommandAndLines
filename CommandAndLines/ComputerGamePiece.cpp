#include "ComputerGamePiece.h"
#include "Powerup.h"
#include "Terminal.h"
#include "Helpers.h"

#include <format>

ComputerGamePiece::ComputerGamePiece(std::string name, int suceedingNumber)
	: m_name(std::move(name)), m_succeedingNumber(suceedingNumber), m_position(0), m_currentPowerup(PowerupTypes::None),
	m_movementInversed(false)
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

	m_position + moveValue;
}

PowerupTypes ComputerGamePiece::ShouldUsePowerup()
{
	return PowerupTypes::None;
}