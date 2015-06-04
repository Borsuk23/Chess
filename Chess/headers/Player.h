#pragma once
#include "Piece.h"
#include  <string>

/*!
* \brief Player class klasa definiujaca gracza
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
	* \return zwraca kolor 0 to bialy, 1 czarny
	*/
	int getColor();
	/*!
	* \brief capturePiece metoda zbijajaca figure
	* \param piece zbijana figura
	*/
	void capturePiece(Piece* piece);
	/*!
	* \brief checkPiece metoda sprawdzajaca czy jest to figura danego gracza
	* \param piece figura do sprawdzenia
	*/
	bool checkPiece(Piece* piece);
	/*!
	* \brief removeCapturedPiece metoda usuwajaca zbita figure z wektora figur gracza
	* \param piece zbita figura
	*/
	void removeCapturedPiece(Piece* piece);
	/*!
	* \brief getLastCapturedPiece metoda zwracajaca ostatnia zbita figure przeciwnika w celu usuniecia jej poŸniej z wektora figur gracza
	* \return zwraca ostatnia zbita figure
	*/
	Piece* getLastCapturedPiece();
	/*!
	* \brief getPieces metoda zwracajaca figury gracza
	* \return zwraca figury gracza
	*/
	std::vector < Piece* > getPieces();
	/*!
	* \brief getNickname metoda zwracajaca nick gracza
	* \return nick gracza
	*/
	std::string getNickname();
	/*!
	* \brief setNickname metoda ustawiajaca nick gracza
	* \param nickname nick gracza
	*/
	void setNickname(std::string nickname);
	/*!
	* \brief getCapturedPieces metoda zwracajaca zbite figury
	* \return zwraca wektor zbitych figur
	*/ 
	std::vector < Piece* > getCapturedPieces();
private:
	std::string nickName;	//! nick gracza
	int color;			//! kolor gracza
	int numberOfCapturedPieces;		//! iloœæ zbitych figur
	
};

