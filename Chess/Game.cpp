#include "pch.h"
#include "Game.h"


Game::Game(std::string whitePlayerNickName, std::string blackPlayerNickName)
{
	players.push_back(new Player(0,whitePlayerNickName)); //0 bialy
	players.push_back(new Player(1,blackPlayerNickName)); //1 czarny
	board = new Board(players[0],players[1]);
	currentPlayer = players[0];	//bialy zaczyna
	turnNumber = 0;
	isFinished = false;
}


Game::~Game()
{
}


void Game::userAction(int row, int column)
{
	
	Board::Exit e = board->userAction(row, column, currentPlayer);
	Board::GameState gameState;		// czemu to jest zmienna lokalna funkcji userAction a nie atrybut klasy Game?
	// za kazdym wejsciem w userAction tworzysz nowa i nie pamietasz jej na przyszlosc (a jak masz wyswietlac to chyba fajnie by bylo pamietac)
	//chyba ze o to Ci chodzilo i nie chcesz tego zapamietywac na potem
	switch (e) {
	case Board::Exit::NO_CHANGES: 
		; break;
	case Board::Exit::PIECE_SELECTED:
			; break;
	case Board::Exit::PIECE_UNSELECTED:
		; break;
	case Board::Exit::PIECE_MOVED:
		gameState = board->checkGameState(currentPlayer);
		gameState = gameState;
		changeTurn();
		 break;
	case Board::Exit::PIECE_CAPTURED:
		gameState = board->checkGameState(currentPlayer);
		changeTurn();	
		 break;
	default:
		break;
	}
}


void Game::changeTurn()
{
	turnNumber++;
	currentPlayer = players[turnNumber % 2]; //zwraca obecnego gracza; jak parzysta to bialy jak nieparzysta to czarny
}


void Game::removeCapturedPieces()
{
	Piece* capturedPiece;
	capturedPiece = currentPlayer->getLastCapturedPiece();
	players[(turnNumber + 1) % 2]->removeCapturedPiece(capturedPiece);  //drugiego gracza
}

Board* Game::getBoard() {
	return this->board;
}
