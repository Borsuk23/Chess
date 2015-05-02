#include "pch.h"
#include "Pawn.h"


Pawn::Pawn(int color) : Piece(color)
{
	possibleMovements = std::vector<Translation*>(4); 
	possibleMovements = {
		new Translation(-1, 0),
		new Translation(-2, 0), //pierwszy ruch moze byc o 2
		new Translation(-1, -1), //bicie
		new Translation(-1, 1), //bicie
	};
}


Pawn::~Pawn()
{
}


std::vector<Translation*> Pawn::getPossibleMovements()
{
	return possibleMovements;
}


Platform::String^ Pawn::getName()
{
	if (color == 0)
		return "White Pawn";
	else
		return "Black Pawn";
}