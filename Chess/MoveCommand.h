#ifndef _MOVECOMMAND_H_
#define _MOVECOMMAND_H_

struct MoveCommand{
	MoveCommand();
	MoveCommand(int from, int to, char promo);

	int fromPosition8x8;
	int toPosition8x8;
	char promotionCode;

	bool operator==(MoveCommand& cmd);
};
#endif _MOVECOMMAND_H_