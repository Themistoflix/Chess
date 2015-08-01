#include "MoveCommand.h"

MoveCommand::MoveCommand(){
	toPosition8x8 = -1;
	fromPosition8x8 = -1;
	promotionCode = '.';
}

MoveCommand::MoveCommand(int from, int to, char promo){
	fromPosition8x8 = from;
	toPosition8x8 = to;
	promotionCode = promo;
}