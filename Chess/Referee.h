#ifndef _REFEREE_H_
#define _REFEREE_H_

#include <vector>
#include <ctime>

#include "GameResult.h"
#include "Board.h"
#include "ExtendedBoard.h"
#include "Move.h"
#include "MoveCommand.h"

using namespace std;

class Referee{
public:
	Referee();

	GameResult verifyMove(MoveCommand cmd);
	Board returnActualizedBoard();

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

	vector<ExtendedBoard> boardLog;
};
#endif