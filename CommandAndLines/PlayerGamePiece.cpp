#include "PlayerGamePiece.h"
#include "Powerup.h"
#include "Terminal.h"
#include "Helpers.h"

#include <format>

PlayerGamePiece::PlayerGamePiece(std::string name, int suceedingNumber)
	: m_name(std::move(name)), m_succeedingNumber(suceedingNumber), m_position(0), m_currentPowerup(PowerupTypes::None),
	m_movementInversed(false)
{

}

void PlayerGamePiece::PromptPieceMove()
{
	// calculate movement
	PromptAndWait(std::format("It's {}'s turn! Press any key to roll the dice..", m_name));

	auto moveValue = GenerateRandomNumber(1, 12);

	if (m_movementInversed)
	{
		Prompt(std::format("{} rolled a {}, but it got inversed!", m_name, moveValue));
		moveValue =- moveValue / 2;
		m_movementInversed = false;
	}
	else
	{
		Prompt(std::format("{} rolled a {}!", m_name, moveValue));
	}

	m_position + moveValue;
}

PowerupTypes PlayerGamePiece::ShouldUsePowerup()
{
	return PowerupTypes::None;
}