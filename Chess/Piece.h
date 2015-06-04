#pragma once
#include "Translation.h"
#include "sstream"

/*!
* \brief The Piece class klasa nadrzêdna definiuj¹ca figury
*/
class Piece
{
public:
	int _id;	//! id figury
	int color;	//! kolor
	int numberOfMoves;	//! iloœæ ruchów
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
	* \brief getPossibleMovements metoda pobieraj¹ca mo¿liwe ruchy danej figury
	* \return zwraca wektor mo¿liwych translacji ruchów
	*/
	virtual std::vector<std::vector<Translation*>> getPossibleMovements() = 0;
	/*!
	* \brief getName metoda pobieraj¹ca nazwê figury na potrzeby GUI
	* \return zwraca nazwê figury
	*/
	virtual Platform::String^ getName() = 0;
	/*!
	* \brief getName metoda pobieraj¹ca nazwê figury na potrzeby GUI
	* \return zwraca nazwê figury
	*/
	virtual std::string getStringName() = 0;
	/*!
	* \brief pieceMoved metoda zliczaj¹ca ile razy figura ruszy³a siê
	*/
	virtual void pieceMoved();
	
protected:
	std::vector<std::vector<Translation*>> possibleMovements;	//! mo¿liwe ruchy
};

