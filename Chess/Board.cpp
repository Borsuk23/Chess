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
		fields[0][i]->placePiece(blacks[i]);
		fields[1][i]->placePiece(blacks[i+8]);
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


int Board::userAction(int row, int column, Player* player)
{
	Piece* currentPiece;
	//sprawdzenie czy 1 czy 2 klikniecie
	if (pieceSelected != NULL)
	{
		//obsluga 2 klikniecia
		if (fields[row][column]->isHighlighted() == true) //jesli bylo podswietlone czyli to 2 klikniecie
		{
			currentPiece = fields[row][column]->checkField();
			if (currentPiece == pieceSelected) //jesli to moja figura
			{
				clearSelection();
				pieceSelected = NULL;
				return 3;
			}
			else if (currentPiece != NULL)
			{
				player->capturePiece(currentPiece);
				fields[row][column]->placePiece(pieceSelected); //nowo klikniete pole
				fieldSelected->removeFromSelectedField(); //pole przy pierwszym kliknieciu
				clearSelection();
				pieceSelected = NULL;
				return 5;
			}
			else
			{
				fields[row][column]->placePiece(pieceSelected);
				fieldSelected->removeFromSelectedField();
				clearSelection();
				pieceSelected = NULL;
				return 4;
			}
			
		}
		else
			return 1;
	}
	//obsluga 1 klikniecia
	else
	{
		currentPiece = fields[row][column]->checkField();
		//jesli cos tu stoi
		if (currentPiece != NULL)
		{
			//jesli obecnego gracza
			if (player->checkPiece(currentPiece) == true)
			{
				pieceSelected = currentPiece;
				fields[row][column]->setHighlighted(true);
				fieldSelected = fields[row][column];
				calculatePossibleMovements(row, column);
				return 2;
			}
			else
				return 1;
		}
		else
			return 1;
	}
}


Field* Board::checkField(int row, int column)
{
	return NULL;
}


void Board::clearSelection()
{
	pieceSelected = NULL;
	//odznacza wszystkie podswietlone wczesniej
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			fields[i][j]->setHighlighted(false);
		}
	}
}


void Board::calculatePossibleMovements(int row, int column)
{
	std::vector<Translation*> possibleTranslations;
	possibleTranslations = pieceSelected->getPossibleMovements();
	std::vector<Translation*>::iterator it;
	int tempX, tempY;
	//sprawdza wszystkie mozliwe kombinacje
	for (it = possibleTranslations.begin(); it < possibleTranslations.end(); it++)
	{
		tempX = row + (*it)->x;
		tempY = column + (*it)->y;
		//podswietla tylko te, ktore sie mieszcza w planszy
		if ((tempX >= 0) && (tempX <= 7) && (tempY >= 0) && (tempY <= 7))
		{
			fields[tempX][tempY]->setHighlighted(true);
		}
		//blokowanie ruchu jak stoi moj pionek 
	}

	//podwojny for najpierw po kierunkach pozniej po polach i break jak spotka moja
	//przekazywac playera do calculateposmov
	//std::vector<std::vector<translation>> gora, skos, prawo, skos itp
}


std::vector<std::vector<Field*>> Board::getFields()
{
	return this->fields;
}