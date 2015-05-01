#include "pch.h"
#include "Pawn.h"


Pawn::Pawn(int color) : Piece(color)
{
	possibleMovements = std::vector<Translation*>(4); 
	possibleMovements = {
		new Translation(0, 1),
		new Translation(0, 2), //pierwszy ruch moze byc o 2
		new Translation(1, 1), //bicie
		new Translation(-1, 1), //bicie
	};
}


Pawn::~Pawn()
{
}


std::vector<Translation*> Pawn::getPossibleMovements()
{
	return std::vector<Translation*>();
}