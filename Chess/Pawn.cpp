#include "pch.h"
#include "Pawn.h"
#include "Piece.h"


Pawn::Pawn(int color) : Piece(color)
{  
	if (color == 0)
	{
		possibleMovements = std::vector<std::vector<Translation*>> {
				{
					new Translation(-1, 0, 2),
					new Translation(-2, 0, 2), //first move
				},
				{
					new Translation(-1, 1, 1), //capture
				},
				{
					new Translation(-1, -1, 1), //capture
				}
			};
	
	}
	else
	{
		possibleMovements = std::vector<std::vector<Translation*>> {
				{
					new Translation(1, 0, 2),
					new Translation(2, 0, 2), //first move
				},
				{
					new Translation(1, -1, 1), //capture
				},
				{
					new Translation(1, 1, 1), //capture
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
		return "white_pawn.png";
	else
		return "black_pawn.png";
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
	numberOfMoves++;
	//erase translation for 2 field movement
	if (numberOfMoves == 1)
	{
		std::vector<std::vector<Translation*>>::iterator it_row;
		it_row = possibleMovements.begin();
		std::vector<Translation* > ::iterator it_col;
		it_col = it_row->begin();
		it_row->erase(it_col + 1); //erase second element from inner vector

	}
}


