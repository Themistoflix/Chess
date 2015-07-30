#ifndef _MOVE_H_
#define _MOVE_H_

#include <cstring>

struct Move{
	int positionsAndDeltas[8];
	//positionsAndDeltas[0],[2],[4],[6] = Positionen
	//positionsAndDeltas[1],[3],[5],[7] = Deltas
	
	int KingWPosition10x12Delta;
	int KingBPosition10x12Delta;

	bool castlingNowForbidden[4];
	//castlingNowForbidden[0] = longCastlingWAllowed;
	//castlingNowForbidden[1] = shortCastlingWAllowed;
	//castlingNowForbidden[2] = longCastlingBAllowed;
	//castlingNowForbidden[3] = shortCastlingBAllowed;
	
	Move();
};
#endif _MOVE_H_