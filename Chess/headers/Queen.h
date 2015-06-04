#pragma once
#include "Piece.h"

/*!
* \brief The Queen class klasa podrzedna definiujaca krolowa
*/
class Queen :
public Piece
{
public:
	/*!
	* \brief Queen konstruktor sparametryzowany
	* \param color kolor figury
	*/
	Queen(int color);
	/*!
	* \brief Queen destruktor
	*/
	virtual ~Queen();
	/*!
	* \brief getPossibleMovements metoda pobierajaca mozliwe ruchy danej figury
	* \return zwraca wektor mozliwych translacji ruchow
	*/
	virtual std::vector<std::vector<Translation*>> getPossibleMovements();
	/*!
	* \brief getName metoda pobierajaca nazwe figury na potrzeby GUI
	* \return zwraca nazwe figury
	*/
	virtual Platform::String^ getName();
	/*!
	* \brief getStringName metoda pobierajaca nazwe figury
	* \return zwraca nazwe figury
	*/
	virtual std::string getStringName();
	
};

