#pragma once
#include "Piece.h"
#include  <string>

class Player
{
public:
	Player(int color, std::string nickName);
	virtual ~Player();
private:
	std::string nickName;
	int color;
	std::vector < Piece* > pieces;
	std::vector < Piece* > capturedPieces;
public:
	void capturePiece(Piece* piece);
	void checkPiece(Piece* piece);
	std::vector < Piece* > getPieces();
};

