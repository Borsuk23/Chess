#pragma once
#include "pch.h"
#include "Click.h"
#include <sqlite3.h>
#include <sstream>

/*!
* \brief definicja funkcji callback do odczytu danych na potrzeby API sqlite3
*/
typedef int(*sqlite3_callback)(
	void*,
	int,
	char**,
	char**
	);

/*!
* \brief DatabaseManager class klasa obs�uguj�ca baz� danych
*/
class DatabaseManager {

public:
	/*!
	* \brief getInstance metoda pobieraj�ca instancj� klasy DatabaseManager
	* \return instancj� klasy
	*/
	static DatabaseManager* getInstance();
	/*!
	* \brief openConnection metoda tworz�ca po��czenie z baz� danych
	* \return zwraca czy po��czenie zosta�o poprawnie utworzone
	*/
	int openConnection();
	/*!
	* \brief closeConnection metoda zamykaj�ca po��czenie z baz� danych
	* \return zwraca czy po��czenie zosta�o poprawnie zamkni�te
	*/
	int closeConnection();
	/*!
	* \brief readMovesFromDatabase metoda odczytuj�ca z bazy kolejne ruchy
	* \return zwraca kolejne klikni�cia
	*/
	std::vector<Click*> readMovesFromDatabase();
	/*!
	* \brief readPlayersFromDatabase metoda odczytuj�ca dane graczy z bazy
	* \return zwraca nicki  graczy
	*/
	std::vector<std::string> readPlayersFromDatabase();
	/*!
	* \brief insertMoves metoda wpisuj�ca do bazy ruchy
	* \param click kolejne klini�cia
	* \return zwraca poprawno�� wykonania wpisania
	*/
	int insertMoves(Click* click);
	/*!
	* \brief insertPlayers metoda wpisuj�ca do bazy graczy
	* \param whitePlayerNickname nick bia�ego gracza
	* \param blackPlayerNickname nick czarnego gracza
	* \return zwraca poprawno�� wykonania wpisania
	*/
	int insertPlayers(std::string whitePlayerNickname, std::string blackPlayerNickname);
	/*!
	* \brief clearDatabase metoda czyszcz�ca baz�
	* \return zwraca poprawno�� wykonania zapytania
	*/
	int clearDatabase();
	/*!
	* \brief callback metoda zapewniaj�ca spos�b otrzymywania wynik�w z zapyta� dotycz�cych tabeli zawieraj�cej ruchy
	* \param NotUsed dane z jednego z argument�w z funkcji sqlite3_exec()
	* \param numberOfColumns liczba kolumn w tabeli
	* \param fieldsInTheRow ciag znak�w reprezentuj�cy dane odczytane z jednego wiersza
	* \param azColName ciag znak�w reprezentuj�cy nazwy kolumn
	* \return zwraca poprawno�� wykonania funkcji
	*/
	static 	int callback(void *NotUsed, int numberOfColumns, char **fieldsInTheRow, char **azColName);
	/*!
	* \brief callbackPlayers metoda zapewniaj�ca spos�b otrzymywania wynik�w z zapyta� dotycz�cych tabeli zawieraj�cej graczy
	* \param NotUsed dane z jednego z argument�w z funkcji sqlite3_exec()
	* \param numberOfColumns liczba kolumn w tabeli
	* \param fieldsInTheRow ciag znak�w reprezentuj�cy dane odczytane z jednego wiersza
	* \param azColName ciag znak�w reprezentuj�cy nazwy kolumn
	* \return zwraca poprawno�� wykonania funkcji
	*/
	static int callbackPlayers(void *NotUsed, int numberOfColumns, char **fieldsInTheRow, char **azColName);
	/*!
	* \brief DatabaseManager destruktor
	*/
	~DatabaseManager();
private:
	static DatabaseManager *instance; //! instancja klasy DatabaseManager
	int lastRowID;		//! ostatni wpisany numer ID wiersza
	sqlite3 *database;	//! baza danych
	char *errorMessage = 0;		//! kod b��du
	int  remoteConnection;		//! po��czenie
	std::vector<Click*> moves;	//! wektor wykonanych ruch�w
	std::vector<std::string> nicknames;		//! nicki graczy
	/*!
	* \brief DatabaseManager konstruktor domy�lny
	*/
	DatabaseManager();
};


//static int callback(void *NotUsed, int numberOfColumns, char **fieldsInTheRow, char **azColName){
//	int i;
//	for (i = 0; i<numberOfColumns; i++){
//		printf("%s = %s\n", azColName[i], fieldsInTheRow[i] ? fieldsInTheRow[i] : "NULL");
//	}
//	printf("\n");
//	return 0;
//}
//
////typedef int(*sqlite3_callback)(
////	void*,    /* Data provided in the 4th argument of sqlite3_exec() */
////	int,      /* The number of columns in row */
////	char**,   /* An array of strings representing fields in the row */
////	char**    /* An array of strings representing column names */
////	);
//
////skad wiadomo ile ma byc tych kolumn?
////gdzie ten wielki char jest przekazywany? nazwy kolumn?
//void createTable(int numberOfColumns, char* fieldsInTheRow[])
//{
//	sqlite3 *db;
//	char *zErrMsg = 0;
//	int  rc;
//	char *sql;
//	
//
//	/* Open database */
//	rc = sqlite3_open("test.db", &db);
//	if (rc){
//		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//		exit(0);
//	}
//	else{
//		fprintf(stdout, "Opened database successfully\n");
//	}
//
//	/* Create SQL statement */
//	sql = "CREATE TABLE COMPANY("  \
//		"ID INT PRIMARY KEY     NOT NULL," \
//		"NAME           TEXT    NOT NULL," \
//		"AGE            INT     NOT NULL," \
//		"ADDRESS        CHAR(50)," \
//		"SALARY         REAL );";
//
//	/* Execute SQL statement */
//	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	if (rc != SQLITE_OK){
//		fprintf(stderr, "SQL error: %s\n", zErrMsg);
//		sqlite3_free(zErrMsg);
//	}
//	else{
//		fprintf(stdout, "Table created successfully\n");
//	}
//
//	sqlite3_close(db);
//	
//}