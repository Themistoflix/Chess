#include "Tournament.h"

Tournament::Tournament(){
	Referee referee;
}

void Tournament::setupTournament(int games, long gameTime){
	this->games = games;
	referee.setTimeLimit(gameTime);
}

void Tournament::setPlayers(AbstractPlayer* player1, AbstractPlayer* player2){
	this->player1 = player1;
	this->player2 = player2;
}

void Tournament::runTournament(){
	for (int i = 0; i < games; i++){
		Game* game = new Game();;
		game->setReferee(&referee);

		if (i % 2 == 0){
			game->setPlayers(player1, player2);
		}
		else{
			game->setPlayers(player2, player1);
		}
		
		GameResult result = game->run();
		results.push_back(result);

		referee.reset();
		delete game;
	}
	return;
}