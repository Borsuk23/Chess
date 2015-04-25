#include "pch.h"
#include "Rook.h"


Rook::Rook(int color) : Piece(color)
{
}


Rook::~Rook()
{
}



std::vector<Translation*> Rook::getPossibleMovements()
{
	return std::vector<Translation*>();
}