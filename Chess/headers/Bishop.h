#pragma once
#include "Piece.h"

/*!
* \brief The Bishop class klasa podrzedna definiujaca gonca
*/
class Bishop :
public Piece
{
public:
	/*!
	* \brief Bishop konstruktor sparametryzowany
	* \param color kolor figury
	*/
	Bishop(int color);
	/*!
	* \brief Bishop destruktor
	*/
	virtual ~Bishop();
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

