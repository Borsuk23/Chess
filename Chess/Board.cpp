#include "pch.h"
#include "Board.h"


Board::Board(Player* playerWhite, Player* playerBlack)
{	
	//table of Fields
	fields = std::vector<std::vector<Field*>>(8, std::vector<Field*>(8));
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if ((i+j)%2==0)
				fields[i][j] = new Field(1); //black
			else
				fields[i][j] = new Field(0); //white
		}

	pieceSelected = NULL;
	fieldSelected = NULL;
	this->stateCheckmate = false;

	//place Pieces on Board
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


Board::Exit Board::userAction(int row, int column, Player* player) 
{
	Piece* currentPiece;

	//check if first or second click
	if (pieceSelected != NULL)
	{
		//2 click
		if (fields[row][column]->isHighlighted() == true) 
		{
			currentPiece = fields[row][column]->checkField();
			//if the same piece clicked
			if (currentPiece == pieceSelected) 
			{
				clearSelection();
				pieceSelected = NULL;
				return Exit::PIECE_UNSELECTED;
			}
			else if (currentPiece != NULL)
			{
				player->capturePiece(currentPiece);
				fields[row][column]->placePiece(pieceSelected); //new clicked field
				pieceSelected->pieceMoved();
				fieldSelected->removeFromSelectedField(); //first click field
				clearSelection();
				pieceSelected = NULL;
				endEnPassantField = NULL;
				middleEnPassantField = NULL;
				return Exit::PIECE_CAPTURED;
			}
			else if (currentPiece==NULL && (fields[row][column]==middleEnPassantField))		//En Passant capture
			{
					player->capturePiece(endEnPassantField->checkField());
					fields[row][column]->placePiece(pieceSelected);					//new clicked field
					pieceSelected->pieceMoved();
					fieldSelected->removeFromSelectedField();						//first click field
					endEnPassantField->removeFromSelectedField();
					clearSelection();
					pieceSelected = NULL;
					endEnPassantField = NULL;
					middleEnPassantField = NULL;
					return Exit::PIECE_CAPTURED;
			}
			else if (fields[row][column] == longCastlingField)		//long castling move
			{
				fields[row][column]->placePiece(pieceSelected);
				fields[row][column + 1]->placePiece(castlingPiece); //move Rook
				pieceSelected->pieceMoved();
				castlingPiece->pieceMoved();						//add numberOfMoves to Rook
				fieldSelected->removeFromSelectedField();
				fields[row][column - 2]->removeFromSelectedField();
				clearSelection();
				pieceSelected = NULL;
				castlingPiece = NULL;
				longCastlingField = NULL;
				endEnPassantField = NULL;
				middleEnPassantField = NULL;
				return Exit::PIECE_MOVED;
			}
			else if (fields[row][column] == shortCastlingField)		//short castling move
			{
				fields[row][column]->placePiece(pieceSelected);
				fields[row][column - 1]->placePiece(castlingPiece); //move Rook
				pieceSelected->pieceMoved();
				castlingPiece->pieceMoved();						//add numberOfMoves to Rook
				fieldSelected->removeFromSelectedField();
				fields[row][column+1]->removeFromSelectedField();
				clearSelection();
				pieceSelected = NULL;
				castlingPiece = NULL;
				shortCastlingField = NULL;
				endEnPassantField = NULL;
				middleEnPassantField = NULL;
				return Exit::PIECE_MOVED;
			}
			else if (fields[row][column]==highlightedEndEnPassantField) //first pawn 2 field move, possible en passant
			{
				endEnPassantField = highlightedEndEnPassantField;
				middleEnPassantField = highlightedMiddleEnPassantField;
				fields[row][column]->placePiece(pieceSelected);
				pieceSelected->pieceMoved();
				fieldSelected->removeFromSelectedField();
				clearSelection();
				pieceSelected = NULL;
				return Exit::PIECE_MOVED;
			}
			else													//normal move
			{
				fields[row][column]->placePiece(pieceSelected);
				pieceSelected->pieceMoved();
				fieldSelected->removeFromSelectedField();
				clearSelection();
				pieceSelected = NULL;
				endEnPassantField = NULL;
				middleEnPassantField = NULL;
				//checkPromotion(row, column, player);
				return Exit::PIECE_MOVED;
			}
			
		}
		else
			return Exit::NO_CHANGES;
	}
	//1 click
	else
	{
		currentPiece = fields[row][column]->checkField();
		
		if (currentPiece != NULL)
		{
			//if my piece
			if (player->checkPiece(currentPiece) == true)
			{
				pieceSelected = currentPiece;
				fields[row][column]->setHighlighted(true);
				fieldSelected = fields[row][column];
				calculatePossibleMovements(row, column, player);		
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
	
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			fields[i][j]->setHighlighted(false);
		}
	}
}

//**************************************************************************************************
//*************************************** POSSIBLE MOVEMENTS ***************************************
//**************************************************************************************************

void Board::calculatePossibleMovements(int row, int column, Player* player)
{
	std::vector<std::vector<Translation*>> possibleTranslations;
	possibleTranslations = pieceSelected->getPossibleMovements();
	std::vector<std::vector<Translation*>>::iterator it_row;
	std::vector<Translation*>::iterator it_col;
	int tempR, tempC;
	Piece* standingPiece;
	Piece* tempPiece;
	tempPiece = pieceSelected;
	Piece*  tempStandingPiece;
	


	for (it_row = possibleTranslations.begin(); it_row < possibleTranslations.end(); it_row++)
	{
		for (it_col = it_row->begin(); it_col < it_row->end(); it_col++)
		{
			tempR = row + (*it_col)->row;
			tempC = column + (*it_col)->column;

			//only these, which fit the board
			if ((tempR >= 0) && (tempR <= 7) && (tempC >= 0) && (tempC <= 7))
			{

				standingPiece = fields[tempR][tempC]->checkField();

				//castlingPiece = standingPiece;

				//my piece on way
				if ((player->checkPiece(standingPiece)) == true)
					break;

				//if opponents piece is standing
				if ((fields[tempR][tempC]->checkField() != NULL) && ((player->checkPiece(standingPiece)) == false))
				{
					tempStandingPiece = standingPiece;

					switch ((*it_col)->option){
					case 0:

						fields[tempR][tempC]->placePiece(pieceSelected);
						fields[row][column]->removeFromSelectedField();
						if (checkGameState(player) == Board::GameState::OK)
						{
							fields[tempR][tempC]->setHighlighted(true);
						}
						fields[row][column]->placePiece(tempPiece);
						fields[tempR][tempC]->removeFromSelectedField();
						fields[tempR][tempC]->placePiece(tempStandingPiece);
						break;
					case 1: //pawn capture
						fields[tempR][tempC]->placePiece(pieceSelected);
						fields[row][column]->removeFromSelectedField();
						if ((checkGameState(player) == Board::GameState::OK))
						{
							fields[tempR][tempC]->setHighlighted(true);
						}
							
						fields[row][column]->placePiece(tempPiece);
						fields[tempR][tempC]->removeFromSelectedField();
						fields[tempR][tempC]->placePiece(tempStandingPiece);
						break;
					case 2: //pawn move without capture
						break;
					
					}
				}
				else
				{
					switch ((*it_col)->option){
					case 0:

						fields[tempR][tempC]->placePiece(pieceSelected);
						fields[row][column]->removeFromSelectedField();
						if (checkGameState(player) == Board::GameState::OK)
						{
							fields[tempR][tempC]->setHighlighted(true);
						}
						fields[row][column]->placePiece(tempPiece);
						fields[tempR][tempC]->removeFromSelectedField();
						break;
					case 1: //pawn capture
						if (fields[tempR][tempC]==middleEnPassantField)	//En Passant Capture
						{
							fields[tempR][tempC]->placePiece(pieceSelected);
							fields[row][column]->removeFromSelectedField();
							if ((checkGameState(player) == Board::GameState::OK))
							{
								fields[tempR][tempC]->setHighlighted(true);
							}

							fields[row][column]->placePiece(tempPiece);
							fields[tempR][tempC]->removeFromSelectedField();
							
						}
						break;
					case 2: //pawn move without capture
						fields[tempR][tempC]->placePiece(pieceSelected);
						fields[row][column]->removeFromSelectedField();
						if ((checkGameState(player) == Board::GameState::OK))
						{
							fields[tempR][tempC]->setHighlighted(true);
						}
							
						fields[row][column]->placePiece(tempPiece);
						fields[tempR][tempC]->removeFromSelectedField();

						if (pieceSelected->numberOfMoves == 0)						//first move, possible en passant
						{
							if ((pieceSelected->color==1) && (fields[tempR][tempC] == fields[row + 2][column]))
							{
								highlightedMiddleEnPassantField = fields[tempR - 1][tempC];
								highlightedEndEnPassantField = fields[tempR][tempC];
							}
							if ((pieceSelected->color == 0) && (fields[tempR][tempC] == fields[row - 2][column]))
							{
								highlightedMiddleEnPassantField = fields[tempR + 1][tempC];
								highlightedEndEnPassantField = fields[tempR][tempC];
							}
						}
						
						
						break;
					case 3: //short castling
						
						if ((checkGameState(player) == Board::GameState::OK) && (fields[tempR][tempC+1]->checkField() != NULL) && (player->checkPiece(fields[tempR][tempC+1]->checkField()) == true) && (pieceSelected->numberOfMoves==0))
						{
								this->castlingPiece = fields[tempR][tempC+1]->checkField(); //Rook


							if ((castlingPiece->getStringName() == "Rook") && (castlingPiece->numberOfMoves == 0) && (fields[tempR][tempC-1]->checkField() == NULL))
							{
								fields[tempR][tempC-1]->placePiece(pieceSelected);
								fields[row][column]->removeFromSelectedField();
								if ((checkGameState(player) == Board::GameState::OK))
								{

									fields[tempR][tempC]->placePiece(pieceSelected);
									fields[row][column]->removeFromSelectedField();
									if ((checkGameState(player) == Board::GameState::OK))
									{
										fields[tempR][tempC]->setHighlighted(true);
										this->shortCastlingField = fields[tempR][tempC];
									}
									fields[row][column]->placePiece(tempPiece);
									fields[tempR][tempC]->removeFromSelectedField();
								}
								fields[row][column]->placePiece(tempPiece);
								fields[tempR][tempC-1]->removeFromSelectedField();
							}
						}
						break;
					case 4: //long castling
						if ((checkGameState(player) == Board::GameState::OK) && (fields[tempR][tempC -2]->checkField() != NULL) && (player->checkPiece(fields[tempR][tempC -2]->checkField()) == true) && (pieceSelected->numberOfMoves == 0))
						{
							this->castlingPiece = fields[tempR][tempC -2]->checkField(); //Rook

							if ((castlingPiece->getStringName() == "Rook") && (castlingPiece->numberOfMoves == 0) && (fields[tempR][tempC + 1]->checkField() == NULL))
							{
								fields[tempR][tempC + 1]->placePiece(pieceSelected);
								fields[row][column]->removeFromSelectedField();
								if ((checkGameState(player) == Board::GameState::OK))
								{

									fields[tempR][tempC]->placePiece(pieceSelected);
									fields[row][column]->removeFromSelectedField();
									if ((checkGameState(player) == Board::GameState::OK))
									{
										fields[tempR][tempC]->setHighlighted(true);
										this->longCastlingField = fields[tempR][tempC];
									}
									fields[row][column]->placePiece(tempPiece);
									fields[tempR][tempC]->removeFromSelectedField();
								}
								fields[row][column]->placePiece(tempPiece);
								fields[tempR][tempC + 1]->removeFromSelectedField();
							}
						}
						break;
					}
				}

				//first opponents piece
				if (((player->checkPiece(standingPiece)) == false) && (fields[tempR][tempC]->checkField() != NULL))
				{
					break;
				}
			}

		}

	}


}


//*****************************************************************************************************
//**************************************** G A M E S T A T E*******************************************
//*****************************************************************************************************

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
				gameState = calculateCheck(i, j, player, standingPiece); //check every standing piece on board
			if (gameState == GameState::CHECK)
			{	
				return GameState::CHECK;
			}

		}
	}
	return gameState;
}


//**************************************************************************************************
//*************************************** C H E C K ************************************************
//**************************************************************************************************

//oppponent cause check, am i checked
Board::GameState Board::calculateCheck(int row, int column, Player* player, Piece* pieceToCheck)
{
	std::vector<std::vector<Translation*>> possibleTranslations;
	possibleTranslations = pieceToCheck->getPossibleMovements();
	std::vector<std::vector<Translation*>>::iterator it_row;
	std::vector<Translation*>::iterator it_col;
	int tempX, tempY;
	Piece* standingPiece ;
	std::string pieceName;
	
	
	for (it_row = possibleTranslations.begin(); it_row < possibleTranslations.end(); it_row++)
	{
		for (it_col = it_row->begin(); it_col < it_row->end(); it_col++)
		{
			
			tempX = row + (*it_col)->row;
			tempY = column + (*it_col)->column;
			
			//only these, which fit the board
			if ((tempX >= 0) && (tempX <= 7) && (tempY >= 0) && (tempY <= 7))
			{
				//oppponents piece on check way
				standingPiece = fields[tempX][tempY]->checkField();
				if (((player->checkPiece(standingPiece)) == false) && (standingPiece != NULL))
					break;

				//my piece on check way
				if (((player->checkPiece(standingPiece)) == true) && (standingPiece->getStringName().compare("King") != 0)) 
					break;

				switch ((*it_col)->option){
				case 0:
					
					if (((player->checkPiece(standingPiece)) == true) && (fields[tempX][tempY]->checkField() != NULL) && (standingPiece->getStringName().compare("King") == 0))
					{
						pieceName = pieceName;
						return GameState::CHECK;
					}
					break;
					
				case 1: //pawn capture
					if (((player->checkPiece(standingPiece)) == true) && (fields[tempX][tempY]->checkField() != NULL) && (standingPiece->getStringName().compare("King") == 0))
						return GameState::CHECK;
					break;
					
				case 2: //pawn move without capture					
					break;
				
				}

			}

		}

	}

	return GameState::OK;
	
}


//**************************************************************************************************
//*************************************** C H E C K M A T E ****************************************
//**************************************************************************************************


bool Board::checkCheckmateState(Player* player)
{

	Piece* standingPiece;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			standingPiece = fields[i][j]->checkField();
			if ((player->checkPiece(standingPiece) == true))
			{
				this->stateCheckmate = calculateCheckmateMovements(i, j, player, standingPiece); //check every standing piece on board
				if (this->stateCheckmate == false)
				{
					return false;
				}
			}

		}
	}	
	return true;
}


bool Board::calculateCheckmateMovements(int row, int column, Player* player, Piece* pieceToCheck)
{
	std::vector<std::vector<Translation*>> possibleTranslations;
	possibleTranslations = pieceToCheck->getPossibleMovements();
	std::vector<std::vector<Translation*>>::iterator it_row;
	std::vector<Translation*>::iterator it_col;
	int tempX, tempY;
	Piece* standingPiece;
	Piece* tempPiece;
	tempPiece = pieceToCheck;
	Piece*  tempStandingPiece;
	bool stateCheckMate = true;


	for (it_row = possibleTranslations.begin(); it_row < possibleTranslations.end(); it_row++)
	{
		for (it_col = it_row->begin(); it_col < it_row->end(); it_col++)
		{
			tempX = row + (*it_col)->row;
			tempY = column + (*it_col)->column;

			//only these, which fit the board
			if ((tempX >= 0) && (tempX <= 7) && (tempY >= 0) && (tempY <= 7))
			{

				standingPiece = fields[tempX][tempY]->checkField();

				//my piece on way
				if ((player->checkPiece(standingPiece)) == true)
					break;

				//if opponents piece is standing
				if ((fields[tempX][tempY]->checkField() != NULL) && ((player->checkPiece(standingPiece)) == false))
				{
					tempStandingPiece = standingPiece;

					switch ((*it_col)->option){
					case 0:

						fields[tempX][tempY]->placePiece(pieceToCheck);
						fields[row][column]->removeFromSelectedField();
						if (checkGameState(player) == Board::GameState::OK)
						{
							stateCheckMate = false;
						}
						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						fields[tempX][tempY]->placePiece(tempStandingPiece);
						break;
					case 1: //pawn capture
						fields[tempX][tempY]->placePiece(pieceToCheck);
						fields[row][column]->removeFromSelectedField();
						if ((checkGameState(player) == Board::GameState::OK))
						{
							stateCheckMate = false;
						}

						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						fields[tempX][tempY]->placePiece(tempStandingPiece);
						break;
					case 2: //pawn move without capture
						break;

					}
				}
				else
				{
					switch ((*it_col)->option){
					case 0:

						fields[tempX][tempY]->placePiece(pieceToCheck);
						fields[row][column]->removeFromSelectedField();
						if (checkGameState(player) == Board::GameState::OK)
						{
							stateCheckMate = false;
						}
						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						break;
					case 1: //pawn capture

						break;
					case 2: //pawn move without capture
						fields[tempX][tempY]->placePiece(pieceToCheck);
						fields[row][column]->removeFromSelectedField();
						if ((checkGameState(player) == Board::GameState::OK))
						{
							stateCheckMate = false;
						}

						fields[row][column]->placePiece(tempPiece);
						fields[tempX][tempY]->removeFromSelectedField();
						break;
					
					}
				}

				//first opponents piece
				if (((player->checkPiece(standingPiece)) == false) && (fields[tempX][tempY]->checkField() != NULL))
				{

					break;
				}
			}

		}

	}

	return stateCheckMate;

}


//**************************************************************************************************
//*************************************** P R O M O T I O N ****************************************
//**************************************************************************************************

bool Board::checkPromotion(int row, int column, Player* player)
{
	Piece* movedPiece;
	
	movedPiece = fields[row][column]->checkField();
	if ((movedPiece->getStringName() == "White Pawn") && (row==0))
	{
		return true;
		
	}
	else if ((movedPiece->getStringName() == "Black Pawn") && (row == 7))
	{
		return true;
	}
	return false;

}

Piece* Board::promotePawn(int row, int column, Player* player, int color, Piece* movedPawn, int promotionPiece)
{
	Piece* whitePromotionPiece;
	Piece* blackPromotionPiece;
	std::vector<Piece*>::iterator it;
	Piece* promotedPawn;


	switch (promotionPiece)
	{
	case 0:
	default:
		whitePromotionPiece = new Queen(0);
		blackPromotionPiece = new Queen(1);
		break;
	case 1:
		whitePromotionPiece = new Knight(0);
		blackPromotionPiece = new Knight(1);	
		break;
	case 2:
		whitePromotionPiece = new Rook(0);
		blackPromotionPiece = new Rook(1);
		break;
	case 3:
		whitePromotionPiece = new Bishop(0);
		blackPromotionPiece = new Bishop(1);
		break;
	}


	//find Pawn in players pieces
	it = std::find(player->pieces.begin(), player->pieces.end(), movedPawn);

	if (color == 0)	//white player promotion
	{
		//if found erase it and place new piece
		if (it != player->pieces.end())
		{
			player->pieces.erase(it);
			player->pieces.push_back(whitePromotionPiece);
		};

		fields[row][column]->removeFromSelectedField();
		fields[row][column]->placePiece(whitePromotionPiece);
	}
	else    //black player  promotion
	{

		if (it != player->pieces.end())
		{
			player->pieces.erase(it);
			player->pieces.push_back(blackPromotionPiece);
		};

		fields[row][column]->removeFromSelectedField();
		fields[row][column]->placePiece(blackPromotionPiece);
	}

	promotedPawn = fields[row][column]->checkField();

	return promotedPawn;
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
//
//Board::GameState Board::checkMoveForCheck(int x, int y, Player* currentPlayer, int moveOption)
//{
//	Piece *standingPiece = fields[x][y]->checkField();
//
//	if (standingPiece == NULL) //empty field
//		return GameState::OK;
//
//	if (currentPlayer->checkPiece(standingPiece) == false) //opponent piece
//		return GameState::OK;
//
//	if (standingPiece->getStringName().compare("King") != 0) //current player's piece, but not king
//		return GameState::OK;
//
//	switch (moveOption)
//	{
//	case 0:
//	case 1:
//		if (standingPiece->getStringName().compare("King") == 0)
//			return GameState::CHECK;
//		break;
//	default:
//		break;
//	}
//	return GameState::OK;
//}
//
//
////sprawdzenie czy przeciwnik mnie szachuje
//Board::GameState Board::calculateCheck(int row, int column, Player player, Piece* pieceToCheck)
//{
//	std::vector<std::vector<Translation*>> possibleTranslations;
//	possibleTranslations = pieceToCheck->getPossibleMovements();
//	std::vector<std::vector<Translation*>>::iterator it_row;
//	std::vector<Translation*>::iterator it_col;
//	int tempX, tempY;
//
//	//sprawdza wszystkie mozliwe kombinacje
//	for (it_row = possibleTranslations.begin(); it_row < possibleTranslations.end(); it_row++)
//	{
//		for (it_col = it_row->begin(); it_col < it_row->end(); it_col++)
//		{
//
//			tempX = row + (*it_col)->row;
//			tempY = column + (*it_col)->column;
//			//tempXNext = row + (*it_col+1)->row;
//			//podswietla tylko te, ktore sie mieszcza w planszy
//			if ((tempX >= 0) && (tempX <= 7) && (tempY >= 0) && (tempY <= 7))
//			{
//				if (checkMoveForCheck(tempX, tempY, player, (*it_col)->option) == GameState::CHECK)
//					return GameState::CHECK;
//			}
//		}
//	}
//	return GameState::OK;
//}
//
