#pragma once
#include "Piece.h"

/*!
* \brief The Queen class klasa podrzêdna definiuj¹ca królow¹
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
	* \brief getPossibleMovements metoda pobieraj¹ca mo¿liwe ruchy danej figury
	* \return zwraca wektor mo¿liwych translacji ruchów
	*/
	virtual std::vector<std::vector<Translation*>> getPossibleMovements();
	/*!
	* \brief getName metoda pobieraj¹ca nazwê figury na potrzeby GUI
	* \return zwraca nazwê figury
	*/
	virtual Platform::String^ getName();
	/*!
	* \brief getStringName metoda pobieraj¹ca nazwê figury
	* \return zwraca nazwê figury
	*/
	virtual std::string getStringName();
	
};

