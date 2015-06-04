#pragma once
#include "Piece.h"

/*!
* \brief The Knight class klasa podrzedna definiujaca konia
*/
class Knight :
public Piece
{
public:
	/*!
	* \brief Knight konstruktor sparametryzowany
	* \param color kolor figury
	*/
	Knight(int color);
	/*!
	* \brief Knight destruktor
	*/
	virtual ~Knight();
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

