#include "Pch.h"
#include "SkConsoleWindow.h"

class GlobalEnvironment : public ::testing::Environment
{
	virtual void SetUp()
	{
		//ske::ConsoleWindow::Init();
	}

	virtual void TearDown()
	{
		//ske::ConsoleWindow::Cleanup();
	}
};

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);  
  ::testing::AddGlobalTestEnvironment(new GlobalEnvironment);
  
  return RUN_ALL_TESTS();
}