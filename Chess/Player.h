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
	int numberOfCapturedPieces;
public:
	std::vector < Piece* > capturedPieces;
	void capturePiece(Piece* piece);
	bool checkPiece(Piece* piece);
	void Player::removeCapturedPiece(Piece* piece);
	Piece* Player::getLastCapturedPiece();
	std::vector < Piece* > getPieces();
	std::vector < Piece* > getCapturedPieces();
};

