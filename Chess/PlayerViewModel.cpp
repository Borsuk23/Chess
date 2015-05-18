#include "pch.h"
#include "PlayerViewModel.h"

using namespace Chess;
using namespace WUXD;

PlayerViewModel::PlayerViewModel()
{
	MyTurn = false;
	Check = false;
}

PlayerViewModel::~PlayerViewModel()
{
}


Platform::Boolean PlayerViewModel::IsMyTurn::get(){ return MyTurn; }

void PlayerViewModel::IsMyTurn::set(Platform::Boolean value)
{
	if (MyTurn != value)
	{
		MyTurn = value;
		NotifyPropertyChanged("IsMyTurn");
	}
}

Platform::Boolean PlayerViewModel::IsCheck::get(){ return Check; }

void PlayerViewModel::IsCheck::set(Platform::Boolean value)
{
	if (Check != value)
	{
		Check = value;
		NotifyPropertyChanged("IsCheck");
	}
}

Platform::String^ PlayerViewModel::CapturedPiece::get(){ return m_CapturedPiece; }

void PlayerViewModel::CapturedPiece::set(Platform::String^ value)
{
	if (m_CapturedPiece != value)
	{
		m_CapturedPiece = value;
		auto bitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
		Platform::String^ path = "ms-appx:///Assets/" + value;
		bitmapImage->UriSource = ref new Windows::Foundation::Uri(path);
		m_CapturedPieceImage = bitmapImage;
		NotifyPropertyChanged("CapturedPiece");
	}
}


Windows::UI::Xaml::Media::Imaging::BitmapImage^ PlayerViewModel::CapturedPieceImage::get(){ return m_CapturedPieceImage; }

void PlayerViewModel::CapturedPieceImage::set(Windows::UI::Xaml::Media::Imaging::BitmapImage^ value)
{
	if (m_CapturedPieceImage != value)
	{
		m_CapturedPieceImage = value;
		NotifyPropertyChanged("CapturedPieceImage");
	}
}

void PlayerViewModel::NotifyPropertyChanged(Platform::String^ prop)
{
	PropertyChangedEventArgs^ args = ref new PropertyChangedEventArgs(prop);
	PropertyChanged(this, args);
}

