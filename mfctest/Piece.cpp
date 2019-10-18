#include "Piece.h"

Piece::Piece(PieceType mPieceType, PlayerColor mPlayerColor, int mPiecePosition)
{
	pieceType = mPieceType;
	playerColor = mPlayerColor;
	piecePosition = mPiecePosition;
	doMove = false;
}

PlayerColor Piece::get_PlayerColor()
{
	return playerColor;
}

PieceType Piece::get_PieceType()
{
	return pieceType;
}
void Piece::set_PieceType(PieceType chage)
{
	pieceType = chage;
}
void Piece::Set_piecePosition(int change)
{
	piecePosition = change;
}
int Piece::Get_piecePosition()
{
	return piecePosition;
}

void Piece::Set_doMove(bool change)
{
	doMove = change;
}
bool Piece::Get_doMove()
{
	return doMove;
}


/*void Piece::ChangePositionStringToInt()
{
	char* ch = &stringPiecePosition[1];
	if (stringPiecePosition[0] >= 65 || stringPiecePosition[0] <= 90)
	{
		stringPiecePosition[0] = stringPiecePosition[0] + 32;
	}
	switch (stringPiecePosition[0])
	{
	case 'a':
		piecePosition = atoi(ch);
		break;
	case 'b':
		piecePosition = atoi(ch) + 8;
		break;
	case 'c':
		piecePosition = atoi(ch) + 16;
		break;
	case 'd':
		piecePosition = atoi(ch) + 24;
		break;
	case 'e':
		piecePosition = atoi(ch) + 32;
		break;
	case 'f':
		piecePosition = atoi(ch) + 40;
		break;
	case 'g':
		piecePosition = atoi(ch) + 48;
		break;
	case 'h':
		piecePosition = atoi(ch) + 56;
		break;

	default:
		break;
	}
}*/