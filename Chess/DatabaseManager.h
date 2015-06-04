#pragma once
#include "pch.h"
#include "Click.h"
#include <sqlite3.h>
#include <sstream>

typedef int(*sqlite3_callback)(
	void*,
	int,
	char**,
	char**
	);

class DatabaseManager {

public:
	static DatabaseManager* getInstance();
	int openConnection();
	int closeConnection();
	std::vector<Click*> readMovesFromDatabase();
	std::vector<std::string> readPlayersFromDatabase();
	int insertMoves(Click* click);
	int insertPlayers(std::string whitePlayerNickname, std::string blackPlayerNickname);
	int clearDatabase();
	static 	int callback(void *NotUsed, int numberOfColumns, char **fieldsInTheRow, char **azColName);
	static int callbackPlayers(void *NotUsed, int numberOfColumns, char **fieldsInTheRow, char **azColName);
	~DatabaseManager();
private:
	DatabaseManager();
	static DatabaseManager *instance;
	int lastRowID;
	sqlite3 *database;
	char *errorMessage = 0;
	int  remoteConnection;
	std::vector<Click*> moves;
	std::vector<std::string> nicknames;

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