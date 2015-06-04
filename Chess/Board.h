#pragma once

#include "Field.h"
#include "Player.h"
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"


/*!
* \brief The Board class klasa definiuj�ca plansz�
*/
class Board
{
public:
	typedef enum Exit { NO_CHANGES, PIECE_SELECTED, PIECE_UNSELECTED, PIECE_MOVED, PIECE_CAPTURED };	//! definicja mo�liwych akcji po klikni�ciu
	typedef enum GameState { OK, CHECK };	//! definifcja mo�liwych stan�w gry	
	GameState gameState;	//!stan gry
	/*!
	* \brief Board konstruktor sparametryzowany
	* \param playerWhite bia�y gracz
	* \param playerBlack czarny gracz
	*/
	Board(Player* playerWhite, Player* playerBlack);
	/*!
	* \brief Board destruktor
	*/
	virtual ~Board();
	/*!
	* \brief checkGameState metoda sprawdzaj�ca stan gry (czy jest szach)
	* \param player gracz, kt�ry do sprawdzenia (czy jest szachowany)
	* \return stan gry
	*/
	GameState checkGameState(Player* player);
	/*!
	* \brief checkCheckmateState metoda sprawdzaj�ca czy jest koniec gry
	* \return zwraca czy jest mat/pat
	*/
	bool checkCheckmateState(Player* player);
	/*!
	* \brief userAction metoda wykonuj�ca konkretne akcji po klikni�ciu przez gracza
	* \param row wiersz
	* \param column kolumna
	* \param player gracz wykonuj�cy klikni�cie
	* \return zwraca wykonana akcj�
	*/
	Exit userAction(int x, int y, Player* player);
	/*!
	* \brief getFields metoda pobieraj�ca pola na planszy
	* \return zwraca pola planszy
	*/
	std::vector<std::vector<Field*>> getFields();
	/*!
	* \brief checkPromotion metoda sprawdzaj�ca czy jest mo�liwa promocja
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \return zwraca czy jest mo�liwa promocja pionka
	*/
	bool checkPromotion(int row, int column, Player* player);
	/*!
	* \brief promotePawn metoda promuj�ca pionka
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param color kolor gracza
	* \param movedPawn pionek do wypromowania
	* \param promotionPiece figura na jak� ma zosta� wypromowany pionek
	* \return zwraca wypromowan� figur�
	*/
	Piece* promotePawn(int row, int column, Player* player, int color, Piece* movedPawn, int promotionPiece);

private:
	Piece* pieceSelected;	//! zaznaczona figura
	Field* fieldSelected;	//! zaznaczone pole
	std::vector<std::vector<Field*>> fields;	//! pola
	bool stateCheckmate;	//! stan gry okre�laj�cy czy jest mat
	Field* shortCastlingField;	//! pole na jakie ma zosta� postawiony kr�l przy kr�tkiej roszadzie
	Field* longCastlingField;	//! pole na jakie ma zosta� postawiony kr�l przy d�ugiej roszadzie
	Piece* castlingPiece;		//! figura - wie�a - uczestnicz�ca w roszadzie
	Field* middleEnPassantField;	//! pierwsze pole przy pierwszym ruchu pionka do bicia w przelocie
	Field* highlightedMiddleEnPassantField;		//! pod�wietlone pierwsze pole przy pierwszym ruchu pionka do bicia w przelocie
	Field* endEnPassantField;		//! drugie pole przy pierwszym ruchu pionka do bicia w przelocie
	Field* highlightedEndEnPassantField;		//! pod�wietlone drugie pole przy pierwszym ruchu pionka do bicia w przelocie
	/*!
	* \brief checkField metoda sprawdzaj�ca czy pole jest puste
	* \param row wiersz
	* \param column kolumna
	* \return zwraca puste pole
	*/
	Field* checkField(int row, int column);
	/*!
	* \brief clearSelection metoda usuwaj�ca zaznaczenie pola
	*/
	void clearSelection();
	/*!
	* \brief calculatePossibleMovements metoda licz�ca wy�wietlaj�ca mo�liwe ruchy na planszy
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	*/
	void calculatePossibleMovements(int x, int y, Player* player);
	/*!
	* \brief calculateCheckmateMovements metoda sprawdzaj�ca czy s� mo�liwe ruchy do wykonania, sprawdza czy jest mat
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param pieceToCheck figura do sprawdzenia czy ma jeszcze mo�liwe ruchy
	* \return zwraca czy s� mo�liwe ruchy
	*/
	bool calculateCheckmateMovements(int row, int column, Player* player, Piece* pieceToCheck);
	/*!
	* \brief calculatePossibleMovements metoda licz�ca wy�wietlaj�ca mo�liwe ruchy na planszy
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param pieceToCheck figura do sprawdzenia czy jej ruch nie spowoduje szacha
	* \return zwraca czy przy danym ruchu nie bedzie szach
	*/
	GameState calculateCheck(int row, int column, Player* player, Piece* pieceToCheck);
	
	
};

