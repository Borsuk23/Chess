﻿

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "GameBoard.xaml.h"




void ::Chess::GameBoard::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///GameBoard.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///GameBoard.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

}

void ::Chess::GameBoard::Connect(int connectionId, Platform::Object^ target)
{
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

