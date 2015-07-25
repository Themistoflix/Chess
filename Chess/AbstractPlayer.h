#ifndef _ABSTRACTPLAYER_H_
#define _ABSTRACHTPLAYER_H_

#include <string>

#include "Board.h"

using namespace std;

class AbstractPlayer{
public:
	virtual string move() = 0;
	virtual void submitNewBoard(Board board, string cmd) = 0;

	string getName(){
		return name;
	}

private:
	string name;

};

#endif _ABSTRACTPLAYER_H_