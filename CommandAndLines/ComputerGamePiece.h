#pragma once

#include "IGamePiece.h"

class ComputerGamePiece : IGamePiece
{
public:
	ComputerGamePiece(std::string name, int suceedingNumber);

	void MovePiece() override;
	int GetPosition() override { return m_position; }
	PowerupTypes ShouldUsePowerup() override;
	void SetPowerup(PowerupTypes powerup) override { m_currentPowerup = powerup; }
	void InverseMovement() override { m_movementInversed = true; }
	std::string GetName() override { return m_name; }

private:
	std::string m_name;
	int m_succeedingNumber;
	int m_position;
	PowerupTypes m_currentPowerup;
	bool m_movementInversed;
};
