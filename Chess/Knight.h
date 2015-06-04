#pragma once
#include "Piece.h"

/*!
* \brief The Knight class klasa podrzêdna definiuj¹ca konia
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

