#include "pch.h"
#include "Field.h"
#include "Piece.h"


Field::Field(int color)
{
	this->color = color;
	pieceOnField = NULL;
	highlighted = false;
}


Field::~Field()
{
}

//check if field is already highlighted
bool Field::isHighlighted()
{
	return highlighted;
}

//check if on field stands piece or null
Piece* Field::checkField()
{
	return pieceOnField;
}

//on and off highlighted (after second click)
void Field::setHighlighted(bool value)
{
	highlighted = value;
}

//place piece on field
void Field::placePiece(Piece* piece)
{
	pieceOnField = piece;
}

//remove piece from previous field
void Field::removeFromSelectedField()
{
	pieceOnField = NULL;
}

