#pragma once
#include "Field.h"
#include "Piece.h"

namespace Chess {
	namespace WUXD = Windows::UI::Xaml::Data;

	[WUXD::Bindable]
	public ref  class PlayerViewModel sealed : WUXD::INotifyPropertyChanged
	{
	public:
		PlayerViewModel();
		virtual ~PlayerViewModel();

		property Platform::Boolean IsMyTurn {
			Platform::Boolean get();
			void set(Platform::Boolean value);
		}

		property Platform::Boolean IsCheck {
			Platform::Boolean get();
			void set(Platform::Boolean value);
		}


		virtual event WUXD::PropertyChangedEventHandler^ PropertyChanged;

	private:
		void NotifyPropertyChanged(Platform::String^ prop);
		Platform::Boolean MyTurn;
		Platform::Boolean Check;

	};
}


