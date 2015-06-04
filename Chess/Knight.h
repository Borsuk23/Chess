#pragma once
#include "Piece.h"

/*!
* \brief The Knight class klasa podrz�dna definiuj�ca konia
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

