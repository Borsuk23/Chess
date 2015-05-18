#include "pch.h"
#include "CapturedPiecesViewModel.h"

using namespace Chess;
using namespace WUXD;

CapturedPiecesViewModel::CapturedPiecesViewModel()
{
	PieceOnField = "";
}

CapturedPiecesViewModel::~CapturedPiecesViewModel()
{
}



Platform::String^ CapturedPiecesViewModel::PieceOnField::get(){ return m_PieceOnField; }

void CapturedPiecesViewModel::PieceOnField::set(Platform::String^ value)
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

Windows::UI::Xaml::Media::Imaging::BitmapImage^ CapturedPiecesViewModel::PieceImage::get(){ return m_PieceImage; }

void CapturedPiecesViewModel::PieceImage::set(Windows::UI::Xaml::Media::Imaging::BitmapImage^ value)
{
	if (m_PieceImage != value)
	{
		m_PieceImage = value;
		NotifyPropertyChanged("PieceImage");
	}
}

void CapturedPiecesViewModel::NotifyPropertyChanged(Platform::String^ prop)
{
	PropertyChangedEventArgs^ args = ref new PropertyChangedEventArgs(prop);
	PropertyChanged(this, args);
}

