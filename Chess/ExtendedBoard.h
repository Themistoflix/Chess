#ifndef EXTENDEDBOARD_H_
#define EXTENDEDBOARD_H_

#include <vector>

#include "Board.h"
#include "Move.h"
#include "MoveCommand.h"

using namespace std;

class ExtendedBoard{
public:
	ExtendedBoard();
	ExtendedBoard(ExtendedBoard &other);
	~ExtendedBoard();

public:
	Board to8x8Board();
	void setupStartPosition();

	Move constructMove(MoveCommand cmd);
	void makeMove(Move move);
	void unmakeMove(Move move);

	bool isWKingAttacked(); //TODO Muss noch implementiert werden
	bool isBKingAttacked();

	void updateCastlingRightsAfterMove(Move move);
	void updateMoveRight();
	void updateEnPassantTargetSquare(MoveCommand cmd);

	bool withinBoard(int position10x12);
	char pieceColor(int position10x12);

	void moveGenerator(int position10x12, vector<MoveCommand*>* legalCommands);

public:
	char field[120];
	enum pieceList { whitePawn = 'B', whiteRook = 'T', whiteKnight = 'H', whiteBishop = 'L', 
		whiteQueen = 'D', whiteKing = 'K',
		blackPawn = 'b', blackRook = 't', blackKnight = 'h', blackBishop = 'l', 
		blackQueen = 'd', blackKing = 'k', 
		empty = '.' };

	int kingWPosition10x12;
	int kingBPosition10x12;
	
	int enPassantTargetSquare10x12;

	bool whitesMove;

	bool longCastlingWAllowed;
	bool shortCastlingWAllowed;

	bool longCastlingBAllowed;
	bool shortCastlingBAllowed;
};

int mailboxTo120(int position8x8);
int mailboxTo64(int position10x12);

#endif EXTENDEDBOARD_H_