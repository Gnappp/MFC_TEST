#include "Board.h"

Board::Board()
	: an_passnt()
	, surrender(false)
	, check(false)
	, castling(false)
	, checkmate(false)
	, stalemate(false)
	, promotion(false)
	, turn(0)
	, selectMoveIntPos(0)
	, kingSideCastling(0)
	, queenSideCastling(0)
	, selectPieceIntPos(0)
	, checkPos(0)
	, mboard(nullptr)
	, selected(false)

{
	MakeBoard();
}


unique_ptr<Piece>* Board::MakeBoard()
{
	
	//일반
	unique_ptr<Piece>* mboard = new unique_ptr < Piece>[65];
	mboard[1] = std::make_unique<Rook>(PlayerColor::White, 1);
	mboard[2] = std::make_unique<Knight>(PlayerColor::White, 2);
	mboard[3] = std::make_unique<Bishop>(PlayerColor::White, 3);
	mboard[4] = std::make_unique<Queen>(PlayerColor::White, 4);
	mboard[5] = std::make_unique<King>(PlayerColor::White, 5);
	mboard[6] = std::make_unique<Bishop>(PlayerColor::White, 6);
	mboard[7] = std::make_unique<Knight>(PlayerColor::White, 7);
	mboard[8] = std::make_unique<Rook>(PlayerColor::White, 8);
	mboard[9] = std::make_unique<Pawn>(PlayerColor::White, 9);
	mboard[10] = std::make_unique<Pawn>(PlayerColor::White, 10);
	mboard[11] = std::make_unique<Pawn>(PlayerColor::White, 11);
	mboard[12] = std::make_unique<Pawn>(PlayerColor::White, 12);
	mboard[13] = std::make_unique<Pawn>(PlayerColor::White, 13);
	mboard[14] = std::make_unique<Pawn>(PlayerColor::White, 14);
	mboard[15] = std::make_unique<Pawn>(PlayerColor::White, 15);
	mboard[16] = std::make_unique<Pawn>(PlayerColor::White, 16);

	mboard[57] = std::make_unique<Rook>(PlayerColor::Black, 57);
	mboard[58] = std::make_unique<Knight>(PlayerColor::Black, 58);
	mboard[59] = std::make_unique<Bishop>(PlayerColor::Black, 59);
	mboard[60] = std::make_unique<Queen>(PlayerColor::Black, 60);
	mboard[61] = std::make_unique<King>(PlayerColor::Black, 61);
	mboard[62] = std::make_unique<Bishop>(PlayerColor::Black, 62);
	mboard[63] = std::make_unique<Knight>(PlayerColor::Black, 63);
	mboard[64] = std::make_unique<Rook>(PlayerColor::Black, 64);
	mboard[49] = std::make_unique<Pawn>(PlayerColor::Black, 49);
	mboard[50] = std::make_unique<Pawn>(PlayerColor::Black, 50);
	mboard[51] = std::make_unique<Pawn>(PlayerColor::Black, 51);
	mboard[52] = std::make_unique<Pawn>(PlayerColor::Black, 52);
	mboard[53] = std::make_unique<Pawn>(PlayerColor::Black, 53);
	mboard[54] = std::make_unique<Pawn>(PlayerColor::Black, 54);
	mboard[55] = std::make_unique<Pawn>(PlayerColor::Black, 55);
	mboard[56] = std::make_unique<Pawn>(PlayerColor::Black, 56);
	this->mboard = mboard;
	cout << "RRR" << endl;

	/*
	//캐슬링
	unique_ptr<Piece>* mboard = new unique_ptr<Piece>[65];
	mboard[1] = std::make_unique<Rook>(PlayerColor::White, 1);
	mboard[5] = std::make_unique<King>(PlayerColor::White, 5);
	mboard[8] = std::make_unique<Rook>(PlayerColor::White, 8);

	mboard[57] = std::make_unique<Rook>(PlayerColor::Black, 57);
	mboard[61] = std::make_unique<King>(PlayerColor::Black, 61);
	mboard[64] = std::make_unique<Rook>(PlayerColor::Black, 64);
	*/
	/*
	//스테일메이트
	unique_ptr<Piece>* board = new unique_ptr<Piece>[65];
	board[8] = std::make_unique<King>(PlayerColor::White, 8);

	board[9] = std::make_unique<Rook>(PlayerColor::Black, 9);
	board[61] = std::make_unique<King>(PlayerColor::Black, 61);
	board[62] = std::make_unique<Rook>(PlayerColor::Black, 62);
*/
	/*
	unique_ptr<Piece>* board = new unique_ptr<Piece>[65];
	board[8] = std::make_unique<King>(PlayerColor::White, 8);

	board[9] = std::make_unique<Pawn>(PlayerColor::Black, 9);
	board[9]->Set_doMove(true);
	board[61] = std::make_unique<King>(PlayerColor::Black, 61);
	board[62] = std::make_unique<Rook>(PlayerColor::Black, 62);
	*/
	//mboard = board;
	return mboard;
	
}

unique_ptr<Piece>* Board::Get_board()
{
	return mboard;
}

Piece* Board::Get_Piece(unique_ptr<Piece> board[],int pos)
{
	return board[pos].get();
}

int Board::ChangePositionStringToInt(string pos)
{
	int posInt;
	char* ch = &pos[1];
	/*if (pos[0] >= 65 || pos[0] <= 90)
	{
		pos[0] = pos[0] + 32;
	}*/
	
	if (!(pos[1] >= 48 || pos[1] <= 57))
	{
		return 0;
	}
	
	switch (pos[0])
	{
	case 'a':
		posInt = ((stoi(ch) - 1) * 8) + 1;
		break;
	case 'b':
		posInt = ((stoi(ch) - 1) * 8) + 2;
		break;
	case 'c':
		posInt = ((stoi(ch) - 1) * 8) + 3;
		break;
	case 'd':
		posInt = ((stoi(ch) - 1) * 8) + 4;
		break;
	case 'e':
		posInt = ((stoi(ch) - 1) * 8) + 5;
		break;
	case 'f':
		posInt = ((stoi(ch) - 1) * 8) + 6;
		break;
	case 'g':
		posInt = ((stoi(ch) - 1) * 8) + 7;
		break;
	case 'h':
		posInt = ((stoi(ch) - 1) * 8) + 8;
		break;

	case 's':
		posInt = 99;
		break;
	default:
		posInt = 0;
		break;
	}
	return posInt;
}


char Board::PieceTypeChar(Piece* piece)
{
	if (piece == nullptr)
		return ' ';
	switch (piece->get_PieceType())
	{
	case PieceType::BISHOP:
		return 'B';
	case PieceType::KING:
		return 'K';
	case PieceType::KNIGHT:
		return 'N';
	case PieceType::PAWN:
		return 'P';
	case PieceType::QUEEN:
		return 'Q';
	case PieceType::ROOK:
		return'R';

	}

}

vector<int> Board::PieceSelect(unique_ptr<Piece> board[], int selPos)
{
	
	if (!selected)
	{
		selectPieceIntPos = selPos;
		if (selectPieceIntPos == 99)
			surrender = true;
		else if (board[selectPieceIntPos] == nullptr)
		{
			movablePlace.push_back(98);
			return movablePlace;
		}
		else if (board[selectPieceIntPos]->get_PlayerColor() != PlayerColor(turn % 2))
		{
			movablePlace.push_back(98);
			return movablePlace;
		}
		else if (board[selectPieceIntPos]->get_PlayerColor() == PlayerColor(turn % 2))
		{
			selected = true;
			//왕 움직임
			if (board[selectPieceIntPos]->get_PieceType() == PieceType::KING)
			{
				vector<int> king_ptr = board[selectPieceIntPos]->CanMovePlace(board);
				movablePlace = KingMovable(board, king_ptr, selectPieceIntPos, PlayerColor(turn % 2));

				//캐슬링
				if (KingSideCastling(board, selectPieceIntPos, PlayerColor(turn % 2)))
				{
					movablePlace.push_back(selectPieceIntPos + 2);
					kingSideCastling = selectPieceIntPos + 2;
				}
				if (QueenSideCastling(board, selectPieceIntPos, PlayerColor(turn % 2)))
				{
					movablePlace.push_back(selectPieceIntPos - 2);
					queenSideCastling = selectPieceIntPos - 2;
				}
			}
			//앙파상
			else if (board[selectPieceIntPos]->get_PieceType() == PieceType::PAWN)
			{
				movablePlace = board[selectPieceIntPos]->CanMovePlace(board);
				if (an_passnt.pawnPos != 0)
				{
					if (turn % 2 != an_passnt.turn % 2)
					{
						int pos = abs(selectPieceIntPos - an_passnt.an_passntPos);
						if (pos == 7 && selectPieceIntPos % 8 != 0)
							movablePlace.push_back(an_passnt.an_passntPos);
						else if (pos == 9 && selectPieceIntPos % 8 != 1)
							movablePlace.push_back(an_passnt.an_passntPos);
					}
				}
			}
			else
			{
				vector<int> v_ptr;
				bool br;
				movablePlace = board[selectPieceIntPos]->CanMovePlace(board);
				for (int i = 0; i < movablePlace.size(); i++)
				{
					unique_ptr<Piece> piece_ptr;
					piece_ptr = move(board[movablePlace[i]]);
					board[movablePlace[i]] = move(board[selectPieceIntPos]);
					board[movablePlace[i]]->Set_piecePosition(movablePlace[i]);
					for (int a = 1; a < 65; a++)
					{
						br = false;
						if (board[a] != nullptr)
						{
							if (board[a]->get_PlayerColor() == PlayerColor((turn+1) % 2))
							{
								if (Check_Check(board, a, PlayerColor((turn + 1) % 2)) != 0)
								{
									br = true;
									break;
								}
							}
						}
					}
					if (!br)
						v_ptr.push_back(movablePlace[i]);
					board[selectPieceIntPos] = move(board[movablePlace[i]]);
					board[selectPieceIntPos]->Set_piecePosition(selectPieceIntPos);
					board[movablePlace[i]] = move(piece_ptr);
				}

				movablePlace = v_ptr;
			}
			

			if (check)
			{
				if (board[selectPieceIntPos]->get_PieceType() == PieceType::KING)
				{
					vector<int> king_ptr = board[selectPieceIntPos]->CanMovePlace(board);
					movablePlace = KingMovable(board, king_ptr, selectPieceIntPos, PlayerColor(turn % 2));

					//캐슬링
					if (KingSideCastling(board, selectPieceIntPos, PlayerColor(turn % 2)))
					{
						movablePlace.push_back(selectPieceIntPos + 2);
						kingSideCastling = selectPieceIntPos + 2;
					}
					if (QueenSideCastling(board, selectPieceIntPos, PlayerColor(turn % 2)))
					{
						movablePlace.push_back(selectPieceIntPos - 2);
						queenSideCastling = selectPieceIntPos - 2;
					}
				}
				else
				{
					vector<int> move_ptr;
					move_ptr.push_back(99);
					for (int c = 0; c < checkMovable.size(); c++)
					{
						for (int m = 0; m < movablePlace.size(); m++)
						{
							if (checkMovable[c] == movablePlace[m])
								move_ptr.push_back(checkMovable[c]);
						}
					}
					movablePlace = move_ptr;
				}

			}
		}
	}
	return movablePlace;
}
int Board::PieceMove(unique_ptr<Piece> board[], int selPos)
{
	selectMoveIntPos = selPos;
	bool find_pos;

	if (promotion)
	{
		int enemyKing;
		//체크
		if (enemyKing = Check_Check(board, selectMoveIntPos, PlayerColor(turn % 2))) //체크 확인
		{
			check = true;
			checkPos = selectMoveIntPos;
		}

		//스테일메이트
		if (StalemateCheck(board, PlayerColor(turn % 2)))
		{
			check = false;
			checkmate = false;
			stalemate = true;
			selected = false;
			find_pos = false;
			kingSideCastling = 0;
			queenSideCastling = 0;
			selectPieceIntPos = 0;
			selectMoveIntPos = 0;
			movablePlace.clear();
			turn++;
			return 99;
		}

		if (check) // 체크메이트 확인
		{
			checkMovable.clear();
			checkMovable.push_back(checkPos);
			vector<int> move_ptr;
			move_ptr = board[checkPos]->CanMovePlace(board);
			for (int m = 0; m < move_ptr.size(); m++) //체크인 말의 움직이는 곳이 체크가 되는곳 찾기
			{
				unique_ptr<Piece> piece_ptr = move(board[move_ptr[m]]);
				board[move_ptr[m]] = move(board[checkPos]);
				board[move_ptr[m]]->Set_piecePosition(move_ptr[m]);
				int int_ptr = Check_Check(board, move_ptr[m], PlayerColor(turn % 2));
				if (enemyKing == int_ptr)
					checkMovable.push_back(move_ptr[m]);
				board[checkPos] = move(board[move_ptr[m]]);
				board[checkPos]->Set_piecePosition(checkPos);
				board[move_ptr[m]] = move(piece_ptr);
			}
			if (CheckmateMoveSimulation(board, enemyKing, checkMovable, PlayerColor(turn % 2)))
			{
				vector<int> v_ptr;
				v_ptr = KingMovable(board, board[enemyKing]->CanMovePlace(board), enemyKing, PlayerColor((turn + 1) % 2));
				if (v_ptr.size() == 0)
				{
					check = false;
					stalemate = false;
					checkmate = true;
				}
				else if (v_ptr.size() != 0)
				{
					check = true;
					stalemate = false;
					checkmate = false;
				}
			}
			else
			{
				check = true;
				stalemate = false;
				checkmate = false;
			}
		}
		selected = false;
		find_pos = false;
		kingSideCastling = 0;
		queenSideCastling = 0;
		selectPieceIntPos = 0;
		selectMoveIntPos = 0;
		movablePlace.clear();
		if (an_passnt.turn != turn)
		{
			an_passnt.an_passntPos = 0;
			an_passnt.pawnPos = 0;
			an_passnt.turn = 0;
		}
		turn++;
		return 99;
	}

	if (selected)
	{
		if (selectMoveIntPos == 99)
			surrender = true;
		else if (selectMoveIntPos == selectPieceIntPos)
		{
			selected = false;
			find_pos = false;

			kingSideCastling = 0;
			queenSideCastling = 0;
			selectPieceIntPos = 0;
			selectMoveIntPos = 0;
			movablePlace.clear();
			return 99;
		}

		for (int m = 0; m < movablePlace.size(); m++)
		{
			if (movablePlace[m] == selectMoveIntPos)
			{
				find_pos = true;
				check = false;
				break;
			}
			find_pos = false;
		}


		if (find_pos)
		{
			int enemyKing;
			board[selectMoveIntPos] = move(board[selectPieceIntPos]);
			board[selectMoveIntPos]->Set_piecePosition(selectMoveIntPos);
			board[selectMoveIntPos]->Set_doMove(true);

			//캐슬링
			if (selectMoveIntPos == kingSideCastling)
			{
				selectMoveIntPos = selectMoveIntPos - 1;
				board[selectMoveIntPos] = move(board[selectPieceIntPos + 3]);
				board[selectMoveIntPos]->Set_piecePosition(selectMoveIntPos);
				board[selectMoveIntPos]->Set_doMove(true);
				kingSideCastling = 0;
			}
			else if (selectMoveIntPos == queenSideCastling)
			{
				selectMoveIntPos = selectMoveIntPos + 1;
				board[selectMoveIntPos] = move(board[selectPieceIntPos - 4]);
				board[selectMoveIntPos]->Set_piecePosition(selectMoveIntPos);
				board[selectMoveIntPos]->Set_doMove(true);
				queenSideCastling = 0;
			}

			//앙파상
			if (board[selectMoveIntPos]->get_PieceType() == PieceType::PAWN)
			{
				if (abs(selectPieceIntPos - selectMoveIntPos) == 16)
				{
					for (int i = 0; i < movablePlace.size(); i++)
					{
						if (abs(movablePlace[i] - selectPieceIntPos) == 8)
						{
							an_passnt.pawnPos = selectMoveIntPos;
							an_passnt.an_passntPos = movablePlace[i];
							an_passnt.turn = turn;
						}
					}
				}
				if (selectMoveIntPos == an_passnt.an_passntPos)
				{
					board[an_passnt.pawnPos] = nullptr;
					an_passnt.an_passntPos = 0;
					an_passnt.pawnPos = 0;
					an_passnt.turn = 0;
				}
			}

			//프로모션 
			if (board[selectMoveIntPos]->get_PieceType() == PieceType::PAWN)
			{
				if (selectMoveIntPos / 8 == 0 || selectMoveIntPos / 8 == 7)
				{
					int ptr = selectPieceIntPos;
					selectPieceIntPos = selectMoveIntPos;
					promotion = true;
					selectPieceIntPos = ptr;
					return 99;
				}
			}


			//체크
			if (enemyKing = Check_Check(board, selectMoveIntPos, PlayerColor(turn % 2))) //체크 확인
			{
				check = true;
				checkPos = selectMoveIntPos;
			}

			//스테일메이트
			if (StalemateCheck(board, PlayerColor(turn % 2)))
			{
				check = false;
				checkmate = false;
				stalemate = true;
				selected = false;
				find_pos = false;
				kingSideCastling = 0;
				queenSideCastling = 0;
				selectPieceIntPos = 0;
				selectMoveIntPos = 0;
				movablePlace.clear();
				turn++;
				return 99;
			}

			if (check) // 체크메이트 확인
			{
				checkMovable.clear();
				checkMovable.push_back(checkPos);
				vector<int> move_ptr;
				move_ptr = board[checkPos]->CanMovePlace(board);
				for (int m = 0; m < move_ptr.size(); m++) //체크인 말의 움직이는 곳이 체크가 되는곳 찾기
				{
					unique_ptr<Piece> piece_ptr = move(board[move_ptr[m]]);
					board[move_ptr[m]] = move(board[checkPos]);
					board[move_ptr[m]]->Set_piecePosition(move_ptr[m]);
					int int_ptr = Check_Check(board, move_ptr[m], PlayerColor(turn % 2));
					if (enemyKing == int_ptr)
						checkMovable.push_back(move_ptr[m]);
					board[checkPos] = move(board[move_ptr[m]]);
					board[checkPos]->Set_piecePosition(checkPos);
					board[move_ptr[m]] = move(piece_ptr);
				}
				if (CheckmateMoveSimulation(board, enemyKing, checkMovable, PlayerColor(turn % 2)))
				{
					vector<int> v_ptr;
					v_ptr = KingMovable(board, board[enemyKing]->CanMovePlace(board), enemyKing, PlayerColor((turn + 1) % 2));
					if (v_ptr.size() == 0)
					{
						check = false;
						stalemate = false;
						checkmate = true;
					}
					else if (v_ptr.size() != 0)
					{
						check = true;
						stalemate = false;
						checkmate = false;
					}
				}
				else
				{
					check = true;
					stalemate = false;
					checkmate = false;
				}
			}
			selected = false;
			find_pos = false;
			kingSideCastling = 0;
			queenSideCastling = 0;
			selectPieceIntPos = 0;
			selectMoveIntPos = 0;
			movablePlace.clear();
			if (an_passnt.turn != turn)
			{
				an_passnt.an_passntPos = 0;
				an_passnt.pawnPos = 0;
				an_passnt.turn = 0;
			}
			turn++;
			return 99; //성공 99
		}
		else if (!find_pos)
		{
			return 98; //실패 98
		}

	}

}

bool Board::KingMoveSimulation(unique_ptr<Piece> board[],int pos, PlayerColor nowPlayer)
{
	
	vector<int> dengerousPlace = FindDengerousPlace(board, nowPlayer);
	for (vector<int>::iterator d = dengerousPlace.begin(); d != dengerousPlace.end(); d++)
	{
		if (pos == *d)
			return false;
	}
	return true;
}

vector<int> Board::FindDengerousPlace(unique_ptr<Piece> board[], PlayerColor nowPlayer)
{
	vector<int> dengerousPlace;
	for (int i = 1; i < 65; i++)
	{
		if (board[i] != nullptr)
		{
			if (board[i]->get_PlayerColor() != nowPlayer)
			{
				vector<int> getPos = board[i]->CanMovePlace(board);
				dengerousPlace.insert(dengerousPlace.end(), getPos.begin(), getPos.end());
			}
		}
	}
	sort(dengerousPlace.begin(), dengerousPlace.end());
	dengerousPlace.erase(unique(dengerousPlace.begin(), dengerousPlace.end()), dengerousPlace.end());
	return dengerousPlace;
}

vector<int> Board::KingMovable(unique_ptr<Piece> board[], vector<int> pos,int selectPos, PlayerColor nowPlayer)
{
	vector<int> v_ptr;
	for (int i = 0; i < pos.size(); i++)
	{
		unique_ptr<Piece> ptr;
		ptr = move(board[pos[i]]);
		board[pos[i]] = move(board[selectPos]);
		if (!KingMoveSimulation(board, pos[i], nowPlayer))
		{
			board[selectPos] = move(board[pos[i]]);
			board[pos[i]] = move(ptr);
		}
		else
		{
			board[selectPos] = move(board[pos[i]]);
			board[pos[i]] = move(ptr);
			v_ptr.push_back(pos[i]);
		}
	}
	return v_ptr;
}

int Board::Check_Check(unique_ptr<Piece> board[],int pos,PlayerColor nowPlayer)
{
	vector<int> move = board[pos]->CanMovePlace(board);
	for (int i = 0; i < move.size(); i++)
	{
		if (board[move[i]] != nullptr)
		{
			if (board[move[i]]->get_PlayerColor()!= nowPlayer && board[move[i]]->get_PieceType() == PieceType::KING)
			{
				return move[i];
			}
		}
	}
	return 0;
}

bool Board::CheckmateMoveSimulation(unique_ptr<Piece> board[],int enemyKing, vector<int> dengerousPos,PlayerColor nowPlayer)
{
	
	for (int i = 1; i < 65; i++)
	{
		if (board[i] == nullptr)
			continue;
		else if (board[i]->get_PlayerColor() != nowPlayer)
		{
			vector<int> move_ptr = board[i]->CanMovePlace(board);
			if (board[i]->get_PieceType() != PieceType::KING) //왕은 왕이 알아서 잘 움직임
			{
				for (int m = 0; m < move_ptr.size(); m++)
				{
					for (int d = 0; d < dengerousPos.size(); d++)
					{
						if (move_ptr[m] == dengerousPos[d])
							return false;
					}
				}
			}
		}
	}
	return true;
}

bool Board::StalemateCheck(unique_ptr<Piece> board[], PlayerColor nowPlayer)
{
	vector<int> movable;
	for (int i = 1; i < 65; i++)
	{
		if (board[i] != nullptr)
		{
			if (board[i]->get_PlayerColor() != nowPlayer)
			{
				if (board[i]->get_PieceType() == PieceType::KING) {
					movable = KingMovable(board, board[i]->CanMovePlace(board), i, board[i]->get_PlayerColor());
				}
				
				if (movable.size() != 0)
					return false;

			}
		}
	}
	if (movable.size() == 0)
		return true;
}

bool Board::KingSideCastling(unique_ptr<Piece> board[],int kingPos,PlayerColor nowPlayer)
{
	bool check;
	int rookPos = kingPos+3;
	if (!board[kingPos]->Get_doMove())
	{
		if (board[rookPos] != nullptr )
		{
			if (board[rookPos]->get_PlayerColor() == turn % 2)
			{
				if (board[rookPos]->get_PieceType() == PieceType::ROOK)
				{
					if (!board[rookPos]->Get_doMove() && !board[kingPos]->Get_doMove())
					{
						for (int i = kingPos + 1; i < rookPos; i++)
						{
							if (board[i] != nullptr)
								return false;
						}

						unique_ptr<Piece> piece_ptr_king;
						unique_ptr<Piece> piece_ptr_rook;
						piece_ptr_king = move(board[kingPos + 2]);
						piece_ptr_rook = move(board[kingPos + 1]);
						board[kingPos + 2] = move(board[kingPos]);
						board[kingPos + 2]->Set_piecePosition(kingPos + 2);
						board[kingPos + 1] = move(board[rookPos]);
						board[kingPos + 1]->Set_piecePosition(kingPos + 1);
						vector<int> dengerousPlace = FindDengerousPlace(board, nowPlayer);
						board[kingPos] = move(board[kingPos + 2]);
						board[kingPos]->Set_piecePosition(kingPos);
						board[kingPos + 2] = move(piece_ptr_king);
						board[rookPos] = move(board[kingPos + 1]);
						board[rookPos]->Set_piecePosition(rookPos);
						board[kingPos + 1] = move(piece_ptr_rook);

						for (int i = 0; i < dengerousPlace.size(); i++)
						{
							if (dengerousPlace[i] == kingPos + 2)
								return false;
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Board::QueenSideCastling(unique_ptr<Piece> board[], int kingPos, PlayerColor nowPlayer)
{
	bool check;
	int rookPos = kingPos - 4;
	if (!board[kingPos]->Get_doMove())
	{
		if (board[rookPos] != nullptr)
		{
			if (board[rookPos]->get_PlayerColor() == turn % 2)
			{
				if (board[rookPos]->get_PieceType() == PieceType::ROOK)
				{
					if (!board[rookPos]->Get_doMove() && !board[kingPos]->Get_doMove())
					{
						for (int i = kingPos - 1; i > rookPos; i--)
						{
							if (board[i] != nullptr)
								return false;
						}
						unique_ptr<Piece> piece_ptr_king;
						unique_ptr<Piece> piece_ptr_rook;
						piece_ptr_king = move(board[kingPos - 2]);
						piece_ptr_rook = move(board[kingPos - 1]);
						board[kingPos - 2] = move(board[kingPos]);
						board[kingPos - 2]->Set_piecePosition(kingPos - 2);
						board[kingPos - 1] = move(board[rookPos]);
						board[kingPos - 1]->Set_piecePosition(kingPos - 1);
						vector<int> dengerousPlace = FindDengerousPlace(board, nowPlayer);
						board[kingPos] = move(board[kingPos - 2]);
						board[kingPos]->Set_piecePosition(kingPos);
						board[kingPos - 2] = move(piece_ptr_king);
						board[rookPos] = move(board[kingPos - 1]);
						board[rookPos]->Set_piecePosition(rookPos);
						board[kingPos - 1] = move(piece_ptr_rook);
						for (int i = 0; i < dengerousPlace.size(); i++)
						{
							if (dengerousPlace[i] == kingPos - 2)
								return false;
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Board::Promotion(unique_ptr<Piece> board[], int pos, int selNum)
{


	CString fileName;

	cout << "Promotion" << endl;
	cout << "1. Rook   2. Knighit   3. Bishop   4. Queen" << endl;
	cout << "Select piece number : ";

	switch (selNum)
	{
	case 1:
		board[pos] = make_unique<Rook>(board[pos]->get_PlayerColor(), board[pos]->Get_piecePosition());
		fileName.Format(L"Pieces\\%s_%s.png", turn % 2 == 0 ? L"Black" : L"White", L"ROOK");
		board[pos]->imgsrc.Load(fileName);
		break;
	case 2:
		board[pos] = make_unique<Knight>(board[pos]->get_PlayerColor(), board[pos]->Get_piecePosition());
		fileName.Format(L"Pieces\\%s_%s.png", turn % 2 == 0 ? L"Black" : L"White", L"KNIGHT");
		board[pos]->imgsrc.Load(fileName);
		break;
	case 3:
		board[pos] = make_unique<Bishop>(board[pos]->get_PlayerColor(), board[pos]->Get_piecePosition());
		fileName.Format(L"Pieces\\%s_%s.png", turn % 2 == 0 ? L"Black" : L"White", L"BISHOP");
		board[pos]->imgsrc.Load(fileName);
		break;
	case 4:
		board[pos] = make_unique<Queen>(board[pos]->get_PlayerColor(), board[pos]->Get_piecePosition());
		fileName.Format(L"Pieces\\%s_%s.png", turn % 2 == 0 ? L"Black" : L"White", L"QUEEN");
		board[pos]->imgsrc.Load(fileName);
		break;
	default:
		promotion = false;
		break;
	}

	PieceMove(board, pos);
	selectPieceIntPos = 0;
	//Draw_Board();
}

bool Board::Get_Selected()
{
	return selected;
}

int Board::Get_turn()
{
	return turn;
}

bool Board::Get_check()
{
	return check;
}

bool Board::Get_checkmate()
{
	return checkmate;
}

bool Board::Get_stalemate()
{
	return stalemate;
}

bool Board::Get_promotion()
{
	return promotion;
}

void Board::Set_promotion(bool pro)
{
	promotion = pro;
}