#pragma once

#include "Field.h"
#include "Player.h"
#include "Piece.h"


class Board
{
public:
	Board(Player* playerWhite, Player* playerBlack);
	virtual ~Board();
	typedef enum exit { NO_CHANGES, PIECE_SELECTED, PIECE_UNSELECTED, PIECE_MOVED, PIECE_CAPTURED } exit;
	typedef enum gameState { OK, CHECK } gameState;
	gameState checkGameState(Player* player);
	exit userAction(int x, int y, Player* player);
	std::vector<std::vector<Field*>> getFields();
private:
	Piece* pieceSelected;
	Field* fieldSelected; //obecnie klikniete pole
	std::vector<std::vector<Field*>> fields;	
	Field* checkField(int x, int y);
	void clearSelection();
	void calculatePossibleMovements(int x, int y, Player* player);
	gameState calculateCheck(int row, int column, Player* player, Piece* pieceToCheck );
	//std::string make_string(const std::wstring& wstring);

	
};

