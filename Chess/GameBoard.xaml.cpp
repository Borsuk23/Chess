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


void GameBoard::OnNavigatedTo(NavigationEventArgs^ e)
{
	players = dynamic_cast<Chess::Navigation::GameStartParameters^>(e->Parameter);
	//GAME - konstruktor (white, black);
	this->game = new Game("Sony", "Maleńka");

	this->fieldModels = game->getBoard()->getFields();
	this->fieldViewModels = ref new Platform::Array<FieldViewModel^>(64);

	//DrawBoard();
	
	//setup viewModels
	for (int column = 0; column < 8; column++)
	{
		for (int row = 0; row < 8; row++)
		{
			fieldViewModels[column*8+row] = SetFieldViewModel(row, column, this->fieldModels[column][row]);
		}
	}
	//start game
;}

FieldViewModel^ GameBoard::SetFieldViewModel(int column, int row, Field* field) {
	auto fieldViewModel = ref new FieldViewModel();
	fieldViewModel->Highlighted = field->isHighlighted();
	if (field->checkField() != NULL)
		fieldViewModel->PieceOnField = field->checkField()->getName();
	else
		fieldViewModel->PieceOnField = "";


	
	Windows::UI::Xaml::Controls::TextBlock^ image = SetPieceView2(column, row);
	Binding^ pieceBinding = ref new Binding();
	pieceBinding->Source = fieldViewModel;
	image->PointerPressed += ref new PointerEventHandler(this, &GameBoard::TextBlock_PointerPressed);
	pieceBinding->Path = ref new PropertyPath("PieceOnField"); //co tu?
	pieceBinding->Mode = BindingMode::OneWay;
	image->SetBinding(image->TextProperty, pieceBinding);


	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = SetHighlights(column, row);
	Binding^ highlightBinding = ref new Binding();
	highlightBinding->Source = fieldViewModel;
	highlightBinding->Path = ref new PropertyPath("Highlighted");
	highlightBinding->Mode = BindingMode::OneWay;
	highlightBinding->Converter = ref new BoolToVisible();
	rectangle->SetBinding(rectangle->VisibilityProperty, highlightBinding);

	return fieldViewModel;
}

Windows::UI::Xaml::Shapes::Rectangle^ GameBoard::SetHighlights(int column, int row) {
	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = ref new Windows::UI::Xaml::Shapes::Rectangle();
	SolidColorBrush^ brush = ref new SolidColorBrush();
	brush->Color = Windows::UI::Colors::GreenYellow;
	rectangle->Fill = brush;
	rectangle->Opacity = 0.6;
	rectangle->PointerPressed += ref new PointerEventHandler(this, &GameBoard::Rectangle_PointerPressed);
	Board->Children->Append(rectangle);
	Board->SetColumn(rectangle, column);
	Board->SetRow(rectangle, row);
	return rectangle;
}

Windows::UI::Xaml::Controls::Image^ GameBoard::SetPieceView(int column, int row) {
	Windows::UI::Xaml::Controls::Image^ image = ref new Windows::UI::Xaml::Controls::Image();
	Board->Children->Append(image);
	Board->SetColumn(image, column);
	Board->SetRow(image, row);
	return image;
}


Windows::UI::Xaml::Controls::TextBlock^ GameBoard::SetPieceView2(int column, int row) {
	Windows::UI::Xaml::Controls::TextBlock^ image = ref new Windows::UI::Xaml::Controls::TextBlock();
	SolidColorBrush^ brush = ref new SolidColorBrush();
	brush->Color = Windows::UI::Colors::Red;
	image->Foreground = brush;
	image->TextAlignment = TextAlignment::Center;
	Board->Children->Append(image);
	Board->SetColumn(image, column);
	Board->SetRow(image, row);
	return image;
}



void GameBoard::DrawBoard() {
	
	for (int column = 0; column < 8; column++)
	{
		for (int row = 0; row < 8; row++)
		{
			Windows::UI::Xaml::Shapes::Rectangle^ rectangle = ref new Windows::UI::Xaml::Shapes::Rectangle();
			SolidColorBrush^ brush = ref new SolidColorBrush();
			if ((column + row) % 2)
				brush->Color = Windows::UI::Colors::DimGray;
			else
				brush->Color = Windows::UI::Colors::Ivory;
			rectangle->Fill = brush;
			Board->Children->Append(rectangle);
			Board->SetColumn(rectangle, column);
			Board->SetRow(rectangle, row);
		}
	}
}

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
}

void Chess::GameBoard::TextBlock_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	Windows::UI::Xaml::Controls::TextBlock^ button = (Windows::UI::Xaml::Controls::TextBlock^) sender;
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


void Chess::GameBoard::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Windows::UI::Xaml::Controls::Button^ button = (Windows::UI::Xaml::Controls::Button^) sender;
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
