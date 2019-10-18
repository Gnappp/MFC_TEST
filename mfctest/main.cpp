#include<iostream>
#include<windows.h>
#include "Board.h"
#include "Piece.h"
#include"Bishop.h"
#include"King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include"Rook.h"

using namespace std;

unique_ptr<Piece>* StartGame()
{
	unique_ptr<Piece>* board = new unique_ptr < Piece>[65];
	board[1] = std::make_unique<Rook>(PlayerColor::White, 1);
	board[2] = std::make_unique<Knight>(PlayerColor::White, 2);
	board[3] = std::make_unique<Bishop>(PlayerColor::White, 3);
	board[4] = std::make_unique<Queen>(PlayerColor::White, 4);
	board[5] = std::make_unique<King>(PlayerColor::White, 5);
	board[6] = std::make_unique<Bishop>(PlayerColor::White, 6);
	board[7] = std::make_unique<Knight>(PlayerColor::White, 7);
	board[8] = std::make_unique<Rook>(PlayerColor::White, 8);
	board[9] = std::make_unique<Pawn>(PlayerColor::White, 9);
	board[10] = std::make_unique<Pawn>(PlayerColor::White, 10);
	board[11] = std::make_unique<Pawn>(PlayerColor::White, 11);
	board[12] = std::make_unique<Pawn>(PlayerColor::White, 12);
	board[13] = std::make_unique<Pawn>(PlayerColor::White, 13);
	board[14] = std::make_unique<Pawn>(PlayerColor::White, 14);
	board[15] = std::make_unique<Pawn>(PlayerColor::White, 15);
	board[16] = std::make_unique<Pawn>(PlayerColor::White, 16);

	board[57] = std::make_unique<Rook>(PlayerColor::Black, 57);
	board[58] = std::make_unique<Knight>(PlayerColor::Black, 58);
	board[59] = std::make_unique<Bishop>(PlayerColor::Black, 59);
	board[60] = std::make_unique<Queen>(PlayerColor::Black, 60);
	board[61] = std::make_unique<King>(PlayerColor::Black, 61);
	board[62] = std::make_unique<Bishop>(PlayerColor::Black, 62);
	board[63] = std::make_unique<Knight>(PlayerColor::Black, 63);
	board[64] = std::make_unique<Rook>(PlayerColor::Black, 64);
	board[49] = std::make_unique<Pawn>(PlayerColor::Black, 49);
	board[50] = std::make_unique<Pawn>(PlayerColor::Black, 50);
	board[51] = std::make_unique<Pawn>(PlayerColor::Black, 51);
	board[52] = std::make_unique<Pawn>(PlayerColor::Black, 52);
	board[53] = std::make_unique<Pawn>(PlayerColor::Black, 53);
	board[54] = std::make_unique<Pawn>(PlayerColor::Black, 54);
	board[55] = std::make_unique<Pawn>(PlayerColor::Black, 55);
	board[56] = std::make_unique<Pawn>(PlayerColor::Black, 56);

	return board;
}



unique_ptr<Piece>* CastlingTest()
{
	unique_ptr<Piece>* board = new unique_ptr<Piece>[65];
	board[1] = std::make_unique<Rook>(PlayerColor::White, 1);
	board[5] = std::make_unique<King>(PlayerColor::White, 5);
	board[8] = std::make_unique<Rook>(PlayerColor::White, 8);

	board[57] = std::make_unique<Rook>(PlayerColor::Black, 57);
	board[61] = std::make_unique<King>(PlayerColor::Black, 61);
	board[64] = std::make_unique<Rook>(PlayerColor::Black, 64);

	return board;
}

unique_ptr<Piece>* An_passntTest()
{
	unique_ptr<Piece>* board = new unique_ptr < Piece>[65];
	board[9] = std::make_unique<Pawn>(PlayerColor::White, 9);
	board[10] = std::make_unique<Pawn>(PlayerColor::White, 10);
	board[11] = std::make_unique<Pawn>(PlayerColor::White, 11);
	board[12] = std::make_unique<Pawn>(PlayerColor::White, 12);
	board[13] = std::make_unique<Pawn>(PlayerColor::White, 13);
	board[14] = std::make_unique<Pawn>(PlayerColor::White, 14);
	board[15] = std::make_unique<Pawn>(PlayerColor::White, 15);
	board[16] = std::make_unique<Pawn>(PlayerColor::White, 16);

	board[49] = std::make_unique<Pawn>(PlayerColor::Black, 49);
	board[50] = std::make_unique<Pawn>(PlayerColor::Black, 50);
	board[51] = std::make_unique<Pawn>(PlayerColor::Black, 51);
	board[52] = std::make_unique<Pawn>(PlayerColor::Black, 52);
	board[53] = std::make_unique<Rook>(PlayerColor::Black, 53);
	board[54] = std::make_unique<Pawn>(PlayerColor::Black, 54);
	board[55] = std::make_unique<Pawn>(PlayerColor::Black, 55);
	board[56] = std::make_unique<Pawn>(PlayerColor::Black, 56);
	return board;
}

unique_ptr<Piece>* PromotionTest()
{
	unique_ptr<Piece>* board = new unique_ptr < Piece>[65];
	board[9] = std::make_unique<Pawn>(PlayerColor::White, 9);
	board[10] = std::make_unique<Pawn>(PlayerColor::White, 10);
	board[11] = std::make_unique<Pawn>(PlayerColor::White, 11);

	board[49] = std::make_unique<Pawn>(PlayerColor::Black, 49);
	board[50] = std::make_unique<Pawn>(PlayerColor::Black, 50);
	board[51] = std::make_unique<Pawn>(PlayerColor::Black, 51);
	return board;
}


int main()
{
	Board board(StartGame());
}