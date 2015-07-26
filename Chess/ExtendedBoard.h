#ifndef EXTENDEDBOARD_H_
#define EXTENDEDBOARD_H_

#include "Board.h"

using namespace std;

class ExtendedBoard{
public:
	ExtendedBoard();
	ExtendedBoard(ExtendedBoard &other);
	~ExtendedBoard();

public:
	Board to8x8Board();
	void setupStartPosition();

public:
	char field[120];
	
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