#pragma once
#include "Piece.h"
#include "FieldViewModel.h"

using namespace Chess;

/*!
* \brief Field class klasa definiuj�ca pola na planszy
*/
class Field
{
private:
	Piece* pieceOnField;		//! figura stoj�ca na danym polu
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
	* \brief placePiece metoda ustawiaj�ca figure na polu
	* \param piece figura do ustawienia
	*/
	void placePiece(Piece* piece);
	/*!
	* \brief removeFromSelectedField metoda usuwaj�ca figure z pola
	*/
	void removeFromSelectedField();
	/*!
	* \brief isHighlighted metoda sprawdzaj�ca czy pole jest pod�wietlone
	* \return zwraca czy pole jest po�wietlone
	*/
	bool isHighlighted();
	/*!
	* \brief checkField sprawdza co stoi na polu
	* \return zwraca figur� stoj�ca na danym polu
	*/
	Piece* checkField();
	/*!
	* \brief setHighlighted pod�wietla pole lub gasi pole
	* \param value parametr mowi�cy czy zapalic (true) czy zgasi� (false)
	*/
	void setHighlighted(bool value);
	
};

