#pragma once

#include "SkNonCopyable.h"

namespace ske
{
	class Window : private NonCopyable
	{
	public:
		Window();
		~Window();

		bool Create(const std::wstring& appName, int width, int height, bool showOnCreate = false);
		void Destroy();

		LRESULT WINAPI MsgProc(UINT msg, WPARAM wParam, LPARAM lParam);

		int		GetWidth() const  { return m_width; }
		int		GetHeight() const { return m_height; }
		HWND	GetHandle() const { return m_hWnd; }

	private:
		bool	IsCreated() const { return m_hWnd != nullptr; }

		int				m_width;
		int				m_height;
		HWND			m_hWnd;
		std::wstring	m_appName;

		bool			m_keyState[256];
	};
}