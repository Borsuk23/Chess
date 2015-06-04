#include "pch.h"
#include "GameViewModel.h"

using namespace Chess;
using namespace WUXD;

GameViewModel::GameViewModel()
{
	CheckMate = false;
}

GameViewModel::~GameViewModel()
{
}


Platform::Boolean GameViewModel::IsCheckMate::get(){ return CheckMate; }
Platform::Boolean GameViewModel::IsStaleMate::get(){ return StaleMate; }

void GameViewModel::IsCheckMate::set(Platform::Boolean value)
{
	if (CheckMate != value)
	{
		CheckMate = value;
		NotifyPropertyChanged("IsCheckMate");
	}
}

void GameViewModel::IsStaleMate::set(Platform::Boolean value)
{
	if (StaleMate != value)
	{
		StaleMate = value;
		NotifyPropertyChanged("IsStaleMate");
	}
}


void GameViewModel::NotifyPropertyChanged(Platform::String^ prop)
{
	PropertyChangedEventArgs^ args = ref new PropertyChangedEventArgs(prop);
	PropertyChanged(this, args);
}

