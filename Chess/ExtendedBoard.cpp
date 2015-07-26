#include "ExtendedBoard.h"

int mailboxTo120(int position8x8){
	int positions[64] = {	21, 22, 23, 24, 25, 26, 27, 28,
							31, 32, 33, 34, 35, 36, 37, 38,
							41, 42, 43, 44, 45, 46, 47, 48,
							51, 52, 53, 54, 55, 56, 57, 58,
							61, 62, 63, 64, 65, 66, 67, 68,
							71, 72, 73, 74, 75, 76, 77, 78,
							81, 82, 83, 84, 85, 86, 87, 88,
							91, 92, 93, 94, 95, 96, 97, 98};

	return positions[position8x8];
}

int mailboxTo64(int position10x12){
	int positions[120] = {  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
							-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
							-1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
							-1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
							-1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
							-1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
							-1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
							-1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
							-1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
							-1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
							-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
							-1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	return positions[position10x12];
}

void ExtendedBoard::setupStartPosition(){
	char c[120] =	{	'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
						'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
						'x', 't', 'h', 'b', 'q', 'k', 'b', 'h', 't', 'x',
						'x', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'x',
						'x', 'T', 'H', 'B', 'Q', 'K', 'B', 'H', 'T', 'x',
						'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
						'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'
					};

	for (int i = 0; i < 120; i++){
		field[i] = c[i];
	}

	enPassantTargetSquare10x12 = 0;

	whitesMove = true;

	longCastlingWAllowed = true;
	shortCastlingWAllowed = true;

	longCastlingBAllowed = true;
	shortCastlingBAllowed = true;

	return;
}

Board ExtendedBoard::to8x8Board(){
	Board b;
	for (int i = 0; i < 64; i++){
		b.field[i] = field[mailboxTo120(i)];
	}

	return b;
}