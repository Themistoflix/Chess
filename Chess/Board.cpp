#include "Board.h"

void Board::reset(){
	char c[8][8] = {	{ 't', 'h', 'b', 'q', 'k', 'b', 'h', 't'},
						{ 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
						{ '.', '.', '.', '.', '.', '.', '.', '.'},
						{ '.', '.', '.', '.', '.', '.', '.', '.'},
						{ '.', '.', '.', '.', '.', '.', '.', '.'},
						{ '.', '.', '.', '.', '.', '.', '.', '.'},
						{ 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
						{ 'T', 'H', 'B', 'Q', 'K', 'B', 'H', 'T'}
					};
	// Kleinbuchstaben = schwarz
	// Groﬂbuchstaben  = weiﬂ

	for (int x = 0; x < 8; x++){
		for (int y = 0; y < 8; y++){
			field[x][y] = c[x][y];
		}
	}
}

void Board::actualize(Board other){
	for (int x = 0; x < 8; x++){
		for (int y = 0; y < 8; y++){
			field[x][y] = other.field[x][y];
		}
	}
}


Board::Board(){

	reset();
}

Board::~Board(){

}