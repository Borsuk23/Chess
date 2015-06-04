#pragma once
#include "pch.h"

/*!
* \brief The Click struct struktura definiuj¹ca klikniêcie na planszy
*/
struct Click
{
	int row;	//! wiersz
	int column;	//! kolumna
	int player;	//! gracz, który klikn¹³
	int promotionPiece;		//! figura wybrana do promocji
	/*!
	* \brief Click konstruktor sparametryzowany
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param promotionPiece figura wybrana do promocji
	*/
	Click(int row, int column, int player, int promotionPiece);
	/*!
	* \brief Click destruktor
	*/
	~Click();
};