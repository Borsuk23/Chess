#pragma once
#include "Player.h"
#include "Board.h"

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
	//typedef enum gameState { OK, CHECK, CHECKMATE } gameState;
private:
	void changeTurn();
	void removeCapturedPieces();
	
	Player* currentPlayer;
	std::vector<Player*> players;
	Board* board;
};

