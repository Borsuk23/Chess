#pragma once
#include "Piece.h"
class King :
public Piece
{
public:
	King(int color);
	virtual ~King();
	virtual std::vector<std::vector<Translation*>> getPossibleMovements();
	virtual Platform::String^ getName();
	virtual std::string getStringName();
};

