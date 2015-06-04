#pragma once
#include "Piece.h"

/*!
* \brief The King class klasa podrz�dna definiuj�ca go�ca
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
	/*!
	* \brief pieceMoved metoda zliczaj�ca ile razy figura ruszy�a si�
	*/
	virtual void pieceMoved();
	
};

