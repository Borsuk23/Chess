#pragma once
#include "Player.h"
#include "Board.h"
#include "Click.h"
#include <iostream>
#include <fstream>
#include "DatabaseManager.h"

/*!
* \brief The Game class klasa definiujaca gre
*/
class Game
{
public:
	
	int turnNumber;		//! kolej gracza
	bool stateCheckMate;	//! stan gry mowiacy o szach macue
	bool stateStaleMate;		//! stan gry okreœlajacy pata
	Board::GameState gameState;		//! stan gry
	bool isFinished;			//! koniec gry
	std::vector<Player*> players;	//! gracze
	bool promotionFlag;			//! flaga mowiaca, ze jest wlaœnie dokonywana promocja
	/*!
	* \brief Game konstruktor sparametryzowany
	* \param whitePlayerNickName nick bialego gracza
	* \param blackPlayerNickName nick czarnego gracza
	*/
	Game(std::string whitePlayerNickName, std::string blackPlayerNickName);
	/*!
	* \brief Game destruktor
	*/
	virtual ~Game();
	/*!
	* \brief userAction metoda odpowiadajaca za wykonanie akcji po kliknieciu gracza
	* \param row wiersz
	* \param column kolumna
	*/
	void userAction(int row, int column);
	/*!
	* \brief getBoard metoda pobierajaca plansze
	* \return zwraca plansze
	*/
	Board* getBoard();
	/*!
	* \brief getCapturedPieces  metoda pobierajaca zbite figury
	* \return zwraca wektor zbitych figur
	*/
	std::vector<std::vector<Piece*>> getCapturedPieces();
	/*!
	* \brief promotion metoda dokonujaca promocji pionka
	* \param promotionPiece figura na jaka ma zostaæ wypromowany pionek
	*/
	void promotion(int promotionPiece);
	/*!
	* \brief saveToFile metoda zapisujaca gre do pliku
	*/
	void saveToFile();
	/*!
	* \brief resumeGame metoda wznawiajaca gre
	* \return zwraca powodzenie wznowienie gry
	*/
	bool resumeGame();
	
private:
	int promotionRow;	//! wiersz dotyczacy promocji
	int promotionColumn; //! kolumna dotyczaca promocji
	Player* currentPlayer; //! obecny gracz
	Board* board;		//! plansza
	std::vector<Click*> moves;	//!wektor wykonanych ruchow na planszy
	DatabaseManager* databaseManager;	//! obiekt zarzadzajacy baza danych
	/*!
	* \brief changeTurn metoda zmieniajaca kolej ruchu graczy
	*/
	void changeTurn();
	/*!
	* \brief removeCapturedPieces metoda usuwajaca zbita figure z wektora figur gracza
	*/
	void removeCapturedPieces();
	
};

