﻿//
// GameBoard.xaml.cpp
// Implementation of the GameBoard class
//

#include "pch.h"
#include "GameBoard.xaml.h"


using namespace Chess;
namespace WUX = Windows::UI::Xaml;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

GameBoard::GameBoard()
{
	InitializeComponent();
}


void GameBoard::OnNavigatedTo(NavigationEventArgs^ e)
{
	startingParameters = dynamic_cast<Chess::Navigation::GameStartParameters^>(e->Parameter);

	WhitePlayerNickname->Text = startingParameters->WhitePlayer;
	BlackPlayerNickname->Text = startingParameters->BlackPlayer;

	//CONVERT PLATFORM STRING TO STRING

	std::wstring wsWhite = startingParameters->WhitePlayer->Data();
	std::wstring wsBlack = startingParameters->BlackPlayer->Data();

	std::string sWhite;
	std::string sBlack;
	sWhite.assign(wsWhite.begin(), wsWhite.end());
	sBlack.assign(wsBlack.begin(), wsBlack.end());

	this->game = new Game(sWhite,sBlack);	

	this->playerViewModels = ref new Platform::Array<PlayerViewModel^>(2);
	playerViewModels[0] = ref new PlayerViewModel();
	playerViewModels[0]->IsMyTurn = true;
	playerViewModels[1] = ref new PlayerViewModel();

	this->gameViewModels = ref new Platform::Array<GameViewModel^>(1);
	gameViewModels[0] = ref new GameViewModel();
	gameViewModels[0]->IsCheckMate = false;
	gameViewModels[0]->IsStaleMate = false;

	this->capturedPieceModels = this->game->getCapturedPieces();	
	this->whitePlayerCapturedPieceViewModels = ref new Platform::Array<CapturedPiecesViewModel^>(16);
	this->blackPlayerCapturedPieceViewModels = ref new Platform::Array<CapturedPiecesViewModel^>(16);

	//************************************************************************
	//********************** BINDINGS ****************************************
	//************************************************************************

	Binding^ whitePlayerTurnBinding = ref new Binding();	//after changes in ViewModel refresh in xaml
	whitePlayerTurnBinding->Source = playerViewModels[0];
	whitePlayerTurnBinding->Path = ref new PropertyPath("IsMyTurn"); 
	whitePlayerTurnBinding->Mode = BindingMode::OneWay;			//tryb oneway - changes in viewModel go to model
	whitePlayerTurnBinding->Converter = ref new BoolToVisible();		//visible or not
	WhitePlayerTurn->SetBinding(WhitePlayerTurn->VisibilityProperty, whitePlayerTurnBinding);


	Binding^ whitePlayerCheckBinding = ref new Binding();	
	whitePlayerCheckBinding->Source = playerViewModels[0];
	whitePlayerCheckBinding->Path = ref new PropertyPath("IsCheck"); 
	whitePlayerCheckBinding->Mode = BindingMode::OneWay;	
	whitePlayerCheckBinding->Converter = ref new BoolToVisible(); 
	WhitePlayerCheck->SetBinding(WhitePlayerCheck->VisibilityProperty, whitePlayerCheckBinding);

	Binding^ whitePlayerCapturedPiecesBinding = ref new Binding();	
	whitePlayerCapturedPiecesBinding->Source = playerViewModels[0];
	whitePlayerCapturedPiecesBinding->Path = ref new PropertyPath("CapturedPiece"); 
	whitePlayerCapturedPiecesBinding->Mode = BindingMode::OneWay;	
	WhitePlayerCapturedPieces->SetBinding(WhitePlayerCapturedPieces->VisibilityProperty, whitePlayerCapturedPiecesBinding);


	Binding^ blackPlayerTurnBinding = ref new Binding();	
	blackPlayerTurnBinding->Source = playerViewModels[1];
	blackPlayerTurnBinding->Path = ref new PropertyPath("IsMyTurn");
	blackPlayerTurnBinding->Mode = BindingMode::OneWay;	
	blackPlayerTurnBinding->Converter = ref new BoolToVisible(); 
	BlackPlayerTurn->SetBinding(BlackPlayerTurn->VisibilityProperty, blackPlayerTurnBinding);

	Binding^ blackPlayerCheckBinding = ref new Binding();	
	blackPlayerCheckBinding->Source = playerViewModels[1];
	blackPlayerCheckBinding->Path = ref new PropertyPath("IsCheck"); 
	blackPlayerCheckBinding->Mode = BindingMode::OneWay;	
	blackPlayerCheckBinding->Converter = ref new BoolToVisible(); 
	BlackPlayerCheck->SetBinding(BlackPlayerCheck->VisibilityProperty, blackPlayerCheckBinding);

	


	Binding^ checkMateBinding = ref new Binding();	
	checkMateBinding->Source = gameViewModels[0];
	checkMateBinding->Path = ref new PropertyPath("IsCheckMate"); 
	checkMateBinding->Mode = BindingMode::OneWay;	
	checkMateBinding->Converter = ref new BoolToVisible(); 
	CheckMate->SetBinding(CheckMate->VisibilityProperty, checkMateBinding);

	Binding^ staleMateBinding = ref new Binding();	
	staleMateBinding->Source = gameViewModels[0];
	staleMateBinding->Path = ref new PropertyPath("IsStaleMate"); 
	staleMateBinding->Mode = BindingMode::OneWay;	
	staleMateBinding->Converter = ref new BoolToVisible(); 
	StaleMate->SetBinding(StaleMate->VisibilityProperty, staleMateBinding);

	this->fieldModels = game->getBoard()->getFields();
	this->fieldViewModels = ref new Platform::Array<FieldViewModel^>(64);

	//DrawBoard();
	
	//setup viewModels
	for (int column = 0; column < 8; column++)
	{
		for (int row = 0; row < 8; row++)
		{
			fieldViewModels[column*8+row] = SetFieldViewModel(row, column, this->fieldModels[column][row]); //for every fieldModel is created fieldViewModel
		}
	}

	for (int column = 0; column < 4; column++)
	{
		for (int row = 0; row < 4; row++)
		{
			whitePlayerCapturedPieceViewModels[row * 4 + column] = SetCapturePieceViewModel(column, row,0, this->capturedPieceModels[0][row * 4 + column]); //white
			blackPlayerCapturedPieceViewModels[row * 4 + column] = SetCapturePieceViewModel(column, row, 1, this->capturedPieceModels[1][row * 4 + column]); //black
			
		}
	}

	//promotion fields
	promotionQueen = ref new Windows::UI::Xaml::Controls::Image();
	promotionQueen->Height = 40;
	auto queenBitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
	Platform::String^ queenPath = "ms-appx:///Assets/white_queen.png";
	queenBitmapImage->UriSource = ref new Windows::Foundation::Uri(queenPath);
	promotionQueen->Source = queenBitmapImage;
	promotionQueen->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	PromotionGrid->Children->Append(promotionQueen);
	PromotionGrid->SetRow(promotionQueen, 0);
	promotionQueen->PointerPressed += ref new PointerEventHandler(this, &GameBoard::PromotionChosen);


	promotionKnight = ref new Windows::UI::Xaml::Controls::Image();
	promotionKnight->Height = 40;
	auto knightBitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
	Platform::String^ knightPath = "ms-appx:///Assets/white_knight.png";
	knightBitmapImage->UriSource = ref new Windows::Foundation::Uri(knightPath);
	promotionKnight->Source = knightBitmapImage;
	promotionKnight->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	PromotionGrid->Children->Append(promotionKnight);
	PromotionGrid->SetRow(promotionKnight, 1);
	promotionKnight->PointerPressed += ref new PointerEventHandler(this, &GameBoard::PromotionChosen);

	promotionRook = ref new Windows::UI::Xaml::Controls::Image();
	promotionRook->Height = 40;
	auto rookBitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
	Platform::String^ rookPath = "ms-appx:///Assets/white_rook.png";
	rookBitmapImage->UriSource = ref new Windows::Foundation::Uri(rookPath);
	promotionRook->Source = rookBitmapImage;
	promotionRook->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	PromotionGrid->Children->Append(promotionRook);
	PromotionGrid->SetRow(promotionRook, 2);
	promotionRook->PointerPressed += ref new PointerEventHandler(this, &GameBoard::PromotionChosen);

	promotionBishop = ref new Windows::UI::Xaml::Controls::Image();
	promotionBishop->Height = 40;
	auto bishopBitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
	Platform::String^ bishopPath = "ms-appx:///Assets/white_bishop.png";
	bishopBitmapImage->UriSource = ref new Windows::Foundation::Uri(bishopPath);
	promotionBishop->Source = bishopBitmapImage;
	promotionBishop->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	PromotionGrid->Children->Append(promotionBishop);
	PromotionGrid->SetRow(promotionBishop, 3);
	promotionBishop->PointerPressed += ref new PointerEventHandler(this, &GameBoard::PromotionChosen); 


	if (startingParameters->Resume == true)
	{
		this->game->resumeGame();
		refreshBoard();

		//resume nicknames
		//convert std::string to platform::string
		std::string sWhite(this->game->players[0]->getNickname());
		std::string sBlack(this->game->players[1]->getNickname());
		std::wstring wsWhite, wsBlack;
		wsWhite.assign(sWhite.begin(), sWhite.end());
		Platform::String^ platformNicknameWhite = ref new String(wsWhite.c_str());

		WhitePlayerNickname->Text = platformNicknameWhite;

		wsBlack.assign(sBlack.begin(), sBlack.end());
		Platform::String^ platformNicknameBlack = ref new String(wsBlack.c_str());

		BlackPlayerNickname->Text = platformNicknameBlack;
	}
	
	//start game
;}

//*********************************************** SET VIEWMODEL ****************************************
//*********************************************** DEFINITIONS ******************************************
//tworzy ViewModel dla 1 pola
FieldViewModel^ GameBoard::SetFieldViewModel(int column, int row, Field* field) {
	auto fieldViewModel = ref new FieldViewModel();
	fieldViewModel->Highlighted = field->isHighlighted(); 
	if (field->checkField() != NULL) 
		fieldViewModel->PieceOnField = field->checkField()->getName();
	else
		fieldViewModel->PieceOnField = "";

	
	/*Windows::UI::Xaml::Controls::TextBlock^ textBlock = SetPieceView2(column, row);
	Binding^ pieceBinding2 = ref new Binding();
	pieceBinding2->Source = fieldViewModel;
	textBlock->PointerPressed += ref new PointerEventHandler(this, &GameBoard::TextBlock_PointerPressed);
	pieceBinding2->Path = ref new PropertyPath("PieceOnField"); 
	pieceBinding2->Mode = BindingMode::OneWay;
	textBlock->SetBinding(textBlock->TextProperty, pieceBinding2);*/


	Windows::UI::Xaml::Controls::Image^ image = SetPieceView(column, row);
	Binding^ pieceBinding = ref new Binding();
	pieceBinding->Source = fieldViewModel;
	pieceBinding->Path = ref new PropertyPath("PieceImage");
	pieceBinding->Mode = BindingMode::OneWay;
	image->SetBinding(image->SourceProperty, pieceBinding);


	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = SetHighlights(column, row);
	Binding^ highlightBinding = ref new Binding();	
	highlightBinding->Source = fieldViewModel;
	highlightBinding->Path = ref new PropertyPath("Highlighted"); 
	highlightBinding->Mode = BindingMode::OneWay;	
	highlightBinding->Converter = ref new BoolToVisible(); 
	rectangle->SetBinding(rectangle->VisibilityProperty, highlightBinding);

	return fieldViewModel;
}

//**************************************************** SET HIGHLIGHTS ********************************************
//**************************************************** SET PIECEVIEW *********************************************
Windows::UI::Xaml::Shapes::Rectangle^ GameBoard::SetHighlights(int column, int row) {
	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = ref new Windows::UI::Xaml::Shapes::Rectangle();
	SolidColorBrush^ brush = ref new SolidColorBrush();
	brush->Color = Windows::UI::Colors::GreenYellow;
	rectangle->Fill = brush;
	rectangle->Opacity = 0.6;
	rectangle->PointerPressed += ref new PointerEventHandler(this, &GameBoard::Rectangle_PointerPressed); //after press rectangle go to rectangle_pointerpressed method
	Board->Children->Append(rectangle); 
	Board->SetColumn(rectangle, column); 
	Board->SetRow(rectangle, row);
	return rectangle;
}

Windows::UI::Xaml::Controls::Image^ GameBoard::SetPieceView(int column, int row) {
	Windows::UI::Xaml::Controls::Image^ image = ref new Windows::UI::Xaml::Controls::Image();
	image->Height = 60;
	image->PointerPressed += ref new PointerEventHandler(this, &GameBoard::Image_PointerPressed);
	Board->Children->Append(image);
	Board->SetColumn(image, column);
	Board->SetRow(image, row);
	return image;
}


//Windows::UI::Xaml::Controls::TextBlock^ GameBoard::SetPieceView2(int column, int row) {
//	Windows::UI::Xaml::Controls::TextBlock^ image = ref new Windows::UI::Xaml::Controls::TextBlock();
//	SolidColorBrush^ brush = ref new SolidColorBrush();
//	brush->Color = Windows::UI::Colors::Red;
//	image->Foreground = brush;
//	image->TextAlignment = TextAlignment::Center;
//	Board->Children->Append(image);
//	Board->SetColumn(image, column);
//	Board->SetRow(image, row);
//	return image;
//}



CapturedPiecesViewModel^ GameBoard::SetCapturePieceViewModel(int column, int row, int color, Piece* piece) {
	auto capturedPieceViewModel = ref new CapturedPiecesViewModel();
	
	if (piece != NULL)
		capturedPieceViewModel->PieceOnField = piece->getName();
	else
		capturedPieceViewModel->PieceOnField = "";
	if (color == 0)
	{
		Windows::UI::Xaml::Controls::Image^ image = SetWhitePlayerCapturedPieceView(column, row);
		Binding^ pieceBinding = ref new Binding();
		pieceBinding->Source = capturedPieceViewModel;
		pieceBinding->Path = ref new PropertyPath("PieceImage");
		pieceBinding->Mode = BindingMode::TwoWay;
		image->SetBinding(image->SourceProperty, pieceBinding);
	}
	else
	{
		Windows::UI::Xaml::Controls::Image^ image = SetBlackPlayerCapturedPieceView(column, row);
		Binding^ pieceBinding = ref new Binding();
		pieceBinding->Source = capturedPieceViewModel;
		pieceBinding->Path = ref new PropertyPath("PieceImage");
		pieceBinding->Mode = BindingMode::TwoWay;
		image->SetBinding(image->SourceProperty, pieceBinding);
	}


	return capturedPieceViewModel;
}




Windows::UI::Xaml::Controls::Image^ GameBoard::SetWhitePlayerCapturedPieceView(int column, int row) {
	Windows::UI::Xaml::Controls::Image^ image = ref new Windows::UI::Xaml::Controls::Image();
	image->Height = 40;
	WhitePlayerCapturedPieces->Children->Append(image);
	WhitePlayerCapturedPieces->SetColumn(image, column);
	WhitePlayerCapturedPieces->SetRow(image, row);
	return image;
}

Windows::UI::Xaml::Controls::Image^ GameBoard::SetBlackPlayerCapturedPieceView(int column, int row) {
	Windows::UI::Xaml::Controls::Image^ image = ref new Windows::UI::Xaml::Controls::Image();
	image->Height = 40;
	BlackPlayerCapturedPieces->Children->Append(image);
	BlackPlayerCapturedPieces->SetColumn(image, column);
	BlackPlayerCapturedPieces->SetRow(image, row);
	return image;
}

//void GameBoard::DrawBoard() {
//	
//	for (int column = 0; column < 8; column++)
//	{
//		for (int row = 0; row < 8; row++)
//		{
//			Windows::UI::Xaml::Shapes::Rectangle^ rectangle = ref new Windows::UI::Xaml::Shapes::Rectangle();
//			SolidColorBrush^ brush = ref new SolidColorBrush();
//			if ((column + row) % 2)
//				brush->Color = Windows::UI::Colors::DimGray;
//			else
//				brush->Color = Windows::UI::Colors::Ivory;
//			rectangle->Fill = brush;
//			Board->Children->Append(rectangle);
//			Board->SetColumn(rectangle, column);
//			Board->SetRow(rectangle, row);
//		}
//	}
//}

//*******************************************************************************************
//************************************ POINTER PRESSED **************************************
//*******************************************************************************************
//puste pola
void Chess::GameBoard::Rectangle_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = (Windows::UI::Xaml::Shapes::Rectangle^) sender;
	int column = (int)rectangle->GetValue(Grid::ColumnProperty);
	int row = (int)rectangle->GetValue(Grid::RowProperty);

	if (game->promotionFlag == true)			//block normal move when promotion
	{
		return;
	}
	game->userAction(row, column);
	
	refreshBoard();
		
}

////figury
void Chess::GameBoard::Image_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	Windows::UI::Xaml::Controls::Image^ button = (Windows::UI::Xaml::Controls::Image^) sender; //obiekt ktory wywolal ten event
	int column = (int) button->GetValue(Grid::ColumnProperty);
	int row = (int) button->GetValue(Grid::RowProperty);

	if (game->promotionFlag == true)			//block normal move when promotion
	{
		return;
	}

	game->userAction(row, column);

	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			fieldViewModels[row * 8 + column]->Highlighted = fieldModels[row][column]->isHighlighted();
			if (fieldModels[row][column]->checkField() != NULL)
				fieldViewModels[row * 8 + column]->PieceOnField = fieldModels[row][column]->checkField()->getName();
			else
				fieldViewModels[row * 8 + column]->PieceOnField = "";
		}
	}
}

void Chess::GameBoard::PromotionChosen(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	Windows::UI::Xaml::Controls::Image^ button = (Windows::UI::Xaml::Controls::Image^) sender; 
	int promotionPiece = (int)button->GetValue(Grid::RowProperty);
	game->promotion(promotionPiece);
	promotionQueen->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	promotionBishop->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	promotionKnight->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	promotionRook->Visibility = Windows::UI::Xaml::Visibility::Collapsed;

	//board refresh
	refreshBoard();
}

void Chess::GameBoard::saveGameButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Button^ b = (Button^)sender;
	
	game->saveToFile();

}

////figury
//void Chess::GameBoard::TextBlock_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
//{
//	Windows::UI::Xaml::Controls::TextBlock^ button = (Windows::UI::Xaml::Controls::TextBlock^) sender; //obiekt ktory wywolal ten event
//	int column = (int)button->GetValue(Grid::ColumnProperty);
//	int row = (int)button->GetValue(Grid::RowProperty);
//
//	game->userAction(row, column);
//
//	for (int row = 0; row < 8; row++)
//	{
//		for (int column = 0; column < 8; column++)
//		{
//			fieldViewModels[row * 8 + column]->Highlighted = fieldModels[row][column]->isHighlighted();
//			if (fieldModels[row][column]->checkField() != NULL)
//				fieldViewModels[row * 8 + column]->PieceOnField = fieldModels[row][column]->checkField()->getName();
//			else
//				fieldViewModels[row * 8 + column]->PieceOnField = "";
//		}
//	}
//}



void Chess::GameBoard::refreshBoard()
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			fieldViewModels[row * 8 + column]->Highlighted = fieldModels[row][column]->isHighlighted();
			if (fieldModels[row][column]->checkField() != NULL)
				fieldViewModels[row * 8 + column]->PieceOnField = fieldModels[row][column]->checkField()->getName();
			else
				fieldViewModels[row * 8 + column]->PieceOnField = "";
		}
	}

	for (int column = 0; column < 4; column++)
	{
		for (int row = 0; row < 4; row++)
		{
			if (this->game->players[0]->capturedPieces[row * 4 + column] != NULL)
				whitePlayerCapturedPieceViewModels[row * 4 + column]->PieceOnField = this->game->players[0]->capturedPieces[row * 4 + column]->getName();
			else
				whitePlayerCapturedPieceViewModels[row * 4 + column]->PieceOnField = "";
			if (this->game->players[1]->capturedPieces[row * 4 + column] != NULL)
				blackPlayerCapturedPieceViewModels[row * 4 + column]->PieceOnField = this->game->players[1]->capturedPieces[row * 4 + column]->getName();
			else
				blackPlayerCapturedPieceViewModels[row * 4 + column]->PieceOnField = "";
		}
	}

	playerViewModels[0]->IsCheck = false;
	playerViewModels[1]->IsCheck = false;

	if (game->stateCheckMate == true)
		gameViewModels[0]->IsCheckMate = true;

	if (game->stateStaleMate == true)
		gameViewModels[0]->IsStaleMate = true;

	if (game->turnNumber % 2 == 0)
	{
		if (game->gameState == Board::GameState::CHECK)
			playerViewModels[0]->IsCheck = true;
		playerViewModels[0]->IsMyTurn = true;
		playerViewModels[1]->IsMyTurn = false;
	}
	else
	{
		if (game->gameState == Board::GameState::CHECK)
			playerViewModels[1]->IsCheck = true;
		playerViewModels[1]->IsMyTurn = true;
		playerViewModels[0]->IsMyTurn = false;
	}


	if (game->promotionFlag == true)
	{
		promotionQueen->Visibility = Windows::UI::Xaml::Visibility::Visible;
		promotionBishop->Visibility = Windows::UI::Xaml::Visibility::Visible;
		promotionKnight->Visibility = Windows::UI::Xaml::Visibility::Visible;
		promotionRook->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}