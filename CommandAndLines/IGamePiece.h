#pragma once

#include <string>
#include "Powerup.h"

class IGamePiece
{
public:
	virtual ~IGamePiece() = default;
	virtual void MovePiece() = 0;
	virtual int GetPosition() = 0;
	virtual PowerupTypes ShouldUsePowerup() = 0;
	virtual void SetPowerup(PowerupTypes powerup) = 0;
	virtual std::string GetName() = 0;
};
