#pragma once
#include "Piece.h"

/*!
* \brief The Rook class klasa podrz�dna definiuj�ca wie��
*/
class Rook :
public Piece
{
public:
	/*!
	* \brief Rook konstruktor sparametryzowany
	* \param color kolor figury
	*/
	Rook(int color);
	/*!
	* \brief Rook destruktor
	*/
	virtual ~Rook();
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

