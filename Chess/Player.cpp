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
	pieces = std::vector<Piece*>(16); //polimorfizm z figurami
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
	capturedPieces = std::vector<Piece*>(16);
}


Player::~Player()
{
}


void Player::capturePiece(Piece* piece)
{
}


void Player::checkPiece(Piece* piece)
{
}

std::vector < Piece* > Player::getPieces()
{
	//zwraca figury zeby moc z nich skorzystac np w innej funkcji
	return this->pieces;
};