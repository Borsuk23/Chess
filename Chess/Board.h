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
* \brief The Board class klasa definiujaca plansze
*/
class Board
{
public:
	typedef enum Exit { NO_CHANGES, PIECE_SELECTED, PIECE_UNSELECTED, PIECE_MOVED, PIECE_CAPTURED };	//! definicja mozliwych akcji po kliknieciu
	typedef enum GameState { OK, CHECK };	//! definifcja mozliwych stanow gry	
	GameState gameState;	//!stan gry
	/*!
	* \brief Board konstruktor sparametryzowany
	* \param playerWhite bialy gracz
	* \param playerBlack czarny gracz
	*/
	Board(Player* playerWhite, Player* playerBlack);
	/*!
	* \brief Board destruktor
	*/
	virtual ~Board();
	/*!
	* \brief checkGameState metoda sprawdzajaca stan gry (czy jest szach)
	* \param player gracz, ktory do sprawdzenia (czy jest szachowany)
	* \return stan gry
	*/
	GameState checkGameState(Player* player);
	/*!
	* \brief checkCheckmateState metoda sprawdzajaca czy jest koniec gry
	* \return zwraca czy jest mat/pat
	*/
	bool checkCheckmateState(Player* player);
	/*!
	* \brief userAction metoda wykonujaca konkretne akcji po kliknieciu przez gracza
	* \param row wiersz
	* \param column kolumna
	* \param player gracz wykonujacy klikniecie
	* \return zwraca wykonana akcje
	*/
	Exit userAction(int x, int y, Player* player);
	/*!
	* \brief getFields metoda pobierajaca pola na planszy
	* \return zwraca pola planszy
	*/
	std::vector<std::vector<Field*>> getFields();
	/*!
	* \brief checkPromotion metoda sprawdzajaca czy jest mozliwa promocja
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \return zwraca czy jest mozliwa promocja pionka
	*/
	bool checkPromotion(int row, int column, Player* player);
	/*!
	* \brief promotePawn metoda promujaca pionka
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param color kolor gracza
	* \param movedPawn pionek do wypromowania
	* \param promotionPiece figura na jaka ma zostaæ wypromowany pionek
	* \return zwraca wypromowana figure
	*/
	Piece* promotePawn(int row, int column, Player* player, int color, Piece* movedPawn, int promotionPiece);

private:
	Piece* pieceSelected;	//! zaznaczona figura
	Field* fieldSelected;	//! zaznaczone pole
	std::vector<std::vector<Field*>> fields;	//! pola
	bool stateCheckmate;	//! stan gry okreœlajacy czy jest mat
	Field* shortCastlingField;	//! pole na jakie ma zostaæ postawiony krol przy krotkiej roszadzie
	Field* longCastlingField;	//! pole na jakie ma zostaæ postawiony krol przy dlugiej roszadzie
	Piece* castlingPiece;		//! figura - wieza - uczestniczaca w roszadzie
	Field* middleEnPassantField;	//! pierwsze pole przy pierwszym ruchu pionka do bicia w przelocie
	Field* highlightedMiddleEnPassantField;		//! podœwietlone pierwsze pole przy pierwszym ruchu pionka do bicia w przelocie
	Field* endEnPassantField;		//! drugie pole przy pierwszym ruchu pionka do bicia w przelocie
	Field* highlightedEndEnPassantField;		//! podœwietlone drugie pole przy pierwszym ruchu pionka do bicia w przelocie
	/*!
	* \brief checkField metoda sprawdzajaca czy pole jest puste
	* \param row wiersz
	* \param column kolumna
	* \return zwraca puste pole
	*/
	Field* checkField(int row, int column);
	/*!
	* \brief clearSelection metoda usuwajaca zaznaczenie pola
	*/
	void clearSelection();
	/*!
	* \brief calculatePossibleMovements metoda liczaca wyœwietlajaca mozliwe ruchy na planszy
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	*/
	void calculatePossibleMovements(int row, int column, Player* player);
	/*!
	* \brief calculateCheckmateMovements metoda sprawdzajaca czy sa mozliwe ruchy do wykonania, sprawdza czy jest mat
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param pieceToCheck figura do sprawdzenia czy ma jeszcze mozliwe ruchy
	* \return zwraca czy sa mozliwe ruchy
	*/
	bool calculateCheckmateMovements(int row, int column, Player* player, Piece* pieceToCheck);
	/*!
	* \brief calculatePossibleMovements metoda liczaca wyœwietlajaca mozliwe ruchy na planszy
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param pieceToCheck figura do sprawdzenia czy jej ruch nie spowoduje szacha
	* \return zwraca czy przy danym ruchu nie bedzie szach
	*/
	GameState calculateCheck(int row, int column, Player* player, Piece* pieceToCheck);
	
	
};

