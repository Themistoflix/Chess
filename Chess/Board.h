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
	void setupStartPosition();

public:
	char field[64]; 

};
#endif