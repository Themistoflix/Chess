#ifndef _ABSTRACTPLAYER_H_
#define _ABSTRACHTPLAYER_H_

#include <string>

#include "Board.h"
#include "MoveCommand.h"

using namespace std;

class AbstractPlayer{
public:
	virtual MoveCommand move() = 0;
	virtual void submitNewBoard(Board board, MoveCommand cmd) = 0;

	string getName(){
		return name;
	}

private:
	string name;

};

#endif _ABSTRACTPLAYER_H_