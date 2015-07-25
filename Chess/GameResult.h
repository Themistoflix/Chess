#ifndef _GAMERESULT_H_
#define _GAMERESULT_H_

#include <string>

using namespace std;

class GameResult{
public:
	GameResult();

public:
	string nameBlack;
	string nameWhite;

	bool gameHasEnded;

	bool whiteWon;
	bool blackWon;
	
	int moves;
	int reason;
};
#endif