//
// GameBoard.xaml.h
// Declaration of the GameBoard class
//

#pragma once

#include "GameBoard.g.h"
#include "FieldViewModel.h"
#include "BoolToVisible.h"
#include "GameStartParameters.h"

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
		void SetFieldViewModel(int column, int row, Field* field);
		Windows::UI::Xaml::Shapes::Rectangle^ SetHighlights(int column, int row);
		Windows::UI::Xaml::Controls::Image^ SetPieceView(int column, int row);
	};
}
