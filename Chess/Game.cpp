#include "pch.h"
#include "Game.h"


Game::Game(std::string whitePlayerNickName, std::string blackPlayerNickName)
{
	players.push_back(new Player(0,whitePlayerNickName)); 
	players.push_back(new Player(1,blackPlayerNickName)); 
	board = new Board(players[0],players[1]);
	currentPlayer = players[0];	
	turnNumber = 0;
	isFinished = false;
	stateCheckMate = false;
	moves = std::vector<Click*>();
	databaseManager = DatabaseManager::getInstance();

}
void Game::startNewGame()
{
	databaseManager->openConnection();
	databaseManager->clearDatabase();
	databaseManager->closeConnection();
}

bool Game::resumeGame()
{
	databaseManager->openConnection();
	std::vector<std::string> nicknames = databaseManager->readPlayersFromDatabase();
	std::vector<Click*> resumeMoves = databaseManager->readMovesFromDatabase();
	std::vector<Click*>::iterator it;
	for (it = resumeMoves.begin(); it < resumeMoves.end(); it++)
	{
		userAction((*it)->row, (*it)->column);
		if ((*it)->promotionPiece != 4)
		{
			promotion((*it)->promotionPiece);
		}
	}

	players[0]->setNickname(nicknames[0]);
	players[1]->setNickname(nicknames[1]);

	databaseManager->closeConnection();
	return true;

}

Game::~Game()
{
}


void Game::userAction(int row, int column)
{
	
	Board::Exit e = board->userAction(row, column, currentPlayer);

	switch (e) {
	case Board::Exit::NO_CHANGES: 
		; break;
	case Board::Exit::PIECE_SELECTED:
		moves.push_back(new Click(row, column, currentPlayer->getColor(), 4));
			; break;
	case Board::Exit::PIECE_UNSELECTED:
		moves.push_back(new Click(row, column, currentPlayer->getColor(), 4));
		; break;
	case Board::Exit::PIECE_MOVED:
		if (board->checkPromotion(row, column, currentPlayer) == true)
		{
			promotionFlag = true;
			promotionRow = row;
			promotionColumn = column;
			break;
		}

		moves.push_back(new Click(row, column, currentPlayer->getColor(), 4));
		changeTurn();
		this->gameState = board->checkGameState(currentPlayer);
		this->board->gameState = this->gameState;
		if (this->gameState == Board::GameState::CHECK)
		{
			this->stateCheckMate = board->checkCheckmateState(currentPlayer);
			if (this->stateCheckMate == true)
				this->isFinished = true;
			
		}
		else
		{
			this->stateStaleMate = board->checkCheckmateState(currentPlayer);
			if (this->stateStaleMate == true)
				this->isFinished = true;
			
		}
			
		 break;
	case Board::Exit::PIECE_CAPTURED:
		if (board->checkPromotion(row, column, currentPlayer) == true)
		{
			promotionFlag = true;
			promotionRow = row;
			promotionColumn = column;
			break;
		}
		moves.push_back(new Click(row, column, currentPlayer->getColor(), 4));
		changeTurn();
		this->gameState = board->checkGameState(currentPlayer);
		this->board->gameState = this->gameState;
		if (this->gameState == Board::GameState::CHECK)
		{
			this->stateCheckMate = board->checkCheckmateState(currentPlayer);
			if (this->stateCheckMate == true)
				this->isFinished = true;
			
		}
		else
		{
			this->stateStaleMate = board->checkCheckmateState(currentPlayer);
			if (this->stateStaleMate == true)
				this->isFinished = true;
			
		}
		 break;
	
	default:
		break;
	}
}


void Game::changeTurn()
{
	turnNumber++;
	currentPlayer = players[turnNumber % 2]; //1 - black, 0 - white
}


void Game::removeCapturedPieces()
{
	Piece* capturedPiece;
	capturedPiece = currentPlayer->getLastCapturedPiece();
	players[(turnNumber + 1) % 2]->removeCapturedPiece(capturedPiece);  //oppponent
}

Board* Game::getBoard() {
	return this->board;
}

std::vector<std::vector<Piece*>> Game::getCapturedPieces()
{
	std::vector<std::vector<Piece*>> temp = std::vector < std::vector<Piece*> > {
		this->players[0]->getCapturedPieces(),
		this->players[1]->getCapturedPieces()
	};
	/*temp[0] = this->players[0]->getCapturedPieces();
	temp[1] = this->players[1]->getCapturedPieces();*/

	return temp;
}

void Game::promotion(int promotionPiece)
{
	//tutaj promocja
	Piece* movedPiece;

	movedPiece = board->getFields()[promotionRow][promotionColumn]->checkField();
	if ((movedPiece->getStringName() == "White Pawn") && (promotionRow == 0))
	{
		movedPiece = board->promotePawn(promotionRow, promotionColumn, currentPlayer, 0, movedPiece,promotionPiece);

	}
	else if ((movedPiece->getStringName() == "Black Pawn") && (promotionRow == 7))
	{
		movedPiece = board->promotePawn(promotionRow, promotionColumn, currentPlayer, 1, movedPiece, promotionPiece);
	}
	promotionFlag = false;
	
	moves.push_back(new Click(promotionRow, promotionColumn, currentPlayer->getColor(), promotionPiece));
	
	changeTurn();
	this->gameState = board->checkGameState(currentPlayer);
	this->board->gameState = this->gameState;
	//if (this->gameState == Board::GameState::CHECK)
	//{
	this->stateCheckMate = board->checkCheckmateState(currentPlayer);
	if (this->stateCheckMate == true)
		this->isFinished = true;
	isFinished = isFinished;

	//}
}

void Game::saveToFile()
{
	databaseManager->openConnection();
	databaseManager->clearDatabase();
	std::vector<Click*>::iterator it;
	Windows::Storage::ApplicationDataContainer^ localSettings = Windows::Storage::ApplicationData::Current->LocalSettings;
	Windows::Storage::StorageFolder^ localFolder = Windows::Storage::ApplicationData::Current->LocalFolder;
	for (it = moves.begin(); it < moves.end(); it++)
	{

		databaseManager->insertMoves(*it);
	}
	
	databaseManager->insertPlayers(players[0]->getNickname(), players[1]->getNickname());

	databaseManager->closeConnection();


	//concurrency::task<Windows::Storage::StorageFile^>^ fileOperation = localFolder->CreateFileAsync("dataFile.txt", Windows::Storage::CreationCollisionOption::ReplaceExisting);
	//fileOperation.then([this](Windows::Storage::StorageFile^ sampleFile)
	//{
	//	auto calendar = ref new Calendar;
	//	auto now = calendar->ToDateTime();
	//	auto formatter = ref new Windows::Globalization::DateTimeFormatting::DateTimeFormatter("longtime");

	//	return Windows::Storage::FileIO::WriteTextAsync(sampleFile, formatter->Format(now));
	//}).then([this](task <void> previousOperation) {
	//	try {
	//		previousOperation.get();
	//	}
	//	catch (Platform::Exception^) {
	//		// Timestamp not written
	//	}
	//});
}




