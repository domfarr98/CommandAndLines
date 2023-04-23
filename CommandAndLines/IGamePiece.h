#pragma once

#include <string>

enum class PowerupTypes;

class IGamePiece
{
public:
	virtual ~IGamePiece() = default;

	virtual void PromptPieceMove() = 0;
	virtual int GetPosition() = 0;
	virtual void OffsetPosition(int offset) = 0;
	virtual PowerupTypes ShouldUsePowerup() = 0;
	virtual void SetPowerup(PowerupTypes powerup) = 0;
	virtual void InverseMovement() = 0;
	virtual std::string GetName() = 0;
	virtual int GetPieceNumber() = 0;
};
