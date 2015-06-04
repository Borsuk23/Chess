#include "pch.h"
#include "King.h"


King::King(int color) : Piece(color)
{
	possibleMovements = std::vector<std::vector<Translation*>>  {
			{ new Translation(0, 1, 0) },
			{ new Translation(1, 1, 0) },
			{ new Translation(1, 0, 0) },
			{ new Translation(1, -1, 0) },
			{ new Translation(0, -1, 0) },
			{ new Translation(-1, -1, 0) },
			{ new Translation(-1, 0, 0) },
			{ new Translation(-1, 1, 0) },
			{ new Translation(0, 2, 3) }, //short castling
			{ new Translation(0, -2, 4) } //long castling
	};
}


King::~King()
{
}


std::vector<std::vector<Translation*>> King::getPossibleMovements()
{
	return possibleMovements;
}


Platform::String^ King::getName()
{
	if (this->color == 0)
		return "white_king.png";
	else
		return "black_king.png";
}

std::string King::getStringName()
{
	return "King";
}

void King::pieceMoved()
{
	numberOfMoves++;
	//erase translation for 2 field movement
	if (numberOfMoves == 1)
	{
		std::vector<std::vector<Translation*>>::iterator it_row;
		it_row = possibleMovements.end();
		possibleMovements.erase(it_row - 1);
		it_row = possibleMovements.end();
		possibleMovements.erase(it_row - 1);
		//std::vector<Translation* > ::iterator it_col;
		//it_col = it_row->begin();
		//it_row->erase(it_col + 1); //erase second element from inner vector

	}
}


