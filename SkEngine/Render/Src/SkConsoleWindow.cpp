#include "Pch.h"
#include "SkConsoleWindow.h"

namespace ske
{

	ConsoleColor ConsoleColor::White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	ConsoleColor ConsoleColor::Black = 0;
	ConsoleColor ConsoleColor::Red = FOREGROUND_RED | FOREGROUND_INTENSITY;
	ConsoleColor ConsoleColor::Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	ConsoleColor ConsoleColor::Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	ConsoleColor ConsoleColor::Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	bool WINAPI HandlerRoutine(DWORD dwCtrlType)
	{
		bool handled = FALSE;

		switch(dwCtrlType)
		{
		case CTRL_C_EVENT:
			handled = TRUE;
			break;
		case CTRL_BREAK_EVENT:
			handled = TRUE;
			break;
		case CTRL_CLOSE_EVENT:
			handled = TRUE;
			break;
		case CTRL_LOGOFF_EVENT:
			break;
		case CTRL_SHUTDOWN_EVENT:
			break;
		}
		return handled;
	}

	HANDLE ConsoleWindow::mHandle = INVALID_HANDLE_VALUE;

	BOOL ConsoleWindow::Init()
	{
		if(!::AllocConsole())
			return FALSE;
		mHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
		if(mHandle == INVALID_HANDLE_VALUE)
		{
			::FreeConsole();
			return FALSE;
		}

		HWND hConsole = ::GetConsoleWindow();
		//	SetForegroundWindow(hConsole);

		EnableMenuItem (GetSystemMenu(hConsole, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_GRAYED );
		RemoveMenu     (GetSystemMenu(hConsole, FALSE), SC_CLOSE, MF_BYCOMMAND );

		SetConsoleCtrlHandler((PHANDLER_ROUTINE)HandlerRoutine, TRUE);

		return TRUE;
	}

	BOOL ConsoleWindow::Cleanup()
	{
		if (mHandle != INVALID_HANDLE_VALUE)
		{
			::FreeConsole();
			::CloseHandle(mHandle);
			mHandle = INVALID_HANDLE_VALUE;
		}

		return TRUE;
	}

	void ConsoleWindow::Print(ConsoleColor consoleColor, const wchar_t* formatString, ...)
	{
		SetConsoleTextAttribute(mHandle, consoleColor.color);

		wchar_t text[512];
		va_list argList;
		va_start(argList, formatString);
		vswprintf_s(text, formatString, argList);
		va_end(argList);

		DWORD charsWritten;
		WriteConsole(mHandle, text, (DWORD)wcslen(text), &charsWritten, nullptr);
	}

}