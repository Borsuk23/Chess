#include "pch.h"
#include "Piece.h"


Piece::Piece(int color)
{
	this->color = color;
	this->_id = (int) this;
}


Piece::~Piece()
{
}
