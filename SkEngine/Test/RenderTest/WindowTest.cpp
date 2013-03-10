#include "Pch.h"
#include "SkWindow.h"

using namespace ske;

TEST(WindowTest, CreateDestroyTest)
{
	Window window;
	EXPECT_TRUE(window.Create(L"CreateTest", 800, 600));
	EXPECT_EQ(800, window.GetWidth());
	EXPECT_EQ(600, window.GetHeight());
	EXPECT_TRUE(nullptr != window.GetHandle());

	// Create again fail
	EXPECT_EQ(false, window.Create(L"CreateAgain", 800, 600));
	
	// Destroy
	window.Destroy();
	
	// Destroy again has no effect
	window.Destroy();
}

TEST(WindowTest, CreateFailTest)
{
	Window window;
	EXPECT_FALSE(window.Create(L"", 800, 600));
	EXPECT_FALSE(window.Create(L"InvalidWidth", 0, 600));
	EXPECT_FALSE(window.Create(L"InvalidHeight", 800, 0));
}