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
* \brief The Board class klasa definiuj¹ca planszê
*/
class Board
{
public:
	typedef enum Exit { NO_CHANGES, PIECE_SELECTED, PIECE_UNSELECTED, PIECE_MOVED, PIECE_CAPTURED };	//! definicja mo¿liwych akcji po klikniêciu
	typedef enum GameState { OK, CHECK };	//! definifcja mo¿liwych stanów gry	
	GameState gameState;	//!stan gry
	/*!
	* \brief Board konstruktor sparametryzowany
	* \param playerWhite bia³y gracz
	* \param playerBlack czarny gracz
	*/
	Board(Player* playerWhite, Player* playerBlack);
	/*!
	* \brief Board destruktor
	*/
	virtual ~Board();
	/*!
	* \brief checkGameState metoda sprawdzaj¹ca stan gry (czy jest szach)
	* \param player gracz, który do sprawdzenia (czy jest szachowany)
	* \return stan gry
	*/
	GameState checkGameState(Player* player);
	/*!
	* \brief checkCheckmateState metoda sprawdzaj¹ca czy jest koniec gry
	* \return zwraca czy jest mat/pat
	*/
	bool checkCheckmateState(Player* player);
	/*!
	* \brief userAction metoda wykonuj¹ca konkretne akcji po klikniêciu przez gracza
	* \param row wiersz
	* \param column kolumna
	* \param player gracz wykonuj¹cy klikniêcie
	* \return zwraca wykonana akcjê
	*/
	Exit userAction(int x, int y, Player* player);
	/*!
	* \brief getFields metoda pobieraj¹ca pola na planszy
	* \return zwraca pola planszy
	*/
	std::vector<std::vector<Field*>> getFields();
	/*!
	* \brief checkPromotion metoda sprawdzaj¹ca czy jest mo¿liwa promocja
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \return zwraca czy jest mo¿liwa promocja pionka
	*/
	bool checkPromotion(int row, int column, Player* player);
	/*!
	* \brief promotePawn metoda promuj¹ca pionka
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param color kolor gracza
	* \param movedPawn pionek do wypromowania
	* \param promotionPiece figura na jak¹ ma zostaæ wypromowany pionek
	* \return zwraca wypromowan¹ figurê
	*/
	Piece* promotePawn(int row, int column, Player* player, int color, Piece* movedPawn, int promotionPiece);

private:
	Piece* pieceSelected;	//! zaznaczona figura
	Field* fieldSelected;	//! zaznaczone pole
	std::vector<std::vector<Field*>> fields;	//! pola
	bool stateCheckmate;	//! stan gry okreœlaj¹cy czy jest mat
	Field* shortCastlingField;	//! pole na jakie ma zostaæ postawiony król przy krótkiej roszadzie
	Field* longCastlingField;	//! pole na jakie ma zostaæ postawiony król przy d³ugiej roszadzie
	Piece* castlingPiece;		//! figura - wie¿a - uczestnicz¹ca w roszadzie
	Field* middleEnPassantField;	//! pierwsze pole przy pierwszym ruchu pionka do bicia w przelocie
	Field* highlightedMiddleEnPassantField;		//! podœwietlone pierwsze pole przy pierwszym ruchu pionka do bicia w przelocie
	Field* endEnPassantField;		//! drugie pole przy pierwszym ruchu pionka do bicia w przelocie
	Field* highlightedEndEnPassantField;		//! podœwietlone drugie pole przy pierwszym ruchu pionka do bicia w przelocie
	/*!
	* \brief checkField metoda sprawdzaj¹ca czy pole jest puste
	* \param row wiersz
	* \param column kolumna
	* \return zwraca puste pole
	*/
	Field* checkField(int row, int column);
	/*!
	* \brief clearSelection metoda usuwaj¹ca zaznaczenie pola
	*/
	void clearSelection();
	/*!
	* \brief calculatePossibleMovements metoda licz¹ca wyœwietlaj¹ca mo¿liwe ruchy na planszy
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	*/
	void calculatePossibleMovements(int x, int y, Player* player);
	/*!
	* \brief calculateCheckmateMovements metoda sprawdzaj¹ca czy s¹ mo¿liwe ruchy do wykonania, sprawdza czy jest mat
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param pieceToCheck figura do sprawdzenia czy ma jeszcze mo¿liwe ruchy
	* \return zwraca czy s¹ mo¿liwe ruchy
	*/
	bool calculateCheckmateMovements(int row, int column, Player* player, Piece* pieceToCheck);
	/*!
	* \brief calculatePossibleMovements metoda licz¹ca wyœwietlaj¹ca mo¿liwe ruchy na planszy
	* \param row wiersz
	* \param column kolumna
	* \param player gracz
	* \param pieceToCheck figura do sprawdzenia czy jej ruch nie spowoduje szacha
	* \return zwraca czy przy danym ruchu nie bedzie szach
	*/
	GameState calculateCheck(int row, int column, Player* player, Piece* pieceToCheck);
	
	
};

