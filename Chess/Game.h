#pragma once
#include "Player.h"
#include "Board.h"
#include "Click.h"
#include <iostream>
#include <fstream>
#include "DatabaseManager.h"

/*!
* \brief The Game class klasa definiuj�ca gr�
*/
class Game
{
public:
	
	int turnNumber;		//! kolej gracza
	bool stateCheckMate;	//! stan gry mowi�cy o szach macue
	bool stateStaleMate;		//! stan gry okre�laj�cy pata
	Board::GameState gameState;		//! stan gry
	bool isFinished;			//! koniec gry
	std::vector<Player*> players;	//! gracze
	bool promotionFlag;			//! flaga m�wi�ca, �e jest w�a�nie dokonywana promocja
	/*!
	* \brief Game konstruktor sparametryzowany
	* \param whitePlayerNickName nick bia�ego gracza
	* \param blackPlayerNickName nick czarnego gracza
	*/
	Game(std::string whitePlayerNickName, std::string blackPlayerNickName);
	/*!
	* \brief Game destruktor
	*/
	virtual ~Game();
	/*!
	* \brief userAction metoda odpowiadaj�ca za wykonanie akcji po klikni�ciu gracza
	* \param row wiersz
	* \param column kolumna
	*/
	void userAction(int row, int column);
	/*!
	* \brief getBoard metoda pobieraj�ca plansz�
	* \return zwraca plansz�
	*/
	Board* getBoard();
	/*!
	* \brief getCapturedPieces  metoda pobieraj�ca zbite figury
	* \return zwraca wektor zbitych figur
	*/
	std::vector<std::vector<Piece*>> getCapturedPieces();
	/*!
	* \brief promotion metoda dokonuj�ca promocji pionka
	* \param promotionPiece figura na jak� ma zosta� wypromowany pionek
	*/
	void promotion(int promotionPiece);
	/*!
	* \brief saveToFile metoda zapisuj�ca gr� do pliku
	*/
	void saveToFile();
	/*!
	* \brief resumeGame metoda wznawiaj�ca gr�
	* \return zwraca powodzenie wznowienie gry
	*/
	bool resumeGame();
	
private:
	int promotionRow;	//! wiersz dotycz�cy promocji
	int promotionColumn; //! kolumna dotycz�ca promocji
	Player* currentPlayer; //! obecny gracz
	Board* board;		//! plansza
	std::vector<Click*> moves;	//!wektor wykonanych ruch�w na planszy
	DatabaseManager* databaseManager;	//! obiekt zarz�dzaj�cy baz� danych
	/*!
	* \brief changeTurn metoda zmieniaj�ca kolej ruchu graczy
	*/
	void changeTurn();
	/*!
	* \brief removeCapturedPieces metoda usuwaj�ca zbita figure z wektora figur gracza
	*/
	void removeCapturedPieces();
	
};

