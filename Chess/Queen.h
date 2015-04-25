#pragma once
#include "Piece.h"
class Queen :
public Piece
{
public:
	Queen(int color);
	virtual ~Queen();
	virtual std::vector<Translation*> getPossibleMovements();
};

