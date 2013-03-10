#include "Pch.h"
#include "SkLog.h"
#include "SkConsoleWindow.h"

namespace ske
{
	void Log::Info(const wchar_t* formatString, ...)
	{
		wchar_t text[512];
		va_list argList;
		va_start(argList, formatString);
		vswprintf_s(text, formatString, argList);
		va_end(argList);
		wcscat_s(text, L"\r\n");

		ConsoleWindow::Print(ConsoleColor::White, text);
	}

	void Log::Warning(const wchar_t* formatString, ...)
	{
		wchar_t text[512];
		va_list argList;
		va_start(argList, formatString);
		vswprintf_s(text, formatString, argList);
		va_end(argList);
		wcscat_s(text, L"\r\n");

		ConsoleWindow::Print(ConsoleColor::Green, text);
	}

	void Log::Error(const wchar_t* formatString, ...)
	{
		wchar_t text[512];
		va_list argList;
		va_start(argList, formatString);
		vswprintf_s(text, formatString, argList);
		va_end(argList);
		wcscat_s(text, L"\r\n");

		ConsoleWindow::Print(ConsoleColor::Red, text);
	}

	void Log::System(const wchar_t* formatString, ...)
	{
		wchar_t text[512];
		va_list argList;
		va_start(argList, formatString);
		vswprintf_s(text, formatString, argList);
		va_end(argList);
		wcscat_s(text, L"\r\n");

		ConsoleWindow::Print(ConsoleColor::Yellow, text);
	}

}