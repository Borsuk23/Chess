#include "pch.h"
#include "Game.h"


Game::Game(std::string whitePlayerNickName, std::string blackPlayerNickName)
{
	players.push_back(new Player(0,whitePlayerNickName)); 
	players.push_back(new Player(1,blackPlayerNickName)); 
	board = new Board(players[0],players[1]);
	currentPlayer = players[0];	
	turnNumber = 0;
	isFinished = false;
	stateCheckMate = false;
}


Game::~Game()
{
}


void Game::userAction(int row, int column)
{
	
	Board::Exit e = board->userAction(row, column, currentPlayer);

	switch (e) {
	case Board::Exit::NO_CHANGES: 
		; break;
	case Board::Exit::PIECE_SELECTED:
			; break;
	case Board::Exit::PIECE_UNSELECTED:
		; break;
	case Board::Exit::PIECE_MOVED:
		if (board->checkPromotion(row, column, currentPlayer) == true)
		{
			promotionFlag = true;
			promotionRow = row;
			promotionColumn = column;
			break;
		}
		changeTurn();
		this->gameState = board->checkGameState(currentPlayer);
		this->board->gameState = this->gameState;
		//if (this->gameState == Board::GameState::CHECK)
		//{
			this->stateCheckMate = board->checkCheckmateState(currentPlayer);
			if (this->stateCheckMate == true)
				this->isFinished = true;
			isFinished = isFinished;
		//}
		 break;
	case Board::Exit::PIECE_CAPTURED:
		if (board->checkPromotion(row, column, currentPlayer) == true)
		{
			promotionFlag = true;
			promotionRow = row;
			promotionColumn = column;
			break;
		}
		
		changeTurn();
		this->gameState = board->checkGameState(currentPlayer);
		this->board->gameState = this->gameState;
		//if (this->gameState == Board::GameState::CHECK)
		//{
			this->stateCheckMate = board->checkCheckmateState(currentPlayer);
			if (this->stateCheckMate == true)
				this->isFinished = true;
			isFinished = isFinished;
		//}
		 break;
	
	default:
		break;
	}
}


void Game::changeTurn()
{
	turnNumber++;
	currentPlayer = players[turnNumber % 2]; //1 - black, 0 - white
}


void Game::removeCapturedPieces()
{
	Piece* capturedPiece;
	capturedPiece = currentPlayer->getLastCapturedPiece();
	players[(turnNumber + 1) % 2]->removeCapturedPiece(capturedPiece);  //oppponent
}

Board* Game::getBoard() {
	return this->board;
}

std::vector<std::vector<Piece*>> Game::getCapturedPieces()
{
	std::vector<std::vector<Piece*>> temp = std::vector < std::vector<Piece*> > {
		this->players[0]->getCapturedPieces(),
		this->players[1]->getCapturedPieces()
	};
	/*temp[0] = this->players[0]->getCapturedPieces();
	temp[1] = this->players[1]->getCapturedPieces();*/

	return temp;
}

void Game::promotion(int promotionPiece)
{
	//tutaj promocja
	Piece* movedPiece;

	movedPiece = board->getFields()[promotionRow][promotionColumn]->checkField();
	if ((movedPiece->getStringName() == "White Pawn") && (promotionRow == 0))
	{
		movedPiece = board->promotePawn(promotionRow, promotionColumn, currentPlayer, 0, movedPiece,promotionPiece);

	}
	else if ((movedPiece->getStringName() == "Black Pawn") && (promotionRow == 7))
	{
		movedPiece = board->promotePawn(promotionRow, promotionColumn, currentPlayer, 1, movedPiece, promotionPiece);
	}
	promotionFlag = false;
	
	changeTurn();
	this->gameState = board->checkGameState(currentPlayer);
	this->board->gameState = this->gameState;
	//if (this->gameState == Board::GameState::CHECK)
	//{
	this->stateCheckMate = board->checkCheckmateState(currentPlayer);
	if (this->stateCheckMate == true)
		this->isFinished = true;
	isFinished = isFinished;
	//}
}