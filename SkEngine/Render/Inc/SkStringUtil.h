#pragma once

#include <string>

namespace ske
{
	class StringUtil
	{
	public:
		static std::wstring ToWide(const std::string& ansi);
		static std::string ToAnsi(const std::wstring& uni);
	};
}