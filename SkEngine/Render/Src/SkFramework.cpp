#include "Pch.h"
#include "SkFramework.h"
#include "SkConsoleWindow.h"
#include "SkLog.h"
#include "SkTextBox.h"
#include "SkUtilities.h"

namespace ske
{
	Framework::Framework()
		: m_textureMgr(nullptr), m_shaderMgr(nullptr), m_isInit(false)
	{
	}

	Framework::~Framework()
	{
		Cleanup();
	}

	bool Framework::Init(const std::wstring& appName, int width, int height, bool showWindow)
	{
		if (IsInitialized())
			return false;

		ConsoleWindow::Init();

		Log::System(L"Framework::Init");

		if (!m_window.Create(appName, width, height, showWindow))
			goto LOCAL_EXIT_FAIL;

		if (!m_renderer.Create(m_window.GetHandle()))
			goto LOCAL_EXIT_FAIL;

		m_textureMgr = new TextureManager(m_renderer.GetDevice());
		m_shaderMgr = new ShaderManager(m_renderer.GetDevice());

		m_isInit = true;
		SK_ENSURE(IsInitialized());
		return true;

LOCAL_EXIT_FAIL:
		Cleanup();
		return false;
	}

	void Framework::Advance(bool& quit)
	{
		bool needQuit = false;

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				needQuit = true;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (!needQuit)
			m_renderer.Render(m_camera);

		quit = needQuit;
	}

	void Framework::Cleanup()
	{
		Log::System(L"Framework::Cleanup");

		m_renderer.Destroy();
		SafeDelete(m_shaderMgr);
		SafeDelete(m_textureMgr);
		ConsoleWindow::Cleanup();

		m_isInit = false;
		SK_ENSURE(!IsInitialized());
	}

	bool Framework::CreateTextBox(const std::wstring& string)
	{
		const RECT rc = {0, 0, m_window.GetWidth(), m_window.GetHeight()};
		TextBox* const textBox = new TextBox(m_renderer.GetDevice(), string, rc);
		m_renderer.AddRenderable(*textBox);
		return true;
	}

	TextureManager* Framework::GetTextureManager()
	{
		return m_textureMgr;
	}

	ShaderManager* Framework::GetShaderManager()
	{
		return m_shaderMgr;
	}
}