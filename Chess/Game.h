#pragma once
#include "Player.h"
#include "Board.h"
#include "Click.h"
#include <iostream>
#include <fstream>
#include "DatabaseManager.h"

class Game
{
public:
	Game(std::string whitePlayerNickName, std::string blackPlayerNickName); 
	virtual ~Game();
	void userAction(int x, int y);
	Board* getBoard();
	int turnNumber;
	bool stateCheckMate;
	Board::GameState gameState;
	bool isFinished;
	std::vector<std::vector<Piece*>> getCapturedPieces();
	std::vector<Player*> players;
	bool promotionFlag;
	void promotion(int promotionPiece);
	void saveToFile();
	bool resumeGame();
	void startNewGame();
	//typedef enum gameState { OK, CHECK, CHECKMATE } gameState;
private:
	void changeTurn();
	void removeCapturedPieces();
	int promotionRow;
	int promotionColumn;
	Player* currentPlayer;
	Board* board;
	std::vector<Click*> moves;
	DatabaseManager* databaseManager;
	

	//void createTable(int numberOfColumns, char* fieldsInTheRow[]);
	
	//static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

