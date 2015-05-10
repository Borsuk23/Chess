#include "pch.h"
#include "FieldViewModel.h"

using namespace Chess;
using namespace WUXD;

FieldViewModel::FieldViewModel()
{
	Highlighted = 0;
	PieceOnField = "";
}

FieldViewModel::~FieldViewModel()
{
}


Platform::Boolean FieldViewModel::Highlighted::get(){ return m_Highlighted; }

void FieldViewModel::Highlighted::set(Platform::Boolean value)
{
	if (m_Highlighted!= value)
	{
		m_Highlighted = value;
		NotifyPropertyChanged("Highlighted");
	}
}

Platform::String^ FieldViewModel::PieceOnField::get(){ return m_PieceOnField; }

void FieldViewModel::PieceOnField::set(Platform::String^ value)
{
	if (m_PieceOnField != value)
	{
		m_PieceOnField = value;
		auto bitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
		Platform::String^ path = "ms-appx:///Assets/" + value;
		bitmapImage->UriSource = ref new Windows::Foundation::Uri(path);
		PieceImage = bitmapImage;
		NotifyPropertyChanged("PieceOnField");
	}
}

Windows::UI::Xaml::Media::Imaging::BitmapImage^ FieldViewModel::PieceImage::get(){ return m_PieceImage; }

void FieldViewModel::PieceImage::set(Windows::UI::Xaml::Media::Imaging::BitmapImage^ value)
{
	if (m_PieceImage != value)
	{
		m_PieceImage = value;
		NotifyPropertyChanged("PieceImage");
	}
}

void FieldViewModel::NotifyPropertyChanged(Platform::String^ prop)
{
	PropertyChangedEventArgs^ args = ref new PropertyChangedEventArgs(prop);
	PropertyChanged(this, args);
}

