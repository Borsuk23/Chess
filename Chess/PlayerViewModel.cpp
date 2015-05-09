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

void PlayerViewModel::NotifyPropertyChanged(Platform::String^ prop)
{
	PropertyChangedEventArgs^ args = ref new PropertyChangedEventArgs(prop);
	PropertyChanged(this, args);
}

