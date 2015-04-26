#pragma once
#include "Player.h"
class Game
{
public:
	Game();
	virtual ~Game();
	void userAction(int x, int y);
private:
	void changeTurn();
	void removeCapturedPieces();
	bool isFinished;
	Player* currentPlayer;
};

