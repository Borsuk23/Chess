#include "pch.h"
#include "GameStartParameters.h"

using namespace Chess::Navigation;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization::NumberFormatting;
using namespace Windows::UI::Xaml::Media;

GameStartParameters::GameStartParameters()
{
	this->BlackPlayer = "BlackPlayer";
	this->WhitePlayer = "WhitePlayer";
	this->Resume = false;
}