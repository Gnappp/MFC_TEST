#include"Rook.h"

Rook::Rook(PlayerColor mPlayerColor, int mPosition)
	:Piece(PieceType::ROOK, mPlayerColor, mPosition)
{
	//ChangePositionStringToInt();
}

vector<int> Rook::CanMovePlace(unique_ptr<Piece> board[])
{
	vector<int> movablePlace;
	//위
	for (int i = piecePosition + 8; i < 65; i=i + 8)
	{
		if (MoveCalcurate(board, i))
			movablePlace.push_back(i);
		if (!MoveCalcurate(board, i) || board[i] != nullptr)
			break;
	}

	//아래
	for (int i = piecePosition - 8; i > 0; i=i - 8)
	{
		if (MoveCalcurate(board, i))
			movablePlace.push_back(i);
		if (!MoveCalcurate(board, i) || board[i] != nullptr)
			break;
	}

	//오른쪽
	for (int i = piecePosition; i%8 <= 8; i++)
	{
		if (i % 8 == 0)
			break;
		else if (i < 65)
		{
			if (MoveCalcurate(board, i+1))
				movablePlace.push_back(i+1);
			if (!MoveCalcurate(board, i+1) || board[i+1] != nullptr)
				break;
		}
	}

	//왼쪽
	for (int i = piecePosition; i%8 >= 0; i--)
	{
		if (i % 8 == 1)
			break;
		else if (i > 0)
		{
			if (MoveCalcurate(board, i-1))
				movablePlace.push_back(i-1);
			if (!MoveCalcurate(board, i-1) || board[i-1] != nullptr)
				break;
		}
	}
	return movablePlace;
}

bool Rook::MoveCalcurate(unique_ptr<Piece> board[], int i)
{
	if (board[i] == nullptr) // 빈자리
		return true;

	else if (this->playerColor == board[i]->get_PlayerColor()) return false;//같은 색 못넘어감

	else if (this->playerColor != board[i]->get_PlayerColor())// 공격 or 끝자리
	{
		return true;
	}
}