#include "pch.h"
#include "Piece.h"


Piece::Piece(int color)
{
	this->color = color;
	this->_id = (int) this;
	numberOfMoves = 0;
}


Piece::~Piece()
{
}

void Piece::pieceMoved()
{
	numberOfMoves++;
}
