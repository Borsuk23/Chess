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
	this->numberOfCapturedPieces = 0;
	capturedPieces = std::vector<Piece*>(16);
}


Player::~Player()
{
}


void Player::capturePiece(Piece* piece)
{
	capturedPieces[numberOfCapturedPieces] = piece; //dodaje zbita figure na koniec wektora capturedPieces
	numberOfCapturedPieces++;
}

void Player::removeCapturedPiece(Piece* piece)
{
	std::vector<Piece*>::iterator it;
	//szuka czy figura znajduje sie w wektorze figur gracza
	it = std::find(pieces.begin(), pieces.end(), piece);
	//jesli tak to ja usuwa
	if (it != pieces.end())
		pieces.erase(it);
}

Piece* Player::getLastCapturedPiece()
{
	std::vector<Piece*>::reverse_iterator it;
	//szuka czy figura znajduje sie w wektorze figur gracza
	it = capturedPieces.rbegin();
	return *it; //wskaznik na iterator - na Piece
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
	//szuka czy figura znajduje sie w wektorze figur gracza
	it = std::find(pieces.begin(), pieces.end(), piece);
	if (it == pieces.end())
		return false;
	return true;
}

std::vector < Piece* > Player::getPieces()
{
	//zwraca figury zeby moc z nich skorzystac np w innej funkcji
	return this->pieces;
};

std::vector < Piece* > Player::getCapturedPieces()
{
	return this->capturedPieces;
}