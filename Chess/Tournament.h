#ifndef _TOURNAMENT_H_
#define _TOURNAMENT_H_

#include "AbstractPlayer.h"
#include "Game.h"
#include "GameResult.h"
#include "Referee.h"

#include <vector>

class Tournament{
public:
	Tournament();

	void setupTournament(int games, long gametime);
	void setPlayers(AbstractPlayer* player1, AbstractPlayer* player2);
	void runTournament();

public:
	Referee referee;
	
	AbstractPlayer* player1;
	AbstractPlayer* player2;

	int games;

	vector<GameResult> results;
};
#endif