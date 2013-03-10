#include "Pch.h"
#include "SkStringUtil.h"

using namespace ske;

TEST(StringUtilTest, ToWideTest)
{
	EXPECT_EQ(L"Test String", StringUtil::ToWide("Test String"));
	EXPECT_EQ("Test String", StringUtil::ToAnsi(L"Test String"));

	EXPECT_EQ(L"", StringUtil::ToWide(""));
	EXPECT_EQ("", StringUtil::ToAnsi(L""));
}