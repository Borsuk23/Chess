#pragma once
#include "Piece.h"
class Queen :
public Piece
{
public:
	Queen(int color);
	virtual ~Queen();
	virtual std::vector<std::vector<Translation*>> getPossibleMovements();
	virtual Platform::String^ getName();
	virtual std::string getStringName();
};

