#pragma once
#include "Player.h"
#include "Board.h"
#include "Click.h"
#include <iostream>
#include <fstream>
#include "DatabaseManager.h"

/*!
* \brief The Game class klasa definiuj¹ca grê
*/
class Game
{
public:
	
	int turnNumber;		//! kolej gracza
	bool stateCheckMate;	//! stan gry mowi¹cy o szach macue
	bool stateStaleMate;		//! stan gry okreœlaj¹cy pata
	Board::GameState gameState;		//! stan gry
	bool isFinished;			//! koniec gry
	std::vector<Player*> players;	//! gracze
	bool promotionFlag;			//! flaga mówi¹ca, ¿e jest w³aœnie dokonywana promocja
	/*!
	* \brief Game konstruktor sparametryzowany
	* \param whitePlayerNickName nick bia³ego gracza
	* \param blackPlayerNickName nick czarnego gracza
	*/
	Game(std::string whitePlayerNickName, std::string blackPlayerNickName);
	/*!
	* \brief Game destruktor
	*/
	virtual ~Game();
	/*!
	* \brief userAction metoda odpowiadaj¹ca za wykonanie akcji po klikniêciu gracza
	* \param row wiersz
	* \param column kolumna
	*/
	void userAction(int row, int column);
	/*!
	* \brief getBoard metoda pobieraj¹ca planszê
	* \return zwraca planszê
	*/
	Board* getBoard();
	/*!
	* \brief getCapturedPieces  metoda pobieraj¹ca zbite figury
	* \return zwraca wektor zbitych figur
	*/
	std::vector<std::vector<Piece*>> getCapturedPieces();
	/*!
	* \brief promotion metoda dokonuj¹ca promocji pionka
	* \param promotionPiece figura na jak¹ ma zostaæ wypromowany pionek
	*/
	void promotion(int promotionPiece);
	/*!
	* \brief saveToFile metoda zapisuj¹ca grê do pliku
	*/
	void saveToFile();
	/*!
	* \brief resumeGame metoda wznawiaj¹ca grê
	* \return zwraca powodzenie wznowienie gry
	*/
	bool resumeGame();
	
private:
	int promotionRow;	//! wiersz dotycz¹cy promocji
	int promotionColumn; //! kolumna dotycz¹ca promocji
	Player* currentPlayer; //! obecny gracz
	Board* board;		//! plansza
	std::vector<Click*> moves;	//!wektor wykonanych ruchów na planszy
	DatabaseManager* databaseManager;	//! obiekt zarz¹dzaj¹cy baz¹ danych
	/*!
	* \brief changeTurn metoda zmieniaj¹ca kolej ruchu graczy
	*/
	void changeTurn();
	/*!
	* \brief removeCapturedPieces metoda usuwaj¹ca zbita figure z wektora figur gracza
	*/
	void removeCapturedPieces();
	
};

