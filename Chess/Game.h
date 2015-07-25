#ifndef _GAME_H_
#define _GAME_H_

#include <string>

#include "Board.h"
#include "GameResult.h"
#include "Referee.h"
#include "AbstractPlayer.h"

using namespace std;

class Game{
public:
	Game();
	~Game();

	GameResult run();
	void setReferee(Referee* referee);
	void setPlayers(AbstractPlayer* playerB, AbstractPlayer* playerW);

public:
	AbstractPlayer* playerB;
	AbstractPlayer* playerW;

	Referee* referee;

	Board board;

};

#endif