#include "pch.h"
#include "Queen.h"


Queen::Queen(int color) : Piece(color)
{
}


Queen::~Queen()
{
}



std::vector<Translation*> Queen::getPossibleMovements()
{
	return std::vector<Translation*>();
}