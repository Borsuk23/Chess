#pragma once
#include "Piece.h"
#include "FieldViewModel.h"

using namespace Chess;

/*!
* \brief Field class klasa definiuj¹ca pola na planszy
*/
class Field
{
private:
	Piece* pieceOnField;		//! figura stoj¹ca na danym polu
	bool highlighted;		//! podœwietlenie pola
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
	* \brief placePiece metoda ustawiaj¹ca figure na polu
	* \param piece figura do ustawienia
	*/
	void placePiece(Piece* piece);
	/*!
	* \brief removeFromSelectedField metoda usuwaj¹ca figure z pola
	*/
	void removeFromSelectedField();
	/*!
	* \brief isHighlighted metoda sprawdzaj¹ca czy pole jest podœwietlone
	* \return zwraca czy pole jest poœwietlone
	*/
	bool isHighlighted();
	/*!
	* \brief checkField sprawdza co stoi na polu
	* \return zwraca figurê stoj¹ca na danym polu
	*/
	Piece* checkField();
	/*!
	* \brief setHighlighted podœwietla pole lub gasi pole
	* \param value parametr mowi¹cy czy zapalic (true) czy zgasiæ (false)
	*/
	void setHighlighted(bool value);
	
};

