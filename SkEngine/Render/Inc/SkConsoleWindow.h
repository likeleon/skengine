#pragma once

#include "SkNonCopyable.h"

#include <windows.h>

namespace ske
{
	class ConsoleColor
	{
	public:
		ConsoleColor(WORD color)
		{
			this->color = color;
		}

		static ConsoleColor White;
		static ConsoleColor Black;
		static ConsoleColor Red;
		static ConsoleColor Green;
		static ConsoleColor Blue;
		static ConsoleColor Yellow;

		WORD color;
	};

	class ConsoleWindow : private NonCopyable
	{
	public:
		ConsoleWindow();
		~ConsoleWindow();

		static BOOL Init();
		static BOOL Cleanup();

		static void Print(ConsoleColor consoleColor, const wchar_t* formatString, ...);

	private:
		static HANDLE mHandle;
	};

}