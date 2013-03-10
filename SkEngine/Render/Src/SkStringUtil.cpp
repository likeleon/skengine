#include "Pch.h"
#include <vector>
#include "SkStringUtil.h"

namespace ske
{
	std::wstring StringUtil::ToWide(const std::string& ansi)
	{
		if (ansi.empty())
			return L"";

		const int unicodeLength = MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), ansi.length(), nullptr, 0);
		std::vector<wchar_t> buf(unicodeLength + 1);
		MultiByteToWideChar(CP_ACP, 0, ansi.c_str(), ansi.length(), 
			&buf[0], buf.size());
		buf[unicodeLength] = 0;
		return std::wstring(&buf[0]);
	}

	std::string StringUtil::ToAnsi(const std::wstring& uni)
	{
		if (uni.empty())
			return "";

		const int ansiLength = WideCharToMultiByte(CP_ACP, 0, uni.c_str(), uni.length(), nullptr, 0, nullptr, nullptr);
		std::vector<char> buf(ansiLength + 1);
		WideCharToMultiByte(CP_ACP, 0, uni.c_str(), uni.length(),
			&buf[0], buf.size(), nullptr, nullptr);
		buf[ansiLength] = 0;
		return std::string(&buf[0]);
	}
}