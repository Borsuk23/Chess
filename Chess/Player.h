#pragma once
#include "Piece.h"
#include  <string>

/*!
* \brief Player class klasa definiuj¹ca gracza
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
	* \return zwraca kolor 0 to bia³y, 1 czarny
	*/
	int getColor();
	/*!
	* \brief capturePiece metoda zbijaj¹ca figure
	* \param piece zbijana figura
	*/
	void capturePiece(Piece* piece);
	/*!
	* \brief checkPiece metoda sprawdzaj¹ca czy jest to figura danego gracza
	* \param piece figura do sprawdzenia
	*/
	bool checkPiece(Piece* piece);
	/*!
	* \brief removeCapturedPiece metoda usuwaj¹ca zbita figurê z wektora figur gracza
	* \param piece zbita figura
	*/
	void removeCapturedPiece(Piece* piece);
	/*!
	* \brief getLastCapturedPiece metoda zwracaj¹ca ostatni¹ zbita figurê przeciwnika w celu usuniêcia jej póŸniej z wektora figur gracza
	* \return zwraca ostatni¹ zbit¹ figurê
	*/
	Piece* getLastCapturedPiece();
	/*!
	* \brief getPieces metoda zwracaj¹ca figury gracza
	* \return zwraca figury gracza
	*/
	std::vector < Piece* > getPieces();
	/*!
	* \brief getNickname metoda zwracaj¹ca nick gracza
	* \return nick gracza
	*/
	std::string getNickname();
	/*!
	* \brief setNickname metoda ustawiaj¹ca nick gracza
	* \param nickname nick gracza
	*/
	void setNickname(std::string nickname);
	/*!
	* \brief getCapturedPieces metoda zwracaj¹ca zbite figury
	* \return zwraca wektor zbitych figur
	*/ 
	std::vector < Piece* > getCapturedPieces();
private:
	std::string nickName;	//! nick gracza
	int color;			//! kolor gracza
	int numberOfCapturedPieces;		//! iloœæ zbitych figur
	
};

