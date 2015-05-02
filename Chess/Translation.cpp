#include "pch.h"
#include "Translation.h"


Translation::Translation(int row, int column)
{
	this->row = row;
	this->column = column;
	this->captureOnly = false;
}

Translation::Translation(int row, int column, bool captureOnly)
{
	this->row = row;
	this->column = column;
	this->captureOnly = captureOnly;
}


Translation::~Translation()
{
}
