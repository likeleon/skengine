#pragma once

#include "SkNonCopyable.h"

namespace ske
{
	class Log : private NonCopyable
	{
	public:
		static void Info(const wchar_t* formatString, ...);
		static void Warning(const wchar_t* formatString, ...);
		static void Error(const wchar_t* formatString, ...);
		static void System(const wchar_t* formatString, ...);
	};
}