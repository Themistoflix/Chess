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

void ExtendedBoard::makeMove(Move move){
	for (int i = 0; i < 4; i++){
		field[move.positionsAndDeltas[i * 2]] += move.positionsAndDeltas[i * 2 + 1];
	}

	kingWPosition10x12 += move.KingWPosition10x12Delta;
	kingBPosition10x12 += move.KingBPosition10x12Delta;
}

void ExtendedBoard::unmakeMove(Move move){
	for (int i = 0; i < 4; i++){
		field[move.positionsAndDeltas[i * 2]] -= move.positionsAndDeltas[i * 2 + 1];
	}

	kingWPosition10x12 -= move.KingWPosition10x12Delta;
	kingBPosition10x12 -= move.KingBPosition10x12Delta;
}

void ExtendedBoard::updateCastlingRightsAfterMove(Move move){
	longCastlingWAllowed = (longCastlingWAllowed && move.castlingNowForbidden[0]);
	shortCastlingWAllowed = (shortCastlingWAllowed && move.castlingNowForbidden[1]);

	longCastlingBAllowed = (longCastlingBAllowed && move.castlingNowForbidden[2]);
	shortCastlingBAllowed = (shortCastlingBAllowed && move.castlingNowForbidden[3]);
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

char ExtendedBoard::pieceColor(int position10x12){
	if (field[position10x12] == '.'){
		return 'n';
	}
	else if (field[position10x12] >= 97){
		return 'b';
	}
	else{
		return 'w';
	}
}

void ExtendedBoard::moveGenerator(int position10x12, vector<MoveCommand*>* legalCommands){
	int queenOffsets[] = { 1, 11, 10, 9, -1, -11, -10, -9 };
	int kingOffsets[] = { 1, 11, 10, 9, -1, -11, -10, -9 };
	int bishopOffsets[] = { 11, 9, -11, -9};
	int knightOffsets[] = {-19, -8, 12, 21, 19, 8, -12 , -21};
	int rookOffsets[] = { 1, 10, -1, -10 };

	int blackPawnOffsets[] = { 9, 10, 11, 20 };
	int whitePawnOffsets[] = { -11, -10, -9, -20 };

	enum kinds { king = 0, queen, bishop, knight, rook, blackPawn, whitePawn };
	int currentKind = -1;

	if (field[position10x12] == 'k' || field[position10x12] == 'K'){
		currentKind = king;
	}
	else if (field[position10x12] == 'd' || field[position10x12] == 'D'){
		currentKind = queen;
	}
	else if (field[position10x12] == 'l' || field[position10x12] == 'L'){
		currentKind = bishop;
	}
	else if (field[position10x12] == 's' || field[position10x12] == 'S'){
		currentKind = knight;
	}
	else if (field[position10x12] == 't' || field[position10x12] == 'T'){
		currentKind = rook;
	}
	else if (field[position10x12] == 'b'){
		currentKind = blackPawn;
	}
	else if (field[position10x12] == 'B'){
		currentKind = whitePawn;
	}

	int newPosition10x12;
	MoveCommand* cmd;

	switch (currentKind){
	case king: 
		for (int i = 0; i < 8; i++){
			newPosition10x12 = position10x12 + kingOffsets[i];
			if (!withinBoard(newPosition10x12) || field[newPosition10x12]){
				break;
			}
			cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
			legalCommands->push_back(cmd);
		}

		int freeFieldsToLeft = 1;
		while (withinBoard(position10x12 - freeFieldsToLeft) && field[position10x12 - freeFieldsToLeft] == '.'){
			freeFieldsToLeft++;
		}
		if (freeFieldsToLeft == 4){
			if (field[position10x12] == 'k' && longCastlingBAllowed){
				cmd = new MoveCommand(position10x12, position10x12 - 2, ' ');
				legalCommands->push_back(cmd);
			}
			else if (field[position10x12] == 'K' && longCastlingWAllowed){
				cmd = new MoveCommand(position10x12, position10x12 - 2, ' ');
				legalCommands->push_back(cmd);
			}
		}

		int freeFieldsToRight = 1;
		while (withinBoard(position10x12 + freeFieldsToRight) && field[position10x12 + freeFieldsToRight] == '.'){
			freeFieldsToRight++;
		}
		if (freeFieldsToRight == 3){
			if (field[position10x12] == 'k' && shortCastlingBAllowed){
				cmd = new MoveCommand(position10x12, position10x12 + 2, ' ');
				legalCommands->push_back(cmd);
			}
			else if (field[position10x12] == 'K' && shortCastlingWAllowed){
				cmd = new MoveCommand(position10x12, position10x12 - 2, ' ');
				legalCommands->push_back(cmd);
			}
		}

		break;
	case queen:
		for (int i = 0; i < 8; i++){
			for (int j = 1;; j++){
				newPosition10x12 = position10x12 + j*queenOffsets[i];
				if (!withinBoard(newPosition10x12) || field[newPosition10x12] != '.'){
					break;
				}
				cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
				legalCommands->push_back(cmd);
			}
		}
		break;
	case bishop:
		for (int i = 0; i < 4; i++){
			for (int j = 1;; j++){
				newPosition10x12 = position10x12 + j*bishopOffsets[i];
				if (!withinBoard(newPosition10x12) || field[newPosition10x12] != '.'){
					break;
				}
				cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
				legalCommands->push_back(cmd);
			}
		}
		break;
	case knight:
		for (int i = 0; i < 8; i++){
			newPosition10x12 = position10x12 + knightOffsets[i];
			if (!withinBoard(newPosition10x12)){
				continue;
			}
			cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
			legalCommands->push_back(cmd);
		}
		break;
	case rook:
		for (int i = 0; i < 4; i++){
			for (int j = 0;; j++){
				newPosition10x12 = position10x12 + j*rookOffsets[i];
				if (!withinBoard(newPosition10x12) || field[newPosition10x12] != '.'){
					break;
				}
				cmd = new MoveCommand(position10x12, newPosition10x12, ' ');
				legalCommands->push_back(cmd);
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

			if ((i == 0 || i == 2) && (pieceColor(newPosition10x12) == 'w' || newPosition10x12 == enPassantTargetSquare10x12)){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				legalCommands->push_back(cmd);
			}
			else if (i == 1 && field[newPosition10x12] == '.'){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				legalCommands->push_back(cmd);
			}
			else if (i == 3 && position10x12 / 10 == 4 && field[position10x12 + 10] == '.' && field[newPosition10x12] == '.'){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				legalCommands->push_back(cmd);
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

			if ((i == 0 || i == 2) && (pieceColor(newPosition10x12) == 'b' || newPosition10x12 == enPassantTargetSquare10x12)){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				legalCommands->push_back(cmd);
			}
			else if (i == 1 && field[newPosition10x12] == '.'){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				legalCommands->push_back(cmd);
			}
			else if (i == 3 && position10x12 / 10 == 7 && field[position10x12 - 10] == '.' && field[newPosition10x12] == '.'){
				cmd = new MoveCommand(position10x12, newPosition10x12, promo);
				legalCommands->push_back(cmd);
			}
		}
		break;
	}
	
}