#pragma once
#include "Field.h"
#include "Piece.h"

namespace Chess {
	namespace WUXD = Windows::UI::Xaml::Data;

	[WUXD::Bindable]
	public ref  class GameViewModel sealed : WUXD::INotifyPropertyChanged
	{
	public:
		GameViewModel();
		virtual ~GameViewModel();

		property Platform::Boolean IsCheckMate {
			Platform::Boolean get();
			void set(Platform::Boolean value);
		}

		property Platform::Boolean IsStaleMate {
			Platform::Boolean get();
			void set(Platform::Boolean value);
		}

		
		virtual event WUXD::PropertyChangedEventHandler^ PropertyChanged;

	private:
		void NotifyPropertyChanged(Platform::String^ prop);
		Platform::Boolean CheckMate;
		Platform::Boolean StaleMate;
	};
}


