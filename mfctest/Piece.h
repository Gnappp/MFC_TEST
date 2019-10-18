#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

enum PieceType
{
	KING,QUEEN,ROOK,BISHOP,KNIGHT,PAWN
};

enum PlayerColor
{
	Black,White
};

class Piece
{
protected:
	PieceType pieceType;
	PlayerColor playerColor;
	int piecePosition;
	bool doMove;

public:
	Piece() = delete;
	Piece(PieceType mPieceType, PlayerColor mPlayerColor, int mPiecePosition);
	virtual ~Piece() = default;
	virtual vector<int> CanMovePlace(unique_ptr<Piece> board[]) = 0;
	//void ChangePositionStringToInt();
	PlayerColor get_PlayerColor();
	PieceType get_PieceType();
	void set_PieceType(PieceType chage);
	void Set_piecePosition(int chage);
	void Set_doMove(bool change);
	bool Get_doMove();
	int Get_piecePosition();
};