#include"Pawn.h"

Pawn::Pawn(PlayerColor mPlayerColor, int mPosition)
	:Piece(PieceType::PAWN, mPlayerColor, mPosition)
{
	//ChangePositionStringToInt();
	
}

vector<int> Pawn::CanMovePlace(unique_ptr<Piece> board[])
{
	vector<int> movablePlace;
	int i = piecePosition;
	//흰색
	if (board[i]->get_PlayerColor() == PlayerColor::White)
	{
		//이동
		if (board[i + 8] == nullptr)
		{
			movablePlace.push_back(i + 8);
			if (!doMove)
			{
				if (board[i + 16] == nullptr)
				{
					movablePlace.push_back(i + 16);
				}
			}
		}
		//공격
		if (board[i + 7] != nullptr && i % 8 != 1)
		{
			if (board[i + 7]->get_PlayerColor() == PlayerColor::Black)
				movablePlace.push_back(i + 7);
		}

		if (board[i + 9] != nullptr && i % 8 != 0)
		{
			if (board[i + 9]->get_PlayerColor() == PlayerColor::Black)
				movablePlace.push_back(i + 9);
		}
		//앙파상
		/*
		if (board[i + 1]->get_PlayerColor() == PlayerColor::Black && board[i + 1]->get_PieceType() == PieceType::PAWN)
		{
				movablePlace.push_back(i + 9);
		}
		if (board[i - 1]->get_PlayerColor() == PlayerColor::Black && board[i - 1]->get_PieceType() == PieceType::PAWN)
		{
				movablePlace.push_back(i + 7);
		}
		*/
	}

	//검은색
	else if (board[i]->get_PlayerColor() == PlayerColor::Black)
	{
		//이동
		if (board[i - 8] == nullptr)
		{
			movablePlace.push_back(i - 8);
			if (!doMove)
			{
				if (board[i - 16] == nullptr)
				{
					movablePlace.push_back(i - 16);
				}
			}
		}
		//공격
		if (board[i - 9] != nullptr && i % 8 != 1)
		{
			if (board[i - 9]->get_PlayerColor() == PlayerColor::White)
				movablePlace.push_back(i - 9);
		}

		if (board[i - 7] != nullptr && i % 8 != 0)
		{
			if (board[i - 7]->get_PlayerColor() == PlayerColor::White)
				movablePlace.push_back(i - 7);
		}
		//앙파상
		/*
		if (board[i + 1]->get_PlayerColor() == PlayerColor::White && board[i + 1]->get_PieceType() == PieceType::PAWN)
		{
				movablePlace.push_back(i - 7);
		}
		if (board[i - 1]->get_PlayerColor() == PlayerColor::White && board[i - 1]->get_PieceType() == PieceType::PAWN)
		{
				movablePlace.push_back(i - 9);
		}
		*/
	}
	return movablePlace;
}