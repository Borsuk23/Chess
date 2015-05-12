//
// GameBoard.xaml.h
// Declaration of the GameBoard class
//

#pragma once

#include "GameBoard.g.h"
#include "FieldViewModel.h"
#include "PlayerViewModel.h"
#include "GameViewModel.h"
#include "BoolToVisible.h"
#include "GameStartParameters.h"
#include "Game.h"
#include "Board.h"
#include "Field.h"

namespace Chess
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class GameBoard sealed
	{
	public:
		GameBoard();
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		Chess::Navigation::GameStartParameters^ players;
		Game* game;
		Platform::Array<FieldViewModel^>^ fieldViewModels;
		Platform::Array<PlayerViewModel^>^ playerViewModels;
		Platform::Array<GameViewModel^>^ gameViewModels;
		std::vector<std::vector<Field*>> fieldModels;
		FieldViewModel^ SetFieldViewModel(int column, int row, Field* field);
		Windows::UI::Xaml::Shapes::Rectangle^ SetHighlights(int column, int row);
		Windows::UI::Xaml::Controls::Image^ SetPieceView(int column, int row);
		Windows::UI::Xaml::Controls::TextBlock^ SetPieceView2(int column, int row);
		void DrawBoard();
		void Rectangle_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Image_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
