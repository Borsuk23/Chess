#pragma once
#include "Piece.h"
class Rook :
public Piece
{
public:
	Rook(int color);
	virtual ~Rook();
	virtual std::vector<std::vector<Translation*>> getPossibleMovements();
	virtual Platform::String^ getName();
	virtual std::string getStringName();
	virtual void pieceMoved();
};

