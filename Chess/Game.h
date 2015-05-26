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
	std::vector<std::vector<Piece*>> getCapturedPieces();
	std::vector<Player*> players;
	bool promotionFlag;
	void promotion(int promotionPiece);
	//typedef enum gameState { OK, CHECK, CHECKMATE } gameState;
private:
	void changeTurn();
	void removeCapturedPieces();
	int promotionRow;
	int promotionColumn;
	Player* currentPlayer;
	Board* board;
};

