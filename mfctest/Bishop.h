#pragma once
#include"Piece.h"

class Bishop :public Piece
{
public:
	Bishop() = delete;
	Bishop(PlayerColor mPlayerColor, int mPosition);
	virtual vector<int> CanMovePlace(unique_ptr<Piece> board[]) override;
	bool MoveCalcurate(unique_ptr<Piece> board[],int i);
};