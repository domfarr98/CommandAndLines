#include "ComputerGamePiece.h"

ComputerGamePiece::ComputerGamePiece(std::string name, int suceedingNumber)
	: m_name(std::move(name)), m_succeedingNumber(suceedingNumber), m_position(0), m_currentPowerup(PowerupTypes::None),
	m_movementInversed(false)
{

}

void ComputerGamePiece::MovePiece()
{
	// calculate movement

	if (m_movementInversed)
	{
		m_movementInversed = false;
	}
}

PowerupTypes ComputerGamePiece::ShouldUsePowerup()
{
	
}