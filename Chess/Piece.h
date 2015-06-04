#pragma once
#include "Translation.h"
#include "sstream"

/*!
* \brief The Piece class klasa nadrz�dna definiuj�ca figury
*/
class Piece
{
public:
	int _id;	//! id figury
	int color;	//! kolor
	int numberOfMoves;	//! ilo�� ruch�w
	/*!
	* \brief Piece konstruktor sparametryzowany
	* \param color kolor figury
	*/
	Piece(int color);
	/*!
	* \brief Piece destruktor
	*/
	virtual ~Piece();
	/*!
	* \brief getPossibleMovements metoda pobieraj�ca mo�liwe ruchy danej figury
	* \return zwraca wektor mo�liwych translacji ruch�w
	*/
	virtual std::vector<std::vector<Translation*>> getPossibleMovements() = 0;
	/*!
	* \brief getName metoda pobieraj�ca nazw� figury na potrzeby GUI
	* \return zwraca nazw� figury
	*/
	virtual Platform::String^ getName() = 0;
	/*!
	* \brief getName metoda pobieraj�ca nazw� figury na potrzeby GUI
	* \return zwraca nazw� figury
	*/
	virtual std::string getStringName() = 0;
	/*!
	* \brief pieceMoved metoda zliczaj�ca ile razy figura ruszy�a si�
	*/
	virtual void pieceMoved();
	
protected:
	std::vector<std::vector<Translation*>> possibleMovements;	//! mo�liwe ruchy
};

