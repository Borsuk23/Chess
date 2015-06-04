#pragma once
#include "Piece.h"
#include  <string>

/*!
* \brief Player class klasa definiuj�ca gracza
*/
class Player
{
public:
	/*!
	* \brief Player konstruktor sparametryzowany
	* \param color kolor gracza
	* \param nickName nick gracza
	*/
	Player(int color, std::string nickName);
	/*!
	* \brief Player destruktor
	*/
	virtual ~Player();
	std::vector < Piece* > capturedPieces;		//! zbite figury przeciwnika
	std::vector < Piece* > pieces;			//! figury gracza
	/*!
	* \brief getColor metoda pozwalajaca sprawdzenie koloru danego gracza
	* \return zwraca kolor 0 to bia�y, 1 czarny
	*/
	int getColor();
	/*!
	* \brief capturePiece metoda zbijaj�ca figure
	* \param piece zbijana figura
	*/
	void capturePiece(Piece* piece);
	/*!
	* \brief checkPiece metoda sprawdzaj�ca czy jest to figura danego gracza
	* \param piece figura do sprawdzenia
	*/
	bool checkPiece(Piece* piece);
	/*!
	* \brief removeCapturedPiece metoda usuwaj�ca zbita figur� z wektora figur gracza
	* \param piece zbita figura
	*/
	void removeCapturedPiece(Piece* piece);
	/*!
	* \brief getLastCapturedPiece metoda zwracaj�ca ostatni� zbita figur� przeciwnika w celu usuni�cia jej p�niej z wektora figur gracza
	* \return zwraca ostatni� zbit� figur�
	*/
	Piece* getLastCapturedPiece();
	/*!
	* \brief getPieces metoda zwracaj�ca figury gracza
	* \return zwraca figury gracza
	*/
	std::vector < Piece* > getPieces();
	/*!
	* \brief getNickname metoda zwracaj�ca nick gracza
	* \return nick gracza
	*/
	std::string getNickname();
	/*!
	* \brief setNickname metoda ustawiaj�ca nick gracza
	* \param nickname nick gracza
	*/
	void setNickname(std::string nickname);
	/*!
	* \brief getCapturedPieces metoda zwracaj�ca zbite figury
	* \return zwraca wektor zbitych figur
	*/ 
	std::vector < Piece* > getCapturedPieces();
private:
	std::string nickName;	//! nick gracza
	int color;			//! kolor gracza
	int numberOfCapturedPieces;		//! ilo�� zbitych figur
	
};

