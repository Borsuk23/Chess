#pragma once
#include "Piece.h"
#include "FieldViewModel.h"

using namespace Chess;
class Field
{
private:
	Piece* pieceOnField;
	bool highlighted;
	int color; //0 bialy, 1 czarny

public:
	Field(int color);	//towrzac obiekt typu filed od razu podaje kolor pola
	virtual ~Field();
	void placePiece(Piece* piece);
	void removeFromSelectedField();
	bool isHighlighted();
	Piece* checkField();
	void setHighlighted(bool value);
// void attachViewModel(FieldViewModel^ viewModel);
private:
//	FieldViewModel^ viewModel;

private:
	

};

