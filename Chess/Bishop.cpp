#include "pch.h"
#include "Bishop.h"


Bishop::Bishop(int color) : Piece(color)
{

}


Bishop::~Bishop()
{
}


std::vector<Translation*> Bishop::getPossibleMovements()
{
	return std::vector<Translation*>();
}
