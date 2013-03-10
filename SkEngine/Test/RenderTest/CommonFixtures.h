#pragma once
#include "SkRenderer.h"
#include "SkWindow.h"
#include "SkCamera.h"

class WindowCreation : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		window.Create(L"Renderer", 320, 240);
	}

	virtual void TearDown()
	{
		window.Destroy();
	}

	ske::Window window;
};

class RendererCreation : public WindowCreation
{
protected:
	virtual void SetUp()
	{
		WindowCreation::SetUp();
		renderer.Create(window.GetHandle());
	}

	virtual void TearDown()
	{
		renderer.Destroy();
		WindowCreation::TearDown();
	}

	ske::Renderer renderer;
	ske::Camera camera;
};
