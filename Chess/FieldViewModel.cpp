#include "pch.h"
#include "FieldViewModel.h"

using namespace Chess;
using namespace WUXD;

FieldViewModel::FieldViewModel()
{
	Highlighted = 0;
	PieceOnField = "";
}


FieldViewModel::FieldViewModel(bool highlighted)
{
	Highlighted = highlighted;
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
		NotifyPropertyChanged("PieceOnField");
	}
}


void FieldViewModel::NotifyPropertyChanged(Platform::String^ prop)
{
	PropertyChangedEventArgs^ args = ref new PropertyChangedEventArgs(prop);
	PropertyChanged(this, args);
}
