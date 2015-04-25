#include "pch.h"
#include "Board.h"


Board::Board(Player* playerWhite, Player* playerBlack)
{	
	//tablica wskaznikow na pola
	fields = std::vector<std::vector<Field*>>(8, std::vector<Field*>(8));
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if ((i+j)%2==0)
				fields[i][j] = new Field(1); //bialy
			else
				fields[i][j] = new Field(0); //czarny
		}

	pieceSelected = NULL;
	fieldSelected = NULL;

	//ustawianie pionkow na planszy
	std::vector<Piece*> blacks = playerBlack->getPieces();
	std::vector<Piece*> whites = playerWhite->getPieces();
	for (int i = 0; i < 8; i++)
	{
		fields[0][7 - i]->placePiece(blacks[i]);
		fields[1][7 - i]->placePiece(blacks[i+8]);
	}
	
	for (int i = 0; i < 8; i++)
	{
		fields[7][i]->placePiece(whites[i]);
		fields[6][i]->placePiece(whites[i + 8]);
	}

}


Board::~Board()
{
}


void Board::userAction(int x, int y, Player* player)
{
}


Field* Board::checkField(int x, int y)
{
	return NULL;
}


void Board::clearSelection()
{
}


void Board::calculatePossibleMovements(int x, int y)
{
}
