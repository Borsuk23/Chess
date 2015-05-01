#include "pch.h"
#include "Field.h"
#include "Piece.h"


Field::Field(int color)
{
	//this oznacza ten konkretny obiekt w ramach ktorego wywoluje konstruktor
	this->color = color;
	pieceOnField = NULL;
	highlighted = false;
}


Field::~Field()
{
}

//sprawdza czy pole jest juz podswietlone
bool Field::isHighlighted()
{
	return highlighted;
}

//zwraca czy na polu stoi figura czy NULL
Piece* Field::checkField()
{
	return pieceOnField;
}

//podswietla lub gasi pole (przy odkliknieciu figury)
void Field::setHighlighted(bool value)
{
	highlighted = value;
}

//ustawia figure
void Field::placePiece(Piece* piece)
{
	pieceOnField = piece;
}

//usuwa figure z poprzedniego pola
void Field::removeFromSelectedField()
{
	pieceOnField = NULL;
}



//void Field::attachViewModel(FieldViewModel^ viewModel) {
//	this->viewModel = viewModel;
//}