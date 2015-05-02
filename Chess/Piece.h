#pragma once
#include "Translation.h"

class Piece
{
public:
	Piece(int color);
	int _id;
	virtual std::vector<Translation*> getPossibleMovements() = 0;
	virtual ~Piece();
	virtual Platform::String^ getName() = 0;
protected:
	int color;
	std::vector<Translation*> possibleMovements;
};

