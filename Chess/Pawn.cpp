#include "pch.h"
#include "Pawn.h"


Pawn::Pawn(int color) : Piece(color)
{
}


Pawn::~Pawn()
{
}


std::vector<Translation*> Pawn::getPossibleMovements()
{
	return std::vector<Translation*>();
}