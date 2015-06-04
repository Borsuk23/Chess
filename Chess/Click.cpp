#include "pch.h"
#include "Click.h"


Click::Click(int row, int column, int player, int promotionPiece)
{
	this->row = row;
	this->column = column;
	this->player = player;
	this->promotionPiece = promotionPiece;
}

Click::~Click()
{
}
