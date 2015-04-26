#pragma once

namespace Chess {
	namespace WUXD = Windows::UI::Xaml::Data;
	[WUXD::Bindable]
	public ref  class FieldViewModel sealed : WUXD::INotifyPropertyChanged
	{
	public:
		FieldViewModel();
		FieldViewModel(bool highlighted);
		virtual ~FieldViewModel();

		property Platform::Boolean Highlighted {
			Platform::Boolean get();
			void set(Platform::Boolean value);
		}
		virtual event WUXD::PropertyChangedEventHandler^ PropertyChanged;

	private:
		void NotifyPropertyChanged(Platform::String^ prop);
		Platform::Boolean m_Highlighted;
	};
}


