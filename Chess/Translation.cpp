#include "pch.h"
#include "Translation.h"


Translation::Translation(int row, int column)
{
	this->row = row;
	this->column = column;
	this->option = 0;
}

Translation::Translation(int row, int column, int option)
{
	this->row = row;
	this->column = column;
	this->option = option;
}


Translation::~Translation()
{
}
