//
// GameBoard.xaml.h
// Declaration of the GameBoard class
//

#pragma once

#include "GameBoard.g.h"
#include "FieldViewModel.h"
#include "PlayerViewModel.h"
#include "GameViewModel.h"
#include "CapturedPiecesViewModel.h"
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
		Platform::Array<CapturedPiecesViewModel^>^ whitePlayerCapturedPieceViewModels;
		Platform::Array<CapturedPiecesViewModel^>^ blackPlayerCapturedPieceViewModels;
		std::vector<std::vector<Field*>> fieldModels;
		std::vector<std::vector<Piece*>> capturedPieceModels;

		Windows::UI::Xaml::Controls::Image^ promotionQueen;
		Windows::UI::Xaml::Controls::Image^ promotionKnight;
		Windows::UI::Xaml::Controls::Image^ promotionRook;
		Windows::UI::Xaml::Controls::Image^ promotionBishop;
		FieldViewModel^ SetFieldViewModel(int column, int row, Field* field);
		Windows::UI::Xaml::Shapes::Rectangle^ SetHighlights(int column, int row);
		Windows::UI::Xaml::Controls::Image^ SetPieceView(int column, int row);
		CapturedPiecesViewModel^ GameBoard::SetCapturePieceViewModel(int column, int row, int color, Piece* piece);
		//Windows::UI::Xaml::Controls::TextBlock^ SetPieceView2(int column, int row);
		Windows::UI::Xaml::Controls::Image^ GameBoard::SetWhitePlayerCapturedPieceView(int column, int row);
		Windows::UI::Xaml::Controls::Image^ GameBoard::SetBlackPlayerCapturedPieceView(int column, int row);
		void DrawBoard();
		void Rectangle_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Image_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		//void TextBlock_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void PromotionChosen(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
	};
}
