#pragma once
#include "Piece.h"
#include "FieldViewModel.h"

using namespace Chess;

/*!
* \brief Field class klasa definiujaca pola na planszy
*/
class Field
{
private:
	Piece* pieceOnField;		//! figura stojaca na danym polu
	bool highlighted;		//! pod�wietlenie pola
	int color;			//! kolor pola
	//0 bialy, 1 czarny

public:
	/*!
	* \brief Field konstruktor sparametryzowany
	* \param color kolor pola
	*/
	Field(int color);
	/*!
	* \brief Field destruktor
	*/
	virtual ~Field();
	/*!
	* \brief placePiece metoda ustawiajaca figure na polu
	* \param piece figura do ustawienia
	*/
	void placePiece(Piece* piece);
	/*!
	* \brief removeFromSelectedField metoda usuwajaca figure z pola
	*/
	void removeFromSelectedField();
	/*!
	* \brief isHighlighted metoda sprawdzajaca czy pole jest pod�wietlone
	* \return zwraca czy pole jest po�wietlone
	*/
	bool isHighlighted();
	/*!
	* \brief checkField sprawdza co stoi na polu
	* \return zwraca figure stojaca na danym polu
	*/
	Piece* checkField();
	/*!
	* \brief setHighlighted pod�wietla pole lub gasi pole
	* \param value parametr mowiacy czy zapalic (true) czy zgasi� (false)
	*/
	void setHighlighted(bool value);
	
};

