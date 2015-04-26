//
// GameBoard.xaml.cpp
// Implementation of the GameBoard class
//

#include "pch.h"
#include "GameBoard.xaml.h"

using namespace Chess;

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
	auto Field = ref new FieldViewModel(1);
	Binding^ binding = ref new Binding();
	binding->Source = Field;
	binding->Path = ref new PropertyPath("Highlighted");
	binding->Mode = BindingMode::OneWay;
	binding->Converter = ref new BoolToVisible();
	A7->SetBinding(A7->VisibilityProperty, binding);
;}