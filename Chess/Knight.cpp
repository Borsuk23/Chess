#include "pch.h"
#include "Knight.h"


Knight::Knight(int color) : Piece(color)
{
	possibleMovements = std::vector<Translation*>(8); 
	possibleMovements = {
		new Translation(1, 2),
		new Translation(2, 1),
		new Translation(2, -1),
		new Translation(1, -2),
		new Translation(-1, -2),
		new Translation(-2, -1),
		new Translation(-2, 1),
		new Translation(-1, 2),
	};
}


Knight::~Knight()
{

}



std::vector<Translation*> Knight::getPossibleMovements()
{
	return possibleMovements;
}