#include "Move.h"

Move::Move(){
	memset(positionsAndDeltas, 0, sizeof(int) * 8);

	KingWPosition10x12Delta = 0;
	KingBPosition10x12Delta = 0;

	memset(castlingNowForbidden, true, sizeof(bool) * 4);
}