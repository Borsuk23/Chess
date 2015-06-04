#pragma once
#include "Piece.h"

/*!
* \brief The Bishop class klasa podrz�dna definiuj�ca go�ca
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
	* \brief getPossibleMovements metoda pobieraj�ca mo�liwe ruchy danej figury
	* \return zwraca wektor mo�liwych translacji ruch�w
	*/
	virtual std::vector<std::vector<Translation*>> getPossibleMovements();
	/*!
	* \brief getName metoda pobieraj�ca nazw� figury na potrzeby GUI
	* \return zwraca nazw� figury
	*/
	virtual Platform::String^ getName();
	/*!
	* \brief getStringName metoda pobieraj�ca nazw� figury
	* \return zwraca nazw� figury
	*/
	virtual std::string getStringName();

};

