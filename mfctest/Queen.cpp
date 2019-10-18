#include "Queen.h"

Queen::Queen(PlayerColor mPlayerColor, int mPosition)
	:Piece(PieceType::QUEEN, mPlayerColor, mPosition)
{
	//ChangePositionStringToInt();
}

vector<int> Queen::CanMovePlace(unique_ptr<Piece> board[])
{
	vector<int> movablePlace;
	//�밢��
	//���� �Ʒ�
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
	//������ �Ʒ�
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
	//���� ��
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
	//������ ��
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
	
	//����
	//��
	for (int i = piecePosition + 8; i < 65; i = i + 8)
	{
		if (MoveCalcurate(board, i))
			movablePlace.push_back(i);
		if (!MoveCalcurate(board, i) || board[i] != nullptr)
			break;
	}

	//�Ʒ�
	for (int i = piecePosition - 8; i > 0; i = i - 8)
	{
		if (MoveCalcurate(board, i))
			movablePlace.push_back(i);
		if (!MoveCalcurate(board, i) || board[i] != nullptr)
			break;
	}

	//������
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

	//����
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
	if (board[i] == nullptr) // ���ڸ�
		return true;

	else if (this->playerColor == board[i]->get_PlayerColor()) return false;//���� �� ���Ѿ

	else if (this->playerColor != board[i]->get_PlayerColor())// ���� or ���ڸ�
	{
		return true;
	}
}