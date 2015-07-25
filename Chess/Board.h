#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <string>

using namespace std;

class Board{
public:
	Board();
	~Board();

	void actualize(Board other);
	void reset();

public:
	char field[8][8]; 

};
#endif