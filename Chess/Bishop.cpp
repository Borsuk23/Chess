#include "pch.h"
#include "Bishop.h"


Bishop::Bishop(int color) : Piece(color)
{
	possibleMovements = std::vector<std::vector<Translation*>> {
			{ 
				new Translation(1, 1),
				new Translation(2, 2),
				new Translation(3, 3),
				new Translation(4, 4),
				new Translation(5, 5),
				new Translation(6, 6),
				new Translation(7, 7)
			},
			{ 
				new Translation(-1, -1),
				new Translation(-2, -2),
				new Translation(-3, -3),
				new Translation(-4, -4),
				new Translation(-5, -5),
				new Translation(-6, -6),
				new Translation(-7, -7),
			},
			{ 
				new Translation(-1, 1),
				new Translation(-2, 2),
				new Translation(-3, 3),
				new Translation(-4, 4),
				new Translation(-5, 5),
				new Translation(-6, 6),
				new Translation(-7, 7),
			},
			{	new Translation(1, -1),
				new Translation(2, -2),
				new Translation(3, -3),
				new Translation(4, -4),
				new Translation(5, -5),
				new Translation(6, -6),
				new Translation(7, -7),
			} };
	
	
}


Bishop::~Bishop()
{
}


std::vector<std::vector<Translation*>> Bishop::getPossibleMovements()
{
	return possibleMovements;
}


Platform::String^ Bishop::getName()
{
	if (this->color == 0)
		return "white_bishop.png";
	else
		return "black_bishop.png";
}

std::string Bishop::getStringName()
{
	return "Bishop";
}