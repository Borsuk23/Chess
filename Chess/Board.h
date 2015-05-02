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
	Field* fieldSelected; //obecnie klikniete pole
	std::vector<std::vector<Field*>> fields;
public:
	int userAction(int x, int y, Player* player);
	std::vector<std::vector<Field*>> getFields();
private:
	Field* checkField(int x, int y);
	void clearSelection();
	void calculatePossibleMovements(int x, int y);
};

