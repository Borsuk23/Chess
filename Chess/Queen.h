#pragma once
#include "Piece.h"

/*!
* \brief The Queen class klasa podrz�dna definiuj�ca kr�low�
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

