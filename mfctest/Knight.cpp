#include "Knight.h"

Knight::Knight(PlayerColor mPlayerColor, int mPosition)
	:Piece(PieceType::KNIGHT, mPlayerColor, mPosition)
{
	//ChangePositionStringToInt();
}

vector<int> Knight::CanMovePlace(unique_ptr<Piece> board[])
{
	vector<int> movablePlace;
	//위-좌
	int i = piecePosition;
	if (CheckTurePlus(i + 15, board) && i % 8!= 1)
		movablePlace.push_back(i + 15);
	//위-우
	if (CheckTurePlus(i + 17, board) && i % 8 != 0)
		movablePlace.push_back(i + 17);
	//아래-좌
	if (CheckTureMinus(i - 17, board) && i % 8 != 1)
		movablePlace.push_back(i - 17);
	//아래-우
	if (CheckTureMinus(i - 15, board) && i % 8 != 0)
		movablePlace.push_back(i - 15);

	//좌-위
	if (CheckTurePlus(i + 6, board) && (i - 1) % 8 != 1)
		movablePlace.push_back(i + 6);
	//좌-아래
	if (CheckTureMinus(i - 10, board) && (i - 1) % 8 != 1)
		movablePlace.push_back(i - 10);
	//우-위
	if (CheckTurePlus(i + 10, board) && (i + 1) % 8 != 0)
		movablePlace.push_back(i + 10);
	//우-아래
	if (CheckTureMinus(i - 6, board) && (i + 1) % 8 != 0)
		movablePlace.push_back(i - 6);
	return movablePlace;
}

bool Knight::CheckTurePlus(int i, unique_ptr<Piece> board[])
{
	if (i <= 64)
	{
		if (board[i] == nullptr)
			return true;

		else if (this->playerColor != board[i]->get_PlayerColor())
			return true;

		else
			return false;
	}
	else
		return false;
}

bool Knight::CheckTureMinus(int i, unique_ptr<Piece> board[])
{
	if (i >= 1)
	{
		if (board[i] == nullptr)
			return true;

		else if (this->playerColor != board[i]->get_PlayerColor())
			return true;

		else
			return false;
	}
	else
		return false;
}