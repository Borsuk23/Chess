#include "pch.h"
#include "Knight.h"


Knight::Knight(int color) : Piece(color)
{
	possibleMovements = std::vector<std::vector<Translation*>>  {
			{ new Translation(1, 2) },
			{ new Translation(2, 1) },
			{ new Translation(2, -1) },
			{ new Translation(1, -2) },
			{ new Translation(-1, -2) },
			{ new Translation(-2, -1) },
			{ new Translation(-2, 1) },
			{ new Translation(-1, 2) }
	};
}


Knight::~Knight()
{

}



std::vector<std::vector<Translation*>> Knight::getPossibleMovements()
{
	return possibleMovements;
}

Platform::String^ Knight::getName()
{
	if (this->color == 0)
		return "white_knight.png";
	else
		return "black_knight.png";
}

std::string Knight::getStringName()
{
	return "Knight";
}


std::string Knight::toString(int color)
{
	std::string returnString = "";
	std::ostringstream stringNumberOfMoves;

	stringNumberOfMoves << numberOfMoves;

	if (color == 0)
	{
		returnString = "white_knight";
		returnString.append(" ");
		returnString.append(stringNumberOfMoves.str());
	}
	else
	{
		returnString = "black_knight";
		returnString.append(" ");
		returnString.append(stringNumberOfMoves.str());
	}

	return returnString;

}