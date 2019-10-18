#pragma once
#include"Piece.h"

class Pawn:public Piece
{

public:
	Pawn() = delete;
	Pawn(PlayerColor mPlayerColor, int mPosition);
	virtual vector<int> CanMovePlace(unique_ptr<Piece> board[]) override;
};