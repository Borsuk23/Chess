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
	int numberOfCapturedPieces;
public:
	std::vector < Piece* > capturedPieces;
	std::vector < Piece* > pieces;
	int getColor();
	void capturePiece(Piece* piece);
	bool checkPiece(Piece* piece);
	void Player::removeCapturedPiece(Piece* piece);
	Piece* Player::getLastCapturedPiece();
	std::vector < Piece* > getPieces();
	std::string getNickname();
	void setNickname(std::string nickname);
	std::vector < Piece* > getCapturedPieces();
};

