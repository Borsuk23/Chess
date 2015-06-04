#include "pch.h"
#include "DatabaseManager.h"


DatabaseManager* DatabaseManager::instance = NULL;
DatabaseManager* DatabaseManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new DatabaseManager();
	}
	return instance;
}


DatabaseManager::DatabaseManager()
{
	moves = std::vector<Click*>();
	lastRowID = 1;
}

int DatabaseManager::openConnection()
{
	/* Open database */


	auto localAppDataParh = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	std::wstring path(localAppDataParh->Data());
	path += L"\\moves.db";
	std::string s((const char*)&path[0], sizeof(wchar_t) / sizeof(char)*path.size());
	this->remoteConnection = sqlite3_open16(path.c_str(), &database);
		//this->remoteConnection = sqlite3_open_v2(s.c_str(), &database, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
		if (this->remoteConnection)	//error
		{
			return -1;
		}

		/* Create SQL statement */
		char* sql = "CREATE TABLE IF NOT EXISTS MOVES("  \
			"ID INT PRIMARY KEY    NOT NULL," \
			"ROW           INT    NOT NULL," \
			"COLUMN        INT     NOT NULL," \
			"PLAYER        INT		NOT NULL," \
			"PROMOTIONPIECE   INT      );";

		/* Execute SQL statement */
		sqlite3_callback callbackFunction = &callback;
		remoteConnection = sqlite3_exec(database, sql, callbackFunction, 0, &errorMessage);
		if (remoteConnection != SQLITE_OK) //error
		{
			sqlite3_free(errorMessage);
			return -1;
		}

		char* sql2 = "CREATE TABLE IF NOT EXISTS PLAYERS("  \
			"ID INT PRIMARY KEY    NOT NULL," \
			"WHITEPLAYER           STRING  ," \
			"BLACKPLAYER        STRING     );";

		sqlite3_callback callbackPlayersFunction = &callbackPlayers;
		remoteConnection = sqlite3_exec(database, sql2, callbackPlayersFunction, 0, &errorMessage);
		if (remoteConnection != SQLITE_OK) //error
		{
			sqlite3_free(errorMessage);
			return -1;
		}

		return 0;	//status OK
}

int DatabaseManager::closeConnection()
{
	return sqlite3_close(database);
}

std::vector<Click*> DatabaseManager::readMovesFromDatabase()
{
	this->moves.clear();
	const char* data = "";
	/* Create SQL statement */
	char* sql = "SELECT * FROM MOVES ORDER BY ID ASC";

	sqlite3_callback callbackFunction = &callback;
	/* Execute SQL statement */
	remoteConnection = sqlite3_exec(database, sql, callbackFunction, (void*)data, &errorMessage);
	if (remoteConnection != SQLITE_OK) //error
	{
		sqlite3_free(errorMessage);
	}
	return this->moves;	//status OK
}

std::vector<std::string> DatabaseManager::readPlayersFromDatabase()
{
	this->nicknames.clear();
	const char* data = "";
	/* Create SQL statement */
	char* sql = "SELECT * FROM PLAYERS ";

	sqlite3_callback callbackPlayersFunction = &callbackPlayers;
	/* Execute SQL statement */
	remoteConnection = sqlite3_exec(database, sql, callbackPlayersFunction, (void*)data, &errorMessage);
	if (remoteConnection != SQLITE_OK) //error
	{
		sqlite3_free(errorMessage);
	}
	return this->nicknames;	//status OK
}

int DatabaseManager::insertPlayers(std::string whitePlayerNickname, std::string blackPlayerNickname)
{
	std::stringstream query;
	query << "INSERT INTO PLAYERS (ID, WHITEPLAYER, BLACKPLAYER) VALUES (";
	query << 1;
	query << " , '";
	query << whitePlayerNickname;
	query << "' , '";
	query << blackPlayerNickname;
	query << "') ; ";
	
	std::string queryString = query.str();
	//char *sql = new char[queryString.length() + 1];
	//strcpy(sql, queryString.c_str());

	/* Execute SQL statement */
	sqlite3_callback callbackPlayersFunction = &callbackPlayers;
	remoteConnection = sqlite3_exec(database, queryString.c_str(), callbackPlayersFunction, 0, &errorMessage);
	if (remoteConnection != SQLITE_OK){
		sqlite3_free(errorMessage);
		return -1;
	}
	lastRowID++;
	return 0;

}

int DatabaseManager::insertMoves(Click* click)
{
	std::stringstream query;
	query << "INSERT INTO MOVES (ID, ROW, COLUMN, PLAYER, PROMOTIONPIECE) VALUES (";
	query << lastRowID;
	query << " , ";
	query << click->row;
	query << " , ";
	query << click->column;
	query << " , ";
	query << click->player;
	query << " , ";
	query << click->promotionPiece;
	query << " ); ";

	std::string queryString = query.str();
	//char *sql = new char[queryString.length() + 1];
	//strcpy(sql, queryString.c_str());

	/* Execute SQL statement */
	sqlite3_callback callbackFunction = &callback;
	remoteConnection = sqlite3_exec(database, queryString.c_str(), callbackFunction, 0, &errorMessage);
	if (remoteConnection != SQLITE_OK){
		sqlite3_free(errorMessage);
		return -1;
	}
	lastRowID++;
	return 0;

}

int DatabaseManager::clearDatabase()
{
	/* delete SQL statement */
	char* sql = "DELETE FROM MOVES; DELETE FROM PLAYERS";

	/* Execute SQL statement */
	sqlite3_callback callbackFunction = &callback;
	remoteConnection = sqlite3_exec(database, sql, callbackFunction, 0, &errorMessage);
	if (remoteConnection != SQLITE_OK) //error
	{
		sqlite3_free(errorMessage);
		return -1;
	}

	sqlite3_callback callbackPlayersFunction = &callbackPlayers;
	remoteConnection = sqlite3_exec(database, sql, callbackPlayersFunction, 0, &errorMessage);
	if (remoteConnection != SQLITE_OK) //error
	{
		sqlite3_free(errorMessage);
		return -1;
	}
	lastRowID = 1;
	return 0;	//status OK
}

int DatabaseManager::callback(void *NotUsed, int numberOfColumns, char **fieldsInTheRow, char **azColName)
{
	if (numberOfColumns == 5)
	{
		int row;
		int column;
		int player;
		int promotionPiece;
		//char to int
		row = std::atoi(fieldsInTheRow[1]);
		column = std::atoi(fieldsInTheRow[2]);
		player = std::atoi(fieldsInTheRow[3]);
		promotionPiece = std::atoi(fieldsInTheRow[4]);
		Click* move = new Click(row, column, player, promotionPiece);
		instance->moves.push_back(move);
		return 0;
	}
	else
		return -1;
	
}

int DatabaseManager::callbackPlayers(void *NotUsed, int numberOfColumns, char **fieldsInTheRow, char **azColName)
{
	if (numberOfColumns == 3)
	{
		std::string whitePlayerNickname;
		std::string blackPlayerNickname;
		
		whitePlayerNickname = fieldsInTheRow[1];
		blackPlayerNickname = fieldsInTheRow[2];
		
		instance->nicknames.push_back(whitePlayerNickname);
		instance->nicknames.push_back(blackPlayerNickname);
		return 0;
	}
	else
		return -1;

}