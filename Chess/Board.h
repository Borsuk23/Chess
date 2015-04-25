#pragma once
#include "Field.h"
#include "Player.h"
#include "Piece.h"


class Board
{
public:
	Board(Player* playerWhite, Player* playerBlack);
	virtual ~Board();
private:
	Piece* pieceSelected;
	Field* fieldSelected;
	std::vector<std::vector<Field*>> fields;
public:
	void userAction(int x, int y, Player* player);
private:
	Field* checkField(int x, int y);
	void clearSelection();
	void calculatePossibleMovements(int x, int y);
};

