#include "pch.h"
#include "Rook.h"


Rook::Rook(int color) : Piece(color)
{
	possibleMovements = std::vector<std::vector<Translation*>> {
			{
				new Translation(1, 0),
				new Translation(2, 0),
				new Translation(3, 0),
				new Translation(4, 0),
				new Translation(5, 0),
				new Translation(6, 0),
				new Translation(7, 0),
			},
			{
				new Translation(-1, 0),
				new Translation(-2, 0),
				new Translation(-3, 0),
				new Translation(-4, 0),
				new Translation(-5, 0),
				new Translation(-6, 0),
				new Translation(-7, 0),
			},
			{
				new Translation(0, 1),
				new Translation(0, 2),
				new Translation(0, 3),
				new Translation(0, 4),
				new Translation(0, 5),
				new Translation(0, 6),
				new Translation(0, 7),
			},
			{
				new Translation(0, -1),
				new Translation(0, -2),
				new Translation(0, -3),
				new Translation(0, -4),
				new Translation(0, -5),
				new Translation(0, -6),
				new Translation(0, -7),
			}
	};
}


Rook::~Rook()
{
}



std::vector<std::vector<Translation*>> Rook::getPossibleMovements()
{
	return possibleMovements;
}


Platform::String^ Rook::getName()
{
	if (this->color == 0)
		return "white_rook.png";
	else
		return "black_rook.png";
}

std::string Rook::getStringName()
{
	return "Rook";
}

void Rook::pieceMoved()
{
	numberOfMoves++;
}

//
//std::string Rook::toString(int color)
//{
//	std::string returnString = "";
//	std::ostringstream stringNumberOfMoves;
//
//	stringNumberOfMoves << numberOfMoves;
//
//	if (color == 0)
//	{
//		returnString = "white_rook";
//		returnString.append(" ");
//		returnString.append(stringNumberOfMoves.str());
//	}
//	else
//	{
//		returnString = "black_rook";
//		returnString.append(" ");
//		returnString.append(stringNumberOfMoves.str());
//	}
//
//	return returnString;
//
//}