#include "Referee.h"

Referee::Referee(){
	ExtendedBoard startBoard;
	boardLog.push_back(startBoard);
}

GameResult Referee::verifyMove(MoveCommand cmd){
	GameResult result;

	result = checkCommand(cmd);
	
	if (!result.gameHasEnded){
		typedef vector<ExtendedBoard>::iterator iter;
		iter curBoard = boardLog.end() - 1;

		Move move = curBoard->constructMove(cmd);
		result = applyMoveAndTestCheck(move);
		
		if (!result.gameHasEnded){
			ExtendedBoard newBoard(*curBoard);
			newBoard.updateCastlingRightsAfterMove(move);
			newBoard.updateEnPassantTargetSquare(cmd);
			newBoard.updateMoveRight();

			boardLog.push_back(newBoard);
		}
	}

	return result;
}

GameResult Referee::checkCommand(MoveCommand cmd){
	GameResult result;
	
	vector<MoveCommand*>* legalCommands = new vector<MoveCommand*>(220);
	(boardLog.end() - 1)->moveGenerator(mailboxTo120(cmd.fromPosition8x8), legalCommands);

	bool found = false;
	for (int i = 0; i < legalCommands->size(); i++){
		if (cmd == *(legalCommands->at(i))){
			found = true;
		}
	}
	
	if (!found){
		result.gameHasEnded = true;
		result.whiteWon = !(boardLog.end() - 1)->whitesMove;
		result.blackWon = !result.whiteWon;
		result.reason = result.unzulässiger_Zug;
	}
	else{
		for (int i = 0; i < legalCommands->size(); i++){
			delete legalCommands->at(i);
		}
		legalCommands->clear();
		delete legalCommands;
	}

	return result;
}

GameResult Referee::applyMoveAndTestCheck(Move move){
	GameResult result;

	typedef vector<ExtendedBoard>::iterator iter;
	iter curBoard = boardLog.end() - 1;
	
	curBoard->makeMove(move);
	
	if (curBoard->whitesMove && curBoard->isWKingAttacked()){
		result.gameHasEnded = true;
		result.blackWon = true;
		result.whiteWon = false;
		result.reason = result.unzulässiger_Zug;

		return result;
	}
	else if (!curBoard->whitesMove && curBoard->isBKingAttacked()){
		result.gameHasEnded = true;
		result.blackWon = false;
		result.whiteWon = true;
		result.reason = result.unzulässiger_Zug;

		return result;
	}

	curBoard->unmakeMove(move);

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
