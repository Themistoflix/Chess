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

bool MoveCommand::operator==(MoveCommand& cmd){
	if (fromPosition8x8 == cmd.fromPosition8x8 && toPosition8x8 == cmd.toPosition8x8){
		if (promotionCode == cmd.promotionCode || promotionCode == '*' || cmd.promotionCode == '*'){
			return true;
		}
	}
	return false;
}