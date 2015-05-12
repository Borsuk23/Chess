//
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

//wywolywana gdy zostaje przeniesiona do okna boarda
void GameBoard::OnNavigatedTo(NavigationEventArgs^ e)
{
	players = dynamic_cast<Chess::Navigation::GameStartParameters^>(e->Parameter);
	//GAME - konstruktor (white, black);
	//wyciagnac z players->whiteplayer, players->blackplayer nicknamey, przerzutowac je na stringi i do konstruktora Gamea
	this->game = new Game("Sony", "Maleńka");	//tworzy nowa gre
	WhitePlayerNickname->Text = players->WhitePlayer;
	BlackPlayerNickname->Text= players->BlackPlayer;
	this->playerViewModels = ref new Platform::Array<PlayerViewModel^>(2);
	playerViewModels[0] = ref new PlayerViewModel();
	playerViewModels[0]->IsMyTurn = true;
	playerViewModels[1] = ref new PlayerViewModel();
	this->gameViewModels = ref new Platform::Array<GameViewModel^>(1);
	gameViewModels[0] = ref new GameViewModel();
	gameViewModels[0]->IsCheckMate = false;


	Binding^ whitePlayerTurnBinding = ref new Binding();	//laczenie, ze w momencie pozniej zmiany w fieldViewModel, zmieni sie xaml
	whitePlayerTurnBinding->Source = playerViewModels[0];
	whitePlayerTurnBinding->Path = ref new PropertyPath("IsMyTurn"); //property highlighted z FieldViewModel
	whitePlayerTurnBinding->Mode = BindingMode::OneWay;	//tryb oneway - zmiany z viewModelu leca do Modelu
	whitePlayerTurnBinding->Converter = ref new BoolToVisible(); //widoczne albo nie podswietlenie
	WhitePlayerTurn->SetBinding(WhitePlayerTurn->VisibilityProperty, whitePlayerTurnBinding);


	Binding^ whitePlayerCheckBinding = ref new Binding();	//laczenie, ze w momencie pozniej zmiany w fieldViewModel, zmieni sie xaml
	whitePlayerCheckBinding->Source = playerViewModels[0];
	whitePlayerCheckBinding->Path = ref new PropertyPath("IsCheck"); //property highlighted z FieldViewModel
	whitePlayerCheckBinding->Mode = BindingMode::OneWay;	//tryb oneway - zmiany z viewModelu leca do Modelu
	whitePlayerCheckBinding->Converter = ref new BoolToVisible(); //widoczne albo nie podswietlenie
	WhitePlayerCheck->SetBinding(WhitePlayerCheck->VisibilityProperty, whitePlayerCheckBinding);


	Binding^ blackPlayerTurnBinding = ref new Binding();	//laczenie, ze w momencie pozniej zmiany w fieldViewModel, zmieni sie xaml
	blackPlayerTurnBinding->Source = playerViewModels[1];
	blackPlayerTurnBinding->Path = ref new PropertyPath("IsMyTurn"); //property highlighted z FieldViewModel
	blackPlayerTurnBinding->Mode = BindingMode::OneWay;	//tryb oneway - zmiany z viewModelu leca do Modelu
	blackPlayerTurnBinding->Converter = ref new BoolToVisible(); //widoczne albo nie podswietlenie
	BlackPlayerTurn->SetBinding(BlackPlayerTurn->VisibilityProperty, blackPlayerTurnBinding);

	Binding^ blackPlayerCheckBinding = ref new Binding();	//laczenie, ze w momencie pozniej zmiany w fieldViewModel, zmieni sie xaml
	blackPlayerCheckBinding->Source = playerViewModels[1];
	blackPlayerCheckBinding->Path = ref new PropertyPath("IsCheck"); //property highlighted z FieldViewModel
	blackPlayerCheckBinding->Mode = BindingMode::OneWay;	//tryb oneway - zmiany z viewModelu leca do Modelu
	blackPlayerCheckBinding->Converter = ref new BoolToVisible(); //widoczne albo nie podswietlenie
	BlackPlayerCheck->SetBinding(BlackPlayerCheck->VisibilityProperty, blackPlayerCheckBinding);


	Binding^ checkMateBinding = ref new Binding();	//laczenie, ze w momencie pozniej zmiany w fieldViewModel, zmieni sie xaml
	checkMateBinding->Source = gameViewModels[0];
	checkMateBinding->Path = ref new PropertyPath("IsCheckMate"); //property highlighted z FieldViewModel
	checkMateBinding->Mode = BindingMode::OneWay;	//tryb oneway - zmiany z viewModelu leca do Modelu
	checkMateBinding->Converter = ref new BoolToVisible(); //widoczne albo nie podswietlenie
	CheckMate->SetBinding(CheckMate->VisibilityProperty, checkMateBinding);

	this->fieldModels = game->getBoard()->getFields();
	this->fieldViewModels = ref new Platform::Array<FieldViewModel^>(64);

	//DrawBoard();
	
	//setup viewModels
	for (int column = 0; column < 8; column++)
	{
		for (int row = 0; row < 8; row++)
		{
			fieldViewModels[column*8+row] = SetFieldViewModel(row, column, this->fieldModels[column][row]); //kazdemu polu w modelu jest tworzony odpowidajacy mu ViewModel
		}
	}
	//start game
;}

//tworzy ViewModel dla 1 pola
FieldViewModel^ GameBoard::SetFieldViewModel(int column, int row, Field* field) {
	auto fieldViewModel = ref new FieldViewModel();
	fieldViewModel->Highlighted = field->isHighlighted(); //highlighted jakie jest w modelu (czy highlited czy nie)
	if (field->checkField() != NULL) 
		fieldViewModel->PieceOnField = field->checkField()->getName();
	else
		fieldViewModel->PieceOnField = "";

	
	//Windows::UI::Xaml::Controls::TextBlock^ textBlock = SetPieceView2(column, row);
	//Binding^ pieceBinding2 = ref new Binding();
	//pieceBinding2->Source = fieldViewModel;
	//textBlock->PointerPressed += ref new PointerEventHandler(this, &GameBoard::TextBlock_PointerPressed);
	//pieceBinding2->Path = ref new PropertyPath("PieceOnField"); 
	//pieceBinding2->Mode = BindingMode::OneWay;
	//textBlock->SetBinding(textBlock->TextProperty, pieceBinding2);


	Windows::UI::Xaml::Controls::Image^ image = SetPieceView(column, row);
	Binding^ pieceBinding = ref new Binding();
	pieceBinding->Source = fieldViewModel;
	pieceBinding->Path = ref new PropertyPath("PieceImage");
	pieceBinding->Mode = BindingMode::OneWay;
	image->SetBinding(image->SourceProperty, pieceBinding);


	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = SetHighlights(column, row);
	Binding^ highlightBinding = ref new Binding();	//laczenie, ze w momencie pozniej zmiany w fieldViewModel, zmieni sie xaml
	highlightBinding->Source = fieldViewModel;
	highlightBinding->Path = ref new PropertyPath("Highlighted"); //property highlighted z FieldViewModel
	highlightBinding->Mode = BindingMode::OneWay;	//tryb oneway - zmiany z viewModelu leca do Modelu
	highlightBinding->Converter = ref new BoolToVisible(); //widoczne albo nie podswietlenie
	rectangle->SetBinding(rectangle->VisibilityProperty, highlightBinding);

	return fieldViewModel;
}

Windows::UI::Xaml::Shapes::Rectangle^ GameBoard::SetHighlights(int column, int row) {
	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = ref new Windows::UI::Xaml::Shapes::Rectangle();
	SolidColorBrush^ brush = ref new SolidColorBrush();
	brush->Color = Windows::UI::Colors::GreenYellow;
	rectangle->Fill = brush;
	rectangle->Opacity = 0.6;
	rectangle->PointerPressed += ref new PointerEventHandler(this, &GameBoard::Rectangle_PointerPressed); //jak klikniesz  wten prostokat to sie wywola tamta metoda
	Board->Children->Append(rectangle); //Board to nazwa samej planszy Grida na xamlu. dodaje rectangle jako children do grida
	Board->SetColumn(rectangle, column); //ustwia kolumne ktora byla podana
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

//puste pola
void Chess::GameBoard::Rectangle_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = (Windows::UI::Xaml::Shapes::Rectangle^) sender;
	int column = (int)rectangle->GetValue(Grid::ColumnProperty);
	int row = (int)rectangle->GetValue(Grid::RowProperty);

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
	playerViewModels[0]->IsCheck = false;
	playerViewModels[1]->IsCheck = false;

	if (game->isFinished == true)
		gameViewModels[0]->IsCheckMate = true;

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
	
		
}

//figury
void Chess::GameBoard::Image_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	Windows::UI::Xaml::Controls::Image^ button = (Windows::UI::Xaml::Controls::Image^) sender; //obiekt ktory wywolal ten event
	int column = (int) button->GetValue(Grid::ColumnProperty);
	int row = (int) button->GetValue(Grid::RowProperty);

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


