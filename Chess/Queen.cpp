#include "pch.h"
#include "Queen.h"


Queen::Queen(int color) : Piece(color)
{
	possibleMovements = std::vector<Translation*>(56); 
	possibleMovements = {
		new Translation(1, 1),
		new Translation(2, 2),
		new Translation(3, 3),
		new Translation(4, 4),
		new Translation(5, 5),
		new Translation(6, 6),
		new Translation(7, 7),
		new Translation(-1, -1),
		new Translation(-2, -2),
		new Translation(-3, -3),
		new Translation(-4, -4),
		new Translation(-5, -5),
		new Translation(-6, -6),
		new Translation(-7, -7),
		new Translation(-1, 1),
		new Translation(-2, 2),
		new Translation(-3, 3),
		new Translation(-4, 4),
		new Translation(-5, 5),
		new Translation(-6, 6),
		new Translation(-7, 7),
		new Translation(1, -1),
		new Translation(2, -2),
		new Translation(3, -3),
		new Translation(4, -4),
		new Translation(5, -5),
		new Translation(6, -6),
		new Translation(7, -7),
		new Translation(1, 0),
		new Translation(2, 0),
		new Translation(3, 0),
		new Translation(4, 0),
		new Translation(5, 0),
		new Translation(6, 0),
		new Translation(7, 0),
		new Translation(-1, 0),
		new Translation(-2, 0),
		new Translation(-3, 0),
		new Translation(-4, 0),
		new Translation(-5, 0),
		new Translation(-6, 0),
		new Translation(-7, 0),
		new Translation(0, 1),
		new Translation(0, 2),
		new Translation(0, 3),
		new Translation(0, 4),
		new Translation(0, 5),
		new Translation(0, 6),
		new Translation(0, 7),
		new Translation(0, -1),
		new Translation(0, -2),
		new Translation(0, -3),
		new Translation(0, -4),
		new Translation(0, -5),
		new Translation(0, -6),
		new Translation(0, -7),
	};
}


Queen::~Queen()
{
}



std::vector<Translation*> Queen::getPossibleMovements()
{
	return possibleMovements;
}

Platform::String^ Queen::getName()
{
	return "Queen";
}