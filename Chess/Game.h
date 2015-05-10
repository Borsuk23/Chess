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
	Board::GameState gameState;
	//typedef enum gameState { OK, CHECK, CHECKMATE } gameState;
private:
	void changeTurn();
	void removeCapturedPieces();
	bool isFinished;
	Player* currentPlayer;
	std::vector<Player*> players;
	Board* board;
};

