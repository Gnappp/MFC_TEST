#pragma once
#include"Piece.h"

class Knight : public Piece
{
public:
	Knight() = delete;
	Knight(PlayerColor mPlayerColor, int mPosition);
	virtual vector<int> CanMovePlace(unique_ptr<Piece> board[]) override;
	bool CheckTurePlus(int i, unique_ptr<Piece> board[]);
	bool CheckTureMinus(int i, unique_ptr<Piece> board[]);
};