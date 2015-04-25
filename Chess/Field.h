#pragma once
#include "Piece.h"
class Field
{
private:
	Piece* pieceOnField;
	bool highlighted;
	int color;

public:
	Field(int color);	//towrzac obiekt typu filed od razu podaje kolor pola
	virtual ~Field();
	void placePiece(Piece* piece);
	void removeFromSelectedField();
private:
	bool isHighlighted();
	Piece* checkField();
	void setHighlighted(bool value);

};

