#include "Game.h"

Game::Game(){
	
}

Game::~Game(){
	playerB = NULL;
	playerW = NULL;
	referee = NULL;
}

GameResult Game::run(){
	GameResult result;

	result.nameBlack = playerB->getName();
	result.nameWhite = playerW->getName();

	MoveCommand cmd;
	while (1){
		referee->startTimer();
		cmd = playerW->move();
		referee->stopTimer();
		referee->actualizeTimerWhite();

		result = referee->verifyMove(cmd);
		if (result.gameHasEnded){
			break;
		}
		board = referee->returnActualizedBoard();
		playerB->submitNewBoard(board, cmd);

		referee->startTimer();
		cmd = playerB->move();
		referee->stopTimer();
		referee->actualizeTimerBlack();

		result = referee->verifyMove(cmd);
		if (result.gameHasEnded){
			break;
		}
		board = referee->returnActualizedBoard();
		playerW->submitNewBoard(board, cmd);
	}

	return result;
}

void Game::setReferee(Referee* referee){
	this->referee = referee;
}

void Game::setPlayers(AbstractPlayer* playerB, AbstractPlayer* playerW){
	this->playerB = playerB;
	this->playerW = playerB;
}