#include "pch.h"
#include "Pawn.h"
#include "Piece.h"


Pawn::Pawn(int color) : Piece(color)
{  
	if (color == 0)
	{
		possibleMovements = std::vector<std::vector<Translation*>> {
				{
					new Translation(-1, 0,2),
					new Translation(-2, 0,2), //pierwszy ruch moze byc o 2
					new Translation(-1, 1, 1), //bicie
					new Translation(-1, -1, 1), //bicie
				}
			};
	
	}
	else
	{
		possibleMovements = std::vector<std::vector<Translation*>> {
				{
					new Translation(1, 0,2),
					new Translation(2, 0,2), //pierwszy ruch moze byc o 2
					new Translation(1, -1, 1), //bicie
					new Translation(1, 1, 1), //bicie
				}
		};
	}
}


Pawn::~Pawn()
{
}


std::vector<std::vector<Translation*>> Pawn::getPossibleMovements()
{
	
	

	return possibleMovements;
}


Platform::String^ Pawn::getName()
{
	if (color == 0)
		return "White Pawn";
	else
		return "Black Pawn";
}

std::string Pawn::getStringName()
{
	if (color == 0)
		return "White Pawn";
	else
		return "Black Pawn";
}

void Pawn::pieceMoved()
{
	//jezeli jest drugi ruch to usuwamy zbedna translacje ktora byla dla 1 ruchu
	if (numberOfMoves == 1)
	{
		std::vector<std::vector<Translation*>>::iterator it_row;
		it_row = possibleMovements.begin();
		std::vector<Translation* > ::iterator it_col;
		it_col = it_row->begin();
		it_row->erase(it_col + 1); //usuwam 2 element wektora wewnetrznego

	}
}
