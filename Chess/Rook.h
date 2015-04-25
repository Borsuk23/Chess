#pragma once
#include "Piece.h"
class Rook :
public Piece
{
public:
	Rook(int color);
	virtual ~Rook();
	virtual std::vector<Translation*> getPossibleMovements();
};

