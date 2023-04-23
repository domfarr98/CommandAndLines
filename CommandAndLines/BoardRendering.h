#pragma once

#include <list>
#include "Board.h"
#include "IGamePiece.h"

void RenderBoard(Board& boardState, std::list<IGamePiece>& piecesList);
