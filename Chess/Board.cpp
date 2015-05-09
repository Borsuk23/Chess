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


Board::Exit Board::userAction(int row, int column, Player* player) //nowy parametr gameState
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
				return Exit::PIECE_UNSELECTED;
			}
			else if (currentPiece != NULL)
			{
				player->capturePiece(currentPiece);
				fields[row][column]->placePiece(pieceSelected); //nowo klikniete pole
				pieceSelected->pieceMoved();
				fieldSelected->removeFromSelectedField(); //pole przy pierwszym kliknieciu
				clearSelection();
				pieceSelected = NULL;
				return Exit::PIECE_CAPTURED;
			}
			else
			{
				fields[row][column]->placePiece(pieceSelected);
				pieceSelected->pieceMoved();
				fieldSelected->removeFromSelectedField();
				clearSelection();
				pieceSelected = NULL;
				return Exit::PIECE_MOVED;
			}
			
		}
		else
			return Exit::NO_CHANGES;
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
				if (gameState == Board::GameState::CHECK)
					calculateBlockCheckMovements(row, column, player);
				else
					calculatePossibleMovements(row, column,player); //z calc zrobic boola bo przy szcahu moze si eokazac ze ten pionek nic nie zrobi i wtedy bedzie return NO CHANGES
				return Exit::PIECE_SELECTED;
			}
			else
				return Exit::NO_CHANGES;
		}
		else
			return Exit::NO_CHANGES;
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

//zrobic z niego boola
void Board::calculatePossibleMovements(int row, int column, Player* player)
{
	std::vector<std::vector<Translation*>> possibleTranslations;
	possibleTranslations = pieceSelected->getPossibleMovements();
	std::vector<std::vector<Translation*>>::iterator it_row;
	std::vector<Translation*>::iterator it_col;
	int tempX, tempY;
	Piece* standingPiece;
	//sprawdza wszystkie mozliwe kombinacje
	for (it_row = possibleTranslations.begin(); it_row < possibleTranslations.end(); it_row++)
	{
		for (it_col = it_row->begin(); it_col < it_row->end(); it_col++)
		{
			tempX = row + (*it_col)->row;
			tempY = column + (*it_col)->column;
			//podswietla tylko te, ktore sie mieszcza w planszy
			if ((tempX >= 0) && (tempX <= 7) && (tempY >= 0) && (tempY <= 7))
			{
				//blokowanie ruchu jak stoi moj pionek 
				standingPiece = fields[tempX][tempY]->checkField();
				if ((player->checkPiece(standingPiece)) == true) 
					break;
				
				switch ((*it_col)->option){
				case 0:
					fields[tempX][tempY]->setHighlighted(true);
					break;
				case 1: //obsluga bicia pionka
					if (((player->checkPiece(standingPiece)) == false) && (fields[tempX][tempY]->checkField() != NULL))
						fields[tempX][tempY]->setHighlighted(true);
					else break;
					; break;
				case 2: //obsluga pionka bez bicia
					if (((player->checkPiece(standingPiece)) == false) && (fields[tempX][tempY]->checkField() != NULL))
						break;
					else if (fields[tempX][tempY]->checkField() == NULL)
						fields[tempX][tempY]->setHighlighted(true);
					; break;
				case 3: //obsluga roszady
					; break;
				}
								
			}
		
		}
				
	}
		
}

Board::GameState Board::checkGameState(Player* player)
{
	GameState gameState = GameState::OK;	
	Piece* standingPiece;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			standingPiece = fields[i][j]->checkField();
			if ((standingPiece !=NULL) && (player->checkPiece(standingPiece) == false) )
				gameState = calculateCheck(i, j, player, standingPiece); // dla kazdej stojacej tam akurat figury
			if (gameState == GameState::CHECK)
			{
				//this->gameState = gameState;		
				return GameState::CHECK;
			}

		}
	}
	//this->gameState = gameState;	
	return gameState;
}
//sprawdzenie czy przeciwnik mnie szachuje
Board::GameState Board::calculateCheck(int row, int column, Player* player, Piece* pieceToCheck)
{
	std::vector<std::vector<Translation*>> possibleTranslations;
	possibleTranslations = pieceToCheck->getPossibleMovements();
	std::vector<std::vector<Translation*>>::iterator it_row;
	std::vector<Translation*>::iterator it_col;
	int tempX, tempY;
	Piece* standingPiece;
	std::string pieceName;
	
	//sprawdza wszystkie mozliwe kombinacje
	for (it_row = possibleTranslations.begin(); it_row < possibleTranslations.end(); it_row++)
	{
		for (it_col = it_row->begin(); it_col < it_row->end(); it_col++)
		{
			
			tempX = row + (*it_col)->row;
			tempY = column + (*it_col)->column;
			tempX = tempX;
			//podswietla tylko te, ktore sie mieszcza w planszy
			if ((tempX >= 0) && (tempX <= 7) && (tempY >= 0) && (tempY <= 7))
			{
				//jesli stoi tam figura przeciwnika
				standingPiece = fields[tempX][tempY]->checkField();
				if (((player->checkPiece(standingPiece)) == false) && (standingPiece != NULL))
					break;

				switch ((*it_col)->option){
				case 0:
					
					if (((player->checkPiece(standingPiece)) == true) && (fields[tempX][tempY]->checkField() != NULL) && (standingPiece->getStringName().compare("King") == 0))
					{
						pieceName = pieceName;
						return GameState::CHECK;
					}
					break;
					
				case 1: //obsluga bicia pionka
					if (((player->checkPiece(standingPiece)) == true) && (fields[tempX][tempY]->checkField() != NULL) && (standingPiece->getStringName().compare("King") == 0))
						return GameState::CHECK;
					break;
					
				case 2: //obsluga pionka bez bicia
					/*if (((player->checkPiece(standingPiece)) == false) && (fields[tempX][tempY]->checkField() != NULL))
						break;
					else if (fields[tempX][tempY]->checkField() == NULL)
						fields[tempX][tempY]->setHighlighted(true);*/
					break;
				case 3: //obsluga roszady
					break;
				
				}

			}

		}

	}

	return GameState::OK;
	
}

void Board::calculateBlockCheckMovements(int row, int column, Player* player)
{
	std::vector<std::vector<Translation*>> possibleTranslations;
	possibleTranslations = pieceSelected->getPossibleMovements();
	std::vector<std::vector<Translation*>>::iterator it_row;
	std::vector<Translation*>::iterator it_col;
	int tempX, tempY;
	Piece* standingPiece;
	Piece* tempPiece;
	tempPiece = pieceSelected;
	Piece*  tempStandingPiece;
	//sprawdza wszystkie mozliwe kombinacje
	for (it_row = possibleTranslations.begin(); it_row < possibleTranslations.end(); it_row++)
	{
		for (it_col = it_row->begin(); it_col < it_row->end(); it_col++)
		{
			tempX = row + (*it_col)->row;
			tempY = column + (*it_col)->column;
			//podswietla tylko te, ktore sie mieszcza w planszy
			if ((tempX >= 0) && (tempX <= 7) && (tempY >= 0) && (tempY <= 7))
			{
				
				standingPiece = fields[tempX][tempY]->checkField();
				
				//blokowanie ruchu jak stoi moj pionek 
				if ((player->checkPiece(standingPiece)) == true)
					break;

				if (((player->checkPiece(standingPiece)) == false) && (fields[tempX][tempY]->checkField() != NULL))
				{
					tempStandingPiece = standingPiece;

					switch ((*it_col)->option){
					case 0:

						fields[tempX][tempY]->placePiece(pieceSelected);
						if (checkGameState(player) == Board::GameState::OK)
						{
							fields[tempX][tempY]->setHighlighted(true);
						}
						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						fields[tempX][tempY]->placePiece(tempStandingPiece);
						break;
					case 1: //obsluga bicia pionka
						fields[tempX][tempY]->placePiece(pieceSelected);
						if (((player->checkPiece(standingPiece)) == false) && (fields[tempX][tempY]->checkField() != NULL) && (checkGameState(player) == Board::GameState::OK))
							fields[tempX][tempY]->setHighlighted(true);
						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						fields[tempX][tempY]->placePiece(tempStandingPiece);
						break;
					case 2: //obsluga pionka bez bicia
						fields[tempX][tempY]->placePiece(pieceSelected);
						if (((player->checkPiece(standingPiece)) == false) && (fields[tempX][tempY]->checkField() != NULL))
						{
							fields[row][column]->placePiece(tempPiece);
							fields[tempX][tempY]->removeFromSelectedField();
							fields[tempX][tempY]->placePiece(tempStandingPiece);
							break;
						}
							
						else if ((fields[tempX][tempY]->checkField() == NULL) && (checkGameState(player) == Board::GameState::OK))
							fields[tempX][tempY]->setHighlighted(true);
						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						fields[tempX][tempY]->placePiece(tempStandingPiece);
						break;
					case 3: //obsluga roszady
						; break;
					}
				}
				else
				{
					switch ((*it_col)->option){
					case 0:

						fields[tempX][tempY]->placePiece(pieceSelected);
						if (checkGameState(player) == Board::GameState::OK)
						{
							fields[tempX][tempY]->setHighlighted(true);
						}
						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						break;
					case 1: //obsluga bicia pionka
						fields[tempX][tempY]->placePiece(pieceSelected);
						if (((player->checkPiece(standingPiece)) == false) && (fields[tempX][tempY]->checkField() != NULL) && (checkGameState(player) == Board::GameState::OK))
							fields[tempX][tempY]->setHighlighted(true);
						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						break;
					case 2: //obsluga pionka bez bicia
						fields[tempX][tempY]->placePiece(pieceSelected);
						if (((player->checkPiece(standingPiece)) == false) && (fields[tempX][tempY]->checkField() != NULL))
						{
							fields[row][column]->placePiece(tempPiece);
							fields[tempX][tempY]->removeFromSelectedField();
							break;
						}
						else if ((fields[tempX][tempY]->checkField() == NULL) && (checkGameState(player) == Board::GameState::OK))
							fields[tempX][tempY]->setHighlighted(true);
						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						break;
					case 3: //obsluga roszady
						; break;
					}
				}
			}

		}

	}

}



//----------------------------------------------------GUI---------------------------------------
std::vector<std::vector<Field*>> Board::getFields()
{
	return this->fields;
}

//std::string make_string(const std::wstring& wstring)
//{
//	auto wideData = wstring.c_str();
//	int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideData, -1, nullptr, 0, NULL, NULL);
//	auto utf8 = std::make_unique<char[]>(bufferSize);
//	if (0 == WideCharToMultiByte(CP_UTF8, 0, wideData, -1, utf8.get(), bufferSize, NULL, NULL))
//		throw std::exception("Can't convert string to UTF8");
//
//	return std::string(utf8.get());
//}