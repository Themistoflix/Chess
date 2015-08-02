#ifndef _MOVE_H_
#define _MOVE_H_


struct Move{
	int positionsAndDeltas[8];
	//positionsAndDeltas[0],[2],[4],[6] = Positionen
	//positionsAndDeltas[1],[3],[5],[7] = Deltas
	
	int kingWPosition10x12Delta;
	int kingBPosition10x12Delta;

	bool castlingRigths[4];
	//castlingRigths[0] = longCastlingWAllowed;
	//castlingRigths[1] = shortCastlingWAllowed;
	//castlingRigths[2] = longCastlingBAllowed;
	//castlingRigths[3] = shortCastlingBAllowed;
	
	Move();
};
#endif _MOVE_H_