#include <Windows.h>
#include "SkFramework.h"

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
	(void)hInst;

	ske::Framework framework;
	
	if (!framework.Init(L"Text Drawing", 640, 480, true))
		return 0;

	framework.CreateTextBox(L"This is a trivial call to ID3DXFont::DrawText");

	bool quit = false;
	do
	{
		framework.Advance(quit);
	} while (!quit);
	framework.Cleanup();
	
	return 0;
}