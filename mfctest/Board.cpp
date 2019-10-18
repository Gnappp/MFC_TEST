#include "Board.h"

Board::Board(unique_ptr<Piece> board[])
	: an_passnt()
	, surrender(false)
	, check(false)
	, checkmate(false)
	, stalemate(false)
	, turn(0)
	, selectMoveIntPos(0)
	, kingSideCastling(0)
	, queenSideCastling(0)
	, selectPieceIntPos(0)
	, checkPos(0)
	, selectPieceStrPos(" ")
	, selectMoveStrPos(" ")
	, take_a_back_board(nullptr)
	, selected(false)

{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	mboard = board;
	copyBoard = new unique_ptr<Piece>[65];
	StartGame();
}

void Board::StartGame()
{
	string str;
	bool find_pos = false;
	while (true)
	{
		system("cls");
		Draw_Board();
		if (surrender)
		{
			SurrenderPrint();
			break;
		}

		if (check)
		{
			cout << "!!Check!!" << endl;
			//check = false;
		}
		else if (checkmate)
		{
			cout << "!!Checkmate!!" << endl << "!!" << (turn % 2 == 0 ? str = "White" : str = "Black") << " is WIN!!" << endl;
			break;
		}
		else if (stalemate)
		{
			cout << "!!Stalemate!!" << endl << "!! DROW !!" << endl;
			break;
		}

		if (!selected)
		{
			cout << (turn % 2 == 0 ? str = "Black" : str = "White") << " is turn" << endl << "Surrender is s0" << endl << "Select Piece : ";
			cin >> selectPieceStrPos;
			selectPieceIntPos = ChangePositionStringToInt(selectPieceStrPos);
			if (selectPieceIntPos == 99)
				surrender = true;
			else if (mboard[selectPieceIntPos] == nullptr)
				continue;
			else if (mboard[selectPieceIntPos]->get_PlayerColor() == PlayerColor(turn % 2))
			{
				selected = true;
				//왕 움직임
				if (mboard[selectPieceIntPos]->get_PieceType() == PieceType::KING) 
				{
					movablePlace = KingMovable(mboard, mboard[selectPieceIntPos]->CanMovePlace(mboard), selectPieceIntPos, PlayerColor(turn % 2));
					if (KingSideCastling(mboard, selectPieceIntPos, PlayerColor(turn % 2)))
					{
						movablePlace.push_back(selectPieceIntPos + 2);
						kingSideCastling = selectPieceIntPos+2;
					}
					if(QueenSideCastling(mboard,selectPieceIntPos,PlayerColor(turn%2)))
					{ 
						movablePlace.push_back(selectPieceIntPos - 2);
						queenSideCastling = selectPieceIntPos - 2;
					}
				}
				//앙파상
				else if (mboard[selectPieceIntPos]->get_PieceType() == PieceType::PAWN)
				{
					movablePlace = mboard[selectPieceIntPos]->CanMovePlace(mboard);
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
					movablePlace = mboard[selectPieceIntPos]->CanMovePlace(mboard);
				if (check)
				{
					if (mboard[selectPieceIntPos]->get_PieceType() == PieceType::KING) //왕 움직임
						movablePlace = KingMovable(mboard, mboard[selectPieceIntPos]->CanMovePlace(mboard), selectPieceIntPos, PlayerColor(turn % 2));
					else
					{
						vector<int> move_ptr;
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
		else if (selected)
		{
			cout << (turn % 2 == 0 ? str = "Black" : str = "White") << " is turn" << endl
				<< "Surrender is s0 , Cancel is " << selectPieceStrPos << endl
				<< "Select Piece : " << selectPieceStrPos << endl;
			cout << "Select move position : ";
			cin >> selectMoveStrPos;
			selectMoveIntPos = ChangePositionStringToInt(selectMoveStrPos);
			if (selectMoveIntPos == 99)
				surrender = true;
			else if (selectMoveStrPos == selectPieceStrPos)
			{
				selected = false;
				find_pos = false;
				
				kingSideCastling = 0;
				queenSideCastling = 0;
				selectPieceIntPos = 0;
				selectPieceStrPos.clear();
				selectMoveIntPos = 0;
				selectMoveStrPos.clear();
				movablePlace.clear();
				continue;
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
				mboard[selectMoveIntPos] = move(mboard[selectPieceIntPos]);
				mboard[selectMoveIntPos]->Set_piecePosition(selectMoveIntPos);
				mboard[selectMoveIntPos]->Set_doMove(true);

				//캐슬링
				if (selectMoveIntPos == kingSideCastling)
				{
					selectMoveIntPos = selectMoveIntPos - 1;
					mboard[selectMoveIntPos] = move(mboard[selectPieceIntPos + 3]);
					mboard[selectMoveIntPos]->Set_piecePosition(selectMoveIntPos);
					mboard[selectMoveIntPos]->Set_doMove(true);
					kingSideCastling = 0;
				}
				else if (selectMoveIntPos == queenSideCastling)
				{
					selectMoveIntPos = selectMoveIntPos + 1;
					mboard[selectMoveIntPos] = move(mboard[selectPieceIntPos -4]);
					mboard[selectMoveIntPos]->Set_piecePosition(selectMoveIntPos);
					mboard[selectMoveIntPos]->Set_doMove(true);
					queenSideCastling = 0;
				}

				//앙파상
				if (mboard[selectMoveIntPos]->get_PieceType() == PieceType::PAWN)
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
						mboard[an_passnt.pawnPos] = nullptr;
						an_passnt.an_passntPos = 0;
						an_passnt.pawnPos = 0;
						an_passnt.turn = 0;
					}
				}
				
				//프로모션 
				if (mboard[selectMoveIntPos]->get_PieceType() == PieceType::PAWN)
				{
					if (selectMoveIntPos / 8 == 0 || selectMoveIntPos / 8 == 7)
					{
						int ptr=selectPieceIntPos;
						selectPieceIntPos = selectMoveIntPos;
						Promotion(mboard, selectMoveIntPos);
						selectPieceIntPos = ptr;
					}
				}


				//체크
				if (enemyKing = Check_Check(mboard, selectMoveIntPos, PlayerColor(turn % 2))) //체크 확인
				{
					check = true;
					checkPos = selectMoveIntPos;
				}

				if (StalemateCheck(mboard, PlayerColor(turn % 2)))
				{
					check = false;
					checkmate = false;
					stalemate = true;
					selected = false;
					find_pos = false;
					kingSideCastling = 0;
					queenSideCastling = 0;
					selectPieceIntPos = 0;
					selectPieceStrPos.clear();
					selectMoveIntPos = 0;
					selectMoveStrPos.clear();
					movablePlace.clear();
					turn++;
					continue;
				}

				if (check) // 체크메이트 확인
				{
					checkMovable.clear();
					checkMovable.push_back(checkPos);
					vector<int> move_ptr;
					move_ptr = mboard[checkPos]->CanMovePlace(mboard);
					for (int m = 0; m < move_ptr.size(); m++) //체크인 말이 움직이는곳이 체크인곳만 넣기.
					{
						unique_ptr<Piece> piece_ptr = move(mboard[move_ptr[m]]);
						mboard[move_ptr[m]] = move(mboard[checkPos]);
						mboard[move_ptr[m]]->Set_piecePosition(move_ptr[m]);
						int int_ptr = Check_Check(mboard, move_ptr[m], PlayerColor(turn % 2));
						if (enemyKing==int_ptr)
							checkMovable.push_back(move_ptr[m]);
						mboard[checkPos] = move(mboard[move_ptr[m]]);
						mboard[checkPos]->Set_piecePosition(checkPos);
						mboard[move_ptr[m]] = move(piece_ptr);
					}
					if (CheckmateMoveSimulation(mboard, enemyKing, checkMovable, PlayerColor(turn % 2)))
					{
						vector<int> v_ptr;
						v_ptr = KingMovable(mboard, mboard[enemyKing]->CanMovePlace(mboard), enemyKing, PlayerColor((turn + 1) % 2));
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
				selectPieceStrPos.clear();
				selectMoveIntPos = 0;
				selectMoveStrPos.clear();
				movablePlace.clear();
				if (an_passnt.turn != turn )
				{
					an_passnt.an_passntPos = 0;
					an_passnt.pawnPos = 0;
					an_passnt.turn = 0;
				}
				turn++;
			}
			else if (!find_pos)
				continue;

		}
	}
}


void Board::Draw_Board()
{
	vector<int> v;
	bool movable = false;

	cout << "   a  b  c  d  e  f  g  h  " << endl; 
	for (int i = 7; i >= 0; i--)
	{
		for (int a = 1; a < 9; a++)
		{
			if (a == 1)
				cout << i + 1 << " ";
			if (selected)
			{
				v = movablePlace;
				for (vector<int>::iterator m =v.begin(); m != v.end(); m++) //이동가능한 자리 찾기
				{
					if (*m == (i * 8 + a))
					{
						v.erase(m);
						movable = true;
						break;
					}
				}
			}
			if ((i + 1) % 2 == 1) //숫자가 홀수일때
			{
				
				if (movable)
				{
					if (mboard[(i * 8 + a)] == nullptr)
						SetConsoleTextAttribute(handle, DARKBLUE_WHITE);

					else if (mboard[(i * 8 + a)]->get_PlayerColor() == PlayerColor::Black)
						SetConsoleTextAttribute(handle, DARKBLUE_BLACK);

					else if (mboard[(i * 8 + a)]->get_PlayerColor() == PlayerColor::White)
						SetConsoleTextAttribute(handle, DARKBLUE_WHITE);

					movable = false;
				}
				else if (selected && (i * 8 + a) == selectPieceIntPos) //선택
				{
					if (mboard[selectPieceIntPos]->get_PlayerColor() == PlayerColor::Black)
						SetConsoleTextAttribute(handle, DARKGREEN_BLACK);

					else if (mboard[selectPieceIntPos]->get_PlayerColor() == PlayerColor::White)
						SetConsoleTextAttribute(handle, DARKGREEN_WHITE);
				}
				else if ((i * 8 + a) % 2 == 1) //일반
				{
					if (mboard[i * 8 + a] == nullptr)
						SetConsoleTextAttribute(handle, DARKRED_BLACK);

					else if (mboard[i * 8 + a]->get_PlayerColor() == PlayerColor::Black)
						SetConsoleTextAttribute(handle, DARKRED_BLACK);

					else if (mboard[i * 8 + a]->get_PlayerColor() == PlayerColor::White)
						SetConsoleTextAttribute(handle, DARKRED_WHITE);
				}
				else if ((i * 8 + a) % 2 != 1)
				{
					if (mboard[i * 8 + a] == nullptr)
						SetConsoleTextAttribute(handle, DARKYELLOW_BLACK);

					else if (mboard[i * 8 + a]->get_PlayerColor() == PlayerColor::Black)
						SetConsoleTextAttribute(handle, DARKYELLOW_BLACK);

					else if (mboard[i * 8 + a]->get_PlayerColor() == PlayerColor::White)
						SetConsoleTextAttribute(handle, DARKYELLOW_WHITE);
				}
				
			}

			else if ((i + 1) % 2 == 0) //숫자가 짝수일때
			{
				if (movable)
				{
					if (mboard[(i * 8 + a)] == nullptr)
						SetConsoleTextAttribute(handle, DARKBLUE_WHITE);
					else if (mboard[(i * 8 + a)]->get_PlayerColor() == PlayerColor::Black)
						SetConsoleTextAttribute(handle, DARKBLUE_BLACK);

					else if (mboard[(i * 8 + a)]->get_PlayerColor() == PlayerColor::White)
						SetConsoleTextAttribute(handle, DARKBLUE_WHITE);

					movable = false;
				}

				else if (selected && (i * 8 + a) == selectPieceIntPos) //선택
				{
					if (mboard[selectPieceIntPos]->get_PlayerColor() == PlayerColor::Black)
						SetConsoleTextAttribute(handle, DARKGREEN_BLACK);

					else if (mboard[selectPieceIntPos]->get_PlayerColor() == PlayerColor::White)
						SetConsoleTextAttribute(handle, DARKGREEN_WHITE);
				}
				else if ((i * 8 + a) % 2 == 1) //일반
				{
					if (mboard[i * 8 + a] == nullptr)
						SetConsoleTextAttribute(handle, DARKYELLOW_BLACK);

					else if (mboard[i * 8 + a]->get_PlayerColor() == PlayerColor::Black)
						SetConsoleTextAttribute(handle, DARKYELLOW_BLACK);

					else if (mboard[i * 8 + a]->get_PlayerColor() == PlayerColor::White)
						SetConsoleTextAttribute(handle, DARKYELLOW_WHITE);
				}
				else if ((i * 8 + a) % 2 != 1)
				{
					if (mboard[i * 8 + a] == nullptr)
						SetConsoleTextAttribute(handle, DARKRED_BLACK);

					else if (mboard[i * 8 + a]->get_PlayerColor() == PlayerColor::Black)
						SetConsoleTextAttribute(handle, DARKRED_BLACK);

					else if (mboard[i * 8 + a]->get_PlayerColor() == PlayerColor::White)
						SetConsoleTextAttribute(handle, DARKRED_WHITE);
				}
				
			}
			if (mboard[i * 8 + a] == nullptr)
			{
				cout << " " << " " << " ";
				SetConsoleTextAttribute(handle, NOMALCOLOR);
			}
			else if (mboard[i * 8 + a] != nullptr)
			{
				cout << " " << PieceTypeChar(mboard[i * 8 + a].get()) << " ";
				SetConsoleTextAttribute(handle, NOMALCOLOR);
			}
			if (a == 8)
			{
				cout << " " << i + 1 << endl;
			}
		}
	}
	cout << "   a  b  c  d  e  f  g  h  " << endl;
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

void Board::SurrenderPrint()
{
	string str;
	system("cls");
	Draw_Board();
	cout << (turn % 2 == 0 ? str = "Black" : str = "White") << " Surrender!" << endl;
	cout << (turn % 2 == 0 ? str = "White" : str = "Black") << " WIN!!" << endl;
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
		if (!KingMoveSimulation(mboard, pos[i], nowPlayer))
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
			if (board[i]->get_PlayerColor() == nowPlayer)
			{
				if (board[i]->get_PieceType() == PieceType::KING)
					movable = KingMovable(board, board[i]->CanMovePlace(board), i, nowPlayer);
				else
					movable = board[i]->CanMovePlace(board);

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
	vector<int> dengerousPlace = FindDengerousPlace(board, nowPlayer);
	if (board[rookPos] != nullptr)
	{
		if (board[rookPos]->get_PieceType() == PieceType::ROOK)
		{
			if (!board[rookPos]->Get_doMove())
			{
				for (int i = kingPos + 1; i < rookPos; i++)
				{
					if (board[i] != nullptr)
						return false;
				}
				for (int i = 0; i < dengerousPlace.size(); i++)
				{
					if (dengerousPlace[i] == kingPos+2)
						return false;
				}
			}
		}
	}
	return true;
}

bool Board::QueenSideCastling(unique_ptr<Piece> board[], int kingPos, PlayerColor nowPlayer)
{
	bool check;
	int rookPos = kingPos - 4;
	vector<int> dengerousPlace = FindDengerousPlace(board, nowPlayer);
	if (board[rookPos] != nullptr)
	{
		if (board[rookPos]->get_PieceType() == PieceType::ROOK)
		{
			if (!board[rookPos]->Get_doMove())
			{
				for (int i = kingPos - 1; i > rookPos; i--)
				{
					if (board[i] != nullptr)
						return false;
				}
				for (int i = 0; i < dengerousPlace.size(); i++)
				{
					if (dengerousPlace[i] == kingPos + 2)
						return false;
				}
			}
		}
	}
	return true;
}

void Board::Promotion(unique_ptr<Piece> board[],int pos)
{
	int promotionNo;
	bool selectcheck=true;

	while (selectcheck)
	{
		system("cls");
		Draw_Board();
		cout << "Promotion" << endl;
		cout << "1. Rook   2. Knghit   3. Bishop   4. Queen" << endl;
		cout << "Select piece number : ";
		cin >> promotionNo;

		switch (promotionNo)
		{
		case 1:
			board[pos] = make_unique<Rook>(board[pos]->get_PlayerColor(), board[pos]->Get_piecePosition());
			selectcheck = false;
			break;
		case 2:
			board[pos] = make_unique<Knight>(board[pos]->get_PlayerColor(), board[pos]->Get_piecePosition());
			selectcheck = false;
			break;
		case 3:
			board[pos] = make_unique<Bishop>(board[pos]->get_PlayerColor(), board[pos]->Get_piecePosition());
			selectcheck = false;
			break;
		case 4:
			board[pos] = make_unique<Queen>(board[pos]->get_PlayerColor(), board[pos]->Get_piecePosition());
			selectcheck = false;
			break;
		default:
			selectcheck = false;
			break;
		}
	}
	selectPieceIntPos = 0;
	Draw_Board();
}
