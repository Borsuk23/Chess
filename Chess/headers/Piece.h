#pragma once
#include "Translation.h"
#include "sstream"

/*!
* \brief The Piece class klasa nadrzedna definiujaca figury
*/
class Piece
{
public:
	int _id;	//! id figury
	int color;	//! kolor
	int numberOfMoves;	//! iloœæ ruchow
	/*!
	* \brief Piece konstruktor sparametryzowany
	* \param color kolor figury
	*/
	Piece(int color);
	/*!
	* \brief Piece destruktor
	*/
	virtual ~Piece();
	/*!
	* \brief getPossibleMovements metoda pobierajaca mozliwe ruchy danej figury
	* \return zwraca wektor mozliwych translacji ruchow
	*/
	virtual std::vector<std::vector<Translation*>> getPossibleMovements() = 0;
	/*!
	* \brief getName metoda pobierajaca nazwe figury na potrzeby GUI
	* \return zwraca nazwe figury
	*/
	virtual Platform::String^ getName() = 0;
	/*!
	* \brief getName metoda pobierajaca nazwe figury na potrzeby GUI
	* \return zwraca nazwe figury
	*/
	virtual std::string getStringName() = 0;
	/*!
	* \brief pieceMoved metoda zliczajaca ile razy figura ruszyla sie
	*/
	virtual void pieceMoved();
	
protected:
	std::vector<std::vector<Translation*>> possibleMovements;	//! mozliwe ruchy
};

