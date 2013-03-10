#include "Pch.h"
#include "SkTextBox.h"
#include "SkLog.h"
#include "SkUtilities.h"
#include "SkD3D9Device.h"

namespace ske
{
	TextBox::TextBox(D3D9Device& device, const std::wstring& content, const RECT& drawRect)
	: m_content(content), m_font(nullptr), m_drawRect(drawRect)
	{
		SK_REQUIRE(!content.empty());

		if (!device.CreateFont(20, L"Consolas", &m_font))
			return;

		SK_ENSURE(m_font);
	}

	TextBox::~TextBox()
	{
		SafeRelease(m_font);
		SK_ENSURE(m_font == nullptr);
	}

	bool TextBox::Render()
	{
		SK_REQUIRE(m_font);

		const int ret =	m_font->DrawText(nullptr, 
										  m_content.c_str(), 
										  -1, 
										  &m_drawRect, 
										  DT_NOCLIP | DT_CENTER | DT_VCENTER | DT_SINGLELINE, 
										  D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		if (ret == 0)
		{
			Log::Error(L"%s DrawText failed, %d", __FUNCTIONW__, ret);
			return false;
		}
		return true;
	}
}