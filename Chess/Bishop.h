#pragma once
#include "Piece.h"
class Bishop :
public Piece
{
public:
	Bishop(int color);
	virtual ~Bishop();
	virtual std::vector<std::vector<Translation*>> getPossibleMovements();
	virtual Platform::String^ getName();
	virtual std::string getStringName();
};

