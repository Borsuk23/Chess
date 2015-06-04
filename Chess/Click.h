#pragma once
#include "pch.h"

struct Click
{
	int row;
	int column;
	int player;
	int promotionPiece;
	Click(int row, int column, int player, int promotionPiece);
	~Click();
};