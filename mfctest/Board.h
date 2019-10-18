#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<Windows.h>
#include<math.h>
#include<string>
#include "Piece.h"
#include"Bishop.h"
#include"King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include"Rook.h"
#include "An_passnt.h"

#define DARKRED_BLACK 64 //일반 홀수
#define DARKRED_WHITE 79
#define DARKYELLOW_BLACK 96// //일반 짝수
#define DARKYELLOW_WHITE 111
#define DARKGREEN_BLACK 32 //선택시
#define DARKGREEN_WHITE 47
#define DARKBLUE_BLACK 16 //이동가능
#define DARKBLUE_WHITE 31
#define NOMALCOLOR 7 //보통

class Board
{
protected:
	vector<int> movablePlace;
	vector<int> kingMove;
	vector<int> checkMovable;
	An_passnt an_passnt;
	bool surrender;
	bool check;
	bool checkmate;
	bool stalemate;
	int kingSideCastling;
	int queenSideCastling;
	int turn;
	int selectPieceIntPos;
	int checkPos;
	string selectPieceStrPos;
	string selectMoveStrPos;
	bool selected;
	int selectMoveIntPos;
	unique_ptr<Piece>* take_a_back_board;
	unique_ptr<Piece>* mboard;
	unique_ptr<Piece>* copyBoard;
	HANDLE handle;

public:
	Board() = delete;
	Board(unique_ptr<Piece> board[]);
	void StartGame();
	void Draw_Board();
	char PieceTypeChar(Piece* piece);
	int ChangePositionStringToInt(string pos);
	void SurrenderPrint();
	vector<int> FindDengerousPlace(unique_ptr<Piece> board[],PlayerColor nowPlayer);
	bool KingMoveSimulation(unique_ptr<Piece> board[],int pos,PlayerColor nowPlayer);
	vector<int> KingMovable(unique_ptr<Piece> board[], vector<int> pos,int selectPos, PlayerColor nowPlayer);
	int Check_Check(unique_ptr<Piece> board[], int pos, PlayerColor nowPlayer);
	bool CheckmateMoveSimulation(unique_ptr<Piece> board[], int enemyKing, vector<int> dengerousPos, PlayerColor nowPlayer);
	bool StalemateCheck(unique_ptr<Piece> board[], PlayerColor nowPlayer);
	bool KingSideCastling(unique_ptr<Piece> board[],int kingPos,PlayerColor nowPlayer);
	bool QueenSideCastling(unique_ptr<Piece> board[], int kingPos, PlayerColor nowPlayer);
	void Promotion(unique_ptr<Piece> board[],int pos);

};