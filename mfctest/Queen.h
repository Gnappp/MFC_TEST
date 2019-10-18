#pragma once
#include"Piece.h"

class Queen :public Piece
{
public:
	Queen() = delete;
	Queen(PlayerColor mPlayerColor, int mPosition);
	virtual vector<int> CanMovePlace(unique_ptr<Piece> board[]) override;
	bool MoveCalcurate(unique_ptr<Piece> board[], int i);
};
