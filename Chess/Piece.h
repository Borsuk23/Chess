#pragma once
#include "Translation.h"

class Piece
{
public:
	Piece(int color);
	virtual std::vector<Translation*> getPossibleMovements() = 0;
	virtual ~Piece();
private:
	int color;
protected:
	std::vector<Translation*> possibleMovements;
};

