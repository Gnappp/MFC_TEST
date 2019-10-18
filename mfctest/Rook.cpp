#include"Rook.h"

Rook::Rook(PlayerColor mPlayerColor, int mPosition)
	:Piece(PieceType::ROOK, mPlayerColor, mPosition)
{
	//ChangePositionStringToInt();
}

vector<int> Rook::CanMovePlace(unique_ptr<Piece> board[])
{
	vector<int> movablePlace;
	//��
	for (int i = piecePosition + 8; i < 65; i=i + 8)
	{
		if (MoveCalcurate(board, i))
			movablePlace.push_back(i);
		if (!MoveCalcurate(board, i) || board[i] != nullptr)
			break;
	}

	//�Ʒ�
	for (int i = piecePosition - 8; i > 0; i=i - 8)
	{
		if (MoveCalcurate(board, i))
			movablePlace.push_back(i);
		if (!MoveCalcurate(board, i) || board[i] != nullptr)
			break;
	}

	//������
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

	//����
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
	if (board[i] == nullptr) // ���ڸ�
		return true;

	else if (this->playerColor == board[i]->get_PlayerColor()) return false;//���� �� ���Ѿ

	else if (this->playerColor != board[i]->get_PlayerColor())// ���� or ���ڸ�
	{
		return true;
	}
}