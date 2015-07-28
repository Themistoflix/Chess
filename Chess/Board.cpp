#include "Board.h"

void Board::setupStartPosition(){
	char c[64] =	{	't', 's', 'l', 'd', 'k', 'l', 's', 't',
						'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b',
						'.', '.', '.', '.', '.', '.', '.', '.',
						'.', '.', '.', '.', '.', '.', '.', '.',
						'.', '.', '.', '.', '.', '.', '.', '.',
						'.', '.', '.', '.', '.', '.', '.', '.',
						'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B',
						'T', 'S', 'L', 'D', 'K', 'L', 'S', 'T'
					};
	// Kleinbuchstaben = schwarz
	// Groﬂbuchstaben  = weiﬂ

	for (int i = 0; i < 64; i++){
		field[i] = c[i];
	}
}

void Board::actualize(Board other){
	for (int i = 0; i < 64; i++){
		field[i] = other.field[i];
	}
}


Board::Board(){

	setupStartPosition();
}

Board::~Board(){

}