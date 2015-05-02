#pragma once
#include "Piece.h"
class King :
public Piece
{
public:
	King(int color);
	virtual ~King();
	virtual std::vector<Translation*> getPossibleMovements();
	virtual Platform::String^ getName();
};

