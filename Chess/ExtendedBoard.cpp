#include "ExtendedBoard.h"

int mailboxTo120(int position8x8){
	int positions[64] = {	21, 22, 23, 24, 25, 26, 27, 28,
							31, 32, 33, 34, 35, 36, 37, 38,
							41, 42, 43, 44, 45, 46, 47, 48,
							51, 52, 53, 54, 55, 56, 57, 58,
							61, 62, 63, 64, 65, 66, 67, 68,
							71, 72, 73, 74, 75, 76, 77, 78,
							81, 82, 83, 84, 85, 86, 87, 88,
							91, 92, 93, 94, 95, 96, 97, 98};

	return positions[position8x8];
}

int mailboxTo64(int position10x12){
	int positions[120] = {  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
							-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
							-1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
							-1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
							-1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
							-1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
							-1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
							-1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
							-1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
							-1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
							-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
							-1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	return positions[position10x12];
}

ExtendedBoard::ExtendedBoard(){
	setupStartPosition();
}

ExtendedBoard::ExtendedBoard(ExtendedBoard &other){
	for (int i = 0; i < 120; i++){
		field[i] = other.field[i];
	}

	enPassantTargetSquare10x12 = other.enPassantTargetSquare10x12;
	
	kingWPosition10x12 = other.kingWPosition10x12;
	kingBPosition10x12 = other.kingBPosition10x12;

	whitesMove = other.whitesMove;

	longCastlingWAllowed = other.longCastlingWAllowed;
	shortCastlingWAllowed = other.shortCastlingWAllowed;

	longCastlingBAllowed = other.longCastlingBAllowed;
	shortCastlingBAllowed = other.shortCastlingBAllowed;
}

ExtendedBoard::~ExtendedBoard(){

}

void ExtendedBoard::setupStartPosition(){
	char c[120] =	{	'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
						'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
						'x', 't', 's', 'l', 'd', 'k', 'l', 's', 't', 'x',
						'x', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', '.', '.', '.', '.', '.', '.', '.', '.', 'x',
						'x', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'x',
						'x', 'T', 'S', 'L', 'D', 'K', 'L', 'S', 'T', 'x',
						'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x',
						'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'
					};

	for (int i = 0; i < 120; i++){
		field[i] = c[i];
	}

	enPassantTargetSquare10x12 = -1;

	whitesMove = true;

	kingWPosition10x12 = 95;
	kingBPosition10x12 = 25;

	longCastlingWAllowed = true;
	shortCastlingWAllowed = true;

	longCastlingBAllowed = true;
	shortCastlingBAllowed = true;

	return;
}

Board ExtendedBoard::to8x8Board(){
	Board b;
	for (int i = 0; i < 64; i++){
		b.field[i] = field[mailboxTo120(i)];
	}

	return b;
}

Move ExtendedBoard::constructMove(MoveCommand cmd){
	Move move;

	int fromPosition10x12 = mailboxTo120(cmd.fromPosition8x8);
	int toPosition10x12 = mailboxTo120(cmd.toPosition8x8);

	move.positionsAndDeltas[0] = fromPosition10x12;
	move.positionsAndDeltas[1] = empty - field[fromPosition10x12];
	move.positionsAndDeltas[2] = toPosition10x12;
	move.positionsAndDeltas[3] = field[fromPosition10x12] - field[toPosition10x12];

	move.castlingRigths[0] = longCastlingWAllowed;
	move.castlingRigths[1] = shortCastlingWAllowed;
	move.castlingRigths[2] = longCastlingBAllowed;
	move.castlingRigths[3] = shortCastlingBAllowed;
	
	
	char movedPiece = field[fromPosition10x12];

	switch (movedPiece){
	case whitePawn:
		const int offsetFieldBelow = 10;
		if (toPosition10x12 == enPassantTargetSquare10x12){
			move.positionsAndDeltas[4] = toPosition10x12 + offsetFieldBelow;
			move.positionsAndDeltas[5] = empty - field[toPosition10x12 + offsetFieldBelow];
		}
		break;

	case blackPawn:
		const int offsetFieldAbove = -10;
		if (toPosition10x12 == enPassantTargetSquare10x12){
			move.positionsAndDeltas[4] = toPosition10x12 + offsetFieldAbove;
			move.positionsAndDeltas[5] = empty - field[toPosition10x12 + offsetFieldAbove];
		}
		break;

	case blackRook:
		if (fromPosition10x12 > kingBPosition10x12){
			move.castlingRigths[3] = false;
		}
		else{
			move.castlingRigths[2] = false;
		}
		break;

	case whiteRook:
		if (fromPosition10x12 > kingWPosition10x12){
			move.castlingRigths[1] = false;
		}
		else{
			move.castlingRigths[0] = false;
		}
	case whiteKing || blackKing:
		const int offset1FieldLeft = -1;
		const int offset1FieldRight = 1;

		const int offset2FieldsLeft = -2;
		const int offset2FieldsRight = 2;

		const int offset3FieldsRight = 3;
		
		const int offset4FieldsLeft = -4;
		
		//lange Rochade
		if (toPosition10x12 - fromPosition10x12 == offset2FieldsLeft){
			move.positionsAndDeltas[4] = fromPosition10x12 + offset4FieldsLeft;
			move.positionsAndDeltas[5] = empty - field[fromPosition10x12 + offset4FieldsLeft];

			move.positionsAndDeltas[6] = fromPosition10x12 + offset1FieldLeft;
			move.positionsAndDeltas[7] = field[fromPosition10x12 + offset4FieldsLeft] - empty;
		}//kurze Rochade
		else if (toPosition10x12 - fromPosition10x12 == offset2FieldsRight){
			move.positionsAndDeltas[4] = fromPosition10x12 + offset3FieldsRight;
			move.positionsAndDeltas[5] = empty - field[fromPosition10x12 + offset3FieldsRight];

			move.positionsAndDeltas[6] = fromPosition10x12 + offset1FieldRight;
			move.positionsAndDeltas[7] = field[fromPosition10x12 + offset3FieldsRight] - empty;
		}

		if (pieceSide(fromPosition10x12) == white){
			move.castlingRigths[0] = false;
			move.castlingRigths[1] = false;

			move.kingWPosition10x12Delta = toPosition10x12 - kingWPosition10x12;
		}
		else{
			move.castlingRigths[2] = false;
			move.castlingRigths[3] = false;

			move.kingBPosition10x12Delta = toPosition10x12 - kingBPosition10x12;
		}
	}

	return move;
}

void ExtendedBoard::makeMove(Move move){
	for (int i = 0; i < 4; i++){
		field[move.positionsAndDeltas[i * 2]] += move.positionsAndDeltas[i * 2 + 1];
	}

	kingWPosition10x12 += move.kingWPosition10x12Delta;
	kingBPosition10x12 += move.kingBPosition10x12Delta;
}

void ExtendedBoard::unmakeMove(Move move){
	for (int i = 0; i < 4; i++){
		field[move.positionsAndDeltas[i * 2]] -= move.positionsAndDeltas[i * 2 + 1];
	}

	kingWPosition10x12 -= move.kingWPosition10x12Delta;
	kingBPosition10x12 -= move.kingBPosition10x12Delta;
}

void ExtendedBoard::updateCastlingRightsAfterMove(Move move){
	longCastlingWAllowed = move.castlingRigths[0];
	shortCastlingWAllowed = move.castlingRigths[1];

	longCastlingBAllowed = move.castlingRigths[2];
	shortCastlingBAllowed = move.castlingRigths[3];
}

void ExtendedBoard::updateMoveRight(){
	whitesMove = !whitesMove;
}

void ExtendedBoard::updateEnPassantTargetSquare(MoveCommand cmd){
	int from10x12 = mailboxTo120(cmd.fromPosition8x8);
	int to10x12 = mailboxTo120(cmd.toPosition8x8);

	if (field[from10x12] == 'b' && to10x12 == from10x12 + 20){
		enPassantTargetSquare10x12 = from10x12 + 10;
	}
	else if (field[from10x12] == 'B' && to10x12 == from10x12 - 20){
		enPassantTargetSquare10x12 = from10x12 - 10;
	}
	else{
		enPassantTargetSquare10x12 = -1;
	}
}

bool ExtendedBoard::withinBoard(int position10x12){
	int column = position10x12 % 10;
	int row = position10x12 / 10;

	if (column >= 1 && column <= 8 && row >= 2 && row <= 9){
		return true;
	}

	return false;
}

bool ExtendedBoard::isEmpty(int position10x12){
	if (field[position10x12] == pieceList::empty){
		return true;
	}
	else{
		return false;
	}
}

int ExtendedBoard::pieceSide(int position10x12){
	if (field[position10x12] == pieceList::empty){
		return neutral;
	}
	else if (field[position10x12] == pieceList::blackKing ||
		field[position10x12] == pieceList::blackQueen ||
		field[position10x12] == pieceList::blackRook ||
		field[position10x12] == pieceList::blackBishop ||
		field[position10x12] == pieceList::blackKnight ||
		field[position10x12] == pieceList::blackPawn){
		return black;
	}
	else{
		return white;
	}
}

int ExtendedBoard::pieceKind(int position10x12){
	int currentKind = -1;

	if (field[position10x12] == blackKing || field[position10x12] == whiteKing){
		currentKind = king;
	}
	else if (field[position10x12] == blackQueen || field[position10x12] == whiteQueen){
		currentKind = queen;
	}
	else if (field[position10x12] == blackBishop || field[position10x12] == whiteBishop){
		currentKind = bishop;
	}
	else if (field[position10x12] == blackKnight || field[position10x12] == whiteKnight){
		currentKind = knight;
	}
	else if (field[position10x12] == blackRook || field[position10x12] == whiteRook){
		currentKind = rook;
	}
	else if (field[position10x12] == blackPawn || field[position10x12] == whitePawn){
		currentKind = pawn;
	}
	else{
		currentKind = kinds::empty;
	}

	return currentKind;
}
  
void ExtendedBoard::moveGenerator(int position10x12, vector<MoveCommand*>* pseudoLegalCommands){
	int queenOffsets[] = { 1, 11, 10, 9, -1, -11, -10, -9 };
	int kingOffsets[] = { 1, 11, 10, 9, -1, -11, -10, -9 };
	int bishopOffsets[] = { 11, 9, -11, -9};
	int knightOffsets[] = {-19, -8, 12, 21, 19, 8, -12 , -21};
	int rookOffsets[] = { 1, 10, -1, -10 };

	int blackPawnOffsets[] = { 9, 10, 11, 20 };
	int whitePawnOffsets[] = { -11, -10, -9, -20 };

	
	int currentKind = pieceKind(position10x12);
	if (currentKind = pawn){
		if (field[position10x12] == blackPawn){
			currentKind = blackPawn;
		}
		else{
			currentKind = whitePawn;
		}
	}

	int newPosition10x12;
	MoveCommand* cmd;

	switch (currentKind){
	case king: 
		for (int i = 0; i < 8; i++){
			newPosition10x12 = position10x12 + kingOffsets[i];
			if (!withinBoard(newPosition10x12) || pieceSide(newPosition10x12) == pieceSide(position10x12)){
				continue;
			}
			cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
			pseudoLegalCommands->push_back(cmd);
		}

		int freeFieldsToLeft = 1;
		while (withinBoard(position10x12 - freeFieldsToLeft) && isEmpty(position10x12 - freeFieldsToLeft)){
			freeFieldsToLeft++;
		}
		if (freeFieldsToLeft == 4){
			if (field[position10x12] == blackKing && longCastlingBAllowed){
				cmd = new MoveCommand(position10x12, position10x12 - 2, ' ');
				pseudoLegalCommands->push_back(cmd);
			}
			else if (field[position10x12] == whiteKing && longCastlingWAllowed){
				cmd = new MoveCommand(position10x12, position10x12 - 2, ' ');
				pseudoLegalCommands->push_back(cmd);
			}
		}

		int freeFieldsToRight = 1;
		while (withinBoard(position10x12 + freeFieldsToRight) && isEmpty(position10x12 + freeFieldsToRight)){
			freeFieldsToRight++;
		}
		if (freeFieldsToRight == 3){
			if (field[position10x12] == blackKing && shortCastlingBAllowed){
				cmd = new MoveCommand(position10x12, position10x12 + 2, ' ');
				pseudoLegalCommands->push_back(cmd);
			}
			else if (field[position10x12] == whiteKing && shortCastlingWAllowed){
				cmd = new MoveCommand(position10x12, position10x12 - 2, ' ');
				pseudoLegalCommands->push_back(cmd);
			}
		}

		break;

	case queen:
		for (int i = 0; i < 8; i++){
			for (int j = 1;; j++){
				newPosition10x12 = position10x12 + j*queenOffsets[i];
				if (!withinBoard(newPosition10x12) || pieceSide(newPosition10x12) == pieceSide(position10x12)){
					break;
				}
				cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
				pseudoLegalCommands->push_back(cmd);

				if (!isEmpty(newPosition10x12)){
					break;
				}
			}
		}
		break;

	case bishop:
		for (int i = 0; i < 4; i++){
			for (int j = 1;; j++){
				newPosition10x12 = position10x12 + j*bishopOffsets[i];
				if (!withinBoard(newPosition10x12) || pieceSide(newPosition10x12) == pieceSide(position10x12)){
					break;
				}
				cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
				pseudoLegalCommands->push_back(cmd);

				if (!isEmpty(newPosition10x12)){
					break;
				}
			}
		}
		break;

	case knight:
		for (int i = 0; i < 8; i++){
			newPosition10x12 = position10x12 + knightOffsets[i];
			if (!withinBoard(newPosition10x12) || pieceSide(newPosition10x12) == pieceSide(position10x12)){
				continue;
			}
			cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
			pseudoLegalCommands->push_back(cmd);
		}
		break;

	case rook:
		for (int i = 0; i < 4; i++){
			for (int j = 0;; j++){
				newPosition10x12 = position10x12 + j*rookOffsets[i];
				if (!withinBoard(newPosition10x12) || pieceSide(newPosition10x12) == pieceSide(position10x12)){
					break;
				}
				cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
				pseudoLegalCommands->push_back(cmd);
				if (!isEmpty(newPosition10x12)){
					break;
				}
			}
		}
		break;

	case blackPawn:
		char promo = ' ';
		for (int i = 0; i < 4; i++){
			newPosition10x12 = position10x12 + blackPawnOffsets[i];
			if (!withinBoard(newPosition10x12)){
				continue;
			}

			
			if (newPosition10x12 / 10 == 9){
				promo = '*';
			}

			if ((i == 0 || i == 2) && (pieceSide(newPosition10x12) == white || newPosition10x12 == enPassantTargetSquare10x12)){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				pseudoLegalCommands->push_back(cmd);
			}
			else if (i == 1 && isEmpty(newPosition10x12)){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				pseudoLegalCommands->push_back(cmd);
			}
			else if (i == 3 && position10x12 / 10 == 3 && isEmpty(position10x12 + 10) && isEmpty(newPosition10x12)){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				pseudoLegalCommands->push_back(cmd);
			}
		}
		break;

	case whitePawn:
		char promo = ' ';
		for (int i = 0; i < 4; i++){
			newPosition10x12 = position10x12 + whitePawnOffsets[i];
			if (!withinBoard(newPosition10x12)){
				continue;
			}

			if (newPosition10x12 / 10 == 2){
				promo = '*';
			}

			if ((i == 0 || i == 2) && (pieceSide(newPosition10x12) == black || newPosition10x12 == enPassantTargetSquare10x12)){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				pseudoLegalCommands->push_back(cmd);
			}
			else if (i == 1 && isEmpty(newPosition10x12)){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				pseudoLegalCommands->push_back(cmd);
			}
			else if (i == 3 && position10x12 / 10 == 8 && isEmpty(position10x12 - 10) && isEmpty(newPosition10x12)){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				pseudoLegalCommands->push_back(cmd);
			}
		}
		break;
	}
	
}