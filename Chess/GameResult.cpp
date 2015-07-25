#include "GameResult.h"

GameResult::GameResult(){
	gameHasEnded = false;

	whiteWon = false;
	blackWon = false;

	moves = 0;
	reason = -1;
}