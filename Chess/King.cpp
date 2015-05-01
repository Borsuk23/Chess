#include "pch.h"
#include "King.h"


King::King(int color) : Piece(color)
{
	possibleMovements = std::vector<Translation*>(8); 
	possibleMovements = {
		new Translation(0,1),
		new Translation(1, 1),
		new Translation(1, 0),
		new Translation(1, -1),
		new Translation(0, -1),
		new Translation(-1, -1),
		new Translation(-1, 0),
		new Translation(-1, 1),
	};
}


King::~King()
{
}


std::vector<Translation*> King::getPossibleMovements()
{
	return std::vector<Translation*>();
}