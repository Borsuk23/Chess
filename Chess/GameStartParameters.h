#pragma once

namespace Chess
{
	namespace Navigation
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class GameStartParameters sealed
		{
		public:
			GameStartParameters();

			property Platform::String^ BlackPlayer
			{
				Platform::String^ get()
				{
					return _BlackPlayer;
				}
				void set(Platform::String^ value)
				{
					if (!_BlackPlayer->Equals(value))
					{
						_BlackPlayer = value;
					}
				}
			}

			property Platform::String^ WhitePlayer
			{
				Platform::String^ get()
				{
					return _WhitePlayer;
				}
				void set(Platform::String^ value)
				{
					if (!_WhitePlayer->Equals(value))
					{
						_WhitePlayer = value;
					}
				}
			}

		private:
			Platform::String^ _WhitePlayer;
			Platform::String^ _BlackPlayer;
		};
	}
}


