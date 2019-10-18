#include "Queen.h"

Queen::Queen(PlayerColor mPlayerColor, int mPosition)
	:Piece(PieceType::QUEEN, mPlayerColor, mPosition)
{
	//ChangePositionStringToInt();
}

vector<int> Queen::CanMovePlace(unique_ptr<Piece> board[])
{
	vector<int> movablePlace;
	//대각선
	//왼쪽 아래
	for (int i = piecePosition - 9; i > 0; i = i - 9)
	{
		if (piecePosition % 8 == 1)
			break;

		if (i % 8 == 1)
		{
			if (MoveCalcurate(board, i))
				movablePlace.push_back(i);
			if (!MoveCalcurate(board, i) || board[i] != nullptr)
				break;
			break;
		}
		else
		{
			if (MoveCalcurate(board, i))
				movablePlace.push_back(i);
			if (!MoveCalcurate(board, i) || board[i] != nullptr)
				break;
		}


	}
	//오른쪽 아래
	for (int i = piecePosition - 7; i > 0; i = i - 7)
	{
		if (piecePosition % 8 == 0)
			break;

		if (i % 8 == 0)
		{
			if (MoveCalcurate(board, i))
				movablePlace.push_back(i);
			if (!MoveCalcurate(board, i) || board[i] != nullptr)
				break;
			break;
		}
		else
		{
			if (MoveCalcurate(board, i))
				movablePlace.push_back(i);
			if (!MoveCalcurate(board, i) || board[i] != nullptr)
				break;
		}
	}
	//왼쪽 위
	for (int i = piecePosition + 7; i < 65; i = i + 7)
	{
		if (piecePosition % 8 == 1)
			break;
		if (i % 8 == 1)
		{
			if (MoveCalcurate(board, i))
				movablePlace.push_back(i);
			if (!MoveCalcurate(board, i) || board[i] != nullptr)
				break;
			break;
		}

		else
		{
			if (MoveCalcurate(board, i))
				movablePlace.push_back(i);
			if (!MoveCalcurate(board, i) || board[i] != nullptr)
				break;
		}
	}
	//오른쪽 위
	for (int i = piecePosition + 9; i < 65; i = i + 9)
	{
		if (piecePosition % 8 == 0)
			break;
		if (i % 8 == 0)
		{
			if (MoveCalcurate(board, i))
				movablePlace.push_back(i);
			if (!MoveCalcurate(board, i) || board[i] != nullptr)
				break;
			break;
		}
		else
		{
			if (MoveCalcurate(board, i))
				movablePlace.push_back(i);
			if (!MoveCalcurate(board, i) || board[i] != nullptr)
				break;
		}
	}
	
	//직진
	//위
	for (int i = piecePosition + 8; i < 65; i = i + 8)
	{
		if (MoveCalcurate(board, i))
			movablePlace.push_back(i);
		if (!MoveCalcurate(board, i) || board[i] != nullptr)
			break;
	}

	//아래
	for (int i = piecePosition - 8; i > 0; i = i - 8)
	{
		if (MoveCalcurate(board, i))
			movablePlace.push_back(i);
		if (!MoveCalcurate(board, i) || board[i] != nullptr)
			break;
	}

	//오른쪽
	for (int i = piecePosition; i % 8 <= 8; i++)
	{
		if (i % 8 == 0)
			break;
		else if (i < 65)
		{
			if (MoveCalcurate(board, i + 1))
				movablePlace.push_back(i + 1);
			if (!MoveCalcurate(board, i + 1) || board[i + 1] != nullptr)
				break;
		}
	}

	//왼쪽
	for (int i = piecePosition; i % 8 >= 0; i--)
	{
		if (i % 8 == 1)
			break;
		else if (i > 0)
		{
			if (MoveCalcurate(board, i - 1))
				movablePlace.push_back(i - 1);
			if (!MoveCalcurate(board, i - 1) || board[i - 1] != nullptr)
				break;
		}
	}
	return movablePlace;
}

bool Queen::MoveCalcurate(unique_ptr<Piece> board[], int i)
{
	if (board[i] == nullptr) // 빈자리
		return true;

	else if (this->playerColor == board[i]->get_PlayerColor()) return false;//같은 색 못넘어감

	else if (this->playerColor != board[i]->get_PlayerColor())// 공격 or 끝자리
	{
		return true;
	}
}