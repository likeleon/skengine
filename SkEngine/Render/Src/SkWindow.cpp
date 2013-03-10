#include "Pch.h"
#include "SkWindow.h"
#include "SkLog.h"

namespace ske
{
	Window::Window()
	: m_width(0), m_height(0), m_hWnd(nullptr), m_appName(L"")
	{
		for(int i = 0; i < 256; ++i)
		{
			m_keyState[i] = FALSE;
		}
	}

	Window::~Window()
	{
		Destroy();
	}

	LRESULT WINAPI Window::MsgProc(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_KEYDOWN:
			m_keyState[wParam] = TRUE;
			return 0;

		case WM_KEYUP:
			m_keyState[wParam] = FALSE;
			return 0;

		case WM_DESTROY:
			{
				Destroy();

				PostQuitMessage(0);
			}
			return 0;
		}

		return DefWindowProc(m_hWnd, msg, wParam, lParam);
	}

	static LRESULT WINAPI StaticMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* window = reinterpret_cast<Window*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if(window != nullptr)
		{
			return window->MsgProc(msg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}

	bool Window::Create(const std::wstring& appName, int width, int height, bool showOnCreate)
	{
		if (appName.empty() || width <= 0 || height <= 0)
			return false;
		if (IsCreated())
			return false;

		const WNDCLASSEXW wc = 
		{
			sizeof(WNDCLASSEX), CS_CLASSDC, StaticMsgProc, 0L, 0L,
			GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr,
			appName.c_str(), nullptr
		};
		RegisterClassExW(&wc);

		m_hWnd = CreateWindow(appName.c_str(), appName.c_str(),
							   WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 
							   nullptr, nullptr, wc.hInstance, nullptr);

		if (m_hWnd == nullptr)
		{
			Log::Error(L"CreateWindow failed: %d", GetLastError());
			UnregisterClassW(appName.c_str(), GetModuleHandle(nullptr));
			return false;
		}

		m_appName = appName;
		m_width = width;
		m_height = height;

		// Associate the this pointer as the user-data of the window handle
		::SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG>(this));

		if (showOnCreate)
			ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);

		SK_ENSURE(IsCreated());
		return true;
	}

	void Window::Destroy()
	{
		if (m_hWnd)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = nullptr;

			UnregisterClassW(m_appName.c_str(), GetModuleHandle(nullptr));
			
			m_appName = L"";
			m_width = 0;
			m_height = 0;
		}

		SK_ENSURE(!IsCreated());
	}
}