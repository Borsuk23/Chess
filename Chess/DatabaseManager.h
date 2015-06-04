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
* \brief DatabaseManager class klasa obs³uguj¹ca bazê danych
*/
class DatabaseManager {

public:
	/*!
	* \brief getInstance metoda pobieraj¹ca instancjê klasy DatabaseManager
	* \return instancjê klasy
	*/
	static DatabaseManager* getInstance();
	/*!
	* \brief openConnection metoda tworz¹ca po³¹czenie z baz¹ danych
	* \return zwraca czy po³¹czenie zosta³o poprawnie utworzone
	*/
	int openConnection();
	/*!
	* \brief closeConnection metoda zamykaj¹ca po³¹czenie z baz¹ danych
	* \return zwraca czy po³¹czenie zosta³o poprawnie zamkniête
	*/
	int closeConnection();
	/*!
	* \brief readMovesFromDatabase metoda odczytuj¹ca z bazy kolejne ruchy
	* \return zwraca kolejne klikniêcia
	*/
	std::vector<Click*> readMovesFromDatabase();
	/*!
	* \brief readPlayersFromDatabase metoda odczytuj¹ca dane graczy z bazy
	* \return zwraca nicki  graczy
	*/
	std::vector<std::string> readPlayersFromDatabase();
	/*!
	* \brief insertMoves metoda wpisuj¹ca do bazy ruchy
	* \param click kolejne kliniêcia
	* \return zwraca poprawnoœæ wykonania wpisania
	*/
	int insertMoves(Click* click);
	/*!
	* \brief insertPlayers metoda wpisuj¹ca do bazy graczy
	* \param whitePlayerNickname nick bia³ego gracza
	* \param blackPlayerNickname nick czarnego gracza
	* \return zwraca poprawnoœæ wykonania wpisania
	*/
	int insertPlayers(std::string whitePlayerNickname, std::string blackPlayerNickname);
	/*!
	* \brief clearDatabase metoda czyszcz¹ca bazê
	* \return zwraca poprawnoœæ wykonania zapytania
	*/
	int clearDatabase();
	/*!
	* \brief callback metoda zapewniaj¹ca sposób otrzymywania wyników z zapytañ dotycz¹cych tabeli zawieraj¹cej ruchy
	* \param NotUsed dane z jednego z argumentów z funkcji sqlite3_exec()
	* \param numberOfColumns liczba kolumn w tabeli
	* \param fieldsInTheRow ciag znaków reprezentuj¹cy dane odczytane z jednego wiersza
	* \param azColName ciag znaków reprezentuj¹cy nazwy kolumn
	* \return zwraca poprawnoœæ wykonania funkcji
	*/
	static 	int callback(void *NotUsed, int numberOfColumns, char **fieldsInTheRow, char **azColName);
	/*!
	* \brief callbackPlayers metoda zapewniaj¹ca sposób otrzymywania wyników z zapytañ dotycz¹cych tabeli zawieraj¹cej graczy
	* \param NotUsed dane z jednego z argumentów z funkcji sqlite3_exec()
	* \param numberOfColumns liczba kolumn w tabeli
	* \param fieldsInTheRow ciag znaków reprezentuj¹cy dane odczytane z jednego wiersza
	* \param azColName ciag znaków reprezentuj¹cy nazwy kolumn
	* \return zwraca poprawnoœæ wykonania funkcji
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
	char *errorMessage = 0;		//! kod b³êdu
	int  remoteConnection;		//! po³¹czenie
	std::vector<Click*> moves;	//! wektor wykonanych ruchów
	std::vector<std::string> nicknames;		//! nicki graczy
	/*!
	* \brief DatabaseManager konstruktor domyœlny
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