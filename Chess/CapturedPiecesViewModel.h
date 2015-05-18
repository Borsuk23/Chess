#pragma once
#include "Field.h"
#include "Piece.h"

namespace Chess {
	namespace WUXD = Windows::UI::Xaml::Data;

	[WUXD::Bindable]
	public ref  class CapturedPiecesViewModel sealed : WUXD::INotifyPropertyChanged
	{
	public:
		CapturedPiecesViewModel();
		virtual ~CapturedPiecesViewModel();

		property Platform::String^ PieceOnField {
			Platform::String^ get();
			void set(Platform::String^ value);
		}

		property Windows::UI::Xaml::Media::Imaging::BitmapImage^ PieceImage {
			Windows::UI::Xaml::Media::Imaging::BitmapImage^ get();
			void set(Windows::UI::Xaml::Media::Imaging::BitmapImage^ value);
		}


		virtual event WUXD::PropertyChangedEventHandler^ PropertyChanged;

	private:
		void NotifyPropertyChanged(Platform::String^ prop);
		Platform::String^ m_PieceOnField;
		Windows::UI::Xaml::Media::Imaging::BitmapImage^ m_PieceImage;

	};
}


