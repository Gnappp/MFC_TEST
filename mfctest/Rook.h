#pragma once
#include"Piece.h"

class Rook :public Piece
{
public:
	Rook() = delete;
	Rook(PlayerColor mPlayerColor, int mPosition);
	virtual vector<int> CanMovePlace(unique_ptr<Piece> board[]) override;
	bool MoveCalcurate(unique_ptr<Piece> board[], int i);
};