#include "Move.h"

Move::Move(){
	for (int i = 0; i < 8; i++){
		positionsAndDeltas[i] = 0;
	}

	KingWPosition10x12Delta = 0;
	KingBPosition10x12Delta = 0;

	for (int i = 0; i < 4; i++){
		castlingRigths[i] = true;
	}
}