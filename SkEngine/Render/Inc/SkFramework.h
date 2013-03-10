#pragma once

#include <string>
#include "SkNonCopyable.h"
#include "SkRenderer.h"
#include "SkWindow.h"
#include "SkCamera.h"
#include "SkTextureManager.h"
#include "SkShaderManager.h"

namespace ske
{
	class Framework : private NonCopyable
	{
	public:
		Framework();
		~Framework();

		bool Init(const std::wstring &appName, int width, int height, bool showWindow);
		void Advance(bool& quit);
		void Cleanup();
		bool IsInitialized() const { return m_isInit; }

		bool CreateTextBox(const std::wstring& string);

		// NOTE: Temporary interfaces
		Renderer& GetRenderer() { return m_renderer; }
		Camera& GetCamera() { return m_camera; }
		TextureManager* GetTextureManager();
		ShaderManager* GetShaderManager();

	private:
		void Render();

		Renderer	m_renderer;
		Window		m_window;
		Camera		m_camera;
		TextureManager* m_textureMgr;
		ShaderManager* m_shaderMgr;
		bool		m_isInit;
	};
}