#include "pch.h"
#include "King.h"


King::King(int color) : Piece(color)
{
	possibleMovements = std::vector<Translation*>(8); //jak w Player
	possibleMovements = {
		new Translation(0,1),
	};
}


King::~King()
{
}
