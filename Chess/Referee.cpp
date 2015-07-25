#include "Referee.h"

Referee::Referee(){
	Board startBoard;
	boardLog.push_back(startBoard);
}

GameResult Referee::verfiyMove(string move){
	GameResult result;

	return result;
}

Board Referee::actualizeBoard(){
	return *(boardLog.end() - 1);
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
