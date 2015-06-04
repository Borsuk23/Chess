#pragma once
#include "pch.h"

/*!
* \brief The Click struct struktura definiuj�ca klikni�cie na planszy
*/
struct Click
{
	int row;	//! wiersz
	int column;	//! kolumna
	int player;	//! gracz, kt�ry klikn��
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