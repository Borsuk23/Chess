#pragma once
#include "Player.h"
#include "Board.h"
class Game
{
public:
	Game(std::string whitePlayerNickName, std::string blackPlayerNickName); 
	virtual ~Game();
	void userAction(int x, int y);
private:
	void changeTurn();
	void removeCapturedPieces();
	bool isFinished;
	Player* currentPlayer;
	std::vector<Player*> players;
	int turnNumber;
	Board* board;
	
};

