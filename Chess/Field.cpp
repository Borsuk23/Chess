#include "pch.h"
#include "Field.h"
#include "Piece.h"


Field::Field(int color)
{
	//this oznacza ten konkretny obiekt w ramach ktorego wywoluje konstruktor
	this->color = color;
}


Field::~Field()
{
}


bool Field::isHighlighted()
{
	return false;
}


Piece* Field::checkField()
{
	return NULL;
}


void Field::setHighlighted(bool value)
{
}


void Field::placePiece(Piece* piece)
{
}


void Field::removeFromSelectedField()
{
}
