#pragma once
#include "Piece.h"

/*!
* \brief The King class klasa podrzedna definiujaca krola
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
	/*!
	* \brief pieceMoved metoda zliczajaca ile razy figura ruszyla sie
	*/
	virtual void pieceMoved();
	
};

