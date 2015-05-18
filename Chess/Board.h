#pragma once

#include "Field.h"
#include "Player.h"
#include "Piece.h"


class Board
{
public:
	Board(Player* playerWhite, Player* playerBlack);
	virtual ~Board();
	
	typedef enum Exit { NO_CHANGES, PIECE_SELECTED, PIECE_UNSELECTED, PIECE_MOVED, PIECE_CAPTURED };	//polecam typy z duzej litery zeby nie mylily sie ze zmiennymi i atrybutami
	typedef enum GameState { OK, CHECK };	// bez drugiego gamestate
	GameState gameState;	//zapisane jako atrybut
	GameState checkGameState(Player* player);
	bool checkCheckmateState(Player* player);
	Exit userAction(int x, int y, Player* player);
	std::vector<std::vector<Field*>> getFields();
private:
	Piece* pieceSelected;
	Field* fieldSelected; //obecnie klikniete pole
	std::vector<std::vector<Field*>> fields;	
	Field* checkField(int x, int y);
	void clearSelection();
	bool stateCheckmate;
	Field* shortCastlingField;
	Field* longCastlingField;
	Piece* castlingPiece;
	Field* middleEnPassantField;
	Field* highlightedMiddleEnPassantField;
	Field* endEnPassantField; //en paasant
	Field* highlightedEndEnPassantField;
	void calculatePossibleMovements(int x, int y, Player* player);
	bool calculateCheckmateMovements(int row, int column, Player* player, Piece* pieceToCheck);
	GameState calculateCheck(int row, int column, Player* player, Piece* pieceToCheck);
	
	
};

