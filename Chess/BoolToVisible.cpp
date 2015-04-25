#include "pch.h"
#include "BoolToVisible.h"
namespace Chess
{
	BoolToVisible::BoolToVisible()
	{
	}


	BoolToVisible::~BoolToVisible()
	{
	}

	Object^ BoolToVisible::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
	{
		bool _value = ((Windows::Foundation::IPropertyValue^)value)->GetBoolean();
		if (_value)
		{
			return Visibility::Visible;
		}
		else
			return Visibility::Collapsed;
	}
	Object^ BoolToVisible::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
	{
		throw ref new NotImplementedException();
	}
}
