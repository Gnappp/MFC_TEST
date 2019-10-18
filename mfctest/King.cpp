#include"King.h"

King::King(PlayerColor mPlayerColor, int mPosition)
	:Piece(PieceType::KING, mPlayerColor, mPosition)
{
	//ChangePositionStringToInt();
}

vector<int> King::CanMovePlace(unique_ptr<Piece> board[])
{
	vector<int> movablePlace;
	int i = piecePosition;
	//��
	if (i + 8 < 65)
	{
		if (board[i + 8] == nullptr)
			movablePlace.push_back(i + 8);
		else if (board[i + 8]->get_PlayerColor() != this->playerColor)
			movablePlace.push_back(i + 8);

	}
	//�Ʒ�
	if (i - 8 > 0)
	{
		if (board[i - 8] == nullptr)
			movablePlace.push_back(i - 8);
		else if (board[i - 8]->get_PlayerColor() != this->playerColor)
			movablePlace.push_back(i - 8);
	}

	//������
	if (i % 8 != 0)
	{
		if (i + 1 < 65)
		{
			if (board[i + 1] == nullptr)
				movablePlace.push_back(i + 1);
			else if (board[i + 1]->get_PlayerColor() != this->playerColor)
				movablePlace.push_back(i + 1);
		}
	}

	//����
	if (i % 8 != 1)
	{
		if (i - 1 > 0)
		{
			if (board[i - 1] == nullptr)
				movablePlace.push_back(i - 1);
			else if (board[i - 1]->get_PlayerColor() != this->playerColor)
				movablePlace.push_back(i - 1);
		}
	}

	//��-������
	if (i % 8 != 0)
	{
		if (i + 9 < 65)
		{
			if (board[i + 9] == nullptr)
				movablePlace.push_back(i + 9);
			else if (board[i + 9]->get_PlayerColor() != this->playerColor)
				movablePlace.push_back(i + 9);
		}
	}

	//��-����
	if (i % 8 != 1)
	{
		if(i + 7 < 65)
		{
			if (board[i + 7] == nullptr)
				movablePlace.push_back(i + 7);
			else if (board[i + 7]->get_PlayerColor() != this->playerColor)
				movablePlace.push_back(i + 7);
		}
	}

	//�Ʒ�-������
	if (i % 8 != 0)
	{
		if (i - 7 > 0)
		{
			if (board[i - 7] == nullptr)
				movablePlace.push_back(i - 7);
			else if (board[i - 7]->get_PlayerColor() != this->playerColor)
				movablePlace.push_back(i - 7);
		}
	}

	//�Ʒ�-����
	if (i % 8 != 1)
	{
		if (i - 9 > 0)
		{
			if (board[i - 9] == nullptr)
				movablePlace.push_back(i - 9);
			else if (board[i - 9]->get_PlayerColor() != this->playerColor)
				movablePlace.push_back(i - 9);
		}
	}
	return movablePlace;
}