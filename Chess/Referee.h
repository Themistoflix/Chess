#ifndef _REFEREE_H_
#define _REFEREE_H_

#include <vector>
#include <string>
#include <ctime>

#include "GameResult.h"
#include "Board.h"

using namespace std;

class Referee{
public:
	Referee();

	GameResult verfiyMove(string move);
	Board actualizeBoard();

	void reset();

	void setTimeLimit(long newTimeLimit);
	
	void startTimer();
	void stopTimer();
	
	void actualizeTimerWhite();
	void actualizeTimerBlack();

private:
	long curPlayerStartTime;
	long curPlayerStopTime;


	long timeLeftWhite;
	long timeLeftBlack;

	long timeLimit;

	vector<Board> boardLog;
};
#endif