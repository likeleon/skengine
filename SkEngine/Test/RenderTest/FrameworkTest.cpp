#include "Pch.h"
#include "SkFramework.h"

using namespace ske;

static bool InitFramework(Framework& fw, const std::wstring& appName = L"FrameworkTest", int width = 640, int height = 480)
{
	return fw.Init(appName, width, height, false);
}

TEST(FrameworkTest, InitCleanupTest)
{
	Framework fw;
	EXPECT_FALSE(fw.IsInitialized());

	EXPECT_TRUE(InitFramework(fw));
	EXPECT_FALSE(InitFramework(fw));
	EXPECT_TRUE(fw.IsInitialized());

	fw.Cleanup();
	EXPECT_FALSE(fw.IsInitialized());
}

TEST(FrameworkTest, InitFailTest)
{
	Framework fw;
	EXPECT_FALSE(InitFramework(fw, L"", 640, 480));
	EXPECT_FALSE(InitFramework(fw, L"InvalidWidth", 0, 480));
	EXPECT_FALSE(InitFramework(fw, L"InvalidHeight", 0, 0));
}

TEST(FrameworkTest, GetManagersTest)
{
	Framework fw;
	EXPECT_EQ(nullptr, fw.GetTextureManager());
	EXPECT_EQ(nullptr, fw.GetShaderManager());
	
	InitFramework(fw);
	EXPECT_TRUE(nullptr != fw.GetTextureManager());
	EXPECT_TRUE(nullptr != fw.GetShaderManager());
}