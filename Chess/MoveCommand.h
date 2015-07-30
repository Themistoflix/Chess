#ifndef _MOVECOMMAND_H_
#define _MOVECOMMAND_H_

struct MoveCommand{
	MoveCommand();

	int fromPosition8x8;
	int toPosition8x8;
	char promotionCode;
};
#endif _MOVECOMMAND_H_