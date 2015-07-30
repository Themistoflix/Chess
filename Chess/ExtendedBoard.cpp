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

ExtendedBoard::ExtendedBoard(){
	setupStartPosition();
}

ExtendedBoard::ExtendedBoard(ExtendedBoard &other){
	for (int i = 0; i < 120; i++){
		field[i] = other.field[i];
	}

	enPassantTargetSquare10x12 = other.enPassantTargetSquare10x12;
	
	kingWPosition10x12 = other.kingWPosition10x12;
	kingBPosition10x12 = other.kingBPosition10x12;

	whitesMove = other.whitesMove;

	longCastlingWAllowed = other.longCastlingWAllowed;
	shortCastlingWAllowed = other.shortCastlingWAllowed;

	longCastlingBAllowed = other.longCastlingBAllowed;
	shortCastlingBAllowed = other.shortCastlingBAllowed;
}

ExtendedBoard::~ExtendedBoard(){

}

void ExtendedBoard::setupStartPosition(){
	char c[120] =	{	'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
						'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
						'x', 't', 's', 'l', 'd', 'k', 'l', 's', 't', 'x',
						'x', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'x',
						'x', 'T', 'S', 'L', 'D', 'K', 'L', 'S', 'T', 'x',
						'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
						'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'
					};

	for (int i = 0; i < 120; i++){
		field[i] = c[i];
	}

	enPassantTargetSquare10x12 = -1;

	whitesMove = true;

	kingWPosition10x12 = 95;
	kingBPosition10x12 = 25;

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

void ExtendedBoard::makeMove(Move move){
	for (int i = 0; i < 4; i++){
		field[move.positionsAndDeltas[i * 2]] += move.positionsAndDeltas[i * 2 + 1];
	}

	kingWPosition10x12 += move.KingWPosition10x12Delta;
	kingBPosition10x12 += move.KingBPosition10x12Delta;
}

void ExtendedBoard::updateCastlingRightsAfterMove(Move move){
	longCastlingWAllowed = (longCastlingWAllowed && move.castlingNowForbidden[0]);
	shortCastlingWAllowed = (shortCastlingWAllowed && move.castlingNowForbidden[1]);

	longCastlingBAllowed = (longCastlingBAllowed && move.castlingNowForbidden[2]);
	shortCastlingBAllowed = (shortCastlingBAllowed && move.castlingNowForbidden[3]);
}

void ExtendedBoard::unmakeMove(Move move){
	for (int i = 0; i < 4; i++){
		field[move.positionsAndDeltas[i * 2]] -= move.positionsAndDeltas[i * 2 + 1];
	}

	kingWPosition10x12 -= move.KingWPosition10x12Delta;
	kingBPosition10x12 -= move.KingBPosition10x12Delta;
}

int ExtendedBoard::simpleMoveGenerator(){
	return 0;
}