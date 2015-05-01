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
	//GAME - konstruktor (white, black);
	
	players = dynamic_cast<Chess::Navigation::GameStartParameters^>(e->Parameter);


	for (int column = 0; column < 8; column++)
	{
		for (int row = 0; row < 8; row++)
		{
//			SetFieldViewModel(column, row, new Field(1));
		}
	}
	//start game
;}

void GameBoard::SetFieldViewModel(int column, int row, Field* field) {
	auto fieldViewModel = ref new FieldViewModel();
	//field->attachViewModel(fieldViewModel);

	//highlight
	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = SetHighlights(column, row);
	Binding^ highlightBinding = ref new Binding();
	highlightBinding->Source = fieldViewModel;
	highlightBinding->Path = ref new PropertyPath("Highlighted");
	highlightBinding->Mode = BindingMode::OneWay;
	highlightBinding->Converter = ref new BoolToVisible();
	rectangle->SetBinding(rectangle->VisibilityProperty, highlightBinding);
	
	//pieceView
	Windows::UI::Xaml::Controls::Image^ image = SetPieceView(column, row);
	Binding^ pieceBinding = ref new Binding();
	pieceBinding->Source = fieldViewModel;
	//pieceBinding->Path = ref new PropertyPath("Highlighted"); //co tu?
	pieceBinding->Mode = BindingMode::OneWay;
	//image->SetBinding(rectangle->VisibilityProperty, pieceBinding);


}

Windows::UI::Xaml::Shapes::Rectangle^ GameBoard::SetHighlights(int column, int row) {
	Windows::UI::Xaml::Shapes::Rectangle^ rectangle = ref new Windows::UI::Xaml::Shapes::Rectangle();
	rectangle->Fill->SetValue(rectangle->FillProperty, Windows::UI::Colors::GreenYellow);
	rectangle->Opacity = 0.6;
	Board->SetColumn(rectangle, column);
	Board->SetRow(rectangle, row);
	return rectangle;
}

Windows::UI::Xaml::Controls::Image^ GameBoard::SetPieceView(int column, int row) {
	Windows::UI::Xaml::Controls::Image^ image = ref new Windows::UI::Xaml::Controls::Image();
	Board->SetColumn(image, column);
	Board->SetRow(image, row);
	return image;
}