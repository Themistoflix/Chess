#ifndef _GAME_H_
#define _GAME_H_

#include "AbstractPlayer.h"
#include "Board.h"
#include "GameResult.h"
#include "MoveCommand.h"
#include "Referee.h"


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