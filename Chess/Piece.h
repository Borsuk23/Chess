#pragma once
#include "Translation.h"
#include "sstream"

class Piece
{
public:
	Piece(int color);
	int _id;
	int numberOfMoves;
	virtual std::vector<std::vector<Translation*>> getPossibleMovements() = 0;
	virtual ~Piece();
	virtual Platform::String^ getName() = 0;
	virtual std::string getStringName() = 0;
	virtual void pieceMoved();
	virtual std::string toString(int color) = 0;
	int color;
protected:
	
	std::vector<std::vector<Translation*>> possibleMovements;
};

