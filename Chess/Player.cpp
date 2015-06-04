#include "pch.h"
#include "Player.h"
#include  "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"


Player::Player(int color, std::string nickName)
{
	this->color = color;
	this->nickName = nickName;
	pieces = std::vector<Piece*>(16); 
	pieces = { 
		new Rook(color), 
		new Knight(color), 
		new Bishop(color), 
		new Queen(color), 
		new King(color), 
		new Bishop(color), 
		new Knight(color), 
		new Rook(color), 
		new Pawn(color),
		new Pawn(color), 
		new Pawn(color), 
		new Pawn(color), 
		new Pawn(color), 
		new Pawn(color), 
		new Pawn(color), 
		new Pawn(color)
	};
	this->numberOfCapturedPieces = 0;
	capturedPieces = std::vector<Piece*>(16);
}


Player::~Player()
{
}


void Player::capturePiece(Piece* piece)
{
	capturedPieces[numberOfCapturedPieces] = piece; //add captured Piece to capturedPieces vector
	numberOfCapturedPieces++;
}

void Player::removeCapturedPiece(Piece* piece)
{
	std::vector<Piece*>::iterator it;
	//find piece in players  piece vector
	it = std::find(pieces.begin(), pieces.end(), piece);
	//erase if found
	if (it != pieces.end())
		pieces.erase(it);
}

Piece* Player::getLastCapturedPiece()
{
	std::vector<Piece*>::reverse_iterator it;
	//find piece in players pieces vector
	it = capturedPieces.rbegin();
	return *it; //pointer to iterator,  Piece
}


bool Player::checkPiece(Piece* piece)
{
	
	std::vector<Piece*>::iterator it;
	//it = pieces.begin();
	//for (it; it < pieces.end(); it++)
	//{
	//	if ((*it)->_id == piece->_id)
	//		return true;
	//}
	//return false;
	//find piece in players pieces vector
	it = std::find(pieces.begin(), pieces.end(), piece);
	if (it == pieces.end())
		return false;
	return true;
}

std::vector < Piece* > Player::getPieces()
{
	return this->pieces;
};

std::vector < Piece* > Player::getCapturedPieces()
{
	return this->capturedPieces;
}

int Player::getColor()
{
	return this->color;
	
}

std::string Player::getNickname()
{
	return this->nickName;
}

void Player::setNickname(std::string nickname)
{
	this->nickName = nickname;
}