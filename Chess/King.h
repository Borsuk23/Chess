#pragma once
#include "Piece.h"

/*!
* \brief The King class klasa podrzêdna definiuj¹ca goñca
*/
class King :
public Piece
{
public:
	/*!
	* \brief King konstruktor sparametryzowany
	* \param color kolor figury
	*/
	King(int color);
	/*!
	* \brief King destruktor
	*/
	virtual ~King();
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
	/*!
	* \brief pieceMoved metoda zliczaj¹ca ile razy figura ruszy³a siê
	*/
	virtual void pieceMoved();
	
};

