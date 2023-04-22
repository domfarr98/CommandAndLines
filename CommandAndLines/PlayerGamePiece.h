#pragma once

#include "IGamePiece.h"

class PlayerGamePiece : IGamePiece
{
public:
	PlayerGamePiece(std::string name, int suceedingNumber);

	void MovePiece() override;
	int GetPosition() override { return m_position; };
	PowerupTypes ShouldUsePowerup() override;
	void SetPowerup(PowerupTypes powerup) override { currentPowerup = powerup; }

	std::string GetName() override { return m_name; }
	
private:
	std::string m_name;
	int m_succeedingNumber;
	int m_position;
	PowerupTypes currentPowerup;
};
