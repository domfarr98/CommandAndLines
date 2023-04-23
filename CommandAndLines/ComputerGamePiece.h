#pragma once

#include "IGamePiece.h"

enum class PowerupTypes;

class ComputerGamePiece : public IGamePiece
{
public:
	ComputerGamePiece(std::string name, int pieceNumber);

	~ComputerGamePiece() override = default;

	void PromptPieceMove() override;
	int GetPosition() override { return m_position; }
	void OffsetPosition(int offset) { m_position += offset; }
	PowerupTypes ShouldUsePowerup() override;
	void SetPowerup(PowerupTypes powerup) override { m_currentPowerup = powerup; }
	void InverseMovement() override { m_movementInversed = true; }
	std::string GetName() override { return m_name; }
	int GetPieceNumber() override { return m_pieceNumber; }

private:
	std::string m_name;
	int m_position;
	PowerupTypes m_currentPowerup;
	bool m_movementInversed;
	int m_useChance;
	int m_pieceNumber;
};
