#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King() = delete;
	King(PlayerColor mPlayerColor, int mPosition);
	virtual vector<int> CanMovePlace(unique_ptr<Piece> board[]) override;
};