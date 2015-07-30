#include "Referee.h"

Referee::Referee(){
	ExtendedBoard startBoard;
	boardLog.push_back(startBoard);
}

GameResult Referee::verifyMove(MoveCommand cmd){
	GameResult result;

	return result;
}

Board Referee::returnActualizedBoard(){
	return (boardLog.end() - 1)->to8x8Board();
}

void Referee::setTimeLimit(long newTimeLimit){
	timeLimit = newTimeLimit;

	timeLeftBlack = timeLimit;
	timeLeftWhite = timeLimit;
}


void Referee::reset(){
	boardLog.clear();

	timeLeftBlack = timeLimit;
	timeLeftWhite = timeLimit;
}

void Referee::startTimer(){
	curPlayerStartTime = clock();
}

void Referee::stopTimer(){
	curPlayerStopTime = clock();
}

void Referee::actualizeTimerWhite(){
	timeLeftWhite -= (curPlayerStopTime - curPlayerStartTime);
}

void Referee::actualizeTimerBlack(){
	timeLeftBlack -= (curPlayerStopTime - curPlayerStartTime);
}
