#include "pch.h"
#include "King.h"


King::King(int color) : Piece(color)
{
	possibleMovements = std::vector<std::vector<Translation*>>  {
			{ new Translation(0, 1) },
			{ new Translation(1, 1) },
			{ new Translation(1, 0) },
			{ new Translation(1, -1) },
			{ new Translation(0, -1) },
			{ new Translation(-1, -1) },
			{ new Translation(-1, 0) },
			{ new Translation(-1, 1) }
	};
}


King::~King()
{
}


std::vector<std::vector<Translation*>> King::getPossibleMovements()
{
	return possibleMovements;
}


Platform::String^ King::getName()
{
	if (this->color == 0)
		return "white_king.png";
	else
		return "black_king.png";
}

std::string King::getStringName()
{
	return "King";
}