#include "Board.h"

void Board::setupStartPosition(){
	char c[64] =	{	't', 'h', 'b', 'q', 'k', 'b', 'h', 't',
						'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
						'.', '.', '.', '.', '.', '.', '.', '.',
						'.', '.', '.', '.', '.', '.', '.', '.',
						'.', '.', '.', '.', '.', '.', '.', '.',
						'.', '.', '.', '.', '.', '.', '.', '.',
						'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
						'T', 'H', 'B', 'Q', 'K', 'B', 'H', 'T'
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