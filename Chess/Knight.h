#pragma once
#include "Piece.h"
class Knight :
public Piece
{
public:
	Knight(int color);
	virtual ~Knight();
	virtual std::vector<std::vector<Translation*>> getPossibleMovements();
	virtual Platform::String^ getName();
	virtual std::string getStringName();
};

