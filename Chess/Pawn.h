#pragma once
#include "Piece.h"
class Pawn :
public Piece
{
public:
	Pawn(int color);
	virtual ~Pawn();
	virtual std::vector<Translation*> getPossibleMovements();
	virtual Platform::String^ getName();
};

