#pragma once
namespace Chess
{
	using namespace Platform;
	using namespace Windows::UI::Xaml::Interop;
	using namespace Windows::UI::Xaml;
	using namespace Windows::UI::Xaml::Data;
	public ref class BoolToVisible sealed : IValueConverter
	{
	public:
		BoolToVisible();
		virtual ~BoolToVisible();
		virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
	};

}