#pragma once
class Field
{
public:
	Field(int color);	//towrzac obiekt typu filed od razu podaje kolor pola
	virtual ~Field();
private:
	Piece* pieceOnField;
	bool highlighted;
	int color;
	bool isHighlighted();
	Piece* checkField();
	void setHighlighted(bool value);
public:
	void placePiece(Piece* piece);
	void removeFromSelectedField();
};

